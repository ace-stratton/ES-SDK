/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
/**
 * @addtogroup libsgp4
 * @{
 *
 * @file sgp4_propagator.c
 * @brief SGP4 library main implementation
 *
 * @}
 */

#include "sgp4_propagator.h"
#include <math.h>
#include <string.h>
#if (SGP4_TEST_ON_PC == 0)
  #define PRINTF(...)
#else
  #include <stdio.h>
  //#define PRINTF(...) printf(__VA_ARGS__)
  #define PRINTF(...)
#endif


#define PI            ((sgp4_t)3.14159265359)               // I ate some ... and it was delicious
#define TWO_PI        ((sgp4_t)(2.0 * PI))
#define Re            ((sgp4_t)6378.137)                    // Earth Radius in [km]
#define CK2           ((sgp4_t)5.413179e-4)                 // (1/2)*J2*aE^2 in Re^2 units (aE = 1) -> also known as k2
#define CK4           ((sgp4_t)0.607249e-6)                 // -(3/8)*J4*aE^4 in Re^4 units (aE = 1) -> also known as k4
#define StD           ((sgp4_t)86400.0)                     // Seconds in a civil day
#define MpD           ((sgp4_t)1440.0)                      // Minutes in a civil day
#define A30           ((sgp4_t)0.253243e-5)                 // A3,0 = -J3*aE^3 in Re^3 units (aE = 1)
#define aE            ((sgp4_t)1.0)                         // Earth Radius ( assumed 1 in units of earth radii but can be modified based on official precision measurements )
#define XKE           ((sgp4_t)0.0743668477)                // sqrt(GM) in units [ er/min ]^{3/2} to be used with dimensionless a obtained as sqrt(MG)*60/Re^(3/2)
#define Flat          ((sgp4_t)0.00335281066)               // Earth flatness parameter (f) used for conversion from ECF to Latitude and Longitude

#if defined(SGP4_USE_TYPE_FLOAT) && (SGP4_USE_TYPE_FLOAT == 1)
  #define Ktol        (1e-6)                                // Accuracy tolerance for solving Kepler's eq
#else
  #define Ktol        (1e-8)                                // Accuracy tolerance for solving Kepler's eq
#endif

#define Ntol          (50)                                  // tolerance of max iterations for solving Kepler's eq


static inline sgp4_t to_rad(sgp4_t x) { return ((sgp4_t)(PI * x / 180.0)); }
static inline sgp4_t pow2(sgp4_t x)   { return x * x; }
static inline sgp4_t pow3(sgp4_t x)   { return pow2(x) * x; }
static inline sgp4_t pow4(sgp4_t x)   { return pow3(x) * x; }
static inline sgp4_t pow5(sgp4_t x)   { return pow4(x) * x; }
static inline sgp4_t pow6(sgp4_t x)   { return pow5(x) * x; }
static inline sgp4_t pow7(sgp4_t x)   { return pow6(x) * x; }
static inline sgp4_t pow8(sgp4_t x)   { return pow7(x) * x; }

sgp4_err_t sgp4_propagator(const sgp4_parsed_two_line_element_t* parsed_tle, const sgp4_t jd, sgp4_vec_3d_t* r, sgp4_vec_3d_t* v)
{
    if (parsed_tle == NULL) { return SGP4_ERR; }
    if (r == NULL) { return SGP4_ERR; }
    if (v == NULL) { return SGP4_ERR; }

    const sgp4_err_t param_check_res = sgp4_check_orbit_parameters(parsed_tle);

    if ( SGP4_OK != param_check_res )
    {
        return param_check_res;
    }

    const sgp4_t deltaT = (jd - parsed_tle->epoch + 1.0) * 1440.0;

    // Preparation - convert angles to radians to be used in trig functions and assign
    // some values to variables from TLE
    sgp4_t INC   = to_rad(parsed_tle->incl);
    sgp4_t AOP   = to_rad(parsed_tle->aop);
    sgp4_t RAAN  = to_rad(parsed_tle->raan);
    sgp4_t MA0   = to_rad(parsed_tle->manomaly);
    sgp4_t ECC   = parsed_tle->ecc;
    sgp4_t MM0   = parsed_tle->mmotion * TWO_PI / MpD; // Read in revolutions per day and renorm with n -> n*2*pi/MinDay (1440 sec assumed in a day)
    sgp4_t Theta = cos(INC);

    /************ WP1 - Recover original mean motion (n0) and semimajor axis (a0) from input elements through some helping constants */

    sgp4_t SMA = pow(XKE / MM0, 2.0 / 3.0);                                                       // Original SMA from mean motion
    sgp4_t TV1 = 1.5 * CK2 * (3.0 * pow2(Theta) - 1.0) / (pow2(SMA) * pow(1.0 - pow2(ECC), 1.5)); // d1) correction kept in TV1
    SMA        = (1.0 - TV1 / 3.0 - pow2(TV1) - 134.0 * pow3(TV1) / 81.0) * SMA;                  // a0 first correction from d1 kept in TV1
    TV1        = 1.5 * CK2 * (3.0 * pow2(Theta) - 1.0) / (pow2(SMA) * pow(1.0 - pow2(ECC), 1.5)); // d0 correction kept in TV1
    MM0       /= (1.0 + TV1);                                                                     // Recovered original mean motion with d0 correction kept in TV1
    SMA       /= (1.0 - TV1);                                                                     // Recovered original SMA with d0 correction kept in TV1

    // Used to extract Keplerian elements at epoch after de-averaging operation - not required for the code !!!
    //printf( "SMA as of epoch is %.10e \n" , SMA*Re );

    /************ WP2 - work to be completed here for orbits going lower than 156 km altitude (final days) - not relevant for stable orbit */

    // Implement checking of a0 to determine which s value should be used !!!
    TV1 = ((1.0 - ECC) * SMA - 1.0) * Re; // Gives perigee height in [km] to be used for testing - kept in TV1

    if ((TV1 <= 156.0) && (TV1 > 98.0))
    {
        PRINTF("Scenario 98 < hp < 156 km \n");
        return SGP4_ERR;
    }
    else if (TV1 <= 98.0)
    {
        PRINTF("Scenario hp < 98 - your sat is basically down :/ \n");
        return SGP4_ERR;
    }
    else
    {
        PRINTF("Sat is still high :P \n");
    }
    /************ WP3 - Calculate some constants to be used in propagation */

    const sgp4_t s   = 1.01222928;
    const sgp4_t q0s = 1.88027916 * 1e-9; // default values of s and (q0-s)^4 in Earth radii and Earth Radii to power of 4

           TV1 = 1.0 / (SMA - s);         // Note that Xi is kept in TV1
    sgp4_t TV2 = sqrt(1.0 - pow2(ECC));   // Note that B0 is kept in TV2
    sgp4_t TV3 = SMA * ECC * TV1;         // Note that Eta is kept in TV3

    // TV4 holds the value of C4 constant
    sgp4_t TV4  = q0s * pow4(TV1) * MM0 * pow(1.0 - pow2(TV3), -3.5) * (SMA * (1.0 + 1.5 * pow2(TV3) + 4.0 * ECC * TV3 + ECC * pow3(TV3)) + 1.5 * CK2 * TV1 * (-0.5 + 1.5 * pow2(Theta)) * (8.0 + 24.0 * pow2(TV3) + 3.0 * pow4(TV3)) / (1.0 - pow2(TV3)));
    sgp4_t C1V  = parsed_tle->bstar * TV4;                                           // Note that TV4 holds the value of C2 for 2 rows (its only used do compute C1)
    sgp4_t TV5a = q0s * pow5(TV1) * A30 * aE * MM0 * sin(INC) / (ECC * CK2);         // Holds the value of C3 constant which is used only once further down

    // TV4 is used to keep line reasonably long
    TV4 = 3.0 * (1.0 - 3.0 * pow2(Theta)) * (1.0 + 1.5 * pow2(TV3) - 2.0 * ECC * TV3 - 0.5 * ECC * pow3(TV3)) + 0.75 * (1.0 - pow2(Theta)) * (2.0 * pow2(TV3) - ECC * TV3 - ECC * pow3(TV3)) * cos(2.0 * AOP);
    TV4 = 2.0 * MM0 * q0s * pow4(TV1) * SMA * pow2(TV2) * pow(1.0 - pow2(TV3), -3.5) * ((2.0 * TV3 * (1.0 + ECC * TV3) + 0.5 * ECC + 0.5 * pow3(TV3)) - 2.0 * CK2 * TV1 * TV4 / (SMA * (1.0 - pow2(TV3))));

    // TV4 is given the value of C4 to hold (one use further down)
    sgp4_t TV5 = 2.0 * q0s * pow4(TV1) * SMA * pow2(TV2) * pow(1.0 - pow2(TV3), -3.5) * (1.0 + 11.0 * TV3 * (TV3 + ECC) / 4.0 + ECC * pow3(TV3)); // Holds value of C5 constant
    sgp4_t D2V = 4.0 * SMA * TV1 * pow2(C1V);                                        // D2 constant
    sgp4_t D3V = 4.0 * SMA * pow2(TV1) * (17.00 * SMA + s) * pow3(C1V) / 3.0;        // D3 constant
    sgp4_t D4V = 2.0 * SMA * pow3(TV1) * (221.0 * SMA + 31.0 * s) * pow4(C1V) / 3.0; // D4 constant

    /************ WP4 - Calculate secular effects of drag and gravity */

    // Mean Anomaly at epoch first correction (M_DF)
    sgp4_t MAn = MA0 + (1.0 + 3.0 * CK2 * (3.0 * pow2(Theta) - 1.0) / (2.0 * pow2(SMA) * pow3(TV2)) + 3.0 * pow2(CK2) * (13.0 - 78.0 * pow2(Theta) + 137.0 * pow4(Theta)) / (16.0 * pow4(SMA) * pow7(TV2))) * MM0 * deltaT;

    // Argument of perigee intermediate value (w_DF)
    AOP = AOP + (-3.0 * CK2 * (1.0 - 5.0 * pow2(Theta)) / (2.0 * pow2(SMA) * pow4(TV2)) + 3.0 * pow2(CK2) * (7.0 - 114.0 * pow2(Theta) + 395.0 * pow4(Theta)) / (16.0 * pow4(SMA) * pow8(TV2)) + 5.0 * CK4 * (3.0 - 36.00 * pow2(Theta) + 49.00 * pow4(Theta)) / (4.00 * pow4(SMA) * pow8(TV2))) * MM0 * deltaT;

    // RAAN intermediate value (Om_DF) */
    RAAN = RAAN + (-3.0 * CK2 * Theta / (pow2(SMA) * pow4(TV2)) + 3.0 * pow2(CK2) * (4.0 * Theta - 19.0 * pow3(Theta)) / (2.0 * pow4(SMA) * pow8(TV2)) + 5.0 * CK4 * Theta * (3.0 - 7.0 * pow2(Theta)) / (2.0 * pow4(SMA) * pow8(TV2))) * MM0 * deltaT;

    sgp4_t TV6 = parsed_tle->bstar * TV5a * cos(to_rad(parsed_tle->aop)) * deltaT;                         // dw kept in TV6
    sgp4_t TV7 = -2.0 * q0s * parsed_tle->bstar * pow4(TV1) * aE * (pow3(1.0 + TV3 * cos(MAn)) - pow3(1.0 + TV3 * cos(MA0))) / (3.0 * ECC * TV3); // dM kept in TV7
    MAn  = MAn + TV6 + TV7;                                                                                // Mp = M_DF + dw + dM -> Mean Anomaly
    AOP  = AOP - TV6 - TV7;                                                                                // w = w_DF - dw - dM -> Argument of Perigee
    RAAN = RAAN - 10.5 * MM0 * CK2 * Theta * C1V * pow2(deltaT) / (pow2(SMA) * pow2(TV2));                 // Final RAAN value -> Om
    ECC  = ECC - parsed_tle->bstar * (TV4 * deltaT + TV5 * (sin(MAn) - sin(MA0)));                         // Compute final eccentricity
    SMA  = SMA * pow2(1.0 - C1V * deltaT - D2V * pow2(deltaT) - D3V * pow3(deltaT) - D4V * pow4(deltaT));  // Compute final SMA

    /************ WP5 - Long term periodic effects */

    // Lb value is kept in TV1 variable
    TV1 = MAn + AOP + RAAN + MM0 * (1.5 * C1V * pow2(deltaT) + (D2V + 2.0 * pow2(C1V)) * pow3(deltaT) + 0.25 * (3.0 * D3V + 12.0 * C1V * D2V + 10.0 * pow3(C1V)) * pow4(deltaT) + 0.20 * (3.0 * D4V + 12.0 * C1V * D3V + 6.00 * pow2(D2V) + 30.0 * pow2(C1V) * D2V + 15.0 * pow4(C1V)) * pow5(deltaT));

    // Beta value is kept in TV2 variable
    TV2 = sqrt(1.0 - pow2(ECC));

    // Final Mean Motion (n)
    MM0 = XKE / pow(SMA, 1.5);                                     // multiply by 1440 (MinDay) and divide by 2*pi to get actual number of revolutions per day
    TV3 = ECC * cos(AOP);                                          // a_xN kept in TV3 from here
    TV4 = A30 * sin(INC) * ECC * cos(AOP) * (3.0 + 5.0 * Theta) / (8.0 * CK2 * SMA * pow2(TV2) * (1.0 + Theta)); // Lb_L kept in TV4
    TV5 = A30 * sin(INC) / (4.0 * CK2 * SMA * pow2(TV2));          // a_yNL kept in TV5
    TV1 = TV4 + TV1;                                               // Computing Lb_T = Lb + Lb_L which is now kept in TV1
    TV5 = ECC * sin(AOP) + TV5;                                    // Computing a_yN = a_yNL + e*sin( w )

    // Now Solve Kepler's equation to obtain TA at required time
    TV5a = TV1 - RAAN;                                             // U is kept in TV5a
    TV2  = TV5a;                                                   // TV2 will be used as variable in the loop -> seeded with Lb_T - Om value
    TV4  = Ktol + 1.0;                                             // TV4 will be used for TV4 variable which measures deviation from 2 consequent iterations

    unsigned int i = 0;                                            // Counter which stops the loop if it does not converge in Ntol times
    while ((fabs(TV4) > Ktol) && (i < Ntol))
    {
        // delta(E+w) = ( U - ayN cos( E + w ) + axN sin( E + w ) - ( E + w ) )/( - ayN sin( E + w ) - axN cos( E + w ) + 1 )
        // In these iterations TV1 takes values of E + w -> True Anomaly
        TV4  = (TV5a - TV5 * cos(TV1) + TV3 * sin(TV1) - TV1) / (-TV5 * sin(TV1) - TV3 * cos(TV1) + 1.0);
        TV1 += TV4;
        i++;
    }
    if (i == Ntol)
    {
        PRINTF("The loop for Kepler's eq did not converge to required tolerance, mate! Check it perhaps!\n");
        return SGP4_ERR;
    }

    // At this point TV1 holds the value of E + w and we can proceed to find final values

    // Used to extract Keplerian elements at epoch after de-averaging operation - not required for the code !!!
    //TV1 = SGP4_twoPiMod(TV1);
    //printf("True anomaly at epoch desired is given by %.10e deg \n", TV1*180.0/PI);

    /************ WP6 - Find final values of all orbital parameters at epoch */

    TV2  = TV3 * cos(TV1) + TV5 * sin(TV1);                                                  // e*cos( E ) is held in TV2 variable
    TV4  = TV3 * sin(TV1) - TV5 * cos(TV1);                                                  // e*sin( E ) is held in TV4 variable
    TV5a = sqrt(pow2(TV3) + pow2(TV5));                                                      // e_L is kept in TV5a
    TV6  = SMA * (1.0 - pow2(TV5a));                                                         // pL - semi-latus rectum is kept in TV6
    sgp4_t RAD;
    RAD  = SMA * (1.0 - TV2);                                                                // Keeps preliminary radius value (r)
    C1V  = XKE * sqrt(SMA) * TV4 / RAD;                                                      // C1V keeps value of rdot -> radial component of velocity
    D2V  = XKE * sqrt(TV6) / RAD;                                                            // D2V keeps value of r*fdot -> angular component of velocity
    D3V  = (cos(TV1) - TV3 + TV5 * TV4 / (1.0 + sqrt(1.0 - pow2(TV5a)))) * SMA / RAD;        // Cosine of eccentric anomaly cos( u )
    D4V  = (sin(TV1) - TV5 - TV3 * TV4 / (1.0 + sqrt(1.0 - pow2(TV5a)))) * SMA / RAD;        // Sine of eccentric anomaly sin( u )
    sgp4_t ECCA;
    ECCA = atan(D4V / D3V);                                                                  // u is inverted from tg(u) and kept for use further down in ECCA variable
    TV1  = 2.0 * D3V * D4V;                                                                  // sin (2u) is kept in variable TV1
    TV2  = 2.0 * D3V * D3V - 1.0;                                                            // cos (2u) is kept in variable TV2
    TV3  =  CK2 * (1.0 - pow2(Theta)) * TV2 / (2.0 * TV6);                                   // TV3 holds dr from this point
    TV4  = -CK2 * (7.0 * pow2(Theta) - 1.0) * TV1 / (4.0 * pow2(TV6));                       // TV4 holds du from this point
    MAn  = 1.5 * CK2 * Theta * TV1 / pow2(TV6);                                              // Holds dOm value from this point
    MA0  = 1.5 * CK2 * Theta * sin(INC) * TV2 / pow2(TV6);                                   // Holds di value from this point
    TV5  = -CK2 * MM0 * (1.0 - pow2(Theta)) * TV1 / TV6;                                     // TV5 holds drdot from this point
    TV7  =  CK2 * MM0 * ((1.0 - pow2(Theta)) * TV2 - 1.5 * (1.0 - 3.0 * pow2(Theta))) / TV6; // TV7 holds drfdot from this point

    // Final Values for parameters are
    RAD  = RAD * (1.0 - 1.5 * CK2 * sqrt(1.0 - pow2(TV5a)) * (3.0 * pow2(Theta) - 1.0) / pow2(TV6)) + TV3; // Radial distance ( r ) at desired time
    ECCA = ECCA + TV4;                                                                       // Final value for Elliptic Anomaly u at desired time
    RAAN = RAAN + MAn;                                                                       // Final value for RAAN at desired time
    INC  = INC  + MA0;                                                                       // Final value for inclination at desired time
    C1V  = C1V  + TV5;                                                                       // Final value for radial velocity at desired time
    D2V  = D2V  + TV7;                                                                       // Final value for angular component of velocity at desired time -> rfdot

    // Reduce by 2*pi -> only useful if you need the actual angles and not necessary in general computations
    //Om = SGP4_twoPiMod(Om);
    //i0 = SGP4_twoPiMod(i0);
    //w  = SGP4_twoPiMod(w);

    /************ WP7 - compute position and velocity at required Time and record them in output vectors */

    TV5a  = sin(INC);                                                                        // TV5a keeps sine of inclination
    Theta = cos(INC);                                                                        // Theta once again keeps cosine of inclination
    TV1   = cos(RAAN);                                                                       // TV1 keeps cos( RAAN ) for final orbit orientation computations
    TV2   = sin(RAAN);                                                                       // TV2 keeps sin( RAAN ) for final orbit orientation computations
    TV3   = Re * RAD / aE;                                                                   // TV3 keeps radial norm of orbital position
    TV4   = Re * MpD / StD;                                                                  // TV4 keeps velocity norm -> up to this point it is in units of earth radii per minute -> correct to km/sec

    // Used to extract Keplerian elements at epoch after de-averaging operation - not required for the code !!!
    //printf("ECC, RAAN, INC and AOP are %.10e   %.10e   %.10e   %.10e \n" , ECC , RAAN*180.0/PI , INC*180.0/PI , AOP*180.0/PI );

    // Output vectors for the current moment */
    // \vec{r} = r \vec{U} */
    r->x = TV3 * (-TV2 * Theta * D4V + TV1 * D3V);
    r->y = TV3 * ( TV1 * Theta * D4V + TV2 * D3V);
    r->z = TV3 * TV5a * D4V;

    //printf( "Final r has value %.10e \n" , r*Re );

    // \dot{\vec{r}} = \dot{r}\vec{U} + r\dot{f}\vec{V}
    v->x = (-(C1V * D4V + D2V * D3V) * TV2 * Theta + (C1V * D3V - D2V * D4V) * TV1) * TV4;
    v->y = ( (C1V * D4V + D2V * D3V) * TV1 * Theta + (C1V * D3V - D2V * D4V) * TV2) * TV4;
    v->z = ( (C1V * D4V + D2V * D3V) * TV5a) * TV4;

    // In above notation U is unit radial vector and V is
    // unit tangent vector to trajectory ( U x V would give 3d vector forming orbit local frame )

    return SGP4_OK;
}

sgp4_err_t sgp4_check_orbit_parameters(const sgp4_parsed_two_line_element_t* const p_parsed_tle)
{
	if (NULL == p_parsed_tle) { return SGP4_ERR; }
	if (p_parsed_tle->bstar > BSTAR_MAX_LIMIT) { return SGP4_BSTAR_ERR; }
	if ((INC_MAX_LIMIT < p_parsed_tle->incl) || (INC_MIN_LIMIT > p_parsed_tle->incl)) { return SGP4_INC_ERR; }
	if ((RAAN_MAX_LIMIT < p_parsed_tle->raan) || (RAAN_MIN_LIMIT > p_parsed_tle->raan)) { return SGP4_RAAN_ERR; }
	if ((ECC_MAX_LIMIT < p_parsed_tle->ecc) || (ECC_MIN_LIMIT > p_parsed_tle->ecc)) { return SGP4_ECC_ERR; }
	if ((AOP_MAX_LIMIT < p_parsed_tle->aop) || (AOP_MIN_LIMIT > p_parsed_tle->aop)) { return SGP4_AOP_ERR; }
	if ((MA_MAX_LIMIT < p_parsed_tle->manomaly) || (MA_MIN_LIMIT > p_parsed_tle->manomaly)) { return SGP4_MA_ERR; }
	if ((MM_MAX_LIMIT < p_parsed_tle->mmotion) || (MM_MIN_LIMIT > p_parsed_tle->mmotion)) { return SGP4_MM_ERR; }

	return SGP4_OK;
}

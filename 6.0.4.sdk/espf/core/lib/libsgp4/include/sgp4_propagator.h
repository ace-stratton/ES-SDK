/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef SGP4_PROPAGATOR_H_
#define SGP4_PROPAGATOR_H_

/**
 * @addtogroup Libraries
 * @{
 *
 * @defgroup libsgp4 SGP4 Propagator
 * @{
 *
 * Helper library for SGP4 propagator calculations from TLE.
 *
 * ## Usage:
 *
 *  1. Start by verifying the received TLE by calling "sgp4_tle_verify_format()"
 *  2. If the result of "sgp4_tle_verify_format()" is "SGP4_OK", call "sgp4_tle_verify_checksum()"
 *  3. If the result of "sgp4_tle_verify_checksum()" is "SGP4_OK", call "sgp4_tle_parse()"
 *  4. Finally you can make calls to "sgp4_propagator()". Note that the TLE must be updated regularly
 *     to be able to give accurate estimation.
 *
 * ## NORAD Two-Line Element Set Format
 *
 * ### FORMAT RULES:
 * 1. Columns with a space or period can have no other character.
 * 2. Columns with an 'N' can have any number 0 - 9 or, in some cases, a space.
 * 3. Columns with an 'A' can have any character A - Z or a space.
 * 4. The column with a 'C' can only have a character representing the classification of the element
 *    set normally either a 'U' for unclassified data or an 'S' for secret data
 *    (of course, only unclassified data are publicly available).
 * 5. Columns with a '+' can have either a plus sign, a minus sign,
 * 6. or a space and columns with a '-' can have either a plus or minus sign
 *    (if the rest of the field is not blank).
 *
 * ### FORMAT:
 * Line 1 format:
 *
 * 1 NNNNNC NNNNNAAA NNNNN.NNNNNNNN +.NNNNNNNN +NNNNN-N +NNNNN-N N NNNNN
 *
 * | Field | Column | Description |
 * | ----- | ------ | ----------- |
 * | 1.1   | 01     | Line Number of Element Data
 * | 1.2   | 03-07  | Satellite Number
 * | 1.3   | 08     | Classification
 * | 1.4   | 10-11  | International Designator (Last two digits of launch year)
 * | 1.5   | 12-14  | International Designator (Launch number of the year)
 * | 1.6   | 15-17  | International Designator (Piece of the launch)
 * | 1.7   | 19-20  | Epoch Year (Last two digits of year)
 * | 1.8   | 21-32  | Epoch (Day of the year and fractional portion of the day)
 * | 1.9   | 34-43  | First Time Derivative of the Mean Motion
 * | 1.10  | 45-52  | Second Time Derivative of Mean Motion (decimal point assumed)
 * | 1.11  | 54-61  | BSTAR drag term (decimal point assumed)
 * | 1.12  | 63     | Ephemeris type
 * | 1.13  | 65-68  | Element number
 * | 1.14  | 69     | Checksum (Modulo 10) (Letters, blanks, periods, plus signs = 0; minus signs = 1)
 *
 * Line 2 format:
 *
 * 2 NNNNN NNN.NNNN NNN.NNNN NNNNNNN NNN.NNNN NNN.NNNN NN.NNNNNNNNNNNNNN
 *
 * | Field | Column | Description |
 * | ----- | ------ | ----------- |
 * | 2.1   | 01     | Line Number of Element Data
 * | 2.2   | 03-07  | Satellite Number
 * | 2.3   | 09-16  | Inclination [Degrees]
 * | 2.4   | 18-25  | Right Ascension of the Ascending Node [Degrees]
 * | 2.5   | 27-33  | Eccentricity (decimal point assumed)
 * | 2.6   | 35-42  | Argument of Perigee [Degrees]
 * | 2.7   | 44-51  | Mean Anomaly [Degrees]
 * | 2.8   | 53-63  | Mean Motion [Revs per day]
 * | 2.9   | 64-68  | Revolution number at epoch [Revs]
 * | 2.10  | 69     | Checksum (Modulo 10)
 *
 * _Reference: https://www.celestrak.com/columns/v04n03/_
 *
 * @file sgp4_propagator.h
 * @brief Public interface for the SGP4 library
 *
 * @}
 * @}
 */

#include "sgp4_config.h"
#include <stdbool.h>


#define SGP4_TLE_NUM_LINES      ( 2)
#define SGP4_TLE_CHARS_PER_LINE (69)

/* TLE orbital parameter limits */
#define BSTAR_MAX_LIMIT   0.99999999 /** BSTAR drag term */

#define INC_MAX_LIMIT   179.99999999 /** Inclination [Degrees] */
#define INC_MIN_LIMIT     0.00000001 /** Inclination [Degrees] */

#define RAAN_MAX_LIMIT  359.99999999 /** Right Ascension of the Ascending Node [Degrees] */
#define RAAN_MIN_LIMIT    0.00000001 /** Right Ascension of the Ascending Node [Degrees] */

#define ECC_MAX_LIMIT     0.99999999 /** Eccentricity coefficient */
#define ECC_MIN_LIMIT     0.00000001 /** Eccentricity coefficient */

#define AOP_MAX_LIMIT   359.99999999 /** Argument of Perigee [Degrees] */
#define AOP_MIN_LIMIT     0.00000001 /** Argument of Perigee [Degrees] */

#define MA_MAX_LIMIT    359.99999999 /** Mean Anomaly [Degrees] */
#define MA_MIN_LIMIT      0.00000001 /** Mean Anomaly [Degrees] */

#define MM_MAX_LIMIT     16.99999999 /** Mean Motion [Revs per day] */
#define MM_MIN_LIMIT      0.00000001 /** Mean Motion [Revs per day] */

#if SGP4_USE_TYPE_FLOAT
  typedef float  sgp4_t;
#else
  typedef double sgp4_t;
#endif


typedef enum
{
    SGP4_ERR = 0,
    SGP4_OK,
    SGP4_BSTAR_ERR,
    SGP4_INC_ERR,
    SGP4_RAAN_ERR,
    SGP4_ECC_ERR,
    SGP4_AOP_ERR,
    SGP4_MA_ERR,
    SGP4_MM_ERR
} sgp4_err_t;


typedef struct
{
    union
    {
        struct
        {
            sgp4_t x, y, z;
        };
        sgp4_t vec[3];
    };
} sgp4_vec_3d_t;


SGP4_PACK(typedef struct
{
    char line[SGP4_TLE_NUM_LINES][SGP4_TLE_CHARS_PER_LINE + 3]; // +3 because of CR, LF, and '\0'
}) sgp4_two_line_element_t;


/**
 * Parsed data from raw format (see sgp4_two_line_element_t)
 */
typedef struct
{
    sgp4_t ftdmm; // First Time Derivative of the Mean Motion
    sgp4_t stdmm; // Second Time Derivative of Mean Motion (Leading decimal point assumed)
    sgp4_t bstar; // BSTAR drag term (Leading decimal point assumed)
    sgp4_t incl; // Inclination [Degrees]
    sgp4_t raan; // Right Ascension of the Ascending Node [Degrees]
    sgp4_t ecc; // Eccentricity (Leading decimal point assumed)
    sgp4_t aop; // Argument of Perigee [Degrees]
    sgp4_t manomaly; // Mean Anomaly [Degrees]
    sgp4_t mmotion; // Mean Motion [Revs per day]
    sgp4_t epoch; // Epoch Year (Last two digits of year);Epoch (Day of the year and fractional portion of the day)
} sgp4_parsed_two_line_element_t;


/**
 * calculate Julian date
 */
sgp4_t sgp4_julian_date(sgp4_t year, sgp4_t month, sgp4_t day, sgp4_t hour, sgp4_t minute, sgp4_t second);


/**
 * Simple verification of the "two line element" format.
 */
sgp4_err_t sgp4_tle_verify_format(const sgp4_two_line_element_t* tle);


/**
 * Secondary verification of the actual "two line element" data.
 */
sgp4_err_t sgp4_tle_verify_checksum(const sgp4_two_line_element_t* tle);


/**
 * Function which parses TLE (Two-Line-Elements)
 * from two strings into the appropriate double/single precision numbers
 */
sgp4_err_t sgp4_tle_parse(sgp4_two_line_element_t* tle, sgp4_parsed_two_line_element_t* parsed_tle, bool parse_epoch);


/**
 * Inputs are parsed two line element and julian date.
 * Outputs are vectors R and V which are 3x1 arrays containing position and velocity of object at JD.
 */
sgp4_err_t sgp4_propagator(const sgp4_parsed_two_line_element_t* parsed_tle, const sgp4_t jd, sgp4_vec_3d_t* position, sgp4_vec_3d_t* velocity);

/** @brief Perform range checks on the orbital parameters
 *
 *  @param[in] const sgp4_parsed_two_line_element_t* const p_parsed_tle - pointer to orbit parameters
 *
 *  @return sgp4_err_t - check result
 *
 */
sgp4_err_t sgp4_check_orbit_parameters(const sgp4_parsed_two_line_element_t* const p_parsed_tle);

#endif /* SGP4_PROPAGATOR_H_ */

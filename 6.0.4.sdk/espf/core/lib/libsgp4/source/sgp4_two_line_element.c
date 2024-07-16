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
 * @file sgp4_two_line_element.c
 * @brief TLE parsing and formating
 *
 * @}
 */

#include "sgp4_propagator.h"
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>


#define SGP4_DIGITS   "0123456789"
#define SGP4_ALPHABET "ABCDEFGHIJKLMNOPQRSTUVWXYZ"


sgp4_err_t sgp4_tle_verify_checksum(const sgp4_two_line_element_t* tle)
{
    if (tle == NULL)
    {
        return SGP4_ERR;
    }

    if ((0 == isdigit((int)tle->line[0][68])) ||
        (0 == isdigit((int)tle->line[1][68])))
    {
        return SGP4_ERR;
    }

    int check_sum = 0;

    for (int j = 0; j < SGP4_TLE_NUM_LINES; j++)
    {
        char ch;

        for (int i = 0; i < SGP4_TLE_CHARS_PER_LINE - 1; i++)
        {
            ch = tle->line[j][i];

            if (isdigit(ch))
            {
                check_sum += ch - '0';// there is a problem with atoi(&ch); because of compiler or library issue
            }
            else if (ch == '-')
            {
                check_sum += 1;
            }
            else
            {
                // do nothing
            }
        }

        if ((check_sum % 10) != (tle->line[j][68] - '0'))
        {
            return SGP4_ERR;
        }

        check_sum = 0;
    }

    return SGP4_OK;
}


static sgp4_err_t sgp4_verify_leading_spaces(
    const char* field,
    const uint16_t field_size,
    const char* allowed_chars,
    const bool last_char_can_be_space)
{
    sgp4_err_t err = SGP4_ERR;
    char ch[2] = { '\0', '\0' };

    if ((NULL == field) || (0 == field_size) || (NULL == allowed_chars))
    {
        return err;
    }

    bool prev_char_is_space = true;
    int32_t i = 0;

    for (; i < field_size; i++)
    {
        if (' ' == field[i])
        {
            if (!prev_char_is_space)
            {
                err = SGP4_ERR;
                break;
            }
        }
        else
        {
            prev_char_is_space = false;
            ch[0] = field[i];
            if (!strpbrk(ch, allowed_chars))
            {
                err = SGP4_ERR;
                break;
            }
        }
    }

    if (i == field_size)
    {
        if (!last_char_can_be_space)
        {
            if (' ' != field[i - 1])
            {
                err = SGP4_OK;
            }
        }
        else
        {
            err = SGP4_OK;
        }
    }

    return err;
}


static sgp4_err_t sgp4_verify_trailing_spaces(
    const char* field,
    const uint16_t field_size,
    const char* allowed_chars,
    const bool first_char_can_be_space)
{
    sgp4_err_t err = SGP4_ERR;
    char ch[2] = { '\0', '\0' };

    if ((NULL == field) || (0 == field_size) || (NULL == allowed_chars))
    {
        return err;
    }

    bool prev_char_is_space = true;
    int32_t i = field_size - 1;

    for (; i >= 0; i--)
    {
        if (' ' == field[i])
        {
            if (!prev_char_is_space)
            {
                err = SGP4_ERR;
                break;
            }
        }
        else
        {
            prev_char_is_space = false;
            ch[0] = field[i];
            if (!strpbrk(ch, allowed_chars))
            {
                err = SGP4_ERR;
                break;
            }
        }
    }

    if (i == -1)
    {
        if (!first_char_can_be_space)
        {
            if (' ' != field[i + 1])
            {
                err = SGP4_OK;
            }
        }
        else
        {
            err = SGP4_OK;
        }
    }

    return err;
}


static sgp4_err_t sgp4_tle_verify_line1(const char* line)
{
    sgp4_err_t err = SGP4_ERR;
    char ch[2] = { '\0', '\0' };

    // 1: 01-01 Line number
    if (line[0] != '1')
    {
        return err;
    }

    if (line[1] != ' ')
    {
        return err;
    }

    // 2: 03–07 Satellite catalog number
    if (SGP4_OK != sgp4_verify_leading_spaces(&line[2], 5, SGP4_DIGITS, false))
    {
        return err;
    }

    // 3: 08-08 Classification
    ch[0] = line[7];
    if (!strpbrk(ch, "UCS "))
    {
        return err;
    }

    if (line[8] != ' ')
    {
        return err;
    }

    // 4: 10–11 International Designator(last two digits of launch year)
    if ((0 == isdigit((uint8_t)line[9])) || (0 == isdigit((uint8_t)line[10])))
    {
        return err;
    }

    // 5: 12–14 International Designator (launch number of the year)
    if ((0 == isdigit((uint8_t)line[11])) || (0 == isdigit((uint8_t)line[12])) || (0 == isdigit((uint8_t)line[13])))
    {
        return err;
    }

    // 6: 15–17 International Designator (piece of the launch)
    if (SGP4_OK != sgp4_verify_trailing_spaces(&line[14], 3, SGP4_ALPHABET, false))
    {
        return err;
    }

    if (line[17] != ' ')
    {
        return err;
    }

    // 7: 19–20 Epoch year (last two digits of year)
    if ((0 == isdigit((uint8_t)line[18])) || (0 == isdigit((uint8_t)line[19])))
    {
        return err;
    }

    // 8: 21–32 Epoch (day of the year and fractional portion of the day)
    if (SGP4_OK != sgp4_verify_leading_spaces(&line[20], 3, SGP4_DIGITS, false))
    {
        return err;
    }

    if (line[23] != '.')
    {
        return err;
    }

    if (SGP4_OK != sgp4_verify_trailing_spaces(&line[24], 8, SGP4_DIGITS, false))
    {
        return err;
    }

    if (line[32] != ' ')
    {
        return err;
    }

    // 9: 34–43 First derivative of mean motion; the ballistic coefficient
    ch[0] = line[33];
    if (!strpbrk(ch, "+- "))
    {
        return err;
    }

    if (line[34] != '.')
    {
        return err;
    }

    if (SGP4_OK != sgp4_verify_trailing_spaces(&line[35], 8, SGP4_DIGITS, false))
    {
        return err;
    }

    if (line[43] != ' ')
    {
        return err;
    }

    // 10: 45–52 Second derivative of mean motion(decimal point assumed)
    ch[0] = line[44];
    if (!strpbrk(ch, "+- "))
    {
        return err;
    }

    if ((0 == isdigit((uint8_t)line[45])) ||
        (0 == isdigit((uint8_t)line[46])) ||
        (0 == isdigit((uint8_t)line[47])) ||
        (0 == isdigit((uint8_t)line[48])) ||
        (0 == isdigit((uint8_t)line[49])) ||
        (0 == isdigit((uint8_t)line[51])))
    {
        return err;
    }

    ch[0] = line[50];
    if (!strpbrk(ch, "+-"))
    {
        return err;
    }

    if (line[52] != ' ')
    {
        return err;
    }

    // 11: 54–61 B*, the drag term, or radiation pressure coefficient (decimal point assumed)
    ch[0] = line[53];
    if (!strpbrk(ch, "+- "))
    {
        return err;
    }

    if ((0 == isdigit((uint8_t)line[54])) ||
        (0 == isdigit((uint8_t)line[55])) ||
        (0 == isdigit((uint8_t)line[56])) ||
        (0 == isdigit((uint8_t)line[57])) ||
        (0 == isdigit((uint8_t)line[58])) ||
        (0 == isdigit((uint8_t)line[60])))
    {
        return err;
    }

    ch[0] = line[59];
    if (!strpbrk(ch, "+-"))
    {
        return err;
    }

    if (line[61] != ' ')
    {
        return err;
    }

    // 12: 63-63 Ephemeris type (always zero; only used in undistributed TLE data)
    if (0 == isdigit((uint8_t)line[62]))
    {
        return err;
    }

    if (line[63] != ' ')
    {
        return err;
    }

    // 13: 65–68 Element set number.Incremented when a new TLE is generated for this object.
    if (SGP4_OK != sgp4_verify_leading_spaces(&line[64], 4, SGP4_DIGITS, false))
    {
        return err;
    }

    // 14: 69-69 Checksum (modulo 10)
    if (0 == isdigit((uint8_t)line[68]))
    {
        return err;
    }

    return SGP4_OK;
}


static sgp4_err_t sgp4_tle_verify_line2(const char* line)
{
    sgp4_err_t err = SGP4_ERR;

    // 1: 01-01 Line number
    if (line[0] != '2')
    {
        return err;
    }

    if (line[1] != ' ')
    {
        return err;
    }

    // 2: 03–07 Satellite Catalog number
    if (SGP4_OK != sgp4_verify_trailing_spaces(&line[2], 5, SGP4_DIGITS, false))
    {
        return err;
    }

    if (line[7] != ' ')
    {
        return err;
    }

    // 3: 09–16 Inclination (degrees)
    if (SGP4_OK != sgp4_verify_leading_spaces(&line[8], 3, SGP4_DIGITS, false))
    {
        return err;
    }

    if (line[11] != '.')
    {
        return err;
    }

    if (SGP4_OK != sgp4_verify_trailing_spaces(&line[12], 4, SGP4_DIGITS, false))
    {
        return err;
    }

    if (line[16] != ' ')
    {
        return err;
    }

    // 4: 18–25 Right ascension of the ascending node (degrees)
    if (SGP4_OK != sgp4_verify_leading_spaces(&line[17], 3, SGP4_DIGITS, false))
    {
        return err;
    }

    if (line[20] != '.')
    {
        return err;
    }

    if (SGP4_OK != sgp4_verify_trailing_spaces(&line[21], 4, SGP4_DIGITS, false))
    {
        return err;
    }

    if (line[25] != ' ')
    {
        return err;
    }

    // 5: 27–33 Eccentricity (decimal point assumed)
    if ((0 == isdigit((uint8_t)line[26])) ||
        (0 == isdigit((uint8_t)line[27])) ||
        (0 == isdigit((uint8_t)line[28])) ||
        (0 == isdigit((uint8_t)line[29])) ||
        (0 == isdigit((uint8_t)line[30])) ||
        (0 == isdigit((uint8_t)line[31])) ||
        (0 == isdigit((uint8_t)line[32])))
    {
        return err;
    }

    if (line[33] != ' ')
    {
        return err;
    }

    // 6: 35–42 Argument of perigee (degrees)
    if (SGP4_OK != sgp4_verify_leading_spaces(&line[34], 3, SGP4_DIGITS, false))
    {
        return err;
    }

    if (line[37] != '.')
    {
        return err;
    }

    if (SGP4_OK != sgp4_verify_trailing_spaces(&line[38], 4, SGP4_DIGITS, false))
    {
        return err;
    }

    if (line[42] != ' ')
    {
        return err;
    }

    // 7: 44–51 Mean anomaly (degrees)
    if (SGP4_OK != sgp4_verify_leading_spaces(&line[43], 3, SGP4_DIGITS, false))
    {
        return err;
    }

    if (line[46] != '.')
    {
        return err;
    }

    if (SGP4_OK != sgp4_verify_trailing_spaces(&line[47], 4, SGP4_DIGITS, false))
    {
        return err;
    }

    if (line[51] != ' ')
    {
        return err;
    }

    // 8: 53–63 Mean motion (revolutions per day)
    if (SGP4_OK != sgp4_verify_leading_spaces(&line[52], 2, SGP4_DIGITS, false))
    {
        return err;
    }

    if (line[54] != '.')
    {
        return err;
    }

    if (SGP4_OK != sgp4_verify_trailing_spaces(&line[55], 8, SGP4_DIGITS, false))
    {
        return err;
    }

    // 9: 64–68 Revolution number at epoch (revolutions)
    if (SGP4_OK != sgp4_verify_leading_spaces(&line[63], 5, SGP4_DIGITS, false))
    {
        return err;
    }

    // 10: 69-69 Checksum (modulo 10)
    if (0 == isdigit((uint8_t)line[68]))
    {
        return err;
    }

    return SGP4_OK;
}


sgp4_err_t sgp4_tle_verify_format(const sgp4_two_line_element_t* tle)
{
    sgp4_err_t err = SGP4_ERR;

    if (tle == NULL)
    {
        return err;
    }
    
    err = sgp4_tle_verify_line1(tle->line[0]);
    if (SGP4_OK != err)
    {
        return err;
    }
    
    err = sgp4_tle_verify_line2(tle->line[1]);
    if (SGP4_OK != err)
    {
        return err;
    }
    
    if (('\0' != tle->line[0][SGP4_TLE_CHARS_PER_LINE]) ||
        ('\0' != tle->line[1][SGP4_TLE_CHARS_PER_LINE]))
    {
        err = SGP4_ERR;
    }

    return err;
}


sgp4_err_t sgp4_tle_parse(sgp4_two_line_element_t* tle, sgp4_parsed_two_line_element_t* parsed_tle, bool parse_epoch)
{
    if ((tle == NULL) ||
        (parsed_tle == NULL) ||
        (SGP4_ERR == sgp4_tle_verify_format(tle)) ||
        (SGP4_ERR == sgp4_tle_verify_checksum(tle)))
    {
        return SGP4_ERR;
    }

    char delim1[] = " ";
    char delim2[] = "+-";
    char* rent = tle->line[0];
    const char* ptr = strtok_r(rent, delim1, &rent);

    for (int i = 0; i < 3; i++)
    {
        ptr = strtok_r(rent, delim1, &rent);          // keeps the value of year and epoch in char format
    }

    sgp4_t tv1 = strtod(ptr, NULL);                   // gets entire number YY+day of year (fractional) point from char to double
    if (true != parse_epoch)
    {
        parsed_tle->epoch = tv1;
    }
    else
    {
        sgp4_t tv2 = floor(tv1 * 1e-3);               // Keeps Year - 2000 piece of the epoch
        tv1 = tv1 - tv2 * 1000.0;                     // Keeps day of the year

        sgp4_t yr  = 2000.0 + tv2;
        sgp4_t mon = 1.0;
        sgp4_t day = 1.0;
        sgp4_t hr  = 0.0;
        sgp4_t min = 0.0;
        sgp4_t sec = 0.0;

        parsed_tle->epoch = sgp4_julian_date(yr, mon, day, hr, min, sec); // Returns Julian Date of Jan 1st 00:00 UTC for the year in mind
        parsed_tle->epoch += tv1;                     // Adds the days elapsed since Jan 1st 00:00 UTC to obtain final Julian Date of initial epoch
    }

    ptr = strtok_r(rent, delim1, &rent);              // keeps value of n0_dot in char format
    parsed_tle->ftdmm = strtod(ptr, NULL);

    ptr = strtok_r(rent, delim2, &rent);              // keeps value of n0_ddot base in char format
    char* ptr2 = strtok_r(rent, delim1, &rent);       // keeps value of decimal power to n0_ddot -> "-" should be added
    parsed_tle->stdmm = (strtod(ptr, NULL) * 1e-5) * pow(10.0, -strtod(ptr2, NULL));
   
    ptr  = strtok_r(rent, delim2, &rent);             // keeps value of Bstar coefficient (drag) -> base part
    ptr2 = strtok_r(rent, delim1, &rent);             // keeps value of decimal power of Bstar coefficient (drag) (- sign should be added)
    parsed_tle->bstar = (strtod(ptr, NULL) * 1e-5) * pow(10.0, -strtod(ptr2, NULL));

    rent = tle->line[1];

    ptr = strtok_r(rent, delim1, &rent);              // starting line 2 -> get 2
    ptr = strtok_r(rent, delim1, &rent);              // starting line 2 - get code of sat
    ptr = strtok_r(rent, delim1, &rent);              // Keep inclination in degrees as char
    parsed_tle->incl = strtod(ptr, NULL);

    ptr = strtok_r(rent, delim1, &rent);              // Keep mean RAAN in degrees as char
    parsed_tle->raan = strtod(ptr, NULL);

    ptr = strtok_r(rent, delim1, &rent);              // Keep eccentricity fractional part (0. assumed) with 7 relevant figures (char)
    parsed_tle->ecc = strtod(ptr, NULL) * 1e-7;

    ptr = strtok_r(rent, delim1, &rent);              // keeps mean AOP at epoch (deg) as char
    parsed_tle->aop = strtod(ptr, NULL);

    ptr = strtok_r(rent, delim1, &rent);              // keeps mean mean anomaly at epoch in deg as char
    parsed_tle->manomaly = strtod(ptr, NULL);

    ptr = strtok_r(rent, delim1, &rent);              // keeps mean motion at epoch (rev/day) as char
    parsed_tle->mmotion = strtod(ptr, NULL);

    return SGP4_OK;
}

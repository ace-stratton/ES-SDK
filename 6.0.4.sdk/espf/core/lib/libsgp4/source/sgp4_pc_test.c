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
 * @file sgp4_pc_test.c
 * @brief Module for testing
 *
 * @}
 */

#include "sgp4_propagator.h"
#if (SGP4_TEST_ON_PC == 1)
#include <stdio.h>
#include <assert.h>


/**
 * Note: Currently assuming spherical Earth -> ~ 3 deg error is expected
 *       Elliptical model to be implemented in following weeks
 */
int main()
{
    FILE* file = fopen("<user_location>/LL.txt", "w");

    if (file != NULL)
    {
        sgp4_two_line_element_t tle =
        {
            // ISS tle for reference
            //          1 NNNNNC NNNNNAAA NNNNN.NNNNNNNN +.NNNNNNNN +NNNNN-N +NNNNN-N N NNNNN
            .line[0] = "1 25544U 98067AAA 20042.09407434  .00000583  00000-0  18674-4 0 09995\0",
            //          2 NNNNN NNN.NNNN NNN.NNNN NNNNNNN NNN.NNNN NNN.NNNN NN.NNNNNNNNNNNNNN
            .line[1] = "2 25544 051.6445 257.3095 0004878 252.7385 245.0132 15.49153434212312\0"
        };

        fprintf(file, "%s\n", tle.line[0]);
        fprintf(file, "%s\n", tle.line[1]);

        sgp4_parsed_two_line_element_t parsed_tle;

        if (sgp4_tle_parse(&tle, &parsed_tle, true) == SGP4_ERR)
            assert(false);

        for (int yr = 2021; yr < 2022; yr++)
        {
            for (int mon = 1; mon < 2; mon++)
            {
                for (int day = 1; day < 10; day++)
                {
                    for (int hr = 0; hr < 24; hr++)
                    {
                        for (int min = 0; min < 1; min++)
                        {
                            for (int sec = 0; sec < 1; sec++)
                            {
                                // Compute JD of current time (when location and velocity are needed)
                                sgp4_t jd_now = sgp4_julian_date(yr, mon, day, hr, min, sec);

                                // Find position in inertial ref frame
                                sgp4_vec_3d_t pos;
                                sgp4_vec_3d_t vel;
                                if (sgp4_propagator(&parsed_tle, jd_now, &pos, &vel) == SGP4_ERR)
                                    assert(false);

                                fprintf(file, "%lf %lf %lf %lf\n", jd_now, pos.x, pos.y, pos.z);
                            }
                        }
                    }
                }
            }
        }

        fclose(file);
    }
    else
        assert(false);

    return 0;
}


#endif /* #if (SGP4_TEST_ON_PC == 1) */

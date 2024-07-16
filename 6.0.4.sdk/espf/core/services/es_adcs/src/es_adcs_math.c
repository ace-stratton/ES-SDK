/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */

/**
 * @addtogroup es_adcs
 * @{
 *
 * @file     es_adcs_math.c
 * @brief    EnduroSat ADCS math functionality source file
 *
 * @}
*/

#include <stdint.h>
#include <string.h>
#include <math.h>
#include "es_adcs_math.h"

/**********************************************************************
 *
 * Public functions
 *
 **********************************************************************/
REAL es_adcs_math_VecNorm(es_adcs_vec_3d_t inVec)
{
    return sqrt(inVec.X * inVec.X + inVec.Y * inVec.Y + inVec.Z * inVec.Z);
}

es_adcs_vec_3d_t es_adcs_math_VecNormalize(es_adcs_vec_3d_t inVec)
{
    es_adcs_vec_3d_t tempVec;

    REAL norm = es_adcs_math_VecNorm(inVec);
    if (norm >= DOUBLE_ZERO_LIMIT)
    {
        tempVec.X = inVec.X / norm;
        tempVec.Y = inVec.Y / norm;
        tempVec.Z = inVec.Z / norm;
    }
    else
    {
        tempVec = es_adcs_math_VecSet(1.0, 1.0, 1.0);
    }

    return tempVec;
}

REAL es_adcs_math_VecDotProduct(es_adcs_vec_3d_t inVec1, es_adcs_vec_3d_t inVec2)
{
    return inVec1.X * inVec2.X + inVec1.Y * inVec2.Y + inVec1.Z * inVec2.Z;
}

es_adcs_vec_3d_t es_adcs_math_VecCrossProduct(es_adcs_vec_3d_t inVec1, es_adcs_vec_3d_t inVec2)
{
    es_adcs_vec_3d_t tempVec;

    tempVec.X = inVec1.Y * inVec2.Z - inVec1.Z * inVec2.Y;
    tempVec.Y = inVec1.Z * inVec2.X - inVec1.X * inVec2.Z;
    tempVec.Z = inVec1.X * inVec2.Y - inVec1.Y * inVec2.X;

    return tempVec;
}

void es_adcs_math_MatMatMultiply(const es_adcs_vec_3d_t *inMat1, const es_adcs_vec_3d_t *inMat2, es_adcs_vec_3d_t *outMat)
{
    memset (outMat, 0x00, sizeof (es_adcs_vec_3d_t) * 3);
    for (uint8_t i = 0; i < 3; i++)
    {
        for (uint8_t j = 0; j < 3; j++)
        {
            for (uint8_t k = 0; k < 3; k++)
            {
            	outMat[i].Vec[j] += inMat1[i].Vec[k] * inMat2[k].Vec[j];
            }
        }
    }
}

void es_adcs_math_MatVecMultiply(const es_adcs_vec_3d_t *inMat, es_adcs_vec_3d_t inVec, es_adcs_vec_3d_t *outVec)
{
    /* Help vector used to prevent overlap of variables when inVec is the same as outVec */
    es_adcs_vec_3d_t tempVec = es_adcs_math_VecSet(0.0, 0.0, 0.0);

    memset (outVec, 0x00, sizeof (es_adcs_vec_3d_t));
    for (uint8_t i = 0; i < 3; i++)
    {
        for (uint8_t j = 0; j < 3; j++)
        {
        	tempVec.Vec[i] += inMat[i].Vec[j] * inVec.Vec[j];
        }
    }

    outVec->X = tempVec.X;
    outVec->Y = tempVec.Y;
    outVec->Z = tempVec.Z;
}

es_adcs_vec_3d_t es_adcs_math_VecNegate(es_adcs_vec_3d_t inVec)
{
    es_adcs_vec_3d_t tempVec;

    tempVec.X = - inVec.X;
    tempVec.Y = - inVec.Y;
    tempVec.Z = - inVec.Z;

    return tempVec;
}

es_adcs_vec_3d_t es_adcs_math_VecSet(REAL x, REAL y, REAL z)
{
    es_adcs_vec_3d_t tempVec;

    tempVec.X = x;
    tempVec.Y = y;
    tempVec.Z = z;

    return tempVec;
}

es_adcs_vec_3d_t es_adcs_math_VecAbs(es_adcs_vec_3d_t inVec)
{
    es_adcs_vec_3d_t tempVec;

    tempVec.X = fabs(inVec.X);
    tempVec.Y = fabs(inVec.Y);
    tempVec.Z = fabs(inVec.Z);

    return tempVec;
}

es_adcs_vec_3d_t es_adcs_math_VecAdd(es_adcs_vec_3d_t inVec1, es_adcs_vec_3d_t inVec2)
{
    es_adcs_vec_3d_t tempVec;

    tempVec.X = inVec1.X + inVec2.X;
    tempVec.Y = inVec1.Y + inVec2.Y;
    tempVec.Z = inVec1.Z + inVec2.Z;

    return tempVec;
}

es_adcs_vec_3d_t es_adcs_math_VecSub(es_adcs_vec_3d_t inVec1, es_adcs_vec_3d_t inVec2)
{
    es_adcs_vec_3d_t tempVec;

    tempVec.X = inVec1.X - inVec2.X;
    tempVec.Y = inVec1.Y - inVec2.Y;
    tempVec.Z = inVec1.Z - inVec2.Z;

    return tempVec;
}

es_adcs_vec_3d_t es_adcs_math_VecScale(es_adcs_vec_3d_t inVec1, REAL scaleFactor)
{
    es_adcs_vec_3d_t tempVec;

    tempVec.X = inVec1.X * scaleFactor;
    tempVec.Y = inVec1.Y * scaleFactor;
    tempVec.Z = inVec1.Z * scaleFactor;

    return tempVec;
}

void es_adcs_math_GetDCM(es_adcs_vec_3d_t inVec, es_adcs_vec_3d_t *outMat)
{
    es_adcs_vec_3d_t tempVec = inVec;

    /* Standard 3-2-1 DCM, COLUMN 1 */
    outMat[0].X =                   cos(tempVec.Y) * cos(tempVec.Z);
    outMat[0].Y =                   cos(tempVec.Y) * sin(tempVec.Z);
    outMat[0].Z =                  -sin(tempVec.Y);

    /* Standard 3-2-1 DCM, COLUMN 2 */
    outMat[1].X =  sin(tempVec.X) * sin(tempVec.Y) * cos(tempVec.Z) - cos(tempVec.X) * sin(tempVec.Z);
    outMat[1].Y =  sin(tempVec.X) * sin(tempVec.Y) * sin(tempVec.Z) + cos(tempVec.X) * cos(tempVec.Z);
    outMat[1].Z =  sin(tempVec.X) * cos(tempVec.Y);

    /* Standard 3-2-1 DCM, COLUMN 3 */
    outMat[2].X =  cos(tempVec.X) * sin(tempVec.Y) * cos(tempVec.Z) + sin(tempVec.X) * sin(tempVec.Z);
    outMat[2].Y =  cos(tempVec.X) * sin(tempVec.Y) * sin(tempVec.Z) - sin(tempVec.X) * cos(tempVec.Z);
    outMat[2].Z =  cos(tempVec.X) * cos(tempVec.Y);
}

REAL es_adcs_math_InverseOf(REAL inputNum)
{
	return 1.0/inputNum;
}

/* ******************************************************************************************* */

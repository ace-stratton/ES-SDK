/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */

#ifndef ES_ADCS_MATH_H
#define ES_ADCS_MATH_H

/**
 * @addtogroup es_adcs
 * @{
 *
 * @file     es_adcs_math.h
 * @brief    EnduroSat ADCS math functionality header file
 *
 * @}
*/

/** @brief Degree to radian conversion constant */
#define DEG2RAD    (2 * M_PI) / 360.0

/** @brief Radian to degree conversion constant */
#define RAD2DEG    360.0 / (2 * M_PI)

/** @brief Any difference between two floating point numbers that is less than this define is considered as 0 */
#define DOUBLE_ZERO_LIMIT  1e-15

/**********************************************************************
 *
 * Type definitions
 *
 **********************************************************************/
/** @brief Easily change the floating point type for different systems */
typedef double REAL;

/** @brief General ADCS vector math unit */
typedef struct
{
    union
    {
        struct
        {
            REAL X, Y, Z;
        };
        REAL Vec[3];
    };
} es_adcs_vec_3d_t;

/**********************************************************************
 *
 * Public functions
 *
 **********************************************************************/
/** @brief Compute Euclidean norm N (magnitude) of vector inVec
 *  @param[in] es_adcs_vec_3d_t inVec - input vector
 *  @return    REAL                   - Input vector's Euclidean norm (magnitude) */
extern REAL es_adcs_math_VecNorm(es_adcs_vec_3d_t inVec);

/** @brief Normalize vector inVec
 *  @param[in] es_adcs_vec_3d_t inVec - input vector
 *  @return    es_adcs_vec_3d_t       - Normalized input vector */
extern es_adcs_vec_3d_t es_adcs_math_VecNormalize(es_adcs_vec_3d_t inVec);

/** @brief Dot (scalar) product for 3x1 vectors inVec1 and inVec2
 *  @param[in] es_adcs_vec_3d_t inVec1 - input vector
 *  @param[in] es_adcs_vec_3d_t inVec2 - input vector
 *  @return    REAL                    - Input vectors' dot product */
extern REAL es_adcs_math_VecDotProduct(es_adcs_vec_3d_t inVec1, es_adcs_vec_3d_t inVec2);

/** @brief Cross (vector) product for 3x1 vectors inVec1 and inVec2
 *  @param[in] es_adcs_vec_3d_t inVec1 - input vector
 *  @param[in] es_adcs_vec_3d_t inVec2 - input vector
 *  @return    es_adcs_vec_3d_t        - Input vectors' cross product */
extern es_adcs_vec_3d_t es_adcs_math_VecCrossProduct(es_adcs_vec_3d_t inVec1, es_adcs_vec_3d_t inVec2);

/** @brief Matrix Multiplication function for inMat1 and inMat2 so inMat1.inMat2 = outMat where inMat1, inMat2 and outMat are 3x3 matrices
 *  @param[in] const es_adcs_vec_3d_t *inMat1 - supplied 3x3 first matrix
 *  @param[in] const es_adcs_vec_3d_t *inMat2 - supplied 3x3 second matrix
 *  @param[out]      es_adcs_vec_3d_t *outMat - pointer to resulting 3x3 matrix */
extern void es_adcs_math_MatMatMultiply(const es_adcs_vec_3d_t *inMat1, const es_adcs_vec_3d_t *inMat2, es_adcs_vec_3d_t *outMat);

/** @brief Matrix x Vector multiplication function for inMat and inVec so inMat.inVec = outVec
 *  @param[in] const es_adcs_vec_3d_t  *inMat - supplied 3x3 matrix
 *  @param[in]       es_adcs_vec_3d_t   inVec - supplied 3x1 vector
 *  @param[out]      es_adcs_vec_3d_t *outVec - resulting 3x1 vector */
extern void es_adcs_math_MatVecMultiply(const es_adcs_vec_3d_t *inMat, es_adcs_vec_3d_t inVec, es_adcs_vec_3d_t *outVec);

/** @brief Negate a vector
 *  @param[in] es_adcs_vec_3d_t inVec1 - input vector
 *  @return    es_adcs_vec_3d_t        - Input vector negated */
extern es_adcs_vec_3d_t es_adcs_math_VecNegate(es_adcs_vec_3d_t inVec);

/** @brief Negate a vector
 *  @param[in] REAL x           - X axis value
 *  @param[in] REAL y           - Y axis value
 *  @param[in] REAL z           - Z axis value
 *  @return    es_adcs_vec_3d_t - Input vector with corresponding X, Y, Z values */
extern es_adcs_vec_3d_t es_adcs_math_VecSet(REAL x, REAL y, REAL z);

/** @brief Return a vector consisting of the absolute values of each value in the input vector
 *  @param[in] es_adcs_vec_3d_t inVec - input vector
 *  @return    es_adcs_vec_3d_t       - Vector with absolute values of corresponding input vector's X, Y, Z values */
extern es_adcs_vec_3d_t es_adcs_math_VecAbs(es_adcs_vec_3d_t inVec);

/** @brief Add two 3x1 vectors and returns the result of inVec1 + inVec2
 *  @param[in] es_adcs_vec_3d_t inVec1 - supplied 3x1 vector
 *  @param[in] es_adcs_vec_3d_t inVec2 - supplied 3x1 vector
 *  @return    es_adcs_vec_3d_t        - Sum of input vectors */
extern es_adcs_vec_3d_t es_adcs_math_VecAdd(es_adcs_vec_3d_t inVec1, es_adcs_vec_3d_t inVec2);

/** @brief Subtract two 3x1 vectors and returns the result of inVec1 - inVec2
 *  @param[in] es_adcs_vec_3d_t inVec1 - supplied 3x1 vector
 *  @param[in] es_adcs_vec_3d_t inVec2 - supplied 3x1 vector
 *  @return    es_adcs_vec_3d_t        - Difference of input vectors */
extern es_adcs_vec_3d_t es_adcs_math_VecSub(es_adcs_vec_3d_t inVec1, es_adcs_vec_3d_t inVec2);

/** @brief Scale an input 3x1 vector
 *  @param[in] es_adcs_vec_3d_t      inVec1 - supplied 3x1 vector
 *  @param[in] REAL             scaleFactor - scaling factor to apply to the input vector
 *  @return    es_adcs_vec_3d_t             - Scaled input vector
 *  @note This function can be used for multiplication or division of a vector by a scalar */
extern es_adcs_vec_3d_t es_adcs_math_VecScale(es_adcs_vec_3d_t inVec1, REAL scaleFactor);

/** @brief Apply rotations to the DCM in accordance to input vector consisting of roll, pitch, yaw angles
 *  @param[in]  es_adcs_vec_3d_t   inVec - supplied 3x1 vector with rotation angles
 *  @param[out] es_adcs_vec_3d_t *outMat - pointer to resulting rotated 3x3 DCM */
extern void es_adcs_math_GetDCM(es_adcs_vec_3d_t inVec, es_adcs_vec_3d_t *outMat);

/** @brief Return the inverse of the input number
 *  @param[in]  REAL input - the number which is to be inverted
 *  @return     REAL       - inverse of the input number */
extern REAL es_adcs_math_InverseOf(REAL inputNum);

#endif /* ES_ADCS_MATH_H */
/* ******************************************************************************************* */

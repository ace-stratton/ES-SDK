/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef USER_TYPES_H
#define USER_TYPES_H

/**
 * @addtogroup es_cdef
 * @{
 *
 * Common types to be used with the SW platform.
 *
 * @file    User_types.h
 * @brief   Header of common types
 * @deprecated The types here should not be used in new implementations
 *
 * @}
 */

#include <stdbool.h>
#include <stdint.h>


/** Enumeration of the available magnetorquers
 * @note
 */
typedef enum ES_ReturnType {
  E_OK,
  E_PENDING,
  E_UNKNOWN_FAILURE,
  E_NOT_INIT,
  E_INV_ARG,
  E_INV_CFG,
  E_ERROR,
  E_MMETER_READING,
  E_FILTERING,
  E_DATA_NORMALIZE,
  E_BDOT_CALCULATING,
  E_MTORQ_UPDATE,
  E_NOT_OK
} ES_ReturnType;

typedef struct Magnetorquer_Axis_t {
  double AXIS_X;
  double AXIS_Y;
  double AXIS_Z;  
}__attribute__((__packed__)) Magnetorquer_Axis_t;

typedef struct Compass_Axis_t{
  double AXIS_X;
  double AXIS_Y;
  double AXIS_Z;
}__attribute__((__packed__)) Compass_Axis_t;

typedef enum
{
  SEN_ERROR = 0x00,
  SEN_SUCCESS = 0x01,
  SEN_DISABLED = 0xFF
} status_t;

typedef struct {
  int16_t AXIS_X;
  int16_t AXIS_Y;
  int16_t AXIS_Z;
} AxesRaw_t;

typedef struct {
  int16_t Temp_X;
  int16_t Temp_Y;
  int16_t Temp_Z;
} Temperature_t;

#endif    /* USER_TYPES_H */

/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
#ifndef SGP4_CONFIG_H_
#define SGP4_CONFIG_H_


#define SGP4_TEST_ON_PC     (0)  // 0 when in OBC application
                                 // 1 when testing on PC
#define SGP4_USE_TYPE_FLOAT (0)  // 0 for double
                                 // 1 for float

#ifdef __GNUC__
  #define SGP4_PACK(__declaration__) __declaration__ __attribute__((__packed__))
#elif _MSC_VER
  #define SGP4_PACK(__declaration__) __pragma(pack(push, 1)) __declaration__ __pragma(pack(pop))
#endif



#endif /* SGP4_CONFIG_H_ */

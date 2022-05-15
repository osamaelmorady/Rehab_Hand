/******************************************************************************/
/* @File            : TEMPSENSOR.h       		                              */
/*                                                                            */
/* @Designed by     : khalid ateia                         @Date : 1-10-2017  */
/*                                                                            */
/* @Coded by        : khalid ateia                         @Date : 1-10-2017  */
/*                                                                            */
/* @Coding language : C                                                       */
/*                                                                            */
/* @COPYRIGHT 2016 El-ARABY Research and development center.                  */
/* all rights reserved                                                        */
/******************************************************************************/
#ifndef _APP_TEMPERATURE_MAPPING_H_
#define _APP_TEMPERATURE_MAPPING_H_
/******************************************************************************/
/*! \file
*
* \par
*   Externals of the module TEMPSENSOR.c \n
*   This file contains the externals of the module TEMPSENSOR.c */
/******************************************************************************/
/******************************************************************************/
/*!	\Description TEMP. sensors */
/******************************************************************************/

#include "utils/STD_TYPES.h"
typedef enum
{
	TSENS_FLANGE = 0,
	TSENS_DISPLAY,
} tTSENS;

// Public prototypes
/******************************************************************************/
/*! \Description TEMPSENSOR initialization. \n */
/*! <B>Service Detailed Description:</B> \n */
/*! - Initialize for ADC \n */
/*! - initialize variables for power \n */
/******************************************************************************/
void temperatureSensing_init(void);

/******************************************************************************/
/*! \Description TEMPSENSOR update. */
/******************************************************************************/
void temperatureSensing_update(void *arg);

/******************************************************************************/
/*! \Description return TEMPSENSOR current value. */
/******************************************************************************/
uint8_t app_temperatureSensing_get(tTSENS sensor);

#endif

/******************************************************************************/
/* @File            : SW.h                                     				  */
/*                                                                            */
/* @Designed by     : khalid ateia                         @Date : 1-10-2017  */
/*                                                                            */
/* @Coded by        : khalid ateia                         @Date :  1-10-2017 */
/*                                                                            */
/* @Coding language : C                                                       */
/*                                                                            */
/* @COPYRIGHT 2016 El-ARABY Research and development center.                  */
/* all rights reserved                                                        */
/******************************************************************************/

#ifndef _SW_H
#define _SW_H
/******************************************************************************/
/*! \file
*
* \par
*   Externals of the module SW.c \n
*   This file contains the externals of the module SW.c */
/******************************************************************************/

/******************************************************************************/
/*!	\Description   Switch type. */
/******************************************************************************/
#include "app/inc/config.h"
#include "app/inc/bsp.h"
#include "app/inc/def.h"
#include "utils/utils.h"
#include "os/inc/os.h"
typedef enum
{
    SW_PLUS,
    SW_MINUS,
    SW_STANDBY,
    SW_TURBO
} tSW;

/******************************************************************************/
/*! \Description Switch state. */
/******************************************************************************/
typedef enum
{
    SW_RELEASED,
    SW_PRESSED,
    SW_LONG_PRESSED
} tSWState;


#define SW_STATE_RELEASED 0
#define SW_STATE_PRESSED 1
#define SW_STATE_LONG_PRESSED 2


/******************************************************************************/
/*! \Description Switch initialization. \n */
/*! <B>Service Detailed Description:</B> \n */
/*! - Initialize System Switchs as follow: \n */
/*! - Get the Switch Name [SW_DUST_FULL]. \n */
/*! - control the direction of Switch into INPUT. \n */
/*! - Initialize switch states into Released. \n */
/******************************************************************************/
void SW_Init(tSW sw);

/******************************************************************************/
/*! \Description Switch get status. \n */
/*! <B>Service Detailed Description:</B> \n */
/*! - get the switch name and return the latest state for this switch. \n */
/******************************************************************************/
tSWState SW_GetState(tSW sw);

/******************************************************************************/
/*! \Description Switch update. \n
 Should be called periodically \n
                 called periodically every 20ms in sEOS ISR function \n
                 Period >= debounce period. */
/*! <B>Service Detailed Description:</B> \n */
/*! - Update System Switchs state as follow: \n */
/*!   1- point to the Switch information struct [ SWDustFullInfo ]. \n */
/*!   2- get teh latest sample on Switch PIN.[ Pressed , Released ] \n */
/******************************************************************************/
void SW_Update(void *arg);
/******************************************************************************/
/*! \Description get SW_pressed_time_counter value. \n*/
/*! <B>Service Detailed Description:</B> \n */
/*! - get the switch name and return the pressed time value for this switch. */
/******************************************************************************/
uint32_t SW_PressedGetTimeValue(tSW sw);

/******************************************************************************/
/*! \Description reset SW_pressed_time_counter value. */
/*! <B>Service Detailed Description:</B> \n */
/*! - get the switch name and reset the pressed time value variable for this switch. \n */
/*******************************************************************************/
void SW_PressedResetTimeValue(tSW sw);

/******************************************************************************/
/*! \Description get SW_GetChangeState. \n*/
/*! <B>Service Detailed Description:</B> \n */
/*! - get the switch Level State . */
/******************************************************************************/
tSWState SW_GetSWLevelState(tSW sw);
#endif

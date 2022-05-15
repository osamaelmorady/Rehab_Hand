//Key
//short press,release 60ms
//long press 2000ms
//sampling 20ms

//************
#include "app/input/SW.h"
#include "app/inc/config.h"


#define SW_STATE_CHANGED (1)
#define SW_STATE_UNCHANGED (0)

#ifdef SW_TACTILE_BUTTON
#define SW_PRESSED_LEVEL (1)
#define SW_RELEASED_LEVEL (0)
#endif
#ifdef SW_TOUCH_PAD
#define SW_PRESSED_LEVEL (0)
#define SW_RELEASED_LEVEL (1)
#endif
#ifdef SW_TOUCH_PAD_FINAL_PCB
#define SW_PRESSED_LEVEL (0)
#define SW_RELEASED_LEVEL (1)
#endif

#if SW_TOUCH_BS13_2_MCU
#define SW_PRESSED_LEVEL (1)
#define SW_RELEASED_LEVEL (0)

#define SW_STANDBY_Key 0x04
#define SW_TURBO_Key 0x08
#define SW_PLUS_Key 0x02
#define SW_MINUS_Key 0x01

#endif

#if SW_TOUCH_BS14_2_MCU
#define SW_PRESSED_LEVEL (1)
#define SW_RELEASED_LEVEL (0)

#define SW_STANDBY_Key 0x04
#define SW_TURBO_Key 0x08
#define SW_PLUS_Key 0x01
#define SW_MINUS_Key 0x02


#elif SW_TOUCH_ROHM

#define SW_PRESSED_LEVEL (1)
#define SW_RELEASED_LEVEL (0)

#define SW_STANDBY_Key 0x02
#define SW_TURBO_Key 0x01
#define SW_PLUS_Key 0x08
#define SW_MINUS_Key 0x04

#endif







#define SW_STUCK_TIME_MS (59000)

// Private constants
#define SW_UPDATE_PERIOD_MS (20)
#define NO_OF_PRESS_SAMPLES (3)
#define NO_OF_Release_SAMPLES (3)
#define NO_OF_SHORT_PRESS_SAMPLES (3)
#define NO_OF_LONG_PRESS_SAMPLES (50)

// Switch info
typedef struct
{
    tSWState state;
    tSWState oldstate;
    uint8_t sample;
    uint32_t ReadPressSamples;
    uint32_t ReadReleaseSamples;
    uint8_t SW_StateNotification;
    uint32_t SW_pressed_time_counter;
    uint8_t SW_StuckError;
    uint32_t edgeCounterFlag;
} tSWInfo;

// Private data types
// Switches info

static tSWInfo SW_PLUS_Info;
static tSWInfo SW_MINUS_Info;
static tSWInfo SW_STANDBY_Info;
static tSWInfo SW_TURBO_Info;
static uint8_t SW_UpdateTimeMS;
static uint8_t gByte_SW_signalCarrier;


static tSWInfo SW_PLUS_Info={};		// Modified By Osama Elmorady
static tSWInfo SW_MINUS_Info={};
static tSWInfo SW_STANDBY_Info={};



static void SW_StateUpdate(tSW sw);

// Public functions
/*******************************************************/
// Switch initialization

void SW_Init(tSW sw)
{
    //uint8_t index;
    tSWInfo * SWInfo = NULL;

    switch (sw)
    {
    case SW_PLUS:
        SWInfo = &SW_PLUS_Info;
        break;

    case SW_MINUS:
        SWInfo = &SW_MINUS_Info;
        break;

    case SW_STANDBY:
        SWInfo = &SW_STANDBY_Info;
        break;

    case SW_TURBO:
        SWInfo = &SW_TURBO_Info;
        break;
    }

    SWInfo->sample = SW_RELEASED_LEVEL;
    SWInfo->SW_pressed_time_counter = 0;

    SWInfo->ReadPressSamples = 0;
    SWInfo->ReadReleaseSamples = 0;

    SWInfo->state = SW_RELEASED;
    SWInfo->oldstate = SW_RELEASED;
    SWInfo->SW_StateNotification = SW_STATE_UNCHANGED;
    SWInfo->SW_StuckError = 0;
    SWInfo->edgeCounterFlag = 0;
    SW_UpdateTimeMS = 0;
    gByte_SW_signalCarrier = 0;
}

/*******************************************************/
// Switch update status
// Should be called periodically
// Period >= debounce period
void SW_Update(void *arg)
{



    SW_StateUpdate(SW_PLUS);
    SW_StateUpdate(SW_MINUS);
    SW_StateUpdate(SW_STANDBY);
    SW_StateUpdate(SW_TURBO);

    if (SW_PLUS_Info.SW_StuckError == 1)
    {
//                LOGS_SetError(LOGS_SW_PLUS_STUCK, ERROR);
    }
    else
    {
        	//LOGS_SetError(LOGS_SW_PLUS_STUCK, NO_ERROR);
    }

    if (SW_MINUS_Info.SW_StuckError == 1)
    {
//                LOGS_SetError(LOGS_SW_MINUS_STUCK, ERROR);
    }
    else
    {
        	//LOGS_SetError(LOGS_SW_MINUS_STUCK, NO_ERROR);
    }

    if (SW_STANDBY_Info.SW_StuckError == 1)
    {
//                LOGS_SetError(LOGS_SW_STANDBY_STUCK, ERROR);
    }
    else
    {
        	//LOGS_SetError(LOGS_SW_STANDBY_STUCK, NO_ERROR);
    }

    if (SW_TURBO_Info.SW_StuckError == 1)
    {
               //LOGS_SetError(LOGS_SW_TURBO_STUCK, ERROR);
    }
    else
    {
        	//LOGS_SetError(LOGS_SW_STANDBY_STUCK, NO_ERROR);
    }
}
/*******************************************************/
static void SW_StateUpdate(tSW sw)
{
    tSWInfo *SWInfo = NULL;
    switch (sw)
    {
    case SW_PLUS:
        SWInfo = &SW_PLUS_Info;
        SWInfo->sample = (gByte_SW_signalCarrier & SW_PLUS_Key);
        break;
    case SW_MINUS:
        SWInfo = &SW_MINUS_Info;
        SWInfo->sample = (gByte_SW_signalCarrier & SW_MINUS_Key);
        break;
    case SW_STANDBY:
        SWInfo = &SW_STANDBY_Info;
        SWInfo->sample = (gByte_SW_signalCarrier & SW_STANDBY_Key);
        break;
    case SW_TURBO:
        SWInfo = &SW_TURBO_Info;
        SWInfo->sample = (gByte_SW_signalCarrier & SW_TURBO_Key);
        break;
    }
    /*--------------------------------------------------------------------------------*/
    // Update switch state based on samples
    switch (SWInfo->state)
    {
    case SW_RELEASED:
        SWInfo->ReadReleaseSamples = 0;
        if (SWInfo->sample != SW_RELEASED_LEVEL)
        {
            SWInfo->ReadPressSamples++;
        }
        else
        {
            SWInfo->ReadPressSamples = 0;
        }

        if (SWInfo->ReadPressSamples >= NO_OF_SHORT_PRESS_SAMPLES)
        {
            SWInfo->ReadPressSamples = 0;
            SWInfo->state = SW_PRESSED;
        }
        else
        {
            //state = released
        }
        break;

    case SW_PRESSED:
        if (SWInfo->sample != SW_RELEASED_LEVEL)
        {
            SWInfo->ReadReleaseSamples = 0;
            SWInfo->ReadPressSamples++;
        }
        else
        {
            SWInfo->ReadReleaseSamples++;
        }

        if (SWInfo->ReadPressSamples >= NO_OF_LONG_PRESS_SAMPLES)
        {
            SWInfo->ReadReleaseSamples = 0;
            SWInfo->ReadPressSamples = 0;
            SWInfo->state = SW_LONG_PRESSED;
        }
        else if (SWInfo->ReadReleaseSamples >= NO_OF_Release_SAMPLES)
        {
            SWInfo->ReadReleaseSamples = 0;
            SWInfo->ReadPressSamples = 0;
            SWInfo->state = SW_RELEASED;
        }
        else
        {
            /* state = short pressed  */
        }
        break;

    case SW_LONG_PRESSED:
        SWInfo->ReadPressSamples = 0;

        if (SWInfo->sample == SW_RELEASED_LEVEL)
        {
            SWInfo->ReadReleaseSamples++;
        }
        else
        {
            SWInfo->ReadReleaseSamples = 0;
        }

        if (SWInfo->ReadReleaseSamples >= NO_OF_Release_SAMPLES)
        {
            SWInfo->ReadReleaseSamples = 0;
            SWInfo->ReadPressSamples = 0;
            SWInfo->state = SW_RELEASED;
            SWInfo->SW_pressed_time_counter = 0;
        }
        else if (SWInfo->SW_pressed_time_counter <= SW_STUCK_TIME_MS)
        {
            SWInfo->SW_pressed_time_counter += SW_UPDATE_PERIOD_MS;
        }
        else
        {
            /* state = long pressed  */
        }
        break;
    }
    /*--------------------------------------------------------------------------------*/
    //detect first edge and second edge then update the switch state
    if (SWInfo->state != SWInfo->oldstate)
    {
        if ((SWInfo->oldstate == SW_RELEASED) && (SWInfo->state == SW_PRESSED))
        {
            SWInfo->edgeCounterFlag = 1;
        }
        else if ((SWInfo->edgeCounterFlag == 1) &&
                 (((SWInfo->oldstate == SW_PRESSED) && (SWInfo->state == SW_RELEASED))))
        {
            SWInfo->SW_StateNotification = SWInfo->oldstate;
            SWInfo->edgeCounterFlag = 0;
        }
        else
        {
            //do nothing
        }

        SWInfo->oldstate = SWInfo->state;
    }
    else
    {
        if ((SWInfo->edgeCounterFlag == 1) && (SWInfo->state == SW_LONG_PRESSED))
        {
            SWInfo->SW_StateNotification = SWInfo->state;
            SWInfo->edgeCounterFlag = 0;
        }
        else
        {
            SWInfo->SW_StateNotification = SW_STATE_UNCHANGED;
        }
    }

    //check switch stuck error
    if (SWInfo->SW_pressed_time_counter > SW_STUCK_TIME_MS)
    {
        //log flag error switch stuck
        SWInfo->SW_StuckError = 1;
        SWInfo->SW_pressed_time_counter = 0;
    }
    else
    {
        //no error
        SWInfo->SW_StuckError = 0;
    }

}
/*******************************************************/

// Switch get status
tSWState SW_GetState(tSW sw)
{
    tSWState ret = SW_RELEASED;

    switch (sw)
    {
    case SW_PLUS:
        if ((SW_PLUS_Info.SW_StateNotification != SW_STATE_UNCHANGED))
        {
            ret = SW_PLUS_Info.SW_StateNotification;
        }
        break;
    case SW_MINUS:
        if ((SW_MINUS_Info.SW_StateNotification != SW_STATE_UNCHANGED))
        {
            ret = SW_MINUS_Info.SW_StateNotification;
        }
        break;
    case SW_STANDBY:
        if ((SW_STANDBY_Info.SW_StateNotification != SW_STATE_UNCHANGED))
        {
            ret = SW_STANDBY_Info.SW_StateNotification;
        }
        break;
    case SW_TURBO:
        if ((SW_TURBO_Info.SW_StateNotification != SW_STATE_UNCHANGED))
        {
            ret = SW_TURBO_Info.SW_StateNotification;
        }
        break;
    }
    return ret;
}

/*******************************************************/

//get SW_pressed_time_counter value
uint32_t SW_PressedGetTimeValue(tSW sw)
{
    uint16_t ret = 0;
    switch (sw)
    {
    case SW_PLUS:
        ret = SW_PLUS_Info.SW_pressed_time_counter;
        break;
    case SW_MINUS:
        ret = SW_MINUS_Info.SW_pressed_time_counter;
        break;
    case SW_STANDBY:
        ret = SW_STANDBY_Info.SW_pressed_time_counter;
        break;
    case SW_TURBO:
        ret = SW_TURBO_Info.SW_pressed_time_counter;
        break;
    }
    return ret;
}
/*******************************************************/
//reset SW_pressed_time_counter value
void SW_PressedResetTimeValue(tSW sw)
{
    switch (sw)
    {
    case SW_PLUS:
        SW_PLUS_Info.SW_pressed_time_counter = 0;
        break;
    case SW_MINUS:
        SW_MINUS_Info.SW_pressed_time_counter = 0;
        break;
    case SW_STANDBY:
        SW_STANDBY_Info.SW_pressed_time_counter = 0;
        break;
    case SW_TURBO:
        SW_TURBO_Info.SW_pressed_time_counter = 0;
        break;
    }
}
/*******************************************************/
//get SW Get Level State
tSWState SW_GetSWLevelState(tSW sw)
{
    tSWState ret = SW_RELEASED;
    switch (sw)
    {
    case SW_PLUS:
        ret = SW_PLUS_Info.state;
        break;
    case SW_MINUS:
        ret = SW_MINUS_Info.state;
        break;
    case SW_STANDBY:
        ret = SW_STANDBY_Info.state;
        break;
    case SW_TURBO:
        ret = SW_TURBO_Info.state;
        break;
    }
    return ret;
}

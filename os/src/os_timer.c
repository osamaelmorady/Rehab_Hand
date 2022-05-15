#include "app/inc/config.h"
#include "os/inc/os.h"

typedef struct
{
    os_timer_mode_t mode;
    uint32_t periodMS;
    uint8_t repeat;
    uint8_t os_timerID;
    uint32_t internalCount;
    uint8_t opFlag;
    uint8_t timeoutFlag;
} os_timer_internalHandler_t;

static os_timer_internalHandler_t gax_os_timer_internalHandler[OS_TIMERS_NUM];
static uint8_t gu8_os_timer_internalCounter = 0;

void os_timer_init(os_timer_t *timer)
{
    gax_os_timer_internalHandler[gu8_os_timer_internalCounter].mode = timer->mode;
    gax_os_timer_internalHandler[gu8_os_timer_internalCounter].periodMS = timer->periodMS;
    gax_os_timer_internalHandler[gu8_os_timer_internalCounter].repeat = timer->repeat;
    gax_os_timer_internalHandler[gu8_os_timer_internalCounter].os_timerID = timer->os_timerID;
    gax_os_timer_internalHandler[gu8_os_timer_internalCounter].internalCount = 0;
    gax_os_timer_internalHandler[gu8_os_timer_internalCounter].opFlag = 1;
    gax_os_timer_internalHandler[gu8_os_timer_internalCounter].timeoutFlag = 0;

    gu8_os_timer_internalCounter++;
}

void os_timer_delayMS_wait(uint16_t u16_delay)
{
    uint32_t start = os_tick_millis_get();
    while (start + u16_delay > os_tick_millis_get())
        ;
}

uint32_t os_timer_value_get(uint8_t u8_osTimerID)
{
    uint8_t i = 0;

    for (i = 0; i < gu8_os_timer_internalCounter; i++)
    {
        if (u8_osTimerID == gax_os_timer_internalHandler[i].os_timerID)
        {
            return gax_os_timer_internalHandler[i].internalCount;
        }
    }
    return 255;
}

int8_t os_timer_state_get(uint8_t u8_osTimerID)
{
    uint8_t i = 0;
    int8_t ret = -1;

    for (i = 0; i < gu8_os_timer_internalCounter; i++)
    {
        if (u8_osTimerID == gax_os_timer_internalHandler[i].os_timerID)
        {
            ret = gax_os_timer_internalHandler[i].timeoutFlag;
            gax_os_timer_internalHandler[i].timeoutFlag = 0;
        }
    }
    return ret;
}

void os_timer_reset(uint8_t u8_osTimerID)
{
    uint8_t i = 0;

    for (i = 0; i < gu8_os_timer_internalCounter; i++)
    {
        if (u8_osTimerID == gax_os_timer_internalHandler[i].os_timerID)
        {
            gax_os_timer_internalHandler[i].internalCount = 0;
            gax_os_timer_internalHandler[i].timeoutFlag = 0;
        }
    }
}

void os_timer_disable(uint8_t u8_osTimerID)
{
    uint8_t i = 0;

    for (i = 0; i < gu8_os_timer_internalCounter; i++)
    {
        if (u8_osTimerID == gax_os_timer_internalHandler[i].os_timerID)
        {
            gax_os_timer_internalHandler[i].opFlag = 0;
        }
    }
}

void os_timer_enable(uint8_t u8_osTimerID)
{
    uint8_t i = 0;

    for (i = 0; i < gu8_os_timer_internalCounter; i++)
    {
        if (u8_osTimerID == gax_os_timer_internalHandler[i].os_timerID)
        {
            gax_os_timer_internalHandler[i].opFlag = 1;
        }
    }
}

void os_timer_update(void *arg)
{
    uint8_t i = 0;

    for (i = 0; i < gu8_os_timer_internalCounter; i++)
    {
        if (gax_os_timer_internalHandler[i].opFlag)
        {
            gax_os_timer_internalHandler[i].internalCount += OS_TIMER_UPDATE_PERIOD_MS;

            if (gax_os_timer_internalHandler[i].mode == OS_TIMER_ALARM_MODE)
            {
                if (gax_os_timer_internalHandler[i].internalCount >= gax_os_timer_internalHandler[i].periodMS)
                {
                    gax_os_timer_internalHandler[i].internalCount = 0;
                    if (gax_os_timer_internalHandler[i].repeat == 1)
                    {
                        gax_os_timer_internalHandler[i].opFlag = 1;
                    }
                    else
                    {
                        gax_os_timer_internalHandler[i].opFlag = 0;
                    }

                    gax_os_timer_internalHandler[i].timeoutFlag = 1;
                }
            }
        }
    }
}

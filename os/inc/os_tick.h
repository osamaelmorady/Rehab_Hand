#ifndef OS_TICK_H
#define OS_TICK_H 1

#include "mcal/mcal.h"

void os_tick_init(uint32_t u32_tickPeriod);

#if STRUCT_USE_SDS == 1
#define os_tick_update(updateFn, tickPeriod)            \
    do                                                  \
    {                                                   \
        mcal_sysTick_resume();                          \
        gu32_os_tick_timestamp += (uint32_t)tickPeriod; \
        os_scheduler_update();                          \
        updateFn();                                     \
    } while (0)
#else
void os_tick_update(void (*updateFn)(void), uint32_t tickPeriod);
#endif

uint32_t os_tick_millis_get(void);

#endif

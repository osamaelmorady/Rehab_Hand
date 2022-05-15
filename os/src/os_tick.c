#include "mcal/mcal.h"
#include "app/inc/config.h"

volatile uint32_t gu32_os_tick_timestamp;

void os_tick_init(uint32_t u32_tickPeriod)
{
    mcal_sysTick_set(u32_tickPeriod);
    // TODO: add check for the return
}

#if STRUCT_USE_SDS == 0
void os_tick_update(void (*updateFn)(void), uint32_t tickPeriod)
{
    mcal_sysTick_resume();
    gu32_os_tick_timestamp += tickPeriod;
    updateFn();
}
#endif

uint32_t os_tick_millis_get(void)
{
    return gu32_os_tick_timestamp;
}

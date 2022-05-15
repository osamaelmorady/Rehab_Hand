#include "mcal/mcal.h"
#include "app/inc/bsp.h"

void wdt_init(void)
{
    mcal_wdt_set(MCAL_WDT_RESET_TIME_L4);
    mcal_wdt_feed();
}

void wdt_update(void *arg)
{
    CRITICAL_SECTION_START();
    mcal_wdt_feed();
    CRITICAL_SECTION_END();
}

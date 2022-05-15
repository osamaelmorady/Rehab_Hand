#include "utils/STD_TYPES.h"
#include "mcal/mcal.h"
#include "app/inc/config.h"
#include "core/STM32F103/stm32f10x_wwdg.h"
#include "core/STM32F103/stm32f10x_iwdg.h"

void mcal_wdt_init(void)
{
}

void mcal_wdt_set(uint32_t resetTime)
{

}

void mcal_wdt_feed(void)
{
}

void mcal_wdt_disable(void)
{

}

void mcal_wdt_enable(void)
{

}

//WDT_DETECT_TIME_EXP_15,17,19,21,23,25
//IF YOU WANT TO DUPLICATE TIME DON NOT CLEAR WDT WHEN IT GOES INTERRUPT
//0.41      ,1.64     ,6.55      ,26.21    ,104.86   ,419.43
//CG_DIVIDE_1, CG_DIVIDE_2, CG_DIVIDE_4, CG_DIVIDE_8, CG_DIVIDE_16
//EXP_15     ,EXP_17      , EXP_19     , EXP_21     , EXP_23   , EXP_25
//THIS FUNCTION TO FACILITATE AND COMBINE WDT AND SYSTEM CLOCK
//void mcal_wdt_clockConfig_set(CG_DivideLevel DivideFgearFromFc, uint32_t resetTime)
//{
//}

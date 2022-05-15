#include "utils/STD_TYPES.h"
#include "mcal/mcal.h"
#include "core/STM32F103/stm32f10x_tim.h"
#include "core/STM32F103/MSTK/MSTK_Interface.h"
#include "app/inc/config.h"

mcal_timer_t Timer = MCAL_TIMER_1;

static uint32_t global_val=1000 ;

void mcal_sysTick_init(void)
{
	MSTK_EnuTimerInit() ;

//	mcal_timer_init()  ;

}

void mcal_sysTick_set(uint32_t u32_tickms)
{
	global_val = u32_tickms * 1000U ;

	MSTK_EnuClearFlag();
	MSTK_EnuTimerPreload(global_val) ;
	MSTK_EnuInterruptStatus( SYS_TICK_INT_ENABLE ) ;
	MSTK_EnuStartTimer() ;

//    mcal_timer_timerModeMS_init(&Timer, u32_tickms);
//    mcal_timer_timerFlag_clear('\0') ;
//    mcal_timer_timerInterruptState_set(&Timer, MCAL_TIMER_INT_ENABLE);
//    mcal_timer_timerState_set(&Timer, MCAL_TIMER_START);

}

void mcal_sysTick_resume(void)
{
	MSTK_EnuTimerPreload(global_val) ;

	//	mcal_timer_timerModeMS_init(&Timer, OS_TICK_PERIOD_MS);
}

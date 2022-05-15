/****************************************************************/
#include "os/inc/os.h"
#include "mcal/mcal.h"
#include "app/inc/bsp.h"
#include "app/inc/config.h"
#include "app/inc/app_startup.h"
#include "utils/utils.h"
/****************************************************************/
#include "component/doutput_module/doutput_module.h"
/****************************************************************/
#include "driver/uart/uart.h"
#include "driver/ssw_uart/ssw_uart.h"
#include "core/STM32F103/MSTK/MSTK_Interface.h"
/****************************************************************/


#define DEBUG (0)

//static uint32_t sEOS_counter=0;
//static uint8_t tog_flag=0 ;
//static mcal_gpio_t pin_C13 = {MCAL_GPIO_PORTC,MCAL_GPIO_PIN13,MCAL_GPIO_OUTPUT,MCAL_GPIO_LOW,MCAL_GPIO_EXTINT_DISABLE,MCAL_GPIO_EXTINT_BOTH_EDGES} ;
/***********************************************************************************************/
/* system tick ISR */
void SysTick_Handler(void)
{
	MSTK_EnuClearFlag() ;

	os_tick_update(&os_scheduler_update, OS_TICK_PERIOD_MS );

//	sEOS_counter+=1 ;
//
//	if (sEOS_counter>1000UL)
//	{
//		pin_C13.pinState = tog_flag ;
//		mcal_gpio_pin_init(&pin_C13) ;
//		mcal_gpio_pinState_set(&pin_C13,tog_flag)  ;
//
//		tog_flag = !tog_flag  ;
//
//		sEOS_counter=0 ;
//	}

}



void TIM4_IRQHandler(void)
{
	mcal_timer_timerFlag_clear(0) ;

	os_tick_update(&os_scheduler_update, OS_TICK_PERIOD_MS);

//	mcal_gpio_pinState_set(&pin_A8,tog_flag)  ;
//
//	tog_flag = !tog_flag  ;
}
/***********************************************************************************************/






/***********************************************************************************************/
/* Low Voltage Detection ISR */



/***********************************************************************************************/




/*********************************************************************************************/
void bsp_clockConfig_set(void)
{
    mcal_cg_system_set();
}

void bsp_interruptPriorities_set(void)
{
}


void __assert(const char *file, int line, const char *failedexpr)
{
    __assert_func(file, line, NULL, failedexpr) ;
}
/*********************************************************************************************/

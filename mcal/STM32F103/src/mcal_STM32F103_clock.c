#include "utils/STD_TYPES.h"
#include "mcal/mcal.h"

#include "core/STM32F103/system/include/cmsis/stm32f10x.h"
#include "core/STM32F103/stm32f10x_rcc.h"

//static RCC_ClocksTypeDef clock_set ;

void mcal_cg_init(void)
{
	/* System Clock */
	RCC_SYSCLKConfig(RCC_SYSCLKSource_HSI) ;
	RCC_HCLKConfig(RCC_SYSCLK_Div1);
	RCC_PCLK1Config(RCC_HCLK_Div1);
	RCC_PCLK2Config(RCC_HCLK_Div1);
	RCC_ADCCLKConfig(RCC_PCLK2_Div8);
	//	RCC_GetClocksFreq(&clock_set)  ;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE) ;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE) ;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE) ;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE) ;

	/* UART */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE) ;
//		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE) ;
//		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE) ;


	//	/* Timer & PWM Clocks */
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE) ;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE) ;		/* Buzzer -> PWM */
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE) ;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE) ;		/* Servo -> PWM */



//	/* ADCs Clocks */
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE) ;
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2,ENABLE) ;


//
//	/* WDT */
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG,ENABLE) ;

}

void mcal_cg_system_set(void)
{

}

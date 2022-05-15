// NOTE:
//when Freq is 10 mega
//minimum freq -> (10mega/65535) = 153HZ   , maximum freq -> 10mega
//maximum time -> 6 milli                  , minimum time -> 0.1 micro
#include "utils/STD_TYPES.h"
#include "mcal/mcal.h"
#include "app/inc/config.h"
#include "core/STM32F103/stm32f10x_tim.h"
#include "core/STM32F103/stm32f10x_gpio.h"


TIM_OCInitTypeDef pwm_ch1_set = {TIM_OCMode_PWM1,TIM_OutputState_Enable,TIM_OutputNState_Disable,20000,TIM_OCPolarity_High,TIM_OCNPolarity_Low,TIM_OCIdleState_Set,TIM_OCNIdleState_Reset} ;
TIM_OCInitTypeDef pwm_ch2_set = {TIM_OCMode_PWM1,TIM_OutputState_Enable,TIM_OutputNState_Disable,20000,TIM_OCPolarity_High,TIM_OCNPolarity_Low,TIM_OCIdleState_Set,TIM_OCNIdleState_Reset} ;
TIM_OCInitTypeDef pwm_ch3_set = {TIM_OCMode_PWM1,TIM_OutputState_Enable,TIM_OutputNState_Disable,20000,TIM_OCPolarity_High,TIM_OCNPolarity_Low,TIM_OCIdleState_Set,TIM_OCNIdleState_Reset} ;
TIM_OCInitTypeDef pwm_ch4_set = {TIM_OCMode_PWM1,TIM_OutputState_Enable,TIM_OutputNState_Disable,20000,TIM_OCPolarity_High,TIM_OCNPolarity_Low,TIM_OCIdleState_Set,TIM_OCNIdleState_Reset} ;


TIM_OCInitTypeDef buzzer_ch_set = {TIM_OCMode_PWM1,TIM_OutputState_Enable,TIM_OutputNState_Disable,20000,TIM_OCPolarity_High,TIM_OCNPolarity_Low,TIM_OCIdleState_Set,TIM_OCNIdleState_Reset} ;



GPIO_InitTypeDef pwm_pin1_set = {GPIO_Pin_6,GPIO_Speed_10MHz,GPIO_Mode_AF_PP} ;
GPIO_InitTypeDef pwm_pin2_set = {GPIO_Pin_7,GPIO_Speed_10MHz,GPIO_Mode_AF_PP} ;
GPIO_InitTypeDef pwm_pin3_set = {GPIO_Pin_8,GPIO_Speed_10MHz,GPIO_Mode_AF_PP} ;
GPIO_InitTypeDef pwm_pin4_set = {GPIO_Pin_9,GPIO_Speed_10MHz,GPIO_Mode_AF_PP} ;

GPIO_InitTypeDef buzzer_pin_set = {GPIO_Pin_1,GPIO_Speed_10MHz,GPIO_Mode_AF_PP} ;

void mcal_pwm_init(void)
{
	 GPIO_Init(GPIOB,&pwm_pin1_set) ;
	 GPIO_Init(GPIOB,&pwm_pin2_set) ;
	 GPIO_Init(GPIOB,&pwm_pin3_set) ;
	 GPIO_Init(GPIOB,&pwm_pin4_set) ;

	//	/* Timer Clocks */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE) ;

	TIM_OC1Init(TIM4, &pwm_ch1_set);
	TIM_OC2Init(TIM4, &pwm_ch2_set);
	TIM_OC3Init(TIM4, &pwm_ch3_set);
	TIM_OC4Init(TIM4, &pwm_ch4_set);

	TIM_PrescalerConfig(TIM4,7,TIM_PSCReloadMode_Immediate) ;
	TIM_CounterModeConfig(TIM4,TIM_CounterMode_Down)  ;

	 mcal_pwm_channel_enable(0);

}

void mcal_pwm_channel_set(mcal_pwm_t x_pwmInerface, mcal_pwmConfig_t *x_pwmConfig)
{
	uint16_t frequency  ;
	uint16_t dutycycle  ;

	frequency = ((1000000UL/(uint32_t)x_pwmConfig -> freq)) ;
	dutycycle = (((uint32_t)frequency * (uint32_t)x_pwmConfig -> duty )/ 100UL )   ;

	TIM_SetAutoreload(TIM4,  frequency);

	switch (x_pwmInerface)
	{
	case MCAL_PWM_0 : TIM_SetCompare1(TIM4, dutycycle) ; break;

	case MCAL_PWM_1 : TIM_SetCompare2(TIM4, dutycycle) ;  break;

	case MCAL_PWM_2 : TIM_SetCompare3(TIM4, dutycycle) ;  break;

	case MCAL_PWM_3 : TIM_SetCompare4(TIM4, dutycycle) ; break;
	}

}

void mcal_pwm_channelState_set(mcal_pwm_t x_pwmInerface, mcal_pwm_state_t x_state)
{
    switch (x_state)
    {
    case MCAL_PWM_START:

    	TIM_CCxCmd(TIM4, x_pwmInerface, TIM_CCx_Enable);

        break;
    case MCAL_PWM_STOP:

    	TIM_CCxCmd(TIM4, x_pwmInerface, TIM_CCx_Disable);

        break;
    default:
        break;
    }
}

void mcal_pwm_channel_enable(mcal_pwm_t x_pwmInerface)
{
	TIM_Cmd(TIM4, ENABLE);
}

void mcal_pwm_channel_disable(mcal_pwm_t x_pwmInerface)
{
	TIM_Cmd(TIM4, DISABLE);
}

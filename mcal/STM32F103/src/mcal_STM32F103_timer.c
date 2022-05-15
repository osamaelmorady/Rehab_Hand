#include "utils/STD_TYPES.h"
#include "mcal/mcal.h"
#include "core/STM32F103/stm32f10x_tim.h"
#include "core/STM32F103/MNVIC/MNVIC_Interface.h"

typedef struct
{
    uint16_t time1MS;
    uint16_t time1US;
} mcal_timer_timingConfig_t;

//#define TIMER_FREQUENCY (32000000.0f)
#define TIMER_FREQUENCY (8U)

#define MCAL_PRESCALER (8U)

mcal_timer_timingConfig_t gx_mcal_timerConfigStruct;
typedef struct
{
    uint16_t t16Channel;
    uint16_t t16ClkSrc;
    uint16_t t16ClkDiv;
    uint16_t t16Mode;
} TMR_Config_t;


#define TIMER_USED	TIM1
TIM_TimeBaseInitTypeDef tim5_set = {7,TIM_CounterMode_Up,1000,TIM_CKD_DIV1,0} ;

void mcal_timer_init(void)
{
	TIM_TimeBaseInit(TIMER_USED,&tim5_set) ;

	MNVIC_EnuInit()  ;
	MNVIC_EnuEnableIRQ(MNVIC_TIM1_UP_INT)  ;


  	gx_mcal_timerConfigStruct.time1MS = (TIMER_FREQUENCY / MCAL_PRESCALER)*1000U;
    gx_mcal_timerConfigStruct.time1US = (TIMER_FREQUENCY / MCAL_PRESCALER);
}

void mcal_timer_timerModeMS_init(mcal_timer_t *px_tb, uint32_t u32_timeMS)
{
    uint16_t u16_time;

    u16_time = (uint16_t)(gx_mcal_timerConfigStruct.time1MS * u32_timeMS);

    TIM_SetAutoreload(TIMER_USED, u16_time);

}

void mcal_IRtimer_init(mcal_timer_t *px_tb, uint32_t u32_timeMS)
{
	//	/* Timer Clocks */

}

void mcal_timer_timerModeUS_init(mcal_timer_t *px_tb, uint32_t u32_timeUS)
{
	uint16_t u16_time;

    u16_time = (uint16_t)(gx_mcal_timerConfigStruct.time1US * u32_timeUS);

    TIM_SetAutoreload(TIMER_USED, u16_time);
}

void mcal_timer_eventMode_init(mcal_timer_t *px_tb, mcal_gpio_t *px_portConfig, mcal_timer_eventEdgeConfig_t x_edge)
{

}

void mcal_timer_timerInterruptState_set(mcal_timer_t *px_tb, mcal_timer_intModeEnum_t x_intState)
{
    switch (x_intState)
    {
    case MCAL_TIMER_INT_ENABLE:
    	TIM_ITConfig(TIMER_USED, TIM_IT_Update, ENABLE);
    	MNVIC_EnuEnableIRQ(MNVIC_TIM1_UP_INT)  ;
        break;
    case MCAL_TIMER_INT_DISABLE:
    	TIM_ITConfig(TIMER_USED, TIM_IT_Update, DISABLE);
    	MNVIC_EnuDisableIRQ(MNVIC_TIM1_UP_INT)  ;
        break;
    default:
        break;
    }
}

void mcal_timer_timerChannel_enable(mcal_timer_t *px_tb)
{
}

void mcal_timer_timerChannel_disable(mcal_timer_t *px_tb)
{
}

void mcal_timer_timerState_set(mcal_timer_t *px_tb, mcal_timer_timerState_t x_state)
{
    switch (x_state)
    {
    case MCAL_TIMER_START:
    	TIM_Cmd(TIMER_USED, ENABLE);
        break;
    case MCAL_TIMER_STOP:
    	 TIM_Cmd(TIMER_USED, DISABLE);
        break;
    default:
        break;
    }
}
void mcal_timer_timerFlag_clear(mcal_timer_t *px_tb)
{
	TIM_ClearFlag(TIMER_USED, TIM_FLAG_Update);
}

// TODO: check
uint32_t mcal_timer_timerFlag_get(mcal_timer_t *px_tb)
{
	uint8_t flagstate = 0 ;

	TIM_GetFlagStatus(TIMER_USED, TIM_FLAG_Update);

    return flagstate;
}

// TODO: check
void mcal_timer_timerCounter_reset(mcal_timer_t *px_tb)
{
	TIM_Cmd(TIMER_USED, DISABLE);
}

uint32_t mcal_timer_timerCounter_get(mcal_timer_t *px_tb)
{
	uint16_t counterval = 0 ;

	counterval = TIM_GetCounter(TIMER_USED);

    return (uint32_t)counterval ;
}

#include "utils/STD_TYPES.h"
#include "mcal/mcal.h"

#include "core/STM32F103/stm32f10x_gpio.h"
#include "core/STM32F103/stm32f10x_exti.h"





void mcal_gpio_init(void)
{
    // TODO: has a dep on config.h file... do i need this??

	/* GPIOs Clocks */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE) ;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE) ;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE) ;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE) ;

}

void mcal_gpio_pin_init(mcal_gpio_t *px_gpio)
{
	GPIO_InitTypeDef gpio_set  ;
	EXTI_InitTypeDef exti_set ;

	gpio_set.GPIO_Mode = px_gpio->ioState  	;
	gpio_set.GPIO_Pin = px_gpio->pin  ;
	gpio_set.GPIO_Speed = GPIO_Speed_2MHz  ;

	GPIO_Init(px_gpio->port, &gpio_set);
	GPIO_WriteBit(px_gpio->port,px_gpio->pin,px_gpio->pinState)  ;

//	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0) ;
//
//	exti_set.EXTI_Line = px_gpio->pin  ;
//	exti_set.EXTI_Mode = EXTI_Mode_Interrupt ;
//	exti_set.EXTI_Trigger = px_gpio ->extIntPolarity ;
//	exti_set.EXTI_LineCmd = px_gpio -> extIntState  ;
//
//	EXTI_Init(&exti_set) ;


}

void mcal_gpio_pinState_set(mcal_gpio_t *px_gpio, mcal_gpio_stateEnum_t x_state)
{
	GPIO_WriteBit(px_gpio->port,px_gpio->pin,x_state)  ;
}

void mcal_gpio_portState_set(mcal_gpio_t *px_gpio, mcal_gpio_stateEnum_t x_state)
{
	// no thing
}

uint8_t mcal_gpio_pinState_get(mcal_gpio_t *px_gpio)
{
	uint8_t data = 0;

	data = GPIO_ReadInputDataBit(px_gpio->port,px_gpio->pin) ;

    return data;
}

uint8_t mcal_gpio_portState_get(mcal_gpio_t *px_gpio)
{
    uint8_t data = 0;

    return data;
}



void mcal_gpio_pinIOState_set(mcal_gpio_t *px_gpio, mcal_gpio_ioStateEnum_t x_ioState)
{
	GPIO_InitTypeDef gpio_set  ;

	gpio_set.GPIO_Mode = px_gpio->ioState  	;
	gpio_set.GPIO_Pin = px_gpio->pin  ;
	gpio_set.GPIO_Speed = GPIO_Speed_2MHz  ;

	GPIO_Init(px_gpio->port, &gpio_set);
}

void mcal_gpio_pinState_toggle(mcal_gpio_t *px_gpio)
{
	px_gpio -> pinState = ! (px_gpio -> pinState) ;

	MGPIO_EnuSetPinVal(px_gpio -> port , px_gpio -> pin , px_gpio -> pinState ) ;

}

void mcal_gpio_altFunction_set(mcal_gpio_t *px_gpio, mcal_gpio_alternateFnEnum_t x_func)
{

}

#include "app/inc/config.h"
#include "app/inc/bsp.h"
#include "app/inc/app.h"
#include "os/inc/os.h"
#include "utils/utils.h"
/************************************************************/
#include "driver/hw_timer/hw_timer.h"
/************************************************************/
#include "mcal/mcal.h"

#if 0
/************************************************************/
int main(void)
{
//	SF_Safeguard() ;

    bsp_clockConfig_set();

    bsp_interruptPriorities_set();

    hwTimer_init();
     //   os_runTime_init();
    os_scheduler_init();

    app_init();

    //    os_scheduler_task_add(os_runTime_update, NULL, APP_RUN_TIME_TASK_DELAY, APP_RUN_TIME_TASK_UPDATE_PERIOD_MS);

    os_scheduler_start();

    while (1)
    {
    }
}
/************************************************************/
#endif









/* GPIO */
#if 0
/***************************************************************************************************************/
uint32_t DELAY_COUNTER = 0 ;
#define DELAY_MS(REQ_DELAY) 	for(DELAY_COUNTER = 0 ; (DELAY_COUNTER*3)<(REQ_DELAY*1000UL) ; DELAY_COUNTER++ )	\
									{asm("NOP") ; }
/***************************************************************************************************************/
mcal_gpio_t gpio_c13 ={MCAL_GPIO_PORTC,MCAL_GPIO_PIN13,MCAL_GPIO_OUTPUT,MCAL_GPIO_HIGH,MCAL_GPIO_EXTINT_BOTH_EDGES,MCAL_GPIO_EXTINT_DISABLE} ;
mcal_gpio_t gpio_a2 ={MCAL_GPIO_PORTA,MCAL_GPIO_PIN2,MCAL_GPIO_OUTPUT,MCAL_GPIO_HIGH,MCAL_GPIO_EXTINT_BOTH_EDGES,MCAL_GPIO_EXTINT_DISABLE} ;
mcal_gpio_t gpio_a3 ={MCAL_GPIO_PORTA,MCAL_GPIO_PIN3,MCAL_GPIO_OUTPUT,MCAL_GPIO_HIGH,MCAL_GPIO_EXTINT_BOTH_EDGES,MCAL_GPIO_EXTINT_DISABLE} ;


/************************************************************/
int main(void)
{

	mcal_cg_init() ;
	mcal_gpio_init() ;

	mcal_gpio_pin_init(&gpio_a2)  ;
	mcal_gpio_pin_init(&gpio_a3)  ;
	mcal_gpio_pin_init(&gpio_c13)  ;


    while (1)
    {
    	mcal_gpio_pinState_set(&gpio_a2,MCAL_GPIO_HIGH)  ;
    	mcal_gpio_pinState_set(&gpio_a3,MCAL_GPIO_HIGH)  ;
    	mcal_gpio_pinState_set(&gpio_c13,MCAL_GPIO_HIGH)  ;

    	DELAY_MS(1000)  ;

    	mcal_gpio_pinState_set(&gpio_a2,MCAL_GPIO_LOW)  ;
    	mcal_gpio_pinState_set(&gpio_a3,MCAL_GPIO_LOW)  ;
    	mcal_gpio_pinState_set(&gpio_c13,MCAL_GPIO_LOW)  ;

    	DELAY_MS(1000)  ;
    }
}
/************************************************************/
#endif








/* EXTI */
#if 0
/***************************************************************************************************************/
uint32_t DELAY_COUNTER = 0 ;
#define DELAY_MS(REQ_DELAY) 	for(DELAY_COUNTER = 0 ; (DELAY_COUNTER*5/2)<(REQ_DELAY*1000UL) ; DELAY_COUNTER++ )	\
									{asm("NOP") ; }
/***************************************************************************************************************/
#include "core/STM32F103/system/include/cmsis/stm32f10x.h"
mcal_gpio_t gpio_c13  ;

/************************************************************/
int main(void)
{

	gpio_c13.port = MCAL_GPIO_PORTA ;
	gpio_c13.pin = MCAL_GPIO_PIN10 ;
	gpio_c13.ioState = MCAL_GPIO_INPUT ;
	gpio_c13.pinState = MCAL_GPIO_HIGH ;
	gpio_c13.extIntPolarity= MCAL_GPIO_EXTINT_FALLING_EDGE  ;
	gpio_c13.extIntState= MCAL_GPIO_EXTINT_ENABLE  ;


	mcal_cg_init() ;
	mcal_gpio_init() ;

	mcal_gpio_pin_init(&gpio_c13)  ;




    while (1)
    {
//    	mcal_gpio_pinState_set(&gpio_c13,MCAL_GPIO_HIGH)  ;
//
//    	DELAY_MS(1000)  ;
//
//    	mcal_gpio_pinState_set(&gpio_c13,MCAL_GPIO_LOW)  ;
//
    	DELAY_MS(1000)  ;
    }
}
/************************************************************/

EXTI0_IRQHandler()
{
	    	mcal_gpio_pinState_set(&gpio_c13,MCAL_GPIO_HIGH)  ;

	    	DELAY_MS(1000)  ;

	    	mcal_gpio_pinState_set(&gpio_c13,MCAL_GPIO_LOW)  ;

	    	DELAY_MS(1000)  ;

}


#endif


















/* Systick */
#if 0
/***************************************************************************************************************/
uint32_t DELAY_COUNTER = 0 ;
#define DELAY_MS(REQ_DELAY) 	for(DELAY_COUNTER = 0 ; (DELAY_COUNTER*5/2)<(REQ_DELAY*1000UL) ; DELAY_COUNTER++ )	\
									{asm("NOP") ; }
/***************************************************************************************************************/
#include "core/STM32F103/system/include/cmsis/stm32f10x.h"
static mcal_gpio_t gpio_A8  ;
/************************************************************/
int main(void)
{

	gpio_A8.port = MCAL_GPIO_PORTA ;
	gpio_A8.pin = MCAL_GPIO_PIN8 ;
	gpio_A8.ioState = MCAL_GPIO_OUTPUT ;
	gpio_A8.pinState = MCAL_GPIO_HIGH ;
	gpio_A8.extIntPolarity= MCAL_GPIO_EXTINT_FALLING_EDGE  ;
	gpio_A8.extIntState= MCAL_GPIO_EXTINT_DISABLE  ;


	mcal_cg_init() ;
	mcal_gpio_init() ;
	mcal_sysTick_init() ;


	mcal_gpio_pin_init(&gpio_A8)  ;


	mcal_sysTick_set(1)  ;

    while (1)
    {

//    	    	mcal_gpio_pinState_set(&gpio_A8,MCAL_GPIO_HIGH)  ;
//
//    	    	DELAY_MS(1000)  ;
//
//    	    	mcal_gpio_pinState_set(&gpio_A8,MCAL_GPIO_LOW)  ;
//
//    	    	DELAY_MS(1000)  ;

    }
}
/************************************************************/

#endif










/* PWM */
#if 0
/***************************************************************************************************************/
uint32_t DELAY_COUNTER = 0 ;
#define DELAY_MS(REQ_DELAY) 	for(DELAY_COUNTER = 0 ; (DELAY_COUNTER*5/2)<(REQ_DELAY*1000UL) ; DELAY_COUNTER++ )	\
									{asm("NOP") ; }
/***************************************************************************************************************/
#include "core/STM32F103/system/include/cmsis/stm32f10x.h"
static mcal_gpio_t gpio_A8  ;
static mcal_pwmConfig_t pwm_a8 ;
/************************************************************/
int main(void)
{

	mcal_cg_init() ;
	mcal_gpio_init() ;
	mcal_pwm_init() ;

	pwm_a8.freq=4000 ;
	pwm_a8.duty=50 ;
	mcal_pwm_channel_set(MCAL_PWM_0,&pwm_a8)  ;
	mcal_pwm_channel_set(MCAL_PWM_1,&pwm_a8)  ;
	mcal_pwm_channel_set(MCAL_PWM_2,&pwm_a8)  ;
	mcal_pwm_channel_set(MCAL_PWM_3,&pwm_a8)  ;
	mcal_pwm_channelState_set(MCAL_PWM_0, ENABLE) ;
	mcal_pwm_channelState_set(MCAL_PWM_1, ENABLE) ;
	mcal_pwm_channelState_set(MCAL_PWM_2, ENABLE) ;
	mcal_pwm_channelState_set(MCAL_PWM_3, ENABLE) ;



    while (1)
    {
    	for (uint8_t counter=0;counter<100;counter++)
    	{
    		pwm_a8.duty=counter ;
    		mcal_pwm_channel_set(MCAL_PWM_0,&pwm_a8)  ;
    		mcal_pwm_channel_set(MCAL_PWM_1,&pwm_a8)  ;
    		mcal_pwm_channel_set(MCAL_PWM_2,&pwm_a8)  ;
    		mcal_pwm_channel_set(MCAL_PWM_3,&pwm_a8)  ;
    		DELAY_MS(50)  ;
    	}



    }
}
/************************************************************/

#endif













/* Uart send */
#if 0
/***************************************************************************************************************/
static uint32_t DELAY_COUNTER = 0 ;
#define DELAY_MS(REQ_DELAY) 	for(DELAY_COUNTER = 0 ; (DELAY_COUNTER*5/2)<(REQ_DELAY*1000UL) ; DELAY_COUNTER++ )	\
									{asm("NOP") ; }
/***************************************************************************************************************/
#include "core/STM32F103/system/include/cmsis/stm32f10x.h"
mcal_uartConfig_t uart_set  ;
/************************************************************/
int main(void)
{


	mcal_cg_init() ;
	mcal_gpio_init() ;
	mcal_uart_init() ;

	uart_set.baudRate = 9600 ;
	uart_set.mode = MCAL_UART_DIR_TX ;

	mcal_uart_channel_set(0, &uart_set ) ;

    while (1)
    {
//    	for (volatile uint8_t counter=0 ;counter<28;counter++)
//    	{
//    		mcal_uart_data_put(0,'A'+counter)  ;
//
//    		DELAY_MS(10) ;
//    	}


    	mcal_uart_string_put(0,"Osama ElMorady")  ;

//    	DELAY_MS(10) ;
    }
}
/************************************************************/

#endif







/* Uart Receive */
#if 0
/***************************************************************************************************************/
uint32_t DELAY_COUNTER = 0 ;
#define DELAY_MS(REQ_DELAY) 	for(DELAY_COUNTER = 0 ; (DELAY_COUNTER*5/2)<(REQ_DELAY*1000UL) ; DELAY_COUNTER++ )	\
									{asm("NOP") ; }
/***************************************************************************************************************/
#include "core/STM32F103/system/include/cmsis/stm32f10x.h"

mcal_gpio_t gpio_c13 ={MCAL_GPIO_PORTC,MCAL_GPIO_PIN13,MCAL_GPIO_OUTPUT,MCAL_GPIO_HIGH,MCAL_GPIO_EXTINT_BOTH_EDGES,MCAL_GPIO_EXTINT_DISABLE} ;
mcal_uartConfig_t uart_set  ;
static volatile uint8_t data = 1 ;
/************************************************************/
int main(void)
{
	mcal_cg_init() ;
	mcal_gpio_init() ;
	mcal_uart_init() ;

	uart_set.baudRate = 9600 ;
	uart_set.mode = MCAL_UART_DIR_TX ;
	mcal_uart_channel_set(MCAL_UART_UART1, &uart_set ) ;

	uart_set.baudRate = 9600 ;
	uart_set.mode = MCAL_UART_DIR_RX ;
	mcal_uart_channel_set(MCAL_UART_UART2, &uart_set ) ;

//	uart_set.baudRate = 9600 ;
//	uart_set.mode = MCAL_UART_DIR_TX ;
//	mcal_uart_channel_set(MCAL_UART_UART3, &uart_set ) ;



//	mcal_gpio_pin_init(&gpio_c13)  ;





    while (1)
    {

    	mcal_uart_data_put(MCAL_UART_UART1,'A')  ;
    	DELAY_MS(200) ;


//    	mcal_uart_string_put(MCAL_UART_UART1,"___USART1___")  ;
//    	mcal_uart_string_put(MCAL_UART_UART2,"___USART2___")  ;
//    	mcal_uart_string_put(MCAL_UART_UART3,"___USART3___")  ;

//    	uart_set.mode = MCAL_UART_DIR_RX ;
//    	mcal_uart_channel_set(0, &uart_set ) ;
//    	data = mcal_uart_data_get(0)  ;
//    	DELAY_MS(1) ;


//    	uart_set.mode = MCAL_UART_DIR_TX ;
//    	mcal_uart_channel_set(MCAL_UART_UART2, &uart_set ) ;
//    	mcal_uart_data_put(0,data)  ;
//    	DELAY_MS(1) ;

//
//    	if (data=='A')
//    	{
//    		mcal_gpio_pinState_set(&gpio_c13,MCAL_GPIO_HIGH)  ;
//    		data = 0 ;
//    	}
//    	else if (data=='B')
//    	{
//    		mcal_gpio_pinState_set(&gpio_c13,MCAL_GPIO_LOW)  ;
//    		data = 1 ;
//    	}
//
//    	DELAY_MS(1000)  ;

    }
}
/************************************************************/
static volatile uint8_t u8_data =0x00 ;
void USART1_IRQHandler(void)
{
	if (USART_GetITStatus(USART1,USART_IT_RXNE)==SET)
	{
		u8_data = USART_ReceiveData(USART1);

		USART_ClearFlag(USART1,USART_FLAG_RXNE)  ;

	}

}
void USART2_IRQHandler(void)
{
	if (USART_GetITStatus(USART2,USART_IT_RXNE)==SET)
	{
		u8_data = USART_ReceiveData(USART2);

		USART_ClearFlag(USART2,USART_FLAG_RXNE)  ;

	}

}

void USART3_IRQHandler(void)
{
	if (USART_GetITStatus(USART3,USART_IT_RXNE)==SET)
	{
		u8_data = USART_ReceiveData(USART3);

		USART_ClearFlag(USART3,USART_FLAG_RXNE)  ;

	}

}











#endif















/* Blutooth */
#if 0
/***************************************************************************************************************/
uint32_t DELAY_COUNTER = 0 ;
#define DELAY_MS(REQ_DELAY) 	for(DELAY_COUNTER = 0 ; (DELAY_COUNTER*5/2)<(REQ_DELAY*1000UL) ; DELAY_COUNTER++ )	\
									{asm("NOP") ; }
/***************************************************************************************************************/
#include "core/STM32F103/system/include/cmsis/stm32f10x.h"

mcal_gpio_t gpio_a0 ={MCAL_GPIO_PORTA,MCAL_GPIO_PIN0,MCAL_GPIO_OUTPUT,MCAL_GPIO_HIGH,MCAL_GPIO_EXTINT_BOTH_EDGES,MCAL_GPIO_EXTINT_DISABLE} ;
mcal_uartConfig_t uart_set  ;
static volatile uint8_t data = 1 ;
/************************************************************/
int main(void)
{
	mcal_cg_init() ;
	mcal_gpio_init() ;
	mcal_uart_init() ;

	mcal_gpio_pin_init(&gpio_a0)  ;
	mcal_gpio_pinState_set(&gpio_a0,MCAL_GPIO_HIGH)  ;

	DELAY_MS(1000) ;

	uart_set.baudRate = 38400 ;
	uart_set.mode = MCAL_UART_DIR_TX ;
	mcal_uart_channel_set(MCAL_UART_UART1, &uart_set ) ;

	mcal_uart_string_put(MCAL_UART_UART1,"AT+RESET")  ;

	mcal_gpio_pinState_set(&gpio_a0,MCAL_GPIO_LOW)  ;

	DELAY_MS(2000) ;

	uart_set.baudRate = 9600 ;
	uart_set.mode = MCAL_UART_DIR_TX ;
	mcal_uart_channel_set(MCAL_UART_UART1, &uart_set ) ;

	mcal_uart_string_put(MCAL_UART_UART1,"12345")  ;




    while (1)
    {

//    	mcal_uart_string_put(MCAL_UART_UART1,"Hello World \n\r")  ;

    	DELAY_MS(1000) ;



    }
}
/************************************************************/
static volatile uint8_t u8_data =0x00 ;
void USART1_IRQHandler(void)
{
	if (USART_GetITStatus(USART1,USART_IT_RXNE)==SET)
	{
		u8_data = USART_ReceiveData(USART1);

		USART_ClearFlag(USART1,USART_FLAG_RXNE)  ;

	}

}
void USART2_IRQHandler(void)
{
	if (USART_GetITStatus(USART2,USART_IT_RXNE)==SET)
	{
		u8_data = USART_ReceiveData(USART2);

		USART_ClearFlag(USART2,USART_FLAG_RXNE)  ;

	}

}

void USART3_IRQHandler(void)
{
	if (USART_GetITStatus(USART3,USART_IT_RXNE)==SET)
	{
		u8_data = USART_ReceiveData(USART3);

		USART_ClearFlag(USART3,USART_FLAG_RXNE)  ;

	}

}











#endif


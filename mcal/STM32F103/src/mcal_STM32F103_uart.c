#include "utils/STD_TYPES.h"
#include "mcal/mcal.h"
#include <stdlib.h>
#include "core/STM32F103/stm32f10x_gpio.h"
#include "core/STM32F103/stm32f10x_usart.h"
#include "core/STM32F103/MNVIC/MNVIC_Interface.h"



/***************************************************************************************************************/
static uint32_t DELAY_COUNTER = 0 ;
#define DELAY_uS(REQ_DELAY) 	for(DELAY_COUNTER = 0 ; (DELAY_COUNTER*3)<(REQ_DELAY) ; DELAY_COUNTER++ )	\
									{asm("NOP") ; }
/***************************************************************************************************************/



static USART_ClockInitTypeDef uart_clk_set ;

static USART_InitTypeDef  uart_set = {9600,USART_WordLength_8b,USART_StopBits_1,USART_Parity_No ,USART_Mode_Tx,USART_HardwareFlowControl_None }  ;


static GPIO_InitTypeDef Tx1_pin_set = {GPIO_Pin_9,GPIO_Speed_2MHz,GPIO_Mode_AF_PP} ;
static GPIO_InitTypeDef RX1_pin_set = {GPIO_Pin_10,GPIO_Speed_2MHz,GPIO_Mode_IN_FLOATING} ;


static GPIO_InitTypeDef Tx2_pin_set = {GPIO_Pin_2,GPIO_Speed_2MHz,GPIO_Mode_AF_PP} ;
static GPIO_InitTypeDef RX2_pin_set = {GPIO_Pin_3,GPIO_Speed_2MHz,GPIO_Mode_IN_FLOATING} ;


static GPIO_InitTypeDef Tx3_pin_set = {GPIO_Pin_10,GPIO_Speed_2MHz,GPIO_Mode_AF_PP} ;
static GPIO_InitTypeDef RX3_pin_set = {GPIO_Pin_11,GPIO_Speed_2MHz,GPIO_Mode_IN_FLOATING} ;

void mcal_uart_init(void)
{
		 GPIO_Init(GPIOA,&Tx1_pin_set) ;
		 GPIO_Init(GPIOA,&RX1_pin_set) ;
//		 GPIO_Init(GPIOA,&Tx2_pin_set) ;
//		 GPIO_Init(GPIOA,&RX2_pin_set) ;
//		 GPIO_Init(GPIOB,&Tx3_pin_set) ;
//		 GPIO_Init(GPIOB,&RX3_pin_set) ;
}

void mcal_uart_channel_set(mcal_uart_t x_uart, mcal_uartConfig_t *px_uartConfig)
{
	switch(x_uart)
	{
	case MCAL_UART_UART1 :

		USART_Cmd(USART1, DISABLE);

		uart_set . USART_BaudRate = px_uartConfig->baudRate  ;
		uart_set . USART_Mode = px_uartConfig->mode  ;


		USART_Init(USART1,&uart_set ) ;
		USART_SetPrescaler(USART1, 8);

		USART_ClearFlag(USART1,USART_FLAG_RXNE)  ;

		USART_ITConfig(USART1,USART_IT_RXNE,ENABLE)  ;

		MNVIC_EnuEnableIRQ(MNVIC_USART1_INT)  ;

		USART_Cmd(USART1, ENABLE);

	break;
	case  MCAL_UART_UART2 :

		USART_Cmd(USART2, DISABLE);

		uart_set . USART_BaudRate = px_uartConfig->baudRate  ;
		uart_set . USART_Mode = px_uartConfig->mode  ;


		USART_Init(USART2,&uart_set ) ;
		USART_SetPrescaler(USART2, 8);

		USART_ClearFlag(USART2,USART_FLAG_RXNE)  ;

		USART_ITConfig(USART2,USART_IT_RXNE,ENABLE)  ;

		MNVIC_EnuEnableIRQ(MNVIC_USART2_INT)  ;

		USART_Cmd(USART2, ENABLE);

	break;
	case MCAL_UART_UART3 :

		USART_Cmd(USART3, DISABLE);

		uart_set . USART_BaudRate = px_uartConfig->baudRate  ;
		uart_set . USART_Mode = px_uartConfig->mode  ;
		//	uart_set . USART_WordLength = USART_WordLength_8b  ;
		//	uart_set . USART_StopBits = USART_StopBits_1;
		//	uart_set . USART_HardwareFlowControl = USART_HardwareFlowControl_None ;
		//	uart_set . USART_Parity = USART_Parity_No ;

		USART_Init(USART3,&uart_set ) ;
		USART_SetPrescaler(USART3, 8);

		USART_ClearFlag(USART3,USART_FLAG_RXNE)  ;
		//		USART_ITConfig(USART1,USART_IT_TC,ENABLE)  ;
		//	USART_ITConfig(USART_USED,USART_IT_TXE,ENABLE)  ;

		MNVIC_EnuEnableIRQ(MNVIC_USART3_INT)  ;

		USART_ITConfig(USART3,USART_IT_RXNE,ENABLE)  ;

		/* Sync */
	//	uart_clk_set.USART_CPHA = USART_CPHA_1Edge ;
	//	uart_clk_set.USART_CPOL = USART_CPOL_Low ;
	//	uart_clk_set.USART_Clock = USART_Clock_Enable ;
	//	uart_clk_set.USART_LastBit = USART_LastBit_Enable ;
	//	USART_ClockInit(USART_USED,&uart_clk_set) ;

		USART_Cmd(USART3, ENABLE);
	break ;
	}

}

void mcal_uart_data_put(mcal_uart_t x_uart, uint8_t u8_data)
{
	switch(x_uart)
	{
	case MCAL_UART_UART1 :

		USART_SendData(USART1, u8_data);

		/* Loop if not empty */
		while (USART_GetFlagStatus(USART1,USART_FLAG_TXE)!= SET) {asm("nop");}
		USART_ClearFlag(USART1,USART_FLAG_TC)  ;

		break;
	case  MCAL_UART_UART2 :

		USART_SendData(USART2, u8_data);

		/* Loop if not empty */
		while (USART_GetFlagStatus(USART2,USART_FLAG_TXE)!= SET) {asm("nop");}
		USART_ClearFlag(USART2,USART_FLAG_TC)  ;

		break;
	case MCAL_UART_UART3 :

		USART_SendData(USART3, u8_data);

		/* Loop if not empty */
		while (USART_GetFlagStatus(USART3,USART_FLAG_TXE)!= SET) {asm("nop");}
		USART_ClearFlag(USART3,USART_FLAG_TC)  ;

		break;
	}


}

uint8_t mcal_uart_data_get(mcal_uart_t  x_uart)
{
    uint8_t u8_data;

	switch(x_uart)
	{
	case MCAL_UART_UART1 :

		/* Loop if not empty */
		while (USART_GetFlagStatus(USART1,USART_FLAG_RXNE)== RESET) {asm("nop");}

	    u8_data = USART_ReceiveData(USART1);

	    USART_ClearFlag(USART1,USART_FLAG_RXNE)  ;

		break;
	case  MCAL_UART_UART2 :

		/* Loop if not empty */
		while (USART_GetFlagStatus(USART2,USART_FLAG_RXNE)== RESET) {asm("nop");}

	    u8_data = USART_ReceiveData(USART2);

	    USART_ClearFlag(USART2,USART_FLAG_RXNE)  ;

		break;
	case MCAL_UART_UART3 :

		/* Loop if not empty */
		while (USART_GetFlagStatus(USART3,USART_FLAG_RXNE)== RESET) {asm("nop");}

	    u8_data = USART_ReceiveData(USART3);

	    USART_ClearFlag(USART3,USART_FLAG_RXNE)  ;

		break;
	}



    return u8_data;
}

void mcal_uart_dma_init(void)
{
    // not available in this mcu
}

uint32_t mcal_uart_dma_set(uint8_t *pu8_txBuffer, uint32_t u32_length, uint32_t u32_channel)
{
    // not available in this mcu
    return 0xffffffff;
}

uint32_t mcal_uart_dma_get(uint8_t *pu8_rxBuffer, uint32_t u32_length, uint32_t u32_channel)
{
    // not available in this mcu
    return 0xffffffff;
}

void mcal_uart_string_put(mcal_uart_t x_uart, uint8_t *pu8_ptr)
{
	uint8_t counter ;

	switch(x_uart)
	{
	case MCAL_UART_UART1 :

		for (counter=0 ; pu8_ptr[counter]!='\0' ; counter++)
		{
			mcal_uart_data_put(MCAL_UART_UART1,pu8_ptr[counter])  ;
		}

		break;
	case  MCAL_UART_UART2 :

		for (counter=0 ; pu8_ptr[counter]!='\0' ; counter++)
		{
			mcal_uart_data_put(MCAL_UART_UART2,pu8_ptr[counter])  ;
		}

		break;
	case MCAL_UART_UART3 :

		for (counter=0 ; pu8_ptr[counter]!='\0' ; counter++)
		{
			mcal_uart_data_put(MCAL_UART_UART3,pu8_ptr[counter])  ;
		}

		break;
	}


}

void mcal_uart_string_get(mcal_uart_t x_uart, uint8_t *pu8_ptr)
{
}

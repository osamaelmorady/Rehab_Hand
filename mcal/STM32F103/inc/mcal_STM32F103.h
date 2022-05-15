#ifndef MCAL_C17M24_H_
#define MCAL_C17M24_H_

#include "app/inc/def.h"

#define MCAL_GLOBAL_INTERRUPTS_DISABLE()
#define MCAL_GLOBAL_INTERRUPTS_ENABLE()

/******************************************************************************/
// gpio

typedef uint16_t mcal_gpio_portEnum_t;
#define MCAL_GPIO_PORTA (GPIO_TypeDef *)GPIOA
#define MCAL_GPIO_PORTB (GPIO_TypeDef *)GPIOB
#define MCAL_GPIO_PORTC (GPIO_TypeDef *)GPIOC
#define MCAL_GPIO_PORTD 3
#define MCAL_GPIO_PORTE 4
#define MCAL_GPIO_PORTF 5
#define MCAL_GPIO_PORTG 6
#define MCAL_GPIO_PORTH 7
#define MCAL_GPIO_PORTI 8
#define MCAL_GPIO_PORTJ 9
#define MCAL_GPIO_PORTK 10
#define MCAL_GPIO_PORTL 11
#define MCAL_GPIO_PORTM 12
#define MCAL_GPIO_PORTN 13
#define MCAL_GPIO_PORTO 14
#define MCAL_GPIO_PORTP 15



typedef uint16_t mcal_gpio_pinEnum_t;
#define MCAL_GPIO_PIN0 GPIO_Pin_0
#define MCAL_GPIO_PIN1 GPIO_Pin_1
#define MCAL_GPIO_PIN2 GPIO_Pin_2
#define MCAL_GPIO_PIN3 GPIO_Pin_3
#define MCAL_GPIO_PIN4 GPIO_Pin_4
#define MCAL_GPIO_PIN5 GPIO_Pin_5
#define MCAL_GPIO_PIN6 GPIO_Pin_6
#define MCAL_GPIO_PIN7 GPIO_Pin_7
#define MCAL_GPIO_PIN8 GPIO_Pin_8
#define MCAL_GPIO_PIN9 GPIO_Pin_9
#define MCAL_GPIO_PIN10 GPIO_Pin_10
#define MCAL_GPIO_PIN11 GPIO_Pin_11
#define MCAL_GPIO_PIN12 GPIO_Pin_12
#define MCAL_GPIO_PIN13 GPIO_Pin_13
#define MCAL_GPIO_PIN14 GPIO_Pin_14
#define MCAL_GPIO_PIN15 GPIO_Pin_15
#define MCAL_GPIO_PIN_ALL GPIO_Pin_All



typedef uint16_t mcal_gpio_ioStateEnum_t;
#define MCAL_GPIO_OUTPUT GPIO_Mode_Out_PP
#define MCAL_GPIO_INPUT GPIO_Mode_IPU
#define MCAL_GPIO_NONE GPIO_Mode_AIN

typedef uint8_t mcal_gpio_stateEnum_t;
#define MCAL_GPIO_LOW Bit_RESET
#define MCAL_GPIO_HIGH Bit_SET

typedef uint8_t mcal_gpio_extIntPolarityEnum_t;
#define MCAL_GPIO_EXTINT_NONE (0)
#define MCAL_GPIO_EXTINT_FALLING_EDGE (EXTI_Trigger_Falling)
#define MCAL_GPIO_EXTINT_RISING_EDGE (EXTI_Trigger_Rising)
#define MCAL_GPIO_EXTINT_BOTH_EDGES (EXTI_Trigger_Rising_Falling)


typedef uint8_t mcal_gpio_extIntStateEnum_t;
#define MCAL_GPIO_EXTINT_ENABLE (ENABLE)
#define MCAL_GPIO_EXTINT_DISABLE (DISABLE)

typedef enum
{
    MCAL_GPIO_NORMAL,
    MCAL_GPIO_ALT_FUNC_1,
    MCAL_GPIO_ALT_FUNC_2,
    MCAL_GPIO_ALT_FUNC_3
} mcal_gpio_alternateFnEnum_t;

typedef enum
{
	EXT_INT_LEVEL_LOW ,
	EXT_INT_FALLING_EDGE,
    EXT_INT_RISING_EDGE,
    EXT_INT_LEVEL_TOGGLE,

} mcal_extIntPolarityEnum_t;

typedef struct
{
	GPIO_TypeDef * port;
    mcal_gpio_pinEnum_t pin;
    mcal_gpio_ioStateEnum_t ioState;
    mcal_gpio_stateEnum_t pinState;
    mcal_gpio_extIntStateEnum_t extIntState;
    mcal_gpio_extIntPolarityEnum_t extIntPolarity;
} mcal_gpio_t;

void mcal_gpio_init(void);
void mcal_gpio_pin_init(mcal_gpio_t *px_gpio);
void mcal_gpio_pinState_set(mcal_gpio_t *px_gpio, mcal_gpio_stateEnum_t u8_state);
void mcal_gpio_portState_set(mcal_gpio_t *px_gpio, mcal_gpio_stateEnum_t x_state);
void mcal_gpio_pinIOState_set(mcal_gpio_t *px_gpio, mcal_gpio_ioStateEnum_t x_ioState);
void mcal_gpio_pinState_toggle(mcal_gpio_t *px_gpio);
uint8_t mcal_gpio_pinState_get(mcal_gpio_t *px_gpio);
uint8_t mcal_gpio_portState_get(mcal_gpio_t *px_gpio);
void mcal_gpio_altFunction_set(mcal_gpio_t *px_gpio, mcal_gpio_alternateFnEnum_t x_func);

/********************************************************************************/
// clock generator

void mcal_cg_init(void);
void mcal_cg_system_set(void);
// void mcal_cg_WDTSystem_set(CG_DivideLevel DivideFgearFromFc);
// void mcal_cg_normalToStopMode_set(void);

/********************************************************************************/
// wdt

#define MCAL_WDT_RESET_TIME_L0 (0x01)   // 1 msec
#define MCAL_WDT_RESET_TIME_L1 (0x0b)   // 5 msec
#define MCAL_WDT_RESET_TIME_L2 (0x23)   // 15 msec
#define MCAL_WDT_RESET_TIME_L3 (0xf3)   // 100 msec
#define MCAL_WDT_RESET_TIME_L4 (0x4c3)  // 500 msec
#define MCAL_WDT_RESET_TIME_L5 (0x2624) // 4 sec

void mcal_wdt_init(void);
void mcal_wdt_set(uint32_t resetTime);
void mcal_wdt_feed(void);
void mcal_wdt_disable(void);
void mcal_wdt_enable(void);
// void mcal_wdt_clockConfig_set(CG_DivideLevel DivideFgearFromFc, uint32_t resetTime);

/********************************************************************************/
// systick

void mcal_sysTick_init(void);
void mcal_sysTick_set(uint32_t u32_tickms);
void mcal_sysTick_resume(void);

/********************************************************************************/
// uart

typedef uint32_t mcal_uart_t;
#define MCAL_UART_UART0 (0)
#define MCAL_UART_UART1 (1)
#define MCAL_UART_UART2 (2)
#define MCAL_UART_UART3 (3)

typedef uint32_t mcal_uartDataBitsEnum_t;
#define MCAL_UART_DATA_BITS_7 (0)
#define MCAL_UART_DATA_BITS_8 (USART_WordLength_8b)
#define MCAL_UART_DATA_BITS_9 (USART_WordLength_9b)

typedef uint32_t mcal_uartStopBitsEnum_t;
#define MCAL_UART_STOP_BITS_1 (USART_StopBits_1)
#define MCAL_UART_STOP_BITS_2 (USART_StopBits_2)

typedef uint32_t mcal_uartParityEnum_t;
#define MCAL_UART_PARITY_NO (USART_Parity_No)
#define MCAL_UART_PARITY_EVEN (USART_Parity_Even)
#define MCAL_UART_PARITY_ODD (USART_Parity_Odd)

typedef uint32_t mcal_uartModeEnum_t;
#define MCAL_UART_MODE_RX (USART_Mode_Rx)
#define MCAL_UART_MODE_TX (USART_Mode_Tx)
#define MCAL_UART_MODE_TXRX (2)

typedef uint32_t mcal_uartFlowControlEnum_t;
#define MCAL_UART_FLOW_CTRL_NONE (UART_NONE_FLOW_CTRL)

typedef uint32_t mcal_uartDirectionEnum_t;
#define MCAL_UART_DIR_RX (USART_Mode_Rx)
#define MCAL_UART_DIR_TX (USART_Mode_Tx)

typedef struct
{
    mcal_gpio_t txPin;
    mcal_gpio_t rxPin;
    uint32_t baudRate;
    mcal_uartDataBitsEnum_t dataBits;
    mcal_uartStopBitsEnum_t stopBits;
    mcal_uartParityEnum_t parity;
    mcal_uartModeEnum_t mode;
    mcal_uartFlowControlEnum_t flowControl;
    uint8_t rxInterruptEN;
    uint8_t chainInterval;
} mcal_uartConfig_t;

void mcal_uart_init(void);
void mcal_uart_channel_set(mcal_uart_t x_uart, mcal_uartConfig_t *px_uartConfig);
void mcal_uart_data_put(mcal_uart_t x_uart, uint8_t u8_data);
uint8_t mcal_uart_data_get(mcal_uart_t x_uart);
void mcal_uart_dma_init(void);
uint32_t mcal_uart_dma_set(uint8_t *pu8_txBuffer, uint32_t u32_length, uint32_t u32_channel);
uint32_t mcal_uart_dma_get(uint8_t *pu8_rxBuffer, uint32_t u32_length, uint32_t u32_channel);
void mcal_uart_string_put(mcal_uart_t x_uart, uint8_t *pu8_ptr);
void mcal_uart_string_get(mcal_uart_t x_uart, uint8_t *pu8_ptr);

/********************************************************************************/
// timer

typedef uint16_t mcal_timer_t;
#define MCAL_TIMER_0 0
#define MCAL_TIMER_1 1
#define MCAL_TIMER_2 2
#define MCAL_TIMER_3 3
#define MCAL_TIMER_4 4
#define MCAL_TIMER_5 5
#define MCAL_TIMER_6 6
#define MCAL_TIMER_7 7

typedef uint8_t mcal_timer_timerState_t;
#define MCAL_TIMER_START 1
#define MCAL_TIMER_STOP 0

typedef uint8_t mcal_timer_eventEdgeConfig_t;
#define MCAL_TIMER_EDGE_RISING TRG_RISING_EDGE
#define MCAL_TIMER_EDGE_FALLING TRG_FALLING_EDGE

#define TRG_RISING_EDGE 	0
#define TRG_FALLING_EDGE	1

typedef enum
{
    MCAL_TIMER_INT_ENABLE = 1,
    MCAL_TIMER_INT_DISABLE = 0
} mcal_timer_intModeEnum_t;

void mcal_timer_init(void);
void mcal_timer_timerModeMS_init(mcal_timer_t *px_tb, uint32_t u32_timeMS);
void mcal_timer_timerModeUS_init(mcal_timer_t *px_tb, uint32_t u32_timeUS);
void mcal_timer_eventMode_init(mcal_timer_t *px_tb, mcal_gpio_t *px_portConfig, mcal_timer_eventEdgeConfig_t x_edge);
void mcal_timer_timerInterruptState_set(mcal_timer_t *px_tb, mcal_timer_intModeEnum_t x_intState);
void mcal_timer_timerChannel_enable(mcal_timer_t *px_tb);
void mcal_timer_timerChannel_disable(mcal_timer_t *px_tb);
void mcal_timer_timerState_set(mcal_timer_t *px_tb, mcal_timer_timerState_t x_state);
void mcal_timer_timerFlag_clear(mcal_timer_t *px_tb);
uint32_t mcal_timer_timerFlag_get(mcal_timer_t *px_tb);
void mcal_timer_timerCounter_reset(mcal_timer_t *px_tb);
uint32_t mcal_timer_timerCounter_get(mcal_timer_t *px_tb);
void mcal_timer_softWareCap(mcal_timer_t *px_tb);
void mcal_IRtimer_init(mcal_timer_t *px_tb, uint32_t u32_timeMS);
/********************************************************************************/
// pwm

typedef uint16_t mcal_pwm_t;
#define MCAL_PWM_0 TIM_Channel_1
#define MCAL_PWM_1 TIM_Channel_2
#define MCAL_PWM_2 TIM_Channel_3
#define MCAL_PWM_3 TIM_Channel_4
#define MCAL_PWM_4 4
#define MCAL_PWM_5 5
#define MCAL_PWM_6 6
#define MCAL_PWM_7 7

typedef uint32_t mcal_pwm_state_t;
#define MCAL_PWM_START 1
#define MCAL_PWM_STOP 0

typedef uint32_t mcal_pwm_polarity_t;
#define MCAL_PWM_POLARITY_ACTIVE_LOW TIM_OCPolarity_Low
#define MCAL_PWM_POLARITY_ACTIVE_HIGH TIM_OCPolarity_High

typedef struct
{
    mcal_gpio_portEnum_t port;
    mcal_gpio_pinEnum_t pin;
    uint32_t freq;
    uint32_t duty;
    mcal_pwm_polarity_t polarity ;
    uint8_t type;
    uint8_t channel;
} mcal_pwmConfig_t;


void mcal_pwm_init(void);
void mcal_pwm_channel_set(mcal_pwm_t x_pwmInerface, mcal_pwmConfig_t *x_pwmConfig);
void mcal_pwm_channelState_set(mcal_pwm_t x_pwmInerface, mcal_pwm_state_t x_state);
void mcal_pwm_channel_enable(mcal_pwm_t x_pwmInerface);
void mcal_pwm_channel_disable(mcal_pwm_t x_pwmInerface);

/********************************************************************************/
// adc
typedef enum
{
    MCAL_ADC_CH0 = 0U,
    MCAL_ADC_CH1 = 1U,
    MCAL_ADC_CH2 = 2U,
    MCAL_ADC_CH3 = 3U,
    MCAL_ADC_CH4 = 4U,
    MCAL_ADC_CH5 = 5U,
    MCAL_ADC_CH6,
    MCAL_ADC_CH7,
    MCAL_ADC_CH8,
    MCAL_ADC_CH9,
    MCAL_ADC_CH10,
    MCAL_ADC_CH11,
    MCAL_ADC_CH12,
    MCAL_ADC_CH13,
    MCAL_ADC_CH14,
    MCAL_ADC_CH15,
    MCAL_ADC_CH16,
    MCAL_ADC_CH17,
    MCAL_ADC_CH18,
    MCAL_ADC_CH19,
    MCAL_ADC_CH20,
	MCAL_ADC_CH21,
	MCAL_ADC_CH22,
	MCAL_ADC_CH23,
	MCAL_ADC_CH24
} mcal_adc_chEnum_t;

typedef uint8_t mcal_adc_blkEnum_t;
#define MCAL_ADC_BLK_A 0
#define MCAL_ADC_BLK_B 1

void mcal_adc_init(void);
void mcal_adc_set(mcal_adc_blkEnum_t x_adcBlock);
void mcal_adc_channel_set(mcal_adc_blkEnum_t x_adcBlock, mcal_adc_chEnum_t x_adcCh);
void mcal_adc_conversion_start(mcal_adc_blkEnum_t x_adcBlock, mcal_adc_chEnum_t x_adcCh);
uint32_t mcal_adc_conversionResult_get(mcal_adc_blkEnum_t x_adcBlock, mcal_adc_chEnum_t x_adcCh);
uint32_t mcal_adc_conversionStatus_get(mcal_adc_blkEnum_t x_adcBlock, mcal_adc_chEnum_t x_adcCh);
void mcal_adc_flag_clear(mcal_adc_blkEnum_t x_adcBlock, mcal_adc_chEnum_t x_adcCh);


void mcal_i2c_init(void);
void mcal_i2c_start(void);
void mcal_i2c_stop(void);
uint8_t mcal_i2c_data_put(unsigned char i2cData);
int mcal_i2c_data_get(int Ack);
uint8_t mcal_i2c_Set_Address(unsigned char *i2cData, int i2cDataSize);
uint8_t mcal_i2c_data_get2(unsigned char *i2cdata, int size);








/********************************************************************************/
// dac
typedef enum
{
    MCAL_DAC_CH0 = 0U,
    MCAL_DAC_CH1 = 1U,
} mcal_dac_chEnum_t;

typedef uint8_t mcal_dac_blkEnum_t;
#define MCAL_DAC_BLK_A 0

void mcal_dac_init(void);
void mcal_dac_set(mcal_dac_blkEnum_t *x_dacBlock);
void mcal_dac_channel_set(mcal_dac_blkEnum_t *x_dacBlock, mcal_dac_chEnum_t x_dacCh);
void mcal_dac_channel_enable(mcal_dac_blkEnum_t *x_dacBlock, mcal_dac_chEnum_t x_dacCh);
void mcal_dac_channel_disable(mcal_dac_blkEnum_t *x_dacBlock, mcal_dac_chEnum_t x_dacCh);
void mcal_dac_value_set(mcal_dac_blkEnum_t *x_dacBlock, mcal_dac_chEnum_t x_dacCh, float value);
uint8_t mcal_dac_conversionStatus_get(mcal_dac_blkEnum_t *x_dacBlock, mcal_dac_chEnum_t x_dacCh);
void mcal_dac_flag_clear(mcal_dac_blkEnum_t *x_dacBlock, mcal_dac_chEnum_t x_dacCh);




/********************************************************************************/
// Data Flash
#define MCAL_BLOCK_A_ADDRESS (0x03000) /**< BLOCK A first address */
#define MCAL_BLOCK_B_ADDRESS (0x03400) /**< BLOCK B first address */
#define MCAL_BLOCK_C_ADDRESS (0x03800) /**< BLOCK C first address */
#define MCAL_BLOCK_D_ADDRESS (0x03C00) /**< BLOCK D first address */

#define MCAL_BLOCK_A_SELECT BLOCK_A /**< Use BLOCK A */
#define MCAL_BLOCK_B_SELECT BLOCK_B /**< Use BLOCK B */
#define MCAL_BLOCK_C_SELECT BLOCK_C /**< Use BLOCK C */
#define MCAL_BLOCK_D_SELECT BLOCK_D /**< Use BLOCK D */

#define MCAL_DATA_FLASH_END_ADDRESS (0x3FFFU)

/**
 * @struct mcal_dataFlash_t
 *
 * @brief Configuration structure for the data Flash.
 */
typedef struct
{
    uint8_t dataFlash_block;         /**< Data Flash block Select: can be BLOCK_A/B/C/D_SELECT    */
    uint16_t dataFlash_blockAddress; /**< Data Flash block address                                */
    uint8_t dataFlash_bytes;         /**< Number of bytes to be written in the data Falsh         */
    uint8_t *dataFlash_dataBuffer;   /**< Data buffer that will be written in the data Flash      */
} mcal_dataFlash_t;

uint8_t mcal_flashData_erase(mcal_dataFlash_t *pStr_dataFlash);
uint8_t mcal_flashData_write(mcal_dataFlash_t *pStr_dataFlash);
uint8_t mcal_flashData_read(mcal_dataFlash_t *pStr_dataFlash);




/********************************************************************************/
// voltage detection 1 circuit
typedef uint8_t mcal_onChip_vdet1_refVoltEnum_t;
#define MCAL_ON_CHIP_VDET1_3_40V_REF (ON_CHIP_VDET1_3_40V_REF)
#define MCAL_ON_CHIP_VDET1_3_55V_REF (ON_CHIP_VDET1_3_55V_REF)
#define MCAL_ON_CHIP_VDET1_3_70V_REF (ON_CHIP_VDET1_3_70V_REF)
#define MCAL_ON_CHIP_VDET1_3_85V_REF (ON_CHIP_VDET1_3_85V_REF)
#define MCAL_ON_CHIP_VDET1_4_00V_REF (ON_CHIP_VDET1_4_00V_REF)

typedef uint8_t mcal_onChip_vdet1_intTypeEnum_t;
#define MCAL_ON_CHIP_VDET1_NON_MASKABLE_INT (ON_CHIP_VDET1_NON_MASKABLE_INT)
#define MCAL_ON_CHIP_VDET1_MASKABLE_INT (ON_CHIP_VDET1_MASKABLE_INT)

typedef uint8_t mcal_onChip_vdet1_stateEnum_t;
#define MCAL_ON_CHIP_VDET1_ENABLED (ON_CHIP_VDET1_ENABLED)
#define MCAL_ON_CHIP_VDET1_DISABLED (ON_CHIP_VDET1_DISABLED)

typedef struct
{
    mcal_onChip_vdet1_stateEnum_t vdet1_state;     /**< VDET1 circuit State can be Enabled or Disabled             */
    mcal_onChip_vdet1_intTypeEnum_t vdet1_intType; /**< VDET1 Interrupt type: MASKABLE or NON-MASKABLE             */
    mcal_onChip_vdet1_refVoltEnum_t vdet1_refVolt; /**< VDET1 Reference Voltage                                    */
} mcal_onChip_vdet1Config_t;

void mcal_onChip_vdet1_init(mcal_onChip_vdet1Config_t *pStr_vdet1Config);
void callback_vdet1_intHandler(void (*pfn_vdet1_function)(void));









/********************/
/* Added By Osama Elmorady */
/********************/
#define AOUTPUT_MODULES_NUM		2
#define DAC_CHANNELS_NO			2








#endif /* MCAL_REN33C_H_ */

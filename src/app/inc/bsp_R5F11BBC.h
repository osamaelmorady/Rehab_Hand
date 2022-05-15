#ifndef BSP_R5F11B_H
#define BSP_R5F11B_H

#include "app/inc/component_id.h"
#include "driver/gpio/gpio.h"
#include "driver/adc/adc.h"
#include "app/inc/config.h"




#if 0				/* 813 with the old pin assignment */

/*********************************************************************
Water Heater
**********************************************************************/
// Input Switches
// + Switch
#define SW_PLUS_PORT (GPIO_PORT1)
#define SW_PLUS_PIN (GPIO_PIN1)

/* Modified to run on old board version*/
// - Switch
#define SW_MINUS_PORT (GPIO_PORT1)
#define SW_MINUS_PIN (GPIO_PIN0)

// standby switch
#define SW_STANDBY_PORT (GPIO_PORT1)
#define SW_STANDBY_PIN (GPIO_PIN6)

//Temperature sensors1(operation sensor)
#define SENSOR_FLANGE_CHANNEL	(ADC_CH_18)					///****** Added By Osama Elmorady *****/
#define SENSOR_FLANGE_PORT (GPIO_PORT14)
#define SENSOR_FLANGE_PIN (GPIO_PIN7)

//Temperature sensors2 (display sensor)
#define SENSOR_DISPLAY_CHANNEL	(ADC_CH_23) 				///****** Added By Osama Elmorady *****/
#define SENSOR_DISPLAY_PORT (GPIO_PORT1)
#define SENSOR_DISPLAY_PIN (GPIO_PIN3)

// LEDs
// STANDBY led
#define LED_STANDBY_PORT (GPIO_PORT7)
#define LED_STANDBY_PIN (GPIO_PIN4)

// Relay led
#define LED_RELAY_PORT (GPIO_PORT7)
#define LED_RELAY_PIN (GPIO_PIN3)

// wifi led
#define LED_wifi_PORT (GPIO_PORT6)					/******************************************/
#define LED_wifi_PIN (GPIO_PIN3)


//  led enable
#define LED_ENABLE_PORT (GPIO_PORT6)				/******************************************/
#define LED_ENABLE_PIN (GPIO_PIN3)

// Output Heater control
#define HEATER_CONTROL_PORT (GPIO_PORT1)
#define HEATER_CONTROL_PIN (GPIO_PIN2)



// SSD display
// SSD pin a
#define SSD_A_PORT (GPIO_PORT2)
#define SSD_A_PIN (GPIO_PIN0)

// SSD pin b
#define SSD_E_PORT (GPIO_PORT2)
#define SSD_E_PIN (GPIO_PIN3)

// SSD pin c
#define SSD_C_PORT (GPIO_PORT0)
#define SSD_C_PIN (GPIO_PIN0)

// SSD pin d
#define SSD_D_PORT (GPIO_PORT12)
#define SSD_D_PIN (GPIO_PIN0)

// SSD pin e
#define SSD_B_PORT (GPIO_PORT0)
#define SSD_B_PIN (GPIO_PIN1)

// SSD pin f
#define SSD_F_PORT (GPIO_PORT2)
#define SSD_F_PIN (GPIO_PIN2)

// SSD pin g
#define SSD_G_PORT (GPIO_PORT2)
#define SSD_G_PIN (GPIO_PIN1)

// SSD One select pin
#define SSD_ONES_SELECT_PORT (GPIO_PORT7)
#define SSD_ONES_SELECT_PIN (GPIO_PIN0)

// SSD Two select pin
#define SSD_TENS_SELECT_PORT (GPIO_PORT7)
#define SSD_TENS_SELECT_PIN (GPIO_PIN2)

// BUZZER control
#define BUZZER_PORT (GPIO_PORT1)
#define BUZZER_PIN (GPIO_PIN5)

//IOT spi PINS
/* TODO */
#define SPI_SD0_DDR (GPIO_PORT5)
#define SPI_SD0_PIN (GPIO_PIN1)

#define SPI_SDI_DDR (GPIO_PORT5)
#define SPI_SDI_PIN (GPIO_PIN0)

#define SPI_SCK_DDR (GPIO_PORT3)
#define SPI_SCK_PIN (GPIO_PIN0)

#define IOT_SPI_SCS_DDR (GPIO_PORT3)
#define IOT_SPI_SCS_PIN (GPIO_PIN1)

#define EXROM_SPI_SCS_DDR (GPIO_PORT6)				/******************************************/
#define EXROM_SPI_SCS_PIN (GPIO_PORT3)
/*********************************************************************/
#endif








#if SW_TOUCH_BS13_2_MCU				/* 813 with the old pin assignment */
#if 1				/* 813 with the old pin assignment */

/*********************************************************************
Water Heater 
**********************************************************************/
// Input Switches
// + Switch
#define SW_PLUS_PORT (GPIO_PORT1)
#define SW_PLUS_PIN (GPIO_PIN1)

/* Modified to run on old board version*/
// - Switch
#define SW_MINUS_PORT (GPIO_PORT1)
#define SW_MINUS_PIN (GPIO_PIN0)

// standby switch
#define SW_STANDBY_PORT (GPIO_PORT1)
#define SW_STANDBY_PIN (GPIO_PIN6)

//Temperature sensors1(operation sensor)
#define SENSOR_FLANGE_CHANNEL	(ADC_CH_18)					///****** Added By Osama Elmorady *****/
#define SENSOR_FLANGE_PORT (GPIO_PORT14)
#define SENSOR_FLANGE_PIN (GPIO_PIN7)

//Temperature sensors2 (display sensor)
#define SENSOR_DISPLAY_CHANNEL	(ADC_CH_24) 				///****** Added By Osama Elmorady *****/
#define SENSOR_DISPLAY_PORT (GPIO_PORT1)
#define SENSOR_DISPLAY_PIN (GPIO_PIN4)

// LEDs
// STANDBY led
#define LED_STANDBY_PORT (GPIO_PORT7)
#define LED_STANDBY_PIN (GPIO_PIN4)

// Relay led
#define LED_RELAY_PORT (GPIO_PORT7)
#define LED_RELAY_PIN (GPIO_PIN3)

// wifi led
#define LED_wifi_PORT (GPIO_PORT6)					/******************************************/
#define LED_wifi_PIN (GPIO_PIN3)


//  led enable
#define LED_ENABLE_PORT (GPIO_PORT6)				/******************************************/
#define LED_ENABLE_PIN (GPIO_PIN3)

// Output Heater control
#define HEATER_CONTROL_PORT (GPIO_PORT1)
#define HEATER_CONTROL_PIN (GPIO_PIN7)



// SSD display
// SSD pin a
#define SSD_A_PORT (GPIO_PORT2)
#define SSD_A_PIN (GPIO_PIN0)

// SSD pin b
#define SSD_E_PORT (GPIO_PORT2)
#define SSD_E_PIN (GPIO_PIN3)

// SSD pin c
#define SSD_C_PORT (GPIO_PORT0)
#define SSD_C_PIN (GPIO_PIN0)

// SSD pin d
#define SSD_D_PORT (GPIO_PORT12)
#define SSD_D_PIN (GPIO_PIN0)

// SSD pin e
#define SSD_B_PORT (GPIO_PORT0)
#define SSD_B_PIN (GPIO_PIN1)

// SSD pin f
#define SSD_F_PORT (GPIO_PORT2)
#define SSD_F_PIN (GPIO_PIN2)

// SSD pin g
#define SSD_G_PORT (GPIO_PORT2)
#define SSD_G_PIN (GPIO_PIN1)

// SSD One select pin
#define SSD_ONES_SELECT_PORT (GPIO_PORT1)
#define SSD_ONES_SELECT_PIN (GPIO_PIN3)

// SSD Two select pin
#define SSD_TENS_SELECT_PORT (GPIO_PORT1)
#define SSD_TENS_SELECT_PIN (GPIO_PIN2)

// BUZZER control
#define BUZZER_PORT (GPIO_PORT1)
#define BUZZER_PIN (GPIO_PIN5)

//IOT spi PINS
/* TODO */
#define SPI_SD0_DDR (GPIO_PORT5)
#define SPI_SD0_PIN (GPIO_PIN1)

#define SPI_SDI_DDR (GPIO_PORT5)
#define SPI_SDI_PIN (GPIO_PIN0)

#define SPI_SCK_DDR (GPIO_PORT3)
#define SPI_SCK_PIN (GPIO_PIN0)

#define IOT_SPI_SCS_DDR (GPIO_PORT3)
#define IOT_SPI_SCS_PIN (GPIO_PIN1)

#define EXROM_SPI_SCS_DDR (GPIO_PORT6)				/******************************************/
#define EXROM_SPI_SCS_PIN (GPIO_PORT3)
/*********************************************************************/
#endif
#endif



#if SW_TOUCH_BS14_2_MCU			/* 814 with the New pin assignment */
/*********************************************************************
Water Heater
**********************************************************************/
// Input Switches
// + Switch
#define SW_PLUS_PORT (GPIO_PORT1)
#define SW_PLUS_PIN (GPIO_PIN0)

/* Modified to run on old board version*/
// - Switch
#define SW_MINUS_PORT (GPIO_PORT1)
#define SW_MINUS_PIN (GPIO_PIN1)

// standby switch
#define SW_STANDBY_PORT (GPIO_PORT1)
#define SW_STANDBY_PIN (GPIO_PIN6)

//Temperature sensors1(operation sensor)
#define SENSOR_FLANGE_CHANNEL	(ADC_CH_18)					///****** Added By Osama Elmorady *****/
#define SENSOR_FLANGE_PORT (GPIO_PORT14)
#define SENSOR_FLANGE_PIN (GPIO_PIN7)

//Temperature sensors2 (display sensor)
#define SENSOR_DISPLAY_CHANNEL	(ADC_CH_24) 				///****** Added By Osama Elmorady *****/
#define SENSOR_DISPLAY_PORT (GPIO_PORT1)
#define SENSOR_DISPLAY_PIN (GPIO_PIN4)

// LEDs
// STANDBY led
#define LED_STANDBY_PORT (GPIO_PORT7)
#define LED_STANDBY_PIN (GPIO_PIN4)

// Relay led
#define LED_RELAY_PORT (GPIO_PORT7)
#define LED_RELAY_PIN (GPIO_PIN3)

// wifi led
#define LED_wifi_PORT (GPIO_PORT6)					/******************************************/
#define LED_wifi_PIN (GPIO_PIN3)


//  led enable
#define LED_ENABLE_PORT (GPIO_PORT6)				/******************************************/
#define LED_ENABLE_PIN (GPIO_PIN3)

// Output Heater control
#define HEATER_CONTROL_PORT (GPIO_PORT1)
#define HEATER_CONTROL_PIN (GPIO_PIN7)



// SSD display
// SSD pin a
#define SSD_A_PORT (GPIO_PORT2)
#define SSD_A_PIN (GPIO_PIN0)

// SSD pin b
#define SSD_E_PORT (GPIO_PORT2)
#define SSD_E_PIN (GPIO_PIN3)

// SSD pin c
#define SSD_C_PORT (GPIO_PORT0)
#define SSD_C_PIN (GPIO_PIN0)

// SSD pin d
#define SSD_D_PORT (GPIO_PORT12)
#define SSD_D_PIN (GPIO_PIN0)

// SSD pin e
#define SSD_B_PORT (GPIO_PORT0)
#define SSD_B_PIN (GPIO_PIN1)

// SSD pin f
#define SSD_F_PORT (GPIO_PORT2)
#define SSD_F_PIN (GPIO_PIN2)

// SSD pin g
#define SSD_G_PORT (GPIO_PORT2)
#define SSD_G_PIN (GPIO_PIN1)

// SSD One select pin
#define SSD_ONES_SELECT_PORT (GPIO_PORT1)
#define SSD_ONES_SELECT_PIN (GPIO_PIN3)

// SSD Two select pin
#define SSD_TENS_SELECT_PORT (GPIO_PORT1)
#define SSD_TENS_SELECT_PIN (GPIO_PIN2)

// BUZZER control
#define BUZZER_PORT (GPIO_PORT1)
#define BUZZER_PIN (GPIO_PIN5)

//IOT spi PINS
/* TODO */
#define SPI_SD0_DDR (GPIO_PORT5)
#define SPI_SD0_PIN (GPIO_PIN1)

#define SPI_SDI_DDR (GPIO_PORT5)
#define SPI_SDI_PIN (GPIO_PIN0)

#define SPI_SCK_DDR (GPIO_PORT3)
#define SPI_SCK_PIN (GPIO_PIN0)

#define IOT_SPI_SCS_DDR (GPIO_PORT3)
#define IOT_SPI_SCS_PIN (GPIO_PIN1)

#define EXROM_SPI_SCS_DDR (GPIO_PORT6)				/******************************************/
#define EXROM_SPI_SCS_PIN (GPIO_PORT3)
/*********************************************************************/



#endif










#if SW_TOUCH_ROHM			/* Rohms with the New pin assignment */
/*********************************************************************
Water Heater
**********************************************************************/
// Input Switches
// + Switch
#define SW_PLUS_PORT (GPIO_PORT1)
#define SW_PLUS_PIN (GPIO_PIN0)

/* Modified to run on old board version*/
// - Switch
#define SW_MINUS_PORT (GPIO_PORT1)
#define SW_MINUS_PIN (GPIO_PIN1)

// standby switch
#define SW_STANDBY_PORT (GPIO_PORT1)
#define SW_STANDBY_PIN (GPIO_PIN6)

//Temperature sensors1(operation sensor)
#define SENSOR_FLANGE_CHANNEL	(ADC_CH_18)					///****** Added By Osama Elmorady *****/
#define SENSOR_FLANGE_PORT (GPIO_PORT14)
#define SENSOR_FLANGE_PIN (GPIO_PIN7)

//Temperature sensors2 (display sensor)
#define SENSOR_DISPLAY_CHANNEL	(ADC_CH_24) 				///****** Added By Osama Elmorady *****/
#define SENSOR_DISPLAY_PORT (GPIO_PORT1)
#define SENSOR_DISPLAY_PIN (GPIO_PIN4)

// LEDs
// STANDBY led
#define LED_STANDBY_PORT (GPIO_PORT7)
#define LED_STANDBY_PIN (GPIO_PIN4)

// Relay led
#define LED_RELAY_PORT (GPIO_PORT7)
#define LED_RELAY_PIN (GPIO_PIN3)

// wifi led
#define LED_wifi_PORT (GPIO_PORT6)					/******************************************/
#define LED_wifi_PIN (GPIO_PIN3)


//  led enable
#define LED_ENABLE_PORT (GPIO_PORT6)				/******************************************/
#define LED_ENABLE_PIN (GPIO_PIN3)

// Output Heater control
#define HEATER_CONTROL_PORT (GPIO_PORT1)
#define HEATER_CONTROL_PIN (GPIO_PIN7)



// SSD display
// SSD pin a
#define SSD_A_PORT (GPIO_PORT2)
#define SSD_A_PIN (GPIO_PIN0)

// SSD pin b
#define SSD_E_PORT (GPIO_PORT2)
#define SSD_E_PIN (GPIO_PIN3)

// SSD pin c
#define SSD_C_PORT (GPIO_PORT0)
#define SSD_C_PIN (GPIO_PIN0)

// SSD pin d
#define SSD_D_PORT (GPIO_PORT12)
#define SSD_D_PIN (GPIO_PIN0)

// SSD pin e
#define SSD_B_PORT (GPIO_PORT0)
#define SSD_B_PIN (GPIO_PIN1)

// SSD pin f
#define SSD_F_PORT (GPIO_PORT2)
#define SSD_F_PIN (GPIO_PIN2)

// SSD pin g
#define SSD_G_PORT (GPIO_PORT2)
#define SSD_G_PIN (GPIO_PIN1)

// SSD One select pin
#define SSD_ONES_SELECT_PORT (GPIO_PORT1)
#define SSD_ONES_SELECT_PIN (GPIO_PIN3)

// SSD Two select pin
#define SSD_TENS_SELECT_PORT (GPIO_PORT1)
#define SSD_TENS_SELECT_PIN (GPIO_PIN2)

// BUZZER control
#define BUZZER_PORT (GPIO_PORT1)
#define BUZZER_PIN (GPIO_PIN5)

//IOT spi PINS
/* TODO */
#define SPI_SD0_DDR (GPIO_PORT5)
#define SPI_SD0_PIN (GPIO_PIN1)

#define SPI_SDI_DDR (GPIO_PORT5)
#define SPI_SDI_PIN (GPIO_PIN0)

#define SPI_SCK_DDR (GPIO_PORT3)
#define SPI_SCK_PIN (GPIO_PIN0)

#define IOT_SPI_SCS_DDR (GPIO_PORT3)
#define IOT_SPI_SCS_PIN (GPIO_PIN1)

#define EXROM_SPI_SCS_DDR (GPIO_PORT6)				/******************************************/
#define EXROM_SPI_SCS_PIN (GPIO_PORT3)
/*********************************************************************/
#endif






#endif

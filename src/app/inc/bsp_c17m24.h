#ifndef BSP_C17M24_H
#define BSP_C17M24_H

#include "app/inc/component_id.h"
#include "driver/gpio/gpio.h"

/*********************************************************************
Water Heater 
**********************************************************************/
// Input Switches
// + Switch
#define SW_PLUS_PORT (GPIO_PORTB)
#define SW_PLUS_PIN (GPIO_PIN5)

/* Modified to run on old board version*/
// - Switch
#define SW_MINUS_PORT (GPIO_PORTD)
#define SW_MINUS_PIN (GPIO_PIN1)

// standby switch
#define SW_STANDBY_PORT (GPIO_PORTD)
#define SW_STANDBY_PIN (GPIO_PIN2)

//Temperature sensors1(operation sensor)
#define SENSOR_FLANGE_PORT (GPIO_PORTC)
#define SENSOR_FLANGE_PIN (GPIO_PIN7)

//Temperature sensors2 (display sensor)
#define SENSOR_DISPLAY_PORT (GPIO_PORTC)
#define SENSOR_DISPLAY_PIN (GPIO_PIN6)

// LEDs
// STANDBY led
#define LED_STANDBY_PORT (GPIO_PORTB)
#define LED_STANDBY_PIN (GPIO_PIN4)

// Relay led
#define LED_RELAY_PORT (GPIO_PORTB)
#define LED_RELAY_PIN (GPIO_PIN3)

// wifi led
#define LED_wifi_PORT (GPIO_PORTB)
#define LED_wifi_PIN (GPIO_PIN5)

//  led enable
#define LED_ENABLE_PORT (GPIO_PORTB)
#define LED_ENABLE_PIN (GPIO_PIN2)

// Output Heater control
#define HEATER_CONTROL_PORT (GPIO_PORTE)
#define HEATER_CONTROL_PIN (GPIO_PIN4)

// SSD display
// SSD pin a
#define SSD_A_PORT (GPIO_PORTE)
#define SSD_A_PIN (GPIO_PIN2)

// SSD pin b
#define SSD_B_PORT (GPIO_PORTA)
#define SSD_B_PIN (GPIO_PIN0)

// SSD pin c
#define SSD_C_PORT (GPIO_PORTA)
#define SSD_C_PIN (GPIO_PIN3)

// SSD pin d
#define SSD_D_PORT (GPIO_PORTA)
#define SSD_D_PIN (GPIO_PIN1)

// SSD pin e
#define SSD_E_PORT (GPIO_PORTE)
#define SSD_E_PIN (GPIO_PIN1)

// SSD pin f
#define SSD_F_PORT (GPIO_PORTE)
#define SSD_F_PIN (GPIO_PIN0)

// SSD pin g
#define SSD_G_PORT (GPIO_PORTE)
#define SSD_G_PIN (GPIO_PIN3)

// SSD One select pin
#define SSD_ONES_SELECT_PORT (GPIO_PORTB)
#define SSD_ONES_SELECT_PIN (GPIO_PIN1)

// SSD Two select pin
#define SSD_TENS_SELECT_PORT (GPIO_PORTB)
#define SSD_TENS_SELECT_PIN (GPIO_PIN0)

// BUZZER control
#define BUZZER_PORT (GPIO_PORTA)
#define BUZZER_PIN (GPIO_PIN2)

//IOT spi PINS
/* TODO */
#define SPI_SD0_DDR (GPIO_PORTC)
#define SPI_SD0_PIN (GPIO_PIN3)

#define SPI_SDI_DDR (GPIO_PORTC)
#define SPI_SDI_PIN (GPIO_PIN3)

#define SPI_SCK_DDR (GPIO_PORTC)
#define SPI_SCK_PIN (GPIO_PIN3)

#define IOT_SPI_SCS_DDR (GPIO_PORTC)
#define IOT_SPI_SCS_PIN (GPIO_PIN5)

#define EXROM_SPI_SCS_DDR (GPIO_PORTC)
#define EXROM_SPI_SCS_PIN (GPIO_PIN3)
/*********************************************************************/
#endif

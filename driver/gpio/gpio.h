#ifndef _GPIO_H
#define _GPIO_H

#include "mcal/mcal.h"
//#include "mcal_c17m24.h"

typedef mcal_gpio_portEnum_t gpio_port_t;
#define GPIO_PORTA (MCAL_GPIO_PORTA)
#define GPIO_PORTB (MCAL_GPIO_PORTB)
#define GPIO_PORTC (MCAL_GPIO_PORTC)
#define GPIO_PORTD (MCAL_GPIO_PORTD)
#define GPIO_PORTE (MCAL_GPIO_PORTE)
#define GPIO_PORTF (MCAL_GPIO_PORTF)
#define GPIO_PORTG (MCAL_GPIO_PORTG)
#define GPIO_PORTH (MCAL_GPIO_PORTH)
#define GPIO_PORTI (MCAL_GPIO_PORTI)
#define GPIO_PORTJ (MCAL_GPIO_PORTJ)
#define GPIO_PORTK (MCAL_GPIO_PORTK)
#define GPIO_PORTL (MCAL_GPIO_PORTL)
#define GPIO_PORTM (MCAL_GPIO_PORTM)
#define GPIO_PORTN (MCAL_GPIO_PORTN)
#define GPIO_PORTO (MCAL_GPIO_PORTO)


#define GPIO_PORT0 (MCAL_GPIO_PORTA)
#define GPIO_PORT1 (MCAL_GPIO_PORTB)
#define GPIO_PORT2 (MCAL_GPIO_PORTC)
#define GPIO_PORT3 (MCAL_GPIO_PORTD)
#define GPIO_PORT4 (MCAL_GPIO_PORTE)
#define GPIO_PORT5 (MCAL_GPIO_PORTF)
#define GPIO_PORT6 (MCAL_GPIO_PORTG)
#define GPIO_PORT7 (MCAL_GPIO_PORTH)
#define GPIO_PORT8 (MCAL_GPIO_PORTI)
#define GPIO_PORT9 (MCAL_GPIO_PORTJ)
#define GPIO_PORT10 (MCAL_GPIO_PORTK)
#define GPIO_PORT11 (MCAL_GPIO_PORTL)
#define GPIO_PORT12 (MCAL_GPIO_PORTM)
#define GPIO_PORT13 (MCAL_GPIO_PORTN)
#define GPIO_PORT14 (MCAL_GPIO_PORTO)




typedef mcal_gpio_pinEnum_t gpio_pin_t;
#define GPIO_PIN0 (MCAL_GPIO_PIN0)
#define GPIO_PIN1 (MCAL_GPIO_PIN1)
#define GPIO_PIN2 (MCAL_GPIO_PIN2)
#define GPIO_PIN3 (MCAL_GPIO_PIN3)
#define GPIO_PIN4 (MCAL_GPIO_PIN4)
#define GPIO_PIN5 (MCAL_GPIO_PIN5)
#define GPIO_PIN6 (MCAL_GPIO_PIN6)
#define GPIO_PIN7 (MCAL_GPIO_PIN7)
#define GPIO_PIN_ALL (MCAL_GPIO_PIN_ALL)

typedef mcal_gpio_ioStateEnum_t gpio_ioState_t;
#define GPIO_OUTPUT (MCAL_GPIO_OUTPUT)
#define GPIO_INPUT (MCAL_GPIO_INPUT)

typedef mcal_gpio_stateEnum_t gpio_state_t;
#define GPIO_LOW (MCAL_GPIO_LOW)
#define GPIO_HIGH (MCAL_GPIO_HIGH)

typedef struct
{
    gpio_port_t port;
    gpio_pin_t pin;
    gpio_ioState_t ioState;
    gpio_state_t state;
} gpio_t;

void gpio_pin_init(gpio_t *px_gpio);
void gpio_pinIOState_set(gpio_port_t port, gpio_pin_t pin, gpio_ioState_t ioState);
void gpio_pinState_set(gpio_port_t port, gpio_pin_t pin, gpio_state_t x_state);
uint8_t gpio_pinState_get(gpio_port_t port, gpio_pin_t pin);
void gpio_init(void);
#endif

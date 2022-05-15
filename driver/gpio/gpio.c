#include "driver/gpio/gpio.h"
#include "mcal/mcal.h"

void gpio_init(void)
{
    mcal_gpio_init();
}

void gpio_pin_init(gpio_t *px_gpio)
{
    mcal_gpio_t x_mcalgpio;
    x_mcalgpio.port = px_gpio->port;
    x_mcalgpio.pin = px_gpio->pin;
    x_mcalgpio.ioState = px_gpio->ioState;

    if (px_gpio->state != GPIO_HIGH && px_gpio->state != GPIO_LOW)
    {
        px_gpio->state = GPIO_LOW;
    }

    // LOG: changed the order for the calling of the next functions.
    mcal_gpio_pin_init(&x_mcalgpio);
    mcal_gpio_pinState_set(&x_mcalgpio, px_gpio->state);
}

void gpio_pinIOState_set(gpio_port_t port, gpio_pin_t pin, gpio_ioState_t ioState)
{
    mcal_gpio_t x_mcalgpio;
    x_mcalgpio.port = port;
    x_mcalgpio.pin = pin;
    x_mcalgpio.ioState = ioState;

    mcal_gpio_pinIOState_set(&x_mcalgpio, x_mcalgpio.ioState);
}

void gpio_pinState_set(gpio_port_t port, gpio_pin_t pin, gpio_state_t x_state)
{
    mcal_gpio_t x_mcalgpio;
    x_mcalgpio.port = port;
    x_mcalgpio.pin = pin;
    //x_mcalgpio.ioState = px_gpio->ioState;

    mcal_gpio_pinState_set(&x_mcalgpio, x_state);
}

uint8_t gpio_pinState_get(gpio_port_t port, gpio_pin_t pin)
{
    mcal_gpio_t x_mcalgpio;
    x_mcalgpio.port = port;
    x_mcalgpio.pin = pin;

    return mcal_gpio_pinState_get(&x_mcalgpio);
}

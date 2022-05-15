#ifndef OUTPUT_MODULE_H
#define OUTPUT_MODULE_H

#include "driver/gpio/gpio.h"
#include "app/inc/def.h"

typedef struct
{
    gpio_t gpio;
    uint8_t outputID;
} doutputModule_t;

void doutputModule_init(doutputModule_t *x_doutputModule);
result_t doutputModule_state_set(uint8_t u8_doutputID, gpio_state_t x_state);
gpio_state_t doutputModule_state_get(uint8_t u8_doutputID);
void doutputModule_update(void *arg);

#endif

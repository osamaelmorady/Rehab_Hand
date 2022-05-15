#ifndef AINPUT_MODULE_H
#define AINPUT_MODULE_H

#include "driver/adc/adc.h"
#include "app/inc/def.h"
#include "driver/gpio/gpio.h"
#include "mcal/mcal.h"

typedef struct
{
    adc_block_t adcBlock;
    adc_channel_t adcCh;
    gpio_t gpio;   // in case the mcu requires the pins as gpio to be identified
    uint8_t adcDeviceID;
} ainputModule_t;

void ainputModule_init(ainputModule_t *ainput);
uint32_t ainputModule_value_get(uint8_t u8_adcDeviceID);
void ainputModule_update(void *arg);

#endif





#if 0

#ifndef AINPUT_MODULE_H
#define AINPUT_MODULE_H

#include "def.h"
#include "mcal.h"
#include "adc/adc.h"
#include "gpio/gpio.h"

typedef struct
{
    adc_block_t *adcBlock;
    adc_channel_t adcCh;
    gpio_t gpio; // in case the mcu requires the pins as gpio to be identified
    uint8_t adcDeviceID;
} ainputModule_t;

void ainputModule_init(ainputModule_t *ainput);
uint32_t ainputModule_value_get(uint8_t u8_adcDeviceID);
void ainputModule_update(void *arg);

#endif



#endif

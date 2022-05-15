
#include "driver/adc/adc.h"
#include "app/inc/config.h"
#include "mcal/mcal.h"
#include "app/inc/def.h"
#include "component/ainput_module/ainput_module.h"

typedef struct
{
    adc_block_t adcBlock;
    adc_channel_t adcCh;
    gpio_t gpio; // in case the mcu requires the pins as gpio to be identified
    uint8_t adcDeviceID;
    uint32_t adcValue;
} ainputModule_internalHandler_t;

static ainputModule_internalHandler_t gax_ainputModule_internalHandler[AINPUT_MODULES_NUM];
static uint8_t gu8_inputModule_internalCounter = 0;
static uint8_t gu8_ainputModule_chUpdateCounter = 0;

void ainputModule_init(ainputModule_t *ainput)
{
    gax_ainputModule_internalHandler[gu8_inputModule_internalCounter].gpio.port = ainput->gpio.port;
    gax_ainputModule_internalHandler[gu8_inputModule_internalCounter].gpio.pin = ainput->gpio.pin;
    gax_ainputModule_internalHandler[gu8_inputModule_internalCounter].gpio.ioState = ainput->gpio.ioState;
    gax_ainputModule_internalHandler[gu8_inputModule_internalCounter].gpio.state = ainput->gpio.state;
    gax_ainputModule_internalHandler[gu8_inputModule_internalCounter].adcDeviceID = ainput->adcDeviceID;
    gax_ainputModule_internalHandler[gu8_inputModule_internalCounter].adcValue = 0;
    gax_ainputModule_internalHandler[gu8_inputModule_internalCounter].adcBlock = ainput->adcBlock;
    gax_ainputModule_internalHandler[gu8_inputModule_internalCounter].adcCh = ainput->adcCh;

    //gpio_pin_init(&(gax_ainputModule_internalHandler[gu8_inputModule_internalCounter].gpio));

    /* Added By Osama Elmorady ... To define the pins as analog input */
    	//GPIO_SetAnalogInput(ainput->gpio.port, ainput->gpio.pin, GPIO_STATUS_ENABLE)  ;

    mcal_adc_channel_set(ainput->adcBlock, ainput->adcCh);

    gu8_inputModule_internalCounter++;
}

uint32_t ainputModule_value_get(uint8_t u8_adcDeviceID)
{
    uint8_t i;

    for (i = 0; i < gu8_inputModule_internalCounter; i++)
    {
        if (gax_ainputModule_internalHandler[i].adcDeviceID == u8_adcDeviceID)
        {
            return gax_ainputModule_internalHandler[i].adcValue;
        }
    }

    return 0 ;
}

void ainputModule_update(void *arg)
{


    if (mcal_adc_conversionStatus_get(gax_ainputModule_internalHandler[gu8_ainputModule_chUpdateCounter].adcBlock, gax_ainputModule_internalHandler[gu8_ainputModule_chUpdateCounter].adcCh) == 0)
        return;

    mcal_adc_flag_clear(gax_ainputModule_internalHandler[gu8_ainputModule_chUpdateCounter].adcBlock, gax_ainputModule_internalHandler[gu8_ainputModule_chUpdateCounter].adcCh);

    gax_ainputModule_internalHandler[gu8_ainputModule_chUpdateCounter].adcValue = mcal_adc_conversionResult_get(gax_ainputModule_internalHandler[gu8_ainputModule_chUpdateCounter].adcBlock, gax_ainputModule_internalHandler[gu8_ainputModule_chUpdateCounter].adcCh);



    gu8_ainputModule_chUpdateCounter++;
    if (gu8_ainputModule_chUpdateCounter >= AINPUT_MODULES_NUM)
    {
        gu8_ainputModule_chUpdateCounter = 0;
    }

    mcal_adc_conversion_start(gax_ainputModule_internalHandler[gu8_ainputModule_chUpdateCounter].adcBlock, gax_ainputModule_internalHandler[gu8_ainputModule_chUpdateCounter].adcCh);
}




#if 0

#include "core/R5F11B/LIB/STD_TYPES.h"
#include "adc/adc.h"
#include "config.h"
#include "mcal.h"
#include "def.h"
#include "ainput_module/ainput_module.h"

typedef struct
{
    adc_block_t *adcBlock;
    adc_channel_t adcCh;
    gpio_t gpio; // in case the mcu requires the pins as gpio to be identified
    uint8_t adcDeviceID;
    uint32_t adcValue;
} ainputModule_internalHandler_t;

static ainputModule_internalHandler_t gax_ainputModule_internalHandler[AINPUT_MODULES_NUM];
static uint8_t gu8_inputModule_internalCounter = 0;

void ainputModule_init(ainputModule_t *ainput)
{
    gax_ainputModule_internalHandler[gu8_inputModule_internalCounter].gpio.port = ainput->gpio.port;
    gax_ainputModule_internalHandler[gu8_inputModule_internalCounter].gpio.pin = ainput->gpio.pin;
    gax_ainputModule_internalHandler[gu8_inputModule_internalCounter].gpio.ioState = ainput->gpio.ioState;
    gax_ainputModule_internalHandler[gu8_inputModule_internalCounter].gpio.state = ainput->gpio.state;
    gax_ainputModule_internalHandler[gu8_inputModule_internalCounter].adcDeviceID = ainput->adcDeviceID;
    gax_ainputModule_internalHandler[gu8_inputModule_internalCounter].adcValue = 0;
    gax_ainputModule_internalHandler[gu8_inputModule_internalCounter].adcBlock = ainput->adcBlock;
    gax_ainputModule_internalHandler[gu8_inputModule_internalCounter].adcCh = ainput->adcCh;

    //gpio_init(&(gax_ainputModule_internalHandler[gu8_inputModule_internalCounter].gpio));

    adc_channel_set(ainput->adcBlock, ainput->adcCh);

    gu8_inputModule_internalCounter++;
}

uint32_t ainputModule_value_get(uint8_t u8_adcDeviceID)
{
    uint8_t i;

    for (i = 0; i < gu8_inputModule_internalCounter; i++)
    {
        if (gax_ainputModule_internalHandler[i].adcDeviceID == u8_adcDeviceID)
        {
            return gax_ainputModule_internalHandler[i].adcValue;
        }
    }
}

void ainputModule_update(void *arg)
{
    uint8_t i;

    for (i = 0; i < gu8_inputModule_internalCounter; i++)
    {
        gax_ainputModule_internalHandler[i].adcValue = adc_value_get(gax_ainputModule_internalHandler[i].adcBlock, gax_ainputModule_internalHandler[i].adcCh);
    }
}



#endif

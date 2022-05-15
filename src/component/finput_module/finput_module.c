#include "driver/hw_timer/hw_timer.h"
#include "app/inc/def.h"
#include "app/inc/config.h"
#include "component/finput_module/finput_module.h"

typedef struct
{
    hwTimer_t *timerModule;
    gpio_t gpio;
    hwTimer_eventEdge_t edge;
    uint8_t counterID;
    uint32_t updatePeriod;
    uint32_t counterValue;
    uint32_t internalCounter;
} finputModule_internalHandler_t;

static finputModule_internalHandler_t gax_finputModule_internalHandler[FINPUT_MODULES_NUM];
static uint8_t gu8_inputModule_internalCounter = 0;

void finputModule_init(finputModule_t *x_finputModule)
{
    gax_finputModule_internalHandler[gu8_inputModule_internalCounter].timerModule = x_finputModule->timerModule;
    gax_finputModule_internalHandler[gu8_inputModule_internalCounter].gpio.port = x_finputModule->gpio.port;
    gax_finputModule_internalHandler[gu8_inputModule_internalCounter].gpio.pin = x_finputModule->gpio.pin;
    gax_finputModule_internalHandler[gu8_inputModule_internalCounter].gpio.ioState = x_finputModule->gpio.ioState;
    gax_finputModule_internalHandler[gu8_inputModule_internalCounter].gpio.state = x_finputModule->gpio.state;
    gax_finputModule_internalHandler[gu8_inputModule_internalCounter].counterID = x_finputModule->counterID;
    gax_finputModule_internalHandler[gu8_inputModule_internalCounter].updatePeriod = x_finputModule->updatePeriod;
    gax_finputModule_internalHandler[gu8_inputModule_internalCounter].counterValue = 0;
    gax_finputModule_internalHandler[gu8_inputModule_internalCounter].internalCounter = 0;

    hwTimer_init();
    hwTimer_counterMode_set(x_finputModule->timerModule, &x_finputModule->gpio, x_finputModule->edge);
    hwTimer_channel_enable(x_finputModule->timerModule);
    hwTimer_state_set(x_finputModule->timerModule, HW_TIMER_START);

    gu8_inputModule_internalCounter++;
}

uint32_t finputModule_value_get(uint8_t u8_counterID)
{
    uint8_t i;

    for (i = 0; i < gu8_inputModule_internalCounter; i++)
    {
        if (gax_finputModule_internalHandler[i].counterID == u8_counterID)
        {
            return gax_finputModule_internalHandler[i].counterValue;
        }
    }

    return 0;   // replace with error checking
}

void finputModule_update(void *arg)
{
    uint8_t i;

    for (i = 0; i < gu8_inputModule_internalCounter; i++)
    {
        if (gax_finputModule_internalHandler[i].internalCounter >= gax_finputModule_internalHandler[i].updatePeriod)
        {
            gax_finputModule_internalHandler[i].counterValue = hwTimer_count_get(gax_finputModule_internalHandler[i].timerModule);
            hwTimer_count_reset(gax_finputModule_internalHandler[i].timerModule);
            hwTimer_flag_clear(gax_finputModule_internalHandler[i].timerModule);
            hwTimer_state_set(gax_finputModule_internalHandler[i].timerModule, HW_TIMER_START);
            gax_finputModule_internalHandler[i].internalCounter = 0;
        }
        gax_finputModule_internalHandler[i].internalCounter += FINPUT_MODULE_UPDATE_PERIOD_MS;
    }
}

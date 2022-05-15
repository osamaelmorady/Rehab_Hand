#include "app/inc/config.h"
#include "component/dinput_module/dinput_module.h"
#include "driver/gpio/gpio.h"
#include "app/inc/bsp_R5F11BBC.h"

typedef struct
{
    uint32_t activeStateCnt;
    dinputModule_stateEnum_t activeState;
    dinputModule_stateEnum_t edgeActiveState;
    dinputModule_stateEnum_t onReleaseState;
    dinputModule_t button;
} dinputModule_internalHandler_t;

static uint8_t gu8_dinputModule_internalCounter = 0;
static dinputModule_internalHandler_t gx_dinputModule_internalHandler[DINPUT_MODULES_NUM];

void dinputModule_init(dinputModule_t  * x_dinputModule)
{
    // NOTE: right now the code doesn't implement the pull up part.
    // TODO:  add pull up code
    gx_dinputModule_internalHandler[gu8_dinputModule_internalCounter].activeStateCnt = 0;
    gx_dinputModule_internalHandler[gu8_dinputModule_internalCounter].activeState = DINPUT_MODULE_RELEASED;
    gx_dinputModule_internalHandler[gu8_dinputModule_internalCounter].edgeActiveState = DINPUT_MODULE_RELEASED;
    gx_dinputModule_internalHandler[gu8_dinputModule_internalCounter].onReleaseState = DINPUT_MODULE_RELEASED;
    gx_dinputModule_internalHandler[gu8_dinputModule_internalCounter].button.port = x_dinputModule->port;
    gx_dinputModule_internalHandler[gu8_dinputModule_internalCounter].button.pin = x_dinputModule->pin;
    gx_dinputModule_internalHandler[gu8_dinputModule_internalCounter].button.pullUpEn = x_dinputModule->pullUpEn;
    gx_dinputModule_internalHandler[gu8_dinputModule_internalCounter].button.dinputID = x_dinputModule->dinputID;
    if (x_dinputModule->shortPressMultiplier <= 0)
    {
        x_dinputModule->shortPressMultiplier = 1;
    }
    if (x_dinputModule->longPressMultiplier < x_dinputModule->shortPressMultiplier)
    {
        x_dinputModule->longPressMultiplier = x_dinputModule->shortPressMultiplier;
    }
    gx_dinputModule_internalHandler[gu8_dinputModule_internalCounter].button.shortPressMultiplier = x_dinputModule->shortPressMultiplier;
    gx_dinputModule_internalHandler[gu8_dinputModule_internalCounter].button.longPressMultiplier = x_dinputModule->longPressMultiplier;

    gpio_pinIOState_set(gx_dinputModule_internalHandler[gu8_dinputModule_internalCounter].button.port, gx_dinputModule_internalHandler[gu8_dinputModule_internalCounter].button.pin, GPIO_INPUT);

    gu8_dinputModule_internalCounter++;

}

void dinputModule_update(void *arg)
{
	uint8_t b = 0;

    for (b = 0; b < DINPUT_MODULES_NUM; b++)
    {
        switch (gx_dinputModule_internalHandler[b].activeState)
        {
        case DINPUT_MODULE_RELEASED:
            if (gpio_pinState_get(gx_dinputModule_internalHandler[b].button.port, gx_dinputModule_internalHandler[b].button.pin) == DINPUT_MODULE_PRESSED_LEVEL)
            {
                gx_dinputModule_internalHandler[b].activeStateCnt++;
                if (gx_dinputModule_internalHandler[b].activeStateCnt >= gx_dinputModule_internalHandler[b].button.shortPressMultiplier)
                {
                    gx_dinputModule_internalHandler[b].activeState = DINPUT_MODULE_PRESSED_SHORT_PRESS;
                    // gx_dinputModule_internalHandler[b].edgeActiveState = DINPUT_MODULE_PRESSED_SHORT_PRESS;
                }
            }
            else
            {
                gx_dinputModule_internalHandler[b].activeStateCnt = 0;
            }
            break;

        case DINPUT_MODULE_PRESSED_SHORT_PRESS:
            if (gpio_pinState_get(gx_dinputModule_internalHandler[b].button.port, gx_dinputModule_internalHandler[b].button.pin) == DINPUT_MODULE_PRESSED_LEVEL)
            {
                gx_dinputModule_internalHandler[b].activeStateCnt++;
                if (gx_dinputModule_internalHandler[b].activeStateCnt >= gx_dinputModule_internalHandler[b].button.longPressMultiplier)
                {
                    gx_dinputModule_internalHandler[b].activeState = DINPUT_MODULE_PRESSED_LONG_PRESS;
                    gx_dinputModule_internalHandler[b].edgeActiveState = DINPUT_MODULE_PRESSED_LONG_PRESS;
                    gx_dinputModule_internalHandler[b].activeStateCnt = 0;
                }
            }
            else
            {
                gx_dinputModule_internalHandler[b].activeState = DINPUT_MODULE_RELEASED;
                gx_dinputModule_internalHandler[b].activeStateCnt = 0;
                gx_dinputModule_internalHandler[b].onReleaseState = DINPUT_MODULE_PRESSED_SHORT_PRESS;
                gx_dinputModule_internalHandler[b].edgeActiveState = DINPUT_MODULE_PRESSED_SHORT_PRESS;
            }
            break;

        case DINPUT_MODULE_PRESSED_LONG_PRESS:
            if (gpio_pinState_get(gx_dinputModule_internalHandler[b].button.port, gx_dinputModule_internalHandler[b].button.pin) == DINPUT_MODULE_PRESSED_LEVEL)
            {
                gx_dinputModule_internalHandler[b].activeState = DINPUT_MODULE_PRESSED_LONG_PRESS;
            }
            else
            {
                gx_dinputModule_internalHandler[b].activeState = DINPUT_MODULE_RELEASED;
                gx_dinputModule_internalHandler[b].activeStateCnt = 0;
                gx_dinputModule_internalHandler[b].onReleaseState = DINPUT_MODULE_PRESSED_LONG_PRESS;
            }
            break;

        default:
            // do nothing
            break;
        }
    }
}

dinputModule_stateEnum_t dinputModule_state_get(uint8_t u8_dinputID)
{
    uint8_t i = 0;
    dinputModule_stateEnum_t keyState;

    for (i = 0; i < DINPUT_MODULES_NUM; i++)
    {
        if (gx_dinputModule_internalHandler[i].button.dinputID == u8_dinputID)
        {
            keyState = gx_dinputModule_internalHandler[i].activeState;
            gx_dinputModule_internalHandler[i].edgeActiveState = DINPUT_MODULE_RELEASED;
            return keyState;
        }
    }

    return DINPUT_MODULE_FAULT;
}

dinputModule_stateEnum_t dinputModule_edgeState_get(uint8_t u8_dinputID)
{
    uint8_t i = 0;
    dinputModule_stateEnum_t keyState;

    for (i = 0; i < DINPUT_MODULES_NUM; i++)
    {
        if (gx_dinputModule_internalHandler[i].button.dinputID == u8_dinputID)
        {
            keyState = gx_dinputModule_internalHandler[i].edgeActiveState;
            gx_dinputModule_internalHandler[i].edgeActiveState = DINPUT_MODULE_RELEASED;
            return keyState;
        }
    }

    return DINPUT_MODULE_FAULT;
}

dinputModule_stateEnum_t dinputModule_onReleaseState_get(uint8_t u8_dinputID)
{
    uint8_t i = 0;
    dinputModule_stateEnum_t keyState;

    for (i = 0; i < DINPUT_MODULES_NUM; i++)
    {
        if (gx_dinputModule_internalHandler[i].button.dinputID == u8_dinputID)
        {
            keyState = gx_dinputModule_internalHandler[i].onReleaseState;
            gx_dinputModule_internalHandler[i].edgeActiveState = DINPUT_MODULE_RELEASED;
            gx_dinputModule_internalHandler[i].onReleaseState = DINPUT_MODULE_RELEASED;
            return keyState;
        }
    }

    return DINPUT_MODULE_FAULT;
}

void dinputModule_shortPressMultiplier_set(uint8_t u8_dinputID, uint32_t u32_newMultiplier)
{
    uint8_t i = 0;

    for (i = 0; i < DINPUT_MODULES_NUM; i++)
    {
        if (gx_dinputModule_internalHandler[i].button.dinputID == u8_dinputID)
        {
            gx_dinputModule_internalHandler[i].button.shortPressMultiplier = u32_newMultiplier;
        }
    }
}

void dinputModule_longPressMultiplier_set(uint8_t u8_dinputID, uint32_t u32_newMultiplier)
{
    uint8_t i = 0;

    for (i = 0; i < DINPUT_MODULES_NUM; i++)
    {
        if (gx_dinputModule_internalHandler[i].button.dinputID == u8_dinputID)
        {
            gx_dinputModule_internalHandler[i].button.longPressMultiplier = u32_newMultiplier;
        }
    }
}

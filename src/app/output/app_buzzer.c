#include "app/output/app_buzzer.h"
#include "app/inc/bsp.h"
#include "component/foutput_module/foutput_module.h"
#include "app/inc/component_id.h"
#include "app/inc/config.h"
#include "app/output/app_buzzer.h"
#define NULL ((void *)'\0')

#define APP_BUZZER_NOTES_NUM (APP_BUZZER_TONE_NUM)

typedef struct
{
    uint32_t freq;
    uint32_t onInterval;
    uint32_t offInterval;
    uint8_t duty;
    uint8_t repeat;
} app_buzzerToneConfig_t;

typedef enum
{
    APP_BUZZER_IDLE,
    APP_BUZZER_INIT,
    APP_BUZZER_OFF_INTERVAL,
    APP_BUZZER_ON_INTERVAL
} app_buzzer_state_t;

static uint32_t u32_internalCounter = 0;
static app_buzzer_state_t gx_app_buzzer_currentState;
static uint8_t gu8_app_buzzer_currentToneRepetitionCounter;
static app_buzzerTone_t gx_app_buzzer_currentTone;
static app_buzzerToneConfig_t gx_app_buzzer_tones[APP_BUZZER_NOTES_NUM] = {
    {4000, 300,300, 50, 2},
    {4000, 100, 100, 50, 3},
    {4000, 100, 0, 50, 1},
    {4000, 500, 500, 50, 1},
    {4000, 400, 400, 50, 100},
    {4000, 400,0, 50, 1}
};

void app_buzzer_init(void)
{
    mcal_pwm_init();

    gx_app_buzzer_currentTone = APP_BUZZER_STARTUP_TONE;
    gu8_app_buzzer_currentToneRepetitionCounter = 0;

    app_buzzer_tone_set(APP_BUZZER_STARTUP_TONE);
}

void app_buzzer_tone_set(app_buzzerTone_t tone)
{
    gx_app_buzzer_currentTone = tone;
    gx_app_buzzer_currentState = APP_BUZZER_INIT;
    gu8_app_buzzer_currentToneRepetitionCounter = 0;
    u32_internalCounter = 0;
}

void app_buzzer_freq_set(uint32_t freq, uint32_t period)
{
}

void app_buzzer_state_set(uint8_t state)
{
}

void app_buzzer_update(void *arg)
{
    switch (gx_app_buzzer_currentState)
    {
    case APP_BUZZER_IDLE:
        // do nothing
        break;

    case APP_BUZZER_INIT:
        mcal_pwm_init();
        mcal_pwm_channel_set(NULL, NULL);
        mcal_pwm_channel_enable(NULL);
        gx_app_buzzer_currentState = APP_BUZZER_ON_INTERVAL;
        break;

    case APP_BUZZER_ON_INTERVAL:

        u32_internalCounter += APP_BUZZER_UPDATE_PERIOD;
        if (u32_internalCounter >= gx_app_buzzer_tones[gx_app_buzzer_currentTone].onInterval)
        {
            u32_internalCounter = 0;
            gx_app_buzzer_currentState = APP_BUZZER_OFF_INTERVAL;
            mcal_pwm_channel_disable(NULL);
            //foutputModule_state_set(BUZZER_ID, BUZZER_INACTIVE);
        }
        break;

    case APP_BUZZER_OFF_INTERVAL:

        u32_internalCounter += APP_BUZZER_UPDATE_PERIOD;
        if (u32_internalCounter >= gx_app_buzzer_tones[gx_app_buzzer_currentTone].offInterval)
        {
            u32_internalCounter = 0;
            gx_app_buzzer_currentState = APP_BUZZER_INIT;

            gu8_app_buzzer_currentToneRepetitionCounter++;
            if (gu8_app_buzzer_currentToneRepetitionCounter >= gx_app_buzzer_tones[gx_app_buzzer_currentTone].repeat)
            {
                // mcal_pwm_channel_disable(NULL);
                gx_app_buzzer_currentState = APP_BUZZER_IDLE;
                gu8_app_buzzer_currentToneRepetitionCounter = 0;
            }
        }
        break;

    default:
        // do nothing
        break;
    }
}

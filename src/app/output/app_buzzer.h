#ifndef APP_BUZZER_H
#define APP_BUZZER_H 1

#include "app/inc/def.h"

typedef enum
{
    APP_BUZZER_STARTUP_TONE,
    APP_BUZZER_HIGH_COMFORT_TONE,
    APP_BUZZER_KEY_INPUT_TONE,
    APP_BUZZER_PROCESS_FINISH_TONE,
    APP_BUZZER_PROCESS_ERROR_TONE,
	APP_BUZZER_KEY_LONG_INPUT_TONE,
    APP_BUZZER_TONE_NUM
} app_buzzerTone_t;

#define BUZZER_ACTIVE (1)
#define BUZZER_INACTIVE (0)

void app_buzzer_init(void);
void app_buzzer_tone_set(app_buzzerTone_t tone);
void app_buzzer_freq_set(uint32_t freq, uint32_t period);
void app_buzzer_state_set(uint8_t state);
void app_buzzer_update(void *arg);

#endif

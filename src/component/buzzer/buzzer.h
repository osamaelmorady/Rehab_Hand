#ifndef BUZZER_H
#define BUZZER_H

typedef enum
{
    BUZ_NO_SOUND,
    BUZ_SW_BEEP,
    BUZ_OVER_HEATING_BEEP,
    BUZ_POWER_ON_BEEP,
    BUZ_HEATING_DONE_BEEP,
    BUZ_WIFI_BEEP,
    BUZ_STANDBY_BEEP,
    BUZ_INDICATION_BEEP,
    BUZ_START_TONE,
    BUZ_COURSE_END_TONE
} tBUZSound;



void BUZ_Init(void);
void BUZ_Update(void);
void BUZ_GenerateSound(tBUZSound sound);

#endif

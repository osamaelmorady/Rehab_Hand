#include "utils/STD_TYPES.h"
#include "mcal/mcal.h"
#include "component/buzzer/buzzer.h"
#include "core/STM32F103/system/include/cmsis/stm32f10x.h"

#define BUZ_UPDATE_PERIOD_MS (20)
#define BUZ_SW_BEEP_TIME_MS (200)
#define BUZ_POWER_ON_BEEP_TIME_MS (300)
#define BUZ_STANDBY_BEEP_TIME_MS (600)
#define BUZ_INDICATION_BEEP_TIME_MS (100)
#define BUZ_OVER_HEATING_BEEP_TIME_MS (400)
#define BUZ_WIFI_BEEP_TIME_MS (100)
#define BUZ_HEATING_DONE_BEEP_TIME_MS (300)
#define BUZ_Freq_5K_T100US (100)
#define BUZ_Freq_4K_T125US (125) //125 correct /255 old water heater tone

/*******************************************************/

// define your pitch constants
// these will be notes (Freqs) that can be used to make a song
#define NOTE_B0 31
#define NOTE_C1 33
#define NOTE_CS1 35
#define NOTE_D1 37
#define NOTE_DS1 39
#define NOTE_E1 41
#define NOTE_F1 44
#define NOTE_FS1 46
#define NOTE_G1 49
#define NOTE_GS1 52
#define NOTE_A1 55
#define NOTE_AS1 58
#define NOTE_B1 62
#define NOTE_C2 65
#define NOTE_CS2 69
#define NOTE_D2 73
#define NOTE_DS2 78
#define NOTE_E2 82
#define NOTE_F2 87
#define NOTE_FS2 93
#define NOTE_G2 98
#define NOTE_GS2 104
#define NOTE_A2 110
#define NOTE_AS2 117
#define NOTE_B2 123
#define NOTE_C3 131
#define NOTE_CS3 139
#define NOTE_D3 147
#define NOTE_DS3 156
#define NOTE_E3 165
#define NOTE_F3 175
#define NOTE_FS3 185
#define NOTE_G3 196
#define NOTE_GS3 208
#define NOTE_A3 220
#define NOTE_AS3 233
#define NOTE_B3 247
#define NOTE_C4_1 260
#define NOTE_C4 262
#define NOTE_CS4 277
#define NOTE_D4 294
#define NOTE_DS4 311
#define NOTE_E4 330
#define NOTE_F4 349
#define NOTE_FS4 370
#define NOTE_G4 392
#define NOTE_GS4 415
#define NOTE_A4 440
#define NOTE_AS4 466
#define NOTE_B4 494
#define NOTE_C5 523
#define NOTE_CS5 554
#define NOTE_D5 587
#define NOTE_DS5 622
#define NOTE_E5 659
#define NOTE_F5 698
#define NOTE_FS5 740
#define NOTE_G5 784
#define NOTE_GS5 831
#define NOTE_A5 880
#define NOTE_AS5 932
#define NOTE_B5 988
#define NOTE_C6 1047
#define NOTE_CS6 1109
#define NOTE_D6 1175
#define NOTE_DS6 1245
#define NOTE_E6 1319
#define NOTE_F6 1397
#define NOTE_FS6 1480
#define NOTE_G6 1568
#define NOTE_GS6 1661
#define NOTE_A6 1760
#define NOTE_AS6 1865
#define NOTE_B6 1976
#define NOTE_C7 2093
#define NOTE_CS7 2217
#define NOTE_D7 2349
#define NOTE_DS7 2489
#define NOTE_E7 2637
#define NOTE_F7 2794
#define NOTE_FS7 2960
#define NOTE_G7 3136
#define NOTE_GS7 3322
#define NOTE_A7 3520
#define NOTE_AS7 3729
#define NOTE_B7 3951
#define NOTE_C8 4186
#define NOTE_CS8 4435
#define NOTE_D8 4699
#define NOTE_DS8 4978
#define REST 0

// Next we will set up an Array to store our notes in the melody
// An array is way to store data in a comma seperated structure.
// notes in the birthday melody:
uint16_t BirthdaymelodyNote[] = {
    NOTE_C4_1, NOTE_C4, NOTE_D4, NOTE_C4, NOTE_F4, NOTE_E4,
    NOTE_C4_1, NOTE_C4, NOTE_D4, NOTE_C4, NOTE_G4, NOTE_F4,
    NOTE_C4_1, NOTE_C4, NOTE_C5, NOTE_A4, NOTE_F4, NOTE_F4,
    NOTE_E4, NOTE_D4, NOTE_AS4, NOTE_AS4, NOTE_A4, NOTE_F4, NOTE_G4, NOTE_F4};

// note durations: 4 = quarter note (note = 1sec), 8 = eighth note, etc.
// to calculate the note duration, take one second divided by the
// note type. quarter note = 1000 / 4, eighth note = 1000/8, etc.

uint16_t BirthdaymelodyNoteDurations[] = {     //	int noteDurations[] = {
    260, 260, 500, 500, 500, 1000,             //	4, 4, 2, 2, 2, 1,
    260, 260, 500, 500, 500, 1000,             //	4, 4, 2, 2, 2, 1,
    260, 260, 500, 500, 260, 260,              //  4, 4, 2, 2, 4, 4,
    500, 1000, 260, 260, 500, 500, 500, 1000}; //	2, 1, 4, 4, 2, 2, 2, 1};

/*******************************************************/

#if 1
uint16_t StartMelody[] = {
    NOTE_C7, REST, NOTE_E5, REST, NOTE_G5, REST, NOTE_C6, REST, NOTE_C6, REST, NOTE_C6, REST, NOTE_C6};

uint16_t StartNoteDurations[] = {
    300, 40, 300, 40, 300, 60, 280, 40, 220, 40, 220, 40, 700};
#elif 0
uint16_t StartMelody[] = {
    NOTE_C3, REST, NOTE_E3, REST, NOTE_G3, REST, NOTE_C4, REST, NOTE_C4, REST, NOTE_C4, REST, NOTE_C4};

uint16_t StartNoteDurations[] = {
    500, 40, 500, 40, 500, 60, 380, 40, 380, 40, 380, 40, 1000};
#else

#endif

uint16_t EndMelodyNote[] = {
    NOTE_GS5, REST, NOTE_B6, REST, NOTE_GS7};

uint16_t EndMelodyNoteDurations[] = {
    180, 60, 200, 60, 220};

typedef enum
{
    BUZ_OFF = 0,
    BUZ_ON = 1,
    BUZ_TONE = 2
} tBUZState;

//private variables
static uint8_t BUZ_UpdateTimeMS;
static uint16_t BUZ_OnTimeValue;
static tBUZSound BUZSound;

static tBUZState BUZ_State;

static uint16_t BUZ_OnTimeCounter;
static uint16_t BUZ_ToneCounter = 0;

static uint8_t BEEPS_Number;

static uint16_t *CurrentMelody = NULL;
static uint16_t *CurrentNote = NULL;

// BUZZER set state
static void BUZ_SetState(tBUZState state);

// Public functions
/*******************************************************/
// BUZZER initialization
void BUZ_Init(void)
{
    //buzzer init
    MC_InitBuzzer(831, 50); // (hFreq, bDuty)

    BUZ_SetState(BUZ_TONE);
    BUZSound = BUZ_START_TONE;

    BUZ_UpdateTimeMS = 0;
    BUZ_OnTimeValue = 0;
    BUZ_OnTimeCounter = 0;
    BEEPS_Number = 0;
}
/*******************************************************/
// BUZZER set state
static void BUZ_SetState(tBUZState state)
{
    //CONTROL_BIT(BUZZER_PORT,BUZZER_PORTBIT,command);
    //  switch(state){
    //  	case BUZ_ON:
    //  		MC_BuzzerOutputCmd(ENABLE);
    //  		break;
    //  	case BUZ_TONE:
    //  		MC_BuzzerOutputCmd(ENABLE);
    //  		break;
    //  	case BUZ_OFF:
    //  		MC_BuzzerOutputCmd(DISABLE);
    //  		break;
    //  }
    BUZ_State = state;
}
/*******************************************************/
//buzzer update task
void BUZ_Update(void)
{
    if ((BUZSound == BUZ_OVER_HEATING_BEEP) && (BEEPS_Number < 2))
    {
        BEEPS_Number = 2;
    }

    switch (BUZ_State)
    {
    case BUZ_OFF:
        if (BEEPS_Number == 0)
        {
            //do nothing
        }
        else if (BUZ_OnTimeCounter == BUZ_OnTimeValue)
        {
            BUZ_OnTimeCounter = 0;
            BUZ_SetState(BUZ_ON);
            MC_BuzzerOutputCmd(ENABLE);
        }
        else
        {
            BUZ_OnTimeCounter += BUZ_UPDATE_PERIOD_MS;
        }
        break;

    case BUZ_ON:
        if (BEEPS_Number == 0)
        {
            //do nothing
        }
        else if (BUZ_OnTimeCounter == BUZ_OnTimeValue)
        {
            BUZ_OnTimeCounter = 0;
            BEEPS_Number--;
            BUZ_SetState(BUZ_OFF);
            MC_BuzzerOutputCmd(DISABLE);
        }
        else
        {
            BUZ_OnTimeCounter += BUZ_UPDATE_PERIOD_MS;
        }
        break;
    case BUZ_TONE:

        if (BUZ_ToneCounter == BEEPS_Number)
        {
            BUZ_SetState(BUZ_OFF);
            MC_BuzzerOutputCmd(DISABLE);
            BEEPS_Number = 0;
            //do nothing
        }
        else if (BUZ_OnTimeCounter == BUZ_OnTimeValue)
        {
            BUZ_SetState(BUZ_OFF);
            MC_BuzzerOutputCmd(DISABLE);
            BUZ_OnTimeCounter = 0;
            BUZ_ToneCounter++;
            BUZ_OnTimeValue = CurrentNote[BUZ_ToneCounter];
            if (CurrentMelody[BUZ_ToneCounter] == REST)
            {
                BUZ_SetState(BUZ_TONE);
            }
            else
            {
                MC_ConfigBuzzer(CurrentMelody[BUZ_ToneCounter], 50);
                //BEEPS_Number --;
                BUZ_SetState(BUZ_TONE);
                MC_BuzzerOutputCmd(ENABLE);
            }
        }
        else
        {
            BUZ_OnTimeCounter += BUZ_UPDATE_PERIOD_MS;
        }
        break;
    default:
        break;
    }
}
/*******************************************************/
//External function call from other modules to generate sound
void BUZ_GenerateSound(tBUZSound sound)
{
    if ((BUZSound == BUZ_OVER_HEATING_BEEP) && (sound == BUZ_OVER_HEATING_BEEP))
    {
        return;
    }
    else
    {
        //do nothing
    }
    /*
	if ((BUZSound == BUZ_SW_BEEP) && (sound == BUZ_INDICATION_BEEP))
	{
		return;
	}else
	{
		// do nothing
	}
*/
    BUZSound = sound;
    BUZ_SetState(BUZ_OFF);
    MC_BuzzerOutputCmd(DISABLE);

    switch (BUZSound)
    {
    case BUZ_NO_SOUND:
        BUZ_OnTimeValue = 0;
        //BUZZER_UPDATE_TIMER_REG(BUZ_Freq_4K_T125US);
        MC_ConfigBuzzer(4000, 50); // MC_ConfigBuzzer(hFreq, bDuty)
        BEEPS_Number = 0;
        break;
    case BUZ_SW_BEEP:
        BUZ_OnTimeValue = BUZ_SW_BEEP_TIME_MS;
        MC_ConfigBuzzer(NOTE_C7, 50);
        BEEPS_Number = 1;
        break;
    case BUZ_OVER_HEATING_BEEP:
        BUZ_OnTimeValue = BUZ_OVER_HEATING_BEEP_TIME_MS;
        MC_ConfigBuzzer(4000, 50);
        BEEPS_Number = 2;
        break;
    case BUZ_POWER_ON_BEEP:
        BUZ_OnTimeValue = BUZ_POWER_ON_BEEP_TIME_MS;
        MC_ConfigBuzzer(4000, 50);
        BEEPS_Number = 2;
        break;
    case BUZ_HEATING_DONE_BEEP:
        BUZ_OnTimeValue = BUZ_HEATING_DONE_BEEP_TIME_MS;
        MC_ConfigBuzzer(4000, 50);
        BEEPS_Number = 3;
        break;
    case BUZ_WIFI_BEEP:
        BUZ_OnTimeValue = BUZ_WIFI_BEEP_TIME_MS;
        MC_ConfigBuzzer(4000, 50);
        BEEPS_Number = 3;
        break;
    case BUZ_STANDBY_BEEP:
        BUZ_OnTimeValue = BUZ_STANDBY_BEEP_TIME_MS;
        MC_ConfigBuzzer(4000, 50);
        BEEPS_Number = 1;
        break;
    case BUZ_INDICATION_BEEP:
        BUZ_OnTimeValue = BUZ_INDICATION_BEEP_TIME_MS;
        MC_ConfigBuzzer(4000, 50);
        BEEPS_Number = 1;
        break;
    case BUZ_START_TONE:
        BUZ_OnTimeValue = StartNoteDurations[0];
        //MC_ConfigBuzzer(StartMelody[0], 50);
        BEEPS_Number = (sizeof(StartNoteDurations) / sizeof(uint16_t)); //(27);	//(26+1); (NumberOfMelodyTones+"Give the last note he time to be done.")  // duration time counter	"noteDurations[26]"
        CurrentMelody = StartMelody;
        CurrentNote = StartNoteDurations;
        BUZ_ToneCounter = 0;
        break;
    case BUZ_COURSE_END_TONE:
        BUZ_OnTimeValue = EndMelodyNoteDurations[0];
        //MC_ConfigBuzzer(melody[0], 50);
        BEEPS_Number = (sizeof(EndMelodyNoteDurations) / sizeof(uint16_t)); //(27);	//(26+1); (NumberOfMelodyTones+"Give the last note he time to be done.")  // duration time counter	"noteDurations[26]"
        CurrentMelody = EndMelodyNote;
        CurrentNote = EndMelodyNoteDurations;
        BUZ_ToneCounter = 0;
        break;
    }

    if (BUZSound == BUZ_COURSE_END_TONE)
    {
        BUZ_SetState(BUZ_TONE);
        MC_BuzzerOutputCmd(ENABLE);
        BUZ_OnTimeCounter = 0;
    }
    else if (BUZSound == BUZ_START_TONE)
    {
        BUZ_SetState(BUZ_TONE);
        MC_BuzzerOutputCmd(ENABLE);
        BUZ_OnTimeCounter = 0;
    }
    else if (BUZSound != BUZ_NO_SOUND)
    {
        BUZ_SetState(BUZ_ON);
        MC_BuzzerOutputCmd(ENABLE);
        BUZ_OnTimeCounter = 0;
    }
}
/*******************************************************/

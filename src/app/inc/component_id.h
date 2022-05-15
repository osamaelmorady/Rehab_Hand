#ifndef COMPONENTS_ID_H
#define COMPONENTS_ID_H

typedef enum
{
    PLUS_SWITCH_ID,
    MINUS_SWITCH_ID,
    STANDBY_SWITCH_ID,
    DINPUT_DEVICES_NUM
} dinputID_t;

typedef enum
{
    HEATER_LED_ID,
    STANDBY_LED_ID,
    WIFI_LED_ID,
    HEATER_ID,
    ENABLE_LED_ID,
//    A_ID,
//    B_ID,
//    C_ID,
//    D_ID,
//    E_ID,
//    F_ID,
//    G_ID,
//    Q1_ID,
//    Q2_ID,
//    CLOCK_ID,
    DOUTPUT_DEVICES_NUM
} doutputID_t;

typedef enum
{
    BUZZER_ID,
    FOUTPUT_DEVCIES_NUM
} foutputID_t;



typedef enum
{
    SERVO_1_ID,
	SERVO_2_ID,
	SERVO_3_ID,
	SERVO_4_ID,
    SERVO_DEVCIES_NUM
} ServoID_t;




typedef enum
{
    APP_FAN_SYSTEM_TIMER_ID,
    APP_FAN_ON_TIMING_TIMER_ID,
    OS_TIMERS_NUM
} osTimerID_t;

//No analog inputs for fan project
typedef enum
{
    TEMPERATURE_SENSOR_1,
    TEMPERATURE_SENSOR_2,
    AINPUT_DEVICES_NUM
} ainputID_t;

//No frequency inputs for fan project
typedef enum
{
    FINPUT_DEVCIES_NUM
} finputID_t;

//No seven segments for fan project
typedef enum
{
    SSD_DIGIT_0_ID,
    SSD_DIGIT_1_ID,
    SSD_DIGITS_NUM
} ssdID_t;

//no led matrix
typedef enum
{
    LED_NUM
} ledID_t;

typedef enum
{
    APP_LOG_ID,
    APP_LOG_NUM
} logID_t;
/*********************************************************************/
#endif

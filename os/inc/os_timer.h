#ifndef OS_TIMER_H
#define OS_TIMER_H 1

#include "app/inc/def.h"

typedef enum
{
    OS_TIMER_FREE_RUNNING_MODE,
    OS_TIMER_ALARM_MODE
} os_timer_mode_t;

typedef struct
{
    os_timer_mode_t mode;
    uint32_t periodMS;
    uint8_t repeat;
    uint8_t os_timerID;
} os_timer_t;

void os_timer_init(os_timer_t *timer);
void os_timer_delayMS_wait(uint16_t u16_delay);
uint32_t os_timer_value_get(uint8_t u8_osTimerID);
int8_t os_timer_state_get(uint8_t u8_osTimerID);
void os_timer_reset(uint8_t u8_osTimerID);
void os_timer_disable(uint8_t u8_osTimerID);
void os_timer_enable(uint8_t u8_osTimerID);
void os_timer_update(void *arg);

#endif

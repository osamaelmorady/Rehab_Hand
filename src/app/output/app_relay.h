#ifndef APP_RELAY_H
#define APP_RELAY_H 1

#include "app/inc/def.h"
/************************************************************/
#define LOAD_ACTIVE 0
#define LOAD_INACTIVE 1
/************************************************************/
void app_relay_init(void);
result_t app_relay_state_set(uint8_t relayID, uint8_t u8_state);
uint8_t app_relay_state_get(uint8_t relayID);
/************************************************************/
#endif

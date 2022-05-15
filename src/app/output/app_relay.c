/************************************************************/
#include "app/output/app_relay.h"
#include "app/inc/bsp.h"
#include "app/inc/component_id.h"
#include "app/inc/def.h"
/************************************************************/
#include "component/doutput_module/doutput_module.h"
/************************************************************/


/************************************************************/
void app_relay_init(void)
{

    /******************************* WATER HEATER ****************************************/
    doutputModule_t standby_led, heating_led, wifi_led, heater, ledEnable, ssdOnes, ssdTens;

    ledEnable.gpio.port = LED_ENABLE_PORT;
    ledEnable.gpio.pin = LED_ENABLE_PIN;
    ledEnable.gpio.state = LOAD_INACTIVE;
    ledEnable.gpio.ioState = MCAL_GPIO_OUTPUT ;	// Added By Osama Elmorady
    ledEnable.outputID = ENABLE_LED_ID;
    doutputModule_init(&ledEnable);
    doutputModule_state_set(ENABLE_LED_ID, LOAD_INACTIVE);

    standby_led.gpio.port = LED_STANDBY_PORT;
    standby_led.gpio.pin = LED_STANDBY_PIN;
    standby_led.gpio.state = LOAD_INACTIVE;
    standby_led.gpio.ioState = MCAL_GPIO_OUTPUT ;// Added By Osama Elmorady
    standby_led.outputID = STANDBY_LED_ID;
    doutputModule_init(&standby_led);
    doutputModule_state_set(STANDBY_LED_ID, LOAD_INACTIVE);

    heating_led.gpio.port = LED_RELAY_PORT;
    heating_led.gpio.pin = LED_RELAY_PIN;
    heating_led.gpio.state = LOAD_INACTIVE;
    heating_led.gpio.ioState = MCAL_GPIO_OUTPUT ;// Added By Osama Elmorady
    heating_led.outputID = HEATER_LED_ID;
    doutputModule_init(&heating_led);
    doutputModule_state_set(HEATER_LED_ID, LOAD_INACTIVE);


    heater.gpio.port = HEATER_CONTROL_PORT;
    heater.gpio.pin = HEATER_CONTROL_PIN;
    heater.gpio.state = LOAD_INACTIVE;
    heater.gpio.ioState = MCAL_GPIO_OUTPUT ;// Added By Osama Elmorady
    heater.outputID = HEATER_ID;
    doutputModule_init(&heater);

    doutputModule_state_set(HEATER_ID, LOAD_INACTIVE);
}
/************************************************************/
result_t app_relay_state_set(uint8_t relayID, uint8_t u8_state)
{
    return doutputModule_state_set(relayID, u8_state);
}
/************************************************************/
uint8_t app_relay_state_get(uint8_t relayID)
{
    return doutputModule_state_get(relayID);
}
/************************************************************/

/******************************************************************************/
/* @File            : app_door_sw.c                                    		  */
/*                                                                            */
/* @Designed by     : Ammar Shahin                         @Date : 12-7-2020  */
/*                                                                            */
/* @Designed by     : Ammar Shahin                         @Date : 12-7-2020  */
/*                                                                            */
/* @Coding language : C                                                       */
/*                                                                            */
/* @COPYRIGHT 2020 El-ARABY Research and development center.                  */
/* all rights reserved                                                        */
/******************************************************************************/

/************************************************************************/
/*                            Includes                                  */
/************************************************************************/

#include "app/inc/bsp.h"
#include "app/inc/def.h"
#include "app/input/app_temp_sensor.h"
#include "utils/utils.h"
/*********************************************************************/
#include "component/ainput_module/ainput_module.h"
#include "mcal/mcal.h"
/*********************************************************************/


/************************************************************************/
/*                         Private MACROS                               */
/************************************************************************/


/************************************************************************/
/*                           APIs(Public) Functions                      */
/************************************************************************/
void app_temp_sensor_init(void)
{
	/* Modified By Osama Elmorady */

    ainputModule_t tempSensor_1, tempSensor_2;

    mcal_adc_blkEnum_t adcBlock_1 = 0 , adcBlock_2 = 0 ;

    tempSensor_1.adcBlock = adcBlock_1;
    tempSensor_1.adcCh = SENSOR_FLANGE_CHANNEL;
    tempSensor_1.gpio.port = SENSOR_FLANGE_PORT;
    tempSensor_1.gpio.pin = SENSOR_FLANGE_PIN;
    tempSensor_1.gpio.ioState = GPIO_INPUT;
    tempSensor_1.gpio.state = GPIO_LOW;
    tempSensor_1.adcDeviceID = TEMPERATURE_SENSOR_1;

    ainputModule_init(&tempSensor_1);

    tempSensor_2.adcBlock = adcBlock_2;
    tempSensor_2.adcCh = SENSOR_DISPLAY_CHANNEL;
    tempSensor_2.gpio.port = SENSOR_DISPLAY_PORT;
    tempSensor_2.gpio.pin = SENSOR_DISPLAY_PIN;
    tempSensor_2.gpio.ioState = GPIO_INPUT;
    tempSensor_2.gpio.state = GPIO_LOW;
    tempSensor_2.adcDeviceID = TEMPERATURE_SENSOR_2;

    ainputModule_init(&tempSensor_2);

}
/*********************************************************************/


/*********************************************************************/
uint16_t app_temp_sensor_val_get(uint8_t door_id)
{
    uint16_t adc_value = 0;

    adc_value = ainputModule_value_get(door_id);

    return adc_value;
}

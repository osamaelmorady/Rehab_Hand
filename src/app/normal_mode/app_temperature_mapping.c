#include "app/inc/CONFIG.h"

#ifdef IC_HOLTEK_HT66F489
#include "MAIN_HOLTEK_HT66F489.h"
#endif

#ifdef IC_HOLTEK_HT66F0185
#include "MAIN_HOLTEK_HT66F0185.h"
#endif

#ifdef IC_AVR_ATEMGA32
#include "MAIN_AVR_ATMEGA32.h"
#endif

#ifdef IC_HOLTEK_HT46R24
#include "MAIN_HOLTEK_HT46R24.h"
#endif

#ifdef PORT_AVR_PROTEUS_TEST
#include "PORT_AVR_PROTEUS.h"
#endif

#ifdef PORT_HOTLEK_HT66F0185_TEST
#include "PORT_HOLTEK_HT66F0185_TEST.h"
#endif

#ifdef PORT_HOTLEK_HT66F0185_FINAL
#include "PORT_HOLTEK_HT66F0185_FINAL.h"
#endif

#ifdef PORT_HOTLEK_HT46R24_DWH
#include "PORT_HOLTEK_HT46R24.h"
#endif

#ifdef PORT_HOTLEK_HT66F489_FINAL
#include "PORT_HOLTEK_HT66F489_FINAL.h"
#endif

#ifdef ADC_READING_METHOD2
//#include <stdint.h>
#include <math.h>
#endif
//************

#include "app/input/app_temp_sensor.h"
#include "app/inc/config.h"
#include "utils/utils.h"
#include "app/inc/bsp.h"
#include "app/inc/def.h"
#include "utils/utils.h"
#include "app_temperature_mapping.h"
typedef enum
{
	SENSOR_N0_ERROR = 0,
	SENSOR_NOT_CONNECTED,
	SENSOR_SHORT_CIRCUIT,
	SENSOR_WATER_FRONZEN,
	SENSOR_OVER_HEATING_TEMP,
} tTSENSERROR;

static uint8_t sensorTempValue[2];
static uint8_t ADC_CurrentChannel;

//private functions
static void TSENS_MappingError(uint8_t ADC_CurrentCh, uint8_t ErrorFlag);

#ifdef ADC_READING_METHOD1
const long int AdcMap[91] = {
	3000, 2965, 2930, 2894, 2858, 2821, 2784, 2746, 2708, 2671,
	2632, 2593, 2555, 2516, 2477, 2438, 2399, 2359, 2320, 2281,
	2242, 2202, 2164, 2125, 2086, 2048, 2010, 1972, 1934, 1896,
	1859, 1822, 1786, 1750, 1714, 1678, 1643, 1609, 1575, 1541,
	1508, 1475, 1443, 1411, 1380, 1349, 1319, 1289, 1260, 1231,
	1203, 1175, 1148, 1121, 1095, 1070, 1045, 1020, 996, 972,
	949, 927, 905, 883, 862, 842, 821, 802, 783, 764,
	745, 728, 710, 693, 677, 661, 645, 629, 614, 600,
	585, 571, 558, 544, 531, 519, 506, 494, 482, 471,
	460};
#endif
/*******************************************************/
// SENSOR initialization
void temperatureSensing_init(void)
{
	sensorTempValue[0] = 0;
	sensorTempValue[1] = 0;
	ADC_CurrentChannel = TEMPERATURE_SENSOR_1;
}
/*******************************************************/
// SENSOR update
void temperatureSensing_update(void *arg)
{
	uint16_t adcReadingValue = 0;
	uint8_t ErrorFlag = 0;

#ifdef ADC_READING_METHOD1
	uint8_t arrayindex = 0;
#endif
#ifdef ADC_READING_METHOD2
	float reading = 0;
#endif

	adcReadingValue = app_temp_sensor_val_get(ADC_CurrentChannel);

#ifdef ADC_READING_METHOD1
	for (arrayindex = 0; arrayindex <= 90; arrayindex++)
	{
		if (adcReadingValue > 3500)
		{
			// value of adc reading if ntc sensor resistance[sensor is open] 1Mohm or higher
			//error status : sensor not connected
			sensorTempValue[ADC_CurrentChannel] = 99;
			ErrorFlag = SENSOR_NOT_CONNECTED;
			break;
		}
		else if (adcReadingValue >= AdcMap[2])
		{
			// water temperature equal 2 degree or less water is frozen
			//error status : water temp is frozen
			sensorTempValue[ADC_CurrentChannel] = arrayindex;
			ErrorFlag = SENSOR_WATER_FRONZEN;
			break;
		}
		else if (adcReadingValue <= 50)
		{
			//value of adc reading if ntc sensor resistance[sensor is short] 100ohm or less
			//error status : sensor short circuit
			sensorTempValue[ADC_CurrentChannel] = 97;
			ErrorFlag = SENSOR_SHORT_CIRCUIT;
			break;
		}
		else if (arrayindex >= 85)
		{
			//reach the end of the temperature measurement array
			//error status : over heating
			sensorTempValue[ADC_CurrentChannel] = 96;
			ErrorFlag = SENSOR_OVER_HEATING_TEMP;
			break;
		}
		else if (adcReadingValue >= AdcMap[arrayindex])
		{
			//operational value of adc reading
			sensorTempValue[ADC_CurrentChannel] = arrayindex;
			ErrorFlag = SENSOR_N0_ERROR;
			break;
		}
		else
		{
			//looping till end do nothing
		}
	}
	//error mapping function
	TSENS_MappingError(ADC_CurrentChannel, ErrorFlag);

#endif
#ifdef ADC_READING_METHOD2
	reading = adcReadingValue;
	// I apologize for the following code, it's based off of an Arduino Playground example
	// It seems to mumble something about being a 10K-ohm specific version of a Steinhart-Hart Thermistor Equation :-)
	reading = log(((10240000 / reading) - 10000));
	reading = 1 / (0.001129148 + (0.000234125 * reading) + (0.0000000876741 * reading * reading * reading));
	reading -= 273.15; //K to C
	//reading = (reading * 9.0)/ 5.0 + 32.0; // C to F
	sensorTempValue[ADC_CurrentChannel] = (uint8_t)reading;
#endif

	if (ADC_CurrentChannel == TEMPERATURE_SENSOR_1)
	{
		ADC_CurrentChannel = TEMPERATURE_SENSOR_2;
	}
	else
	{
		ADC_CurrentChannel = TEMPERATURE_SENSOR_1;
	}
}
/*******************************************************/
uint8_t app_temperatureSensing_get(tTSENS sensor)
{
	uint8_t SENSOR_Temp = 0;
	switch (sensor)
	{
	case TSENS_FLANGE:
		SENSOR_Temp = sensorTempValue[1];
		break;
	case TSENS_DISPLAY:
		SENSOR_Temp = sensorTempValue[0];
		break;
	}
	return SENSOR_Temp;
}
/*******************************************************/
static void TSENS_MappingError(uint8_t ADC_CurrentCh, uint8_t ErrorFlag)
{

//	if (ADC_CurrentChannel == TEMPERATURE_SENSOR_2)
//	{
//		LOGS_SetError(LOGS_FLANGE_SENSOR_NOT_CONNECTED, LOG_NO_ERROR);
//		LOGS_SetError(LOGS_FLANGE_SENSOR_WATER_FRONZEN, LOG_NO_ERROR);
//		LOGS_SetError(LOGS_FLANGE_SENSOR_OVER_HEATING_TEMP, LOG_NO_ERROR);
//		LOGS_SetError(LOGS_FLANGE_SENSOR_SHORT_CIRCUIT, LOG_NO_ERROR);
//
//		if (ErrorFlag == SENSOR_NOT_CONNECTED)
//		{
//			LOGS_SetError(LOGS_FLANGE_SENSOR_NOT_CONNECTED, LOG_ERROR);
//		}
//		else if (ErrorFlag == SENSOR_WATER_FRONZEN)
//		{
//			LOGS_SetError(LOGS_FLANGE_SENSOR_WATER_FRONZEN, LOG_ERROR);
//		}
//		else if (ErrorFlag == SENSOR_OVER_HEATING_TEMP)
//		{
//			LOGS_SetError(LOGS_FLANGE_SENSOR_OVER_HEATING_TEMP, LOG_ERROR);
//		}
//		else if (ErrorFlag == SENSOR_SHORT_CIRCUIT)
//		{
//			LOGS_SetError(LOGS_FLANGE_SENSOR_SHORT_CIRCUIT, LOG_ERROR);
//		}
//		else
//		{
//			//do nothing
//		}
//	}
//	else
//	{
//		LOGS_SetError(LOGS_DISPLAY_SENSOR_NOT_CONNECTED, LOG_NO_ERROR);
//		LOGS_SetError(LOGS_DISPLAY_SENSOR_WATER_FRONZEN, LOG_NO_ERROR);
//		LOGS_SetError(LOGS_DISPLAY_SENSOR_OVER_HEATING_TEMP, LOG_NO_ERROR);
//		LOGS_SetError(LOGS_DISPLAY_SENSOR_SHORT_CIRCUIT, LOG_NO_ERROR);
//
//		if (ErrorFlag == SENSOR_NOT_CONNECTED)
//		{
//			LOGS_SetError(LOGS_DISPLAY_SENSOR_NOT_CONNECTED, LOG_ERROR);
//		}
//		else if (ErrorFlag == SENSOR_WATER_FRONZEN)
//		{
//			LOGS_SetError(LOGS_DISPLAY_SENSOR_WATER_FRONZEN, LOG_ERROR);
//		}
//		else if (ErrorFlag == SENSOR_OVER_HEATING_TEMP)
//		{
//			LOGS_SetError(LOGS_DISPLAY_SENSOR_OVER_HEATING_TEMP, LOG_ERROR);
//		}
//		else if (ErrorFlag == SENSOR_SHORT_CIRCUIT)
//		{
//			LOGS_SetError(LOGS_DISPLAY_SENSOR_SHORT_CIRCUIT, LOG_ERROR);
//		}
//		else
//		{
//			//do nothing
//		}
//	}
}




#include "utils/STD_TYPES.h"
#include "mcal/mcal.h"

#include "core/STM32F103/stm32f10x_adc.h"
#include "core/STM32F103/stm32f10x_gpio.h"

void mcal_adc_init(void)
{

}

void mcal_adc_set(mcal_adc_blkEnum_t x_adcBlock)
{
//	ADC_vInit(0) ;
//
//	ADC_vStatusControl(ADC_ON) ;
//
//	ADC_vStartConversion();
}

void mcal_adc_channel_set(mcal_adc_blkEnum_t x_adcBlock, mcal_adc_chEnum_t x_adcCh)
{
//	ADC_vChannelSelect(x_adcCh) ;
}

void mcal_adc_conversion_start(mcal_adc_blkEnum_t x_adcBlock, mcal_adc_chEnum_t x_adcCh)
{
    /*    */
//    ADC_vStopConversion();
//
//	ADC_vChannelSelect(x_adcCh) ;
//
//	ADC_vStartConversion();
}

uint32_t mcal_adc_conversionResult_get(mcal_adc_blkEnum_t x_adcBlock, mcal_adc_chEnum_t x_adcCh)
{
    uint16_t res = 0xFF;

//    res = ADC_u16GetResult() * 16U ;

    return (uint32_t)res;
}

uint32_t mcal_adc_conversionStatus_get(mcal_adc_blkEnum_t x_adcBlock, mcal_adc_chEnum_t x_adcCh)
{
    uint8_t res = 1;

    return res;
}

void mcal_adc_flag_clear(mcal_adc_blkEnum_t x_adcBlock, mcal_adc_chEnum_t x_adcCh)
{
    //do nothing
}

#include "adc/adc.h"
#include "app/inc/config.h"
#include "mcal/mcal.h"

// NOTE: to be called only once in the app
void adc_init(adc_block_t x_adcBlock)
{
    mcal_adc_set(x_adcBlock);
}

void adc_channel_set(adc_block_t x_adcBlock, adc_channel_t x_adcCh)
{
    mcal_adc_channel_set(x_adcBlock, x_adcCh);
}

uint8_t adc_conversionState_get(adc_block_t x_adcBlock, adc_channel_t x_adcCh)
{

    return  mcal_adc_conversionStatus_get(x_adcBlock, x_adcCh);
}

void adc_flag_clear(adc_block_t x_adcBlock, adc_channel_t x_adcCh)
{
    mcal_adc_flag_clear(x_adcBlock, x_adcCh);
}

uint32_t adc_value_get(adc_block_t x_adcBlock, adc_channel_t x_adcCh)
{

    return mcal_adc_conversionResult_get(x_adcBlock, x_adcCh) ;
}

void adc_conversion_start(adc_block_t x_adcBlock, adc_channel_t x_adcCh)
{
    mcal_adc_conversion_start(x_adcBlock, x_adcCh);
}

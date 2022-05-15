#include "utils/STD_TYPES.h"
#include "mcal/mcal.h"

void mcal_dac_init(void)
{
    // do nothing
}

void mcal_dac_set(mcal_dac_blkEnum_t *x_dacBlock)
{
 //   DAC_Init();
}

void mcal_dac_channel_set(mcal_dac_blkEnum_t *x_dacBlock, mcal_dac_chEnum_t x_dacCh)
{
   // DAC_Enable(x_dacCh);
}

void mcal_dac_channel_enable(mcal_dac_blkEnum_t *x_dacBlock, mcal_dac_chEnum_t x_dacCh)
{
    //DAC_Enable(x_dacCh);
}

void mcal_dac_channel_disable(mcal_dac_blkEnum_t *x_dacBlock, mcal_dac_chEnum_t x_dacCh)
{
    //DAC_Disable(x_dacCh);
}

void mcal_dac_value_set(mcal_dac_blkEnum_t *x_dacBlock, mcal_dac_chEnum_t x_dacCh, float value)
{
    //DAC_Value_Set(x_dacCh, value);
}

uint8_t mcal_dac_conversionStatus_get(mcal_dac_blkEnum_t *x_dacBlock, mcal_dac_chEnum_t x_dacCh)
{
    return 1;
}

void mcal_dac_flag_clear(mcal_dac_blkEnum_t *x_dacBlock, mcal_dac_chEnum_t x_dacCh)
{
    // do nothing
}

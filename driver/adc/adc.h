#ifndef ADC_H
#define ADC_H

#include "mcal/mcal.h"
#include "app/inc/config.h"

typedef mcal_adc_chEnum_t adc_channel_t;
#define ADC_CH_0 MCAL_ADC_CH0
#define ADC_CH_1 MCAL_ADC_CH1
#define ADC_CH_2 MCAL_ADC_CH2
#define ADC_CH_3 MCAL_ADC_CH3
#define ADC_CH_4 MCAL_ADC_CH4
#define ADC_CH_5 MCAL_ADC_CH5
#define ADC_CH_6 MCAL_ADC_CH6
#define ADC_CH_7 MCAL_ADC_CH7
#define ADC_CH_8 MCAL_ADC_CH8
#define ADC_CH_9 MCAL_ADC_CH9
#define ADC_CH_10 MCAL_ADC_CH10
#define ADC_CH_11 MCAL_ADC_CH11
#define ADC_CH_12 MCAL_ADC_CH12
#define ADC_CH_13 MCAL_ADC_CH13
#define ADC_CH_14 MCAL_ADC_CH14
#define ADC_CH_15 MCAL_ADC_CH15
#define ADC_CH_16 MCAL_ADC_CH16
#define ADC_CH_17 MCAL_ADC_CH17
#define ADC_CH_18 MCAL_ADC_CH18
#define ADC_CH_19 MCAL_ADC_CH19
#define ADC_CH_20 MCAL_ADC_CH20
#define ADC_CH_21 MCAL_ADC_CH21
#define ADC_CH_22 MCAL_ADC_CH22
#define ADC_CH_23 MCAL_ADC_CH23
#define ADC_CH_24 MCAL_ADC_CH24

typedef mcal_adc_blkEnum_t adc_block_t;
#define ADC_BLK_A MCAL_ADC_BLK_A
#define ADC_BLK_B MCAL_ADC_BLK_B

void adc_init(adc_block_t x_adcBlock);
void adc_channel_set(adc_block_t x_adcBlock, adc_channel_t x_adcCh);
void adc_conversion_start(adc_block_t x_adcBlock, adc_channel_t x_adcCh);
uint32_t adc_value_get(adc_block_t x_adcBlock, adc_channel_t x_adcCh);
void adc_update(void *arg);
uint32_t adc_valueImmed_get(adc_block_t x_adcBlock, adc_channel_t x_adcCh);

#endif

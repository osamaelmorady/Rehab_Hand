/************************************************************/
#include "app/inc/component_id.h"
#include "app/inc/def.h"
#include "app/inc/bsp.h"
/************************************************************/
#include "component/ssd/ssd.h"
/************************************************************/
void app_ssd_init(void)
{
    ssd_t ssdDigits;

/* Modified By Osama Elmorady */
    ssdDigits.ssdDataPort[0] = SSD_A_PORT;
    ssdDigits.ssdDataPin[0] = SSD_A_PIN;
    ssdDigits.ssdDataPort[1] = SSD_B_PORT;
    ssdDigits.ssdDataPin[1] = SSD_B_PIN;
    ssdDigits.ssdDataPort[2] = SSD_C_PORT;
    ssdDigits.ssdDataPin[2] = SSD_C_PIN;
    ssdDigits.ssdDataPort[3] = SSD_D_PORT;
    ssdDigits.ssdDataPin[3] = SSD_D_PIN;
    ssdDigits.ssdDataPort[4] = SSD_E_PORT;
    ssdDigits.ssdDataPin[4] = SSD_E_PIN;
    ssdDigits.ssdDataPort[5] = SSD_F_PORT;
    ssdDigits.ssdDataPin[5] = SSD_F_PIN;
    ssdDigits.ssdDataPort[6] = SSD_G_PORT;
    ssdDigits.ssdDataPin[6] = SSD_G_PIN;

    ssdDigits.ssdID = SSD_DIGIT_1_ID;
    ssdDigits.ssdDigitPort = SSD_ONES_SELECT_PORT;
    ssdDigits.ssdDigitPin = SSD_ONES_SELECT_PIN;
    ssdDigits.initialState_qValue = 1;

    ssd_init(&ssdDigits);


    ssdDigits.ssdID = SSD_DIGIT_0_ID;
    ssdDigits.ssdDigitPort = SSD_TENS_SELECT_PORT;
    ssdDigits.ssdDigitPin = SSD_TENS_SELECT_PIN;
    ssdDigits.initialState_qValue = 1;

    ssd_init(&ssdDigits);
}
/************************************************************/
void app_ssd_value_set(uint8_t ssdID, ssd_symbolEnum_t symbol)
{
    ssd_value_set(ssdID, symbol);
}
/************************************************************/
void app_ssd_dp_set(uint8_t u8_ssdID, uint8_t u8_dpState)
{
    ssd_dp_set(u8_ssdID, u8_dpState);
}
/************************************************************/
void app_ssd_clear(void)
{
    ssd_reset();
}
/************************************************************/

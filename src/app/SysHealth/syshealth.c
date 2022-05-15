/**********************************************************************/
/*                                                                    */
/*  FILE        : R5F11BBC_ADC_config.h                     		 */
/*  DATE        : Tue, Aug 24, 2021                                  */
/*  Last Update : Tue, Aug 24, 2021                            		   */
/*  DESCRIPTION : ADC config  Header                     			 */
/*  CPU GROUP   : R5F11BBC                                            */
/*  Author      : Osama ElMorady						          	  */
/*                          						                  */
/***********************************************************************/

#include "app/output/app_ssd.h"



/********************************************************************************/
void sysHealth_update(void *arg)
{
    static uint8_t var[] = {SSD_SEG_A, SSD_SEG_B, SSD_SEG_C, SSD_SEG_D, SSD_SEG_E, SSD_SEG_F, SSD_SEG_G};
    static uint8_t i = 0;
    char buff[5] = {0};

    app_ssd_value_set(SSD_DIGIT_0_ID, i % 10);
    app_ssd_value_set(SSD_DIGIT_1_ID, i % 10);
    i++;
    if (i == 9)
    {
        i = 0;
    }

    if (0 /*!var*/)
    {
//                var = 1;
//         doutputModule_state_set(B_ID, LOAD_ACTIVE);
         app_ssd_value_set(SSD_DIGIT_0_ID, 80 / 10);
         app_ssd_value_set(SSD_DIGIT_1_ID, 8 % 10);
    }
    else if (0)
    {
//                var = 0;
//         doutputModule_state_set(B_ID, LOAD_INACTIVE);
        app_ssd_value_set(SSD_DIGIT_0_ID, SSD_NULL_SYMBOL);
        app_ssd_value_set(SSD_DIGIT_1_ID, SSD_NULL_SYMBOL);
    }
}
/*******************************************************************************************/





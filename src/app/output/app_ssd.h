#ifndef APP_SSD_H
#define APP_SSD_H
/************************************************************/
#include "app/inc/def.h"
#include "component/ssd/ssd.h"
/************************************************************/
void app_ssd_init(void);
void app_ssd_value_set(uint8_t ssdID, ssd_symbolEnum_t symbol);
void app_ssd_dp_set(uint8_t u8_ssdID, uint8_t u8_dpState);
void app_ssd_clear(void);
/************************************************************/

#endif

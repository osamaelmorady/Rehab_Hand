/*******************************************************************************************/
#include "app/inc/config.h"
#include "app/inc/bsp.h"
#include "app/inc/def.h"
#include "utils/utils.h"
#include "os/inc/os.h"
/*******************************************************************************************/
#include "app/input/app_temp_sensor.h"
#include "app/input/SW.h"
/*****************************************/
#include "app/output/app_relay.h"
#include "app/output/app_buzzer.h"
#include "app/output/app_ssd.h"
/*****************************************/
#include "app/normal_mode/app_temperature_mapping.h"
/*****************************************/

/*******************************************************************************************/
#include "component/doutput_module/doutput_module.h"
#include "component/dinput_module/dinput_module.h"
#include "component/ainput_module/ainput_module.h"
#include "component/ssd/ssd.h"
/*******************************************************************************************/
#include "driver/uart/uart.h"
#include "driver/gpio/gpio.h"
#include "driver/adc/adc.h"
#include "driver/wdt/wdt.h"
/*******************************************************************************************/
#include "mcal/mcal.h"
/*******************************************************************************************/

/*******************************************************************************************/
#define NULL ((void *)'\0')
/*******************************************************************************************/

/*******************************************************************************************/
void app_startup_init(void)
{
	MNVIC_EnuInit()  ;






//	    SW_Init(SW_PLUS);
//	    SW_Init(SW_MINUS);
//	    SW_Init(SW_STANDBY);
//	    SW_Init(SW_TURBO);


#if !APP_USE_WDT
    wdt_disable();
#endif


#if	USE_VLTD
//	mcal_onChip_vdet1_init(0);
#endif

#if INTERNAL_EEPROM
//	EROM_Init();
#endif

#if BUZZER_USED
	app_buzzer_init();
#endif


#if APP_USE_WDT == 1
   wdt_init();
#endif

   }
/*******************************************************************************************/


/*******************************************************************************************/
void app_startupTasks_create(void)
{

#if APP_USE_WDT == 1
   os_scheduler_task_add(wdt_update, NULL, 0, WDT_UPDATE_PERIOD_MS);
#endif

   // os_scheduler_task_add(sysHealth_update, NULL, 0, 1000);

   /* Inputs */
   os_scheduler_task_add(SW_Update, NULL, 100, 20);
   os_scheduler_task_add(ainputModule_update, NULL, 0, 10);

    /* Mode Update */



    /* Outputs */
    os_scheduler_task_add(doutputModule_update, NULL, 200, 10);
    os_scheduler_task_add(app_buzzer_update, NULL, 200, 10);


     /* Software timer */
     os_scheduler_task_add(os_timer_update, NULL, 0, 10);

    /**/
    // os_scheduler_task_add(uart_update, NULL, 0, UART_UPDATE_PERIOD_MS);

}

/********************************************************************************/

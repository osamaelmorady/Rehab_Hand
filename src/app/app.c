#include "app/inc/app.h"
#include "app/inc/app_startup.h"
#include "app/inc/bsp.h"
#include "app/inc/config.h"
#include "app/inc/def.h"
#include "os/inc/os.h"
#include "utils/utils.h"
/************************************************************/
//static uint8_t *TAG = "app";


/************************************************************/
void app_init(void)
{
    app_startup_init();
    app_startupTasks_create();
//    LOG_I("App Init Done..!");
}
/************************************************************/

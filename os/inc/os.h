#ifndef OS_H
#define OS_H 1

#include "os/inc/os_tick.h"
#include "os/inc/os_timer.h"
#include "os/inc/os_runtime.h"
#include "os/inc/os_log.h"
#include "os/inc/os_scheduler.h"
#include "mcal/mcal.h"

#define OS_POR_RESET_FLAG MCAL_POR_REST_FLAG
#define OS_EXT_RESET_FLAG MCAL_EXT_RESET_FLAG
#define OS_WDT_RESET_FLAG MCAL_WDT_RESET_FLAG
#define OS_VLTD_RESET_FLAG MCAL_VLTD_RESET_FLAG
#define OS_DEBUG_RESET_FLAG MCAL_DEBUG_RESET_FLAG
#define OS_OFD_RESET_FLAG MCAL_OFD_RESET_FLAG

#endif

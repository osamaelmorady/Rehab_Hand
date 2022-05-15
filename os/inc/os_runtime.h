#if STRUCT_USE_SDS == 0
// do not use this module in sds
#ifndef OS_RUNTIME_H
#define OS_RUNTIME_H 1

#include "app/inc/def.h"

void os_runTime_init(void);
void os_runTime_userTask_register(void (*p)(void), uint8_t repeated);
void os_runTime_update(void *arg);

#endif
#endif

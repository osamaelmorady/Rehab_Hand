#ifndef BSP_H
#define BSP_H

#include "app/inc/def.h"
#include "mcal/mcal.h"

#if defined(TMPM370)
#include "app/inc/bsp_tmpm370.h"
#elif defined(C17M24)
#include "app/inc/bsp_c17m24.h"
#elif defined(R5F11BBC)
#include "app/inc/bsp_R5F11BBC.h"
#elif defined(STM32F103)
#include "app/inc/bsp_STM32F103.h"
#endif


#define CRITICAL_SECTION_START() MCAL_GLOBAL_INTERRUPTS_DISABLE()
#define CRITICAL_SECTION_END() MCAL_GLOBAL_INTERRUPTS_ENABLE()

void bsp_clockConfig_set(void);
void bsp_interruptPriorities_set(void);

#endif

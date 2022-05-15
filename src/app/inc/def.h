#ifndef DEF_H
#define DEF_H

#ifndef F_OSC
#define F_OSC 20000000UL
#endif

#define F_CPU 32000000
#define PLL_FACTOR (1)



//#define TMPM370
//#define C17M24
//#define R5F11BBC
//#define ren33c
#define STM32F103

#include "mcal/mcal.h"

typedef enum
{
    OP_SUCCESS = 0,
    OP_FAILED = -1
} result_t;

typedef enum
{
    false = 0,
    true = 1
} bool_t;

#endif

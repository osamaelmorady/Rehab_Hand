#ifndef OS_SCH_H
#define OS_SCH_H 1

#include "mcal.h"

#if STRUCT_USE_SDS == 1
typedef struct
{
    uint32_t delay;
    uint32_t period;
    uint8_t run;
    int8_t taskID;
    void *args;
} os_sch_taskHandle_t;
#else
typedef struct
{
    uint32_t delay;
    uint32_t period;
    uint8_t run;
    void (*task)(void *args);
    void *args;
} os_sch_taskHandle_t;
#endif

typedef enum
{
    OS_SCH_NO_FAULT,
    OS_SCH_TASK_OVERFLOW_FAULT,
    OS_SCH_SYS_CLOCK_FAULT
} os_sch_fault_t;

#if STRUCT_USE_SDS == 1
void os_scheduler_init(void);
void os_scheduler_start(void);
void os_scheduler_dispatch(void);
void os_scheduler_update(void);
void os_scheduler_parameters_fill(uint32_t u32_delay, uint32_t u32_period);
uint8_t os_scheduler_release_check(void);

#define os_scheduler_task_add(task, args, u32_delay, u32_period) \
    do                                                           \
    {                                                            \
        os_scheduler_parameters_fill(u32_delay, u32_period);     \
        if (os_scheduler_release_check())                        \
        {                                                        \
            task(args);                                          \
        }                                                        \
    } while (0)

#define os_scheduler_task_delete(task, taskID, u32_delay, u32_period)

#else
void os_scheduler_init(void);
void os_scheduler_start(void);
void os_scheduler_task_add(void (*task)(void *), void *args, uint32_t u32_delay, uint32_t u32_period);
void os_scheduler_task_delete(void (*task)(void *), void *args);
void os_scheduler_taskHigherPri_set(void (*task)(void *));
void os_scheduler_dispatch(void);
void os_scheduler_update(void);
uint32_t *os_scheduler_tasksTimeline_get(void);
uint32_t *os_scheduler_wcetTasksTimeline_get(void);
uint8_t os_scheduler_taskOverRunFlag_get(void);
os_sch_fault_t os_scheduler_fault_get(void);
void os_scheduler_fault_set(os_sch_fault_t fault);
#endif

#endif

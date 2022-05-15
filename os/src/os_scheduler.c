#include "app/inc/config.h"
#include "os/inc/os.h"

#define OS_SCHEDULER_MAX_NUM_OF_TASKS (OS_SCHEDULER_USER_TASKS_NUM + OS_SCHEDULER_SYSTEM_TASKS_NUM)

static os_sch_taskHandle_t gx_os_scheduler_inetrnalUserTaskHandler[OS_SCHEDULER_MAX_NUM_OF_TASKS];
volatile uint32_t gu32_os_scheduler_tasksTimeline[OS_SCHEDULER_MAX_NUM_OF_TASKS] = {0};
volatile uint32_t gu32_os_scheduler_wcettasksTimeline[OS_SCHEDULER_MAX_NUM_OF_TASKS] = {0};
static uint8_t gu8_os_scheduler_taskRelease_flag = 0, gu8_os_scheduler_taskOverRun_flag = 0;
static os_sch_fault_t gu8_os_scheduler_fault = OS_SCH_NO_FAULT;

#if STRUCT_USE_SDS == 1

static uint8_t gu8_os_scheduler_sdsTaskCnt = 0, gu8_os_scheduler_rdy_flag = 0;

void os_scheduler_init(void)
{
    uint8_t i = 0;
    for (i = 0; i < OS_SCHEDULER_MAX_NUM_OF_TASKS; i++)
    {
        gx_os_scheduler_inetrnalUserTaskHandler[i].delay = 0;
        gx_os_scheduler_inetrnalUserTaskHandler[i].period = 0;
        gx_os_scheduler_inetrnalUserTaskHandler[i].run = 0;
        gx_os_scheduler_inetrnalUserTaskHandler[i].taskID = -1;
        gx_os_scheduler_inetrnalUserTaskHandler[i].args = NULL;
    }
    gu8_os_scheduler_sdsTaskCnt = 0;
    gu8_os_scheduler_rdy_flag = 0;
}
#else
void os_scheduler_init(void)
{
    uint8_t i = 0;
    for (i = 0; i < OS_SCHEDULER_MAX_NUM_OF_TASKS; i++)
    {
        gx_os_scheduler_inetrnalUserTaskHandler[i].delay = 0;
        gx_os_scheduler_inetrnalUserTaskHandler[i].period = 0;
        gx_os_scheduler_inetrnalUserTaskHandler[i].run = 0;
        gx_os_scheduler_inetrnalUserTaskHandler[i].task = NULL;
        gx_os_scheduler_inetrnalUserTaskHandler[i].args = NULL;
    }
}
#endif

void os_scheduler_start(void)
{
    os_tick_init(OS_TICK_PERIOD_MS);

#if STRUCT_USE_SDS == 1
    gu8_os_scheduler_rdy_flag = 1;
#else
//    mcal_timer_timerState_set(MCAL_TIMER_0, MCAL_TIMER_STOP);
//    mcal_timer_timerFlag_clear(MCAL_TIMER_0);
//    mcal_timer_timerModeUS_init(MCAL_TIMER_0, 10);
//    mcal_timer_timerState_set(MCAL_TIMER_0, MCAL_TIMER_START);
#endif

    os_scheduler_update();

    for (;;)
    {
        os_scheduler_dispatch();
    }
}

#if STRUCT_USE_SDS == 0
uint32_t *os_scheduler_tasksTimeline_get(void)
{
    return gu32_os_scheduler_tasksTimeline;
}

uint32_t *os_scheduler_wcetTasksTimeline_get(void)
{
    return gu32_os_scheduler_wcettasksTimeline;
}

uint8_t os_scheduler_taskOverRunFlag_get(void)
{
    return gu8_os_scheduler_taskOverRun_flag;
}

os_sch_fault_t os_scheduler_fault_get(void)
{
    return gu8_os_scheduler_fault;
}

void os_scheduler_fault_set(os_sch_fault_t fault)
{
    gu8_os_scheduler_fault = fault;
}
#endif

#if STRUCT_USE_SDS == 0
void os_scheduler_task_add(void (*task)(void *), void *args, uint32_t u32_delay, uint32_t u32_period)
{
    uint8_t i = 0;
    for (i = 0; i < OS_SCHEDULER_MAX_NUM_OF_TASKS; i++)
    {
        if (gx_os_scheduler_inetrnalUserTaskHandler[i].task == NULL)
        {
            gx_os_scheduler_inetrnalUserTaskHandler[i].delay = u32_delay;
            gx_os_scheduler_inetrnalUserTaskHandler[i].period = u32_period;
            gx_os_scheduler_inetrnalUserTaskHandler[i].run = 0;
            gx_os_scheduler_inetrnalUserTaskHandler[i].task = task;
            gx_os_scheduler_inetrnalUserTaskHandler[i].args = args;
            return;
        }
    }
    gu8_os_scheduler_fault = OS_SCH_TASK_OVERFLOW_FAULT;
}
#endif

#if STRUCT_USE_SDS == 0
void os_scheduler_task_delete(void (*task)(void *), void *args)
{
    uint8_t i = 0;
    for (i = 0; i < OS_SCHEDULER_MAX_NUM_OF_TASKS; i++)
    {
        if ((gx_os_scheduler_inetrnalUserTaskHandler[i].task == task) && (gx_os_scheduler_inetrnalUserTaskHandler[i].args == args))
        {
            gx_os_scheduler_inetrnalUserTaskHandler[i].task = NULL;
            break;
        }
    }
}
#endif

#if STRUCT_USE_SDS == 1
void os_scheduler_parameters_fill(uint32_t u32_delay, uint32_t u32_period)
{
    if (gx_os_scheduler_inetrnalUserTaskHandler[gu8_os_scheduler_sdsTaskCnt].taskID == -1 && gu8_os_scheduler_rdy_flag == 0)
    {
        gx_os_scheduler_inetrnalUserTaskHandler[gu8_os_scheduler_sdsTaskCnt].delay = u32_delay;
        gx_os_scheduler_inetrnalUserTaskHandler[gu8_os_scheduler_sdsTaskCnt].period = u32_period;
        gx_os_scheduler_inetrnalUserTaskHandler[gu8_os_scheduler_sdsTaskCnt].run = 0;
        gx_os_scheduler_inetrnalUserTaskHandler[gu8_os_scheduler_sdsTaskCnt].taskID = gu8_os_scheduler_sdsTaskCnt;
        gu8_os_scheduler_sdsTaskCnt++;
    }
}

uint8_t os_scheduler_release_check(void)
{
    static uint8_t releaseCnt = 0;
    uint8_t ret = 0;
    if (gu8_os_scheduler_rdy_flag)
    {
        if (gx_os_scheduler_inetrnalUserTaskHandler[releaseCnt].run > 0)
        {
            gx_os_scheduler_inetrnalUserTaskHandler[releaseCnt].run--;
            ret = 1;
        }
        releaseCnt++;
        if (releaseCnt >= gu8_os_scheduler_sdsTaskCnt)
        {
            releaseCnt = 0;
        }
    }

    return ret;
}
#endif

#if STRUCT_USE_SDS == 1
void os_scheduler_dispatch(void)
{
    // do nothing
}
#else
void os_scheduler_dispatch(void)
{
    uint8_t i = 0;
    uint32_t tmp;

    for (i = 0; i < OS_SCHEDULER_MAX_NUM_OF_TASKS; i++)
    {
        if (gx_os_scheduler_inetrnalUserTaskHandler[i].task != NULL && gx_os_scheduler_inetrnalUserTaskHandler[i].run > 0)
        {
            mcal_timer_timerState_set(MCAL_TIMER_0, MCAL_TIMER_STOP);
            mcal_timer_timerFlag_clear(MCAL_TIMER_0);
            mcal_timer_timerState_set(MCAL_TIMER_0, MCAL_TIMER_START);

            gu8_os_scheduler_taskRelease_flag = 1;
            gx_os_scheduler_inetrnalUserTaskHandler[i].run--;
            gx_os_scheduler_inetrnalUserTaskHandler[i].task(gx_os_scheduler_inetrnalUserTaskHandler[i].args);
            gu8_os_scheduler_taskRelease_flag = 0;

            if (gx_os_scheduler_inetrnalUserTaskHandler[i].period == 0)
            {
                gx_os_scheduler_inetrnalUserTaskHandler[i].task = NULL;
            }

            tmp = mcal_timer_timerCounter_get(MCAL_TIMER_0);
            gu32_os_scheduler_tasksTimeline[i] = tmp;

            if (gu32_os_scheduler_wcettasksTimeline[i] < tmp)
            {
                gu32_os_scheduler_wcettasksTimeline[i] = tmp;
            }
        }
    }
}
#endif

#if STRUCT_USE_SDS == 1
void os_scheduler_update(void)
{
    uint8_t i = 0;
    for (i = 0; i < OS_SCHEDULER_MAX_NUM_OF_TASKS; i++)
    {
        if (gx_os_scheduler_inetrnalUserTaskHandler[i].taskID != -1)
        {
            if (gx_os_scheduler_inetrnalUserTaskHandler[i].delay > 0)
                gx_os_scheduler_inetrnalUserTaskHandler[i].delay -= OS_TICK_PERIOD_MS;

            if (gx_os_scheduler_inetrnalUserTaskHandler[i].delay == 0)
            {
                gx_os_scheduler_inetrnalUserTaskHandler[i].delay = gx_os_scheduler_inetrnalUserTaskHandler[i].period;
                gx_os_scheduler_inetrnalUserTaskHandler[i].run++;
            }
        }
    }

    if (gu8_os_scheduler_taskRelease_flag)
    {
        gu8_os_scheduler_taskOverRun_flag = 1;
    }
}
#else
// FIX: compensated by enabling the systick inside the systick interrupt. to make
//      the systick timer running in the background even inside the systick interrupt

// TODO: with 1 msec tick, the time it blocks to update the tasks
//       it causes deviation in the overall time. to reduce this
//       by increasing the tick time. find another way.

// TODO: add a time compensator. it can use the systick to check how much it took to
//       update the tasks and compensate for it

// NOTE: with higher number of tasks it causes more issue with timing.
void os_scheduler_update(void)
{
    uint8_t i = 0;
    for (i = 0; i < OS_SCHEDULER_MAX_NUM_OF_TASKS; i++)
    {
        if (gx_os_scheduler_inetrnalUserTaskHandler[i].task != NULL)
        {
            if (gx_os_scheduler_inetrnalUserTaskHandler[i].delay > 0)
                gx_os_scheduler_inetrnalUserTaskHandler[i].delay -= OS_TICK_PERIOD_MS;

            if (gx_os_scheduler_inetrnalUserTaskHandler[i].delay == 0)
            {
                gx_os_scheduler_inetrnalUserTaskHandler[i].delay = gx_os_scheduler_inetrnalUserTaskHandler[i].period;
                gx_os_scheduler_inetrnalUserTaskHandler[i].run++;
            }
        }
    }

    // TODO: do i need to clear it?
    if (gu8_os_scheduler_taskRelease_flag)
    {
        gu8_os_scheduler_taskOverRun_flag = 1;
    }
}
#endif

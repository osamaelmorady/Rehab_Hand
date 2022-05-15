#ifndef OS_LOG_H
#define OS_LOG_H 1

// TODO: add append functionality
// TODO: add log display levels

#include "app/inc/def.h"
#include <stdarg.h>
#include <stdio.h>
#include "app/inc/config.h"

extern uint32_t gu32_os_tick_timestamp;

#define OS_LOG_TRAILING_KEEP (0)
#define OS_LOG_TRAILING_RESET (1)

#define COLOR_NONE 0
#define COLOR_ERR 31
#define COLOR_WRN 33
#define CLR_INF 32
#define COLOR_DEBUG 0
#define COLOR_VERBOSE 0

#define CLR_HD "\033[0;%dm"
#define LOG_BOLD_HEAD "\033[1;%dm"
#define CLR_E "\033[0m"

//extern uint8_t gu8_os_log_dispBuf[];
typedef uint8_t os_logID_t;

#if OS_LOG_USE_PRINTF == 1
#define printf(format, ...) os_log_printf(format, ##__VA_ARGS__)
#else
#define printf(format, ...)
#endif

int os_log_vsnprintf(char *buffer, unsigned int buffer_len, const char *fmt, va_list va);
int os_log_snprintf(char *buffer, unsigned int buffer_len, const char *fmt, ...);
int os_log_printf(const char *fmt, ...);

#define LOG_I(format, ...)                                                                                             \
    do                                                                                                                 \
    {                                                                                                                  \
        printf(CLR_HD "[%c] (%d) %s - [%s - %-4u] : ", CLR_INF, 'I', gu32_os_tick_timestamp, TAG, __func__, __LINE__); \
        printf((format), ##__VA_ARGS__);                                                                               \
        printf("%s\n\r", CLR_E);                                                                                       \
    } while (0)

#define LOG_E(format, ...)                                                                  \
    do                                                                                      \
    {                                                                                       \
        printf(CLR_HD "[%c] %s - [%s - %-4u] : ", COLOR_ERR, 'I', TAG, __func__, __LINE__); \
        printf((format), ##__VA_ARGS__);                                                    \
        printf("%s\n\r", CLR_E);                                                            \
    } while (0)

#define LOG_W(format, ...)                                                                  \
    do                                                                                      \
    {                                                                                       \
        printf(CLR_HD "[%c] %s - [%s - %-4u] : ", COLOR_WRN, 'I', TAG, __func__, __LINE__); \
        printf((format), ##__VA_ARGS__);                                                    \
        printf("%s\n\r", CLR_E);                                                            \
    } while (0)

int8_t os_log_add(os_logID_t logID, uint16_t size);
int8_t os_log_write(os_logID_t logID, uint8_t *data, uint8_t size, uint8_t clearTrailing);
int8_t os_log_read(os_logID_t logID, uint8_t *data, uint8_t size);

#endif

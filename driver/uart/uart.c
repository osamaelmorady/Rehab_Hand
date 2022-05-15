#include "app/inc/config.h"
#include "uart/uart.h"
#include "mcal/mcal.h"
#include "app/inc/def.h"
#include "driver/ssw_uart/ssw_uart.h"

#define UART_UPDATE_TIME_UTILIZATION_FACTOR(x) (((x) * (20.0f)) / (100.0f))
#define UART_CONVERT_BPS_TO_MSEC(x) ((10000.0f) / (x))
#define UART_CONVERT_BPS_TO_USEC(x) ((10000000.0f) / (x))
#define UART_ALLOWED_MULTIPLE_BYTES_PERIOD_US (100ul)

static uint8_t gx_uart_interfacesCount = 0;

typedef struct
{
    uart_t actualInterface;
    uart_t virtualInterface;
    uint8_t multiplier;
    uint8_t counter;
    int8_t dataSentFlag;
    uint8_t bytesNum;
} uart_mappingStructure_t;

static uart_mappingStructure_t gx_uart_map[UART_INTERFACES_NUM];

// NOTE: always the idx must be higher in value than its corresponding id0
static uint32_t gau32_uart_recvBufID0[UART_INTERFACES_NUM];   // index at which the s/w will read from
static uint32_t gau32_uart_recvBufIDx[UART_INTERFACES_NUM];   // index at which the h/w will write received data to

static uint32_t gau32_uart_transBufID0[UART_INTERFACES_NUM];   // index at which the h/w will read what data to send
static uint32_t gau32_uart_transBufIDx[UART_INTERFACES_NUM];   // index at which the s/w will put data to be sent later by h/w

static uint8_t gaau8_uart_recvBuffer[UART_INTERFACES_NUM][UART_RECV_BUFFER_SIZE];
static uint8_t gaau8_uart_transBuffer[UART_INTERFACES_NUM][UART_TRANS_BUFFER_SIZE];

//static bool_t gb_uart_initDone_flag = false;

static void uart_dataReg_put(uart_t uartx, const uint8_t character);
static void uart_dataReg_get(uart_t uartx, uart_t vInterface);

void uart_init(uart_t uartx, uart_config_t *uartConfig)
{
    gx_uart_map[gx_uart_interfacesCount].actualInterface = uartx;
    gx_uart_map[gx_uart_interfacesCount].virtualInterface = gx_uart_interfacesCount;
    // gx_uart_map[gx_uart_interfacesCount].multiplier = (uint32_t)((float)(UART_UPDATE_TIME_UTILIZATION_FACTOR(UART_UPDATE_PERIOD_MS)) / (UART_CONVERT_BPS_TO_MSEC(uartConfig->baudRate))) + 1;

    // if (gx_uart_map[gx_uart_interfacesCount].multiplier == 0)
    // {
    //     gx_uart_map[gx_uart_interfacesCount].multiplier = 1;
    // }

    gx_uart_map[gx_uart_interfacesCount].multiplier = (uint32_t)(UART_CONVERT_BPS_TO_MSEC(uartConfig->baudRate)) + 1 + uartConfig->chainInterval;
    gx_uart_map[gx_uart_interfacesCount].counter = 0;
    gx_uart_map[gx_uart_interfacesCount].dataSentFlag = 1;
    if ((uint32_t)(UART_CONVERT_BPS_TO_USEC(uartConfig->baudRate)) < UART_ALLOWED_MULTIPLE_BYTES_PERIOD_US)
    {
        gx_uart_map[gx_uart_interfacesCount].bytesNum = 2;
    }
    else
    {
        gx_uart_map[gx_uart_interfacesCount].bytesNum = 1;
    }

    gx_uart_interfacesCount++;

    if (uartx != UART_SW)
    {
        mcal_uart_channel_set(uartx, uartConfig);
    }
#if SSW_UART_ENABLED == 1
    else if (uartx == UART_SW)
    {
        ssw_uart_init(uartConfig);
    }
#endif
}

#if 0
void uart_deinit(void)
{
    gu32_uart_recvBufID0 = 0;
    gu32_uart_recvBufIDx = 0;
    gu32_uart_transBufID0 = 0;
    gu32_uart_transBufIDx = 0;

    gb_uart_initDone_flag = false;
}
#endif

void uart_update(void *arg)
{
    uint8_t u8_i = 0, u8_j = 0;
    for (u8_i = 0; u8_i < gx_uart_interfacesCount; u8_i++)
    {
        gx_uart_map[u8_i].counter++;
        if (gx_uart_map[u8_i].counter >= gx_uart_map[u8_i].multiplier)
        {
            gx_uart_map[u8_i].counter = 0;
            if (gau32_uart_transBufIDx[u8_i] > gau32_uart_transBufID0[u8_i])
            {
                for (u8_j = 0; u8_j < gx_uart_map[u8_i].bytesNum && gau32_uart_transBufIDx[u8_i] > gau32_uart_transBufID0[u8_i]; u8_j++)
                {
                    uart_dataReg_put(gx_uart_map[u8_i].actualInterface, gaau8_uart_transBuffer[u8_i][gau32_uart_transBufID0[u8_i]]);
                    gau32_uart_transBufID0[u8_i]++;
                }
                // uart_dataReg_put(gx_uart_map[u8_i].actualInterface, gaau8_uart_transBuffer[u8_i][gau32_uart_transBufID0[u8_i]]);
                // gau32_uart_transBufID0[u8_i]++;
                gx_uart_map[u8_i].dataSentFlag = 0;
            }
            else
            {
                gau32_uart_transBufID0[u8_i] = 0;
                gau32_uart_transBufIDx[u8_i] = 0;
                gx_uart_map[u8_i].dataSentFlag = 1;
            }

            if (gau32_uart_recvBufID0[u8_i] == gau32_uart_recvBufIDx[u8_i])
            {
                gau32_uart_recvBufID0[u8_i] = 0;
                gau32_uart_recvBufIDx[u8_i] = 0;
            }
        }

        // check if there is any received data
        /* if (UART_RECV_COMPLETE_FLAG_CHECK())
        {
            if (gu32_uart_recvBufID0 == gu32_uart_recvBufIDx)
            {
                gu32_uart_recvBufID0 = 0;
                gu32_uart_recvBufIDx = 0;
            }

            uart_data_recv();
            //UART_RECV_COMPLETE_FLAG_CLEAR();
        } */
    }

#if SSW_UART_ENABLED == 1
    if (ssw_uart_recv_check() == 1)
    {
        uart_recv_int(UART_SW);
    }
#endif
}

int8_t uart_dataSent_check(uart_t uartx)
{
    uart_t vInterface;
    uint8_t u8_i;

    for (u8_i = 0; u8_i < gx_uart_interfacesCount; u8_i++)
    {
        if (gx_uart_map[u8_i].actualInterface == uartx)
        {
            vInterface = gx_uart_map[u8_i].virtualInterface;
            return gx_uart_map[vInterface].dataSentFlag;
        }
    }

    return -1;
}

void uart_byte_put(uart_t uartx, const uint8_t character)
{
    uart_t vInterface;
    uint8_t u8_i;

    for (u8_i = 0; u8_i < gx_uart_interfacesCount; u8_i++)
    {
        if (gx_uart_map[u8_i].actualInterface == uartx)
        {
            vInterface = gx_uart_map[u8_i].virtualInterface;
            if (gau32_uart_transBufIDx[vInterface] < UART_TRANS_BUFFER_SIZE)
            {
                gaau8_uart_transBuffer[vInterface][gau32_uart_transBufIDx[vInterface]] = character;
                gau32_uart_transBufIDx[vInterface]++;
                gx_uart_map[vInterface].dataSentFlag = 0;
            }
        }
    }
}

void uart_reset(uart_t uartx)
{
    gau32_uart_transBufID0[uartx] = 0;
    gau32_uart_transBufIDx[uartx] = 0;
    gx_uart_map[uartx].dataSentFlag = 1;
}

void uart_data_put(uart_t uartx, uint8_t *pData)
{
    uint8_t i = 0;
    for (i = 0; pData[i] != '\0'; i++)
    {
        uart_byte_put(uartx, pData[i]);
    }
}

static void uart_dataReg_put(uart_t uartx, const uint8_t character)
{
    if (uartx != UART_SW)
    {
        mcal_uart_data_put(uartx, character);
    }
#if SSW_UART_ENABLED == 1
    else if (uartx == UART_SW)
    {
        ssw_uart_send(character);
    }
#endif
}

bool_t uart_recv_check(uart_t uartx)
{
    uart_t vInterface;
    uint8_t u8_i;

    for (u8_i = 0; u8_i < gx_uart_interfacesCount; u8_i++)
    {
        if (gx_uart_map[u8_i].actualInterface == uartx)
        {
            vInterface = gx_uart_map[u8_i].virtualInterface;
            if (gau32_uart_recvBufID0[vInterface] < gau32_uart_recvBufIDx[vInterface])
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    }

    return false;
}

#if UART_RX_INT == 1
static void uart_dataReg_get(uart_t uartx, uart_t vInterface)
{
    if (gau32_uart_recvBufIDx[vInterface] < UART_RECV_BUFFER_SIZE)
    {
        if (uartx != UART_SW)
        {
            gaau8_uart_recvBuffer[vInterface][gau32_uart_recvBufIDx[vInterface]] = mcal_uart_data_get(uartx);
        }
#if SSW_UART_ENABLED == 1
        else if (uartx == UART_SW)
        {
            gaau8_uart_recvBuffer[vInterface][gau32_uart_recvBufIDx[vInterface]] = ssw_uart_get();
        }
#endif

        /*if (gu8_uart_recvBuffer[gu32_uart_recvBufIDx] == '\n' || gu8_uart_recvBuffer[gu32_uart_recvBufIDx] == '\r')
        {
            gu8_uart_recvBuffer[gu32_uart_recvBufIDx] = '\0';
        }*/
        //uart_char_set(gu8_uart_recvBuffer[gu32_uart_recvBufIDx]);
        gau32_uart_recvBufIDx[vInterface]++;
    }
}

uint8_t uart_byte_get(uart_t uartx)
{
    uint8_t retValue = 0;
    uart_t vInterface;
    uint8_t u8_i;

    for (u8_i = 0; u8_i < gx_uart_interfacesCount; u8_i++)
    {
        if (gx_uart_map[u8_i].actualInterface == uartx)
        {
            vInterface = gx_uart_map[u8_i].virtualInterface;
            if (gau32_uart_recvBufID0[vInterface] < gau32_uart_recvBufIDx[vInterface])
            {
                retValue = gaau8_uart_recvBuffer[vInterface][gau32_uart_recvBufID0[vInterface]];
                gau32_uart_recvBufID0[vInterface]++;
            }
            else
            {
                return 0;
            }
            return retValue;
        }
    }

    return 0;
}

// NOTE: gets the whole data in the receiver buffer and returns the number of read data, otherwise return -1
int16_t uart_bytesAvailable_get(uart_t uartx, uint8_t *pData)
{
    uart_t vInterface;
    uint8_t j = 0;
    uint8_t u8_i;

    for (u8_i = 0; u8_i < gx_uart_interfacesCount; u8_i++)
    {
        if (gx_uart_map[u8_i].actualInterface == uartx)
        {
            vInterface = gx_uart_map[u8_i].virtualInterface;
            while (gau32_uart_recvBufID0[vInterface] < gau32_uart_recvBufIDx[vInterface])
            {
                pData[j] = gaau8_uart_recvBuffer[vInterface][gau32_uart_recvBufID0[vInterface]];
                gau32_uart_recvBufID0[vInterface]++;
                j++;
            }
            // gau32_uart_recvBufID0[vInterface] = 0;
            // gau32_uart_recvBufIDx[vInterface] = 0;
            return j;
        }
    }

    return -1;
}

void uart_string_get(uart_t uartx, uint8_t *pString)
{
    uint8_t i = 0, character = 0;
    for (i = 0; (character = uart_byte_get(uartx)) != 0; i++)
    {
        pString[i] = character;
    }
    if (pString[i] == '\n' || pString[i] == '\r')
        pString[i] = '\0';
}

void uart_data_get(uart_t uartx, uint8_t *pData, uint8_t size)
{
    uint8_t i = 0, character = 0;
    for (i = 0; (character = uart_byte_get(uartx)) != 0 && i < size; i++)
    {
        pData[i] = character;
    }
}

void uart_recv_int(uart_t uartx)
{
    uart_t vInterface;
    uint8_t u8_i;

    for (u8_i = 0; u8_i < gx_uart_interfacesCount; u8_i++)
    {
        if (gx_uart_map[u8_i].actualInterface == uartx)
        {
            vInterface = gx_uart_map[u8_i].virtualInterface;
            uart_dataReg_get(uartx, vInterface);
            if (gau32_uart_recvBufID0[vInterface] == gau32_uart_recvBufIDx[vInterface])
            {
                gau32_uart_recvBufID0[vInterface] = 0;
                gau32_uart_recvBufIDx[vInterface] = 0;
            }
        }
    }
}
#endif

void uart_multiplier_get(uint8_t *pData)
{
    uint8_t i;
    for (i = 0; i < UART_INTERFACES_NUM; i++)
    {
        pData[i] = gx_uart_map[i].multiplier;
    }
}

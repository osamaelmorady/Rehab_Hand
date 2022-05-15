#include "component/ssd/ssd.h"
#include "app/inc/config.h"
#include "app/inc/def.h"
#include "driver/gpio/gpio.h"

/*
//7seg symbol
	aaaaa
	f	b
	ggggg	
	e	c
	ddddd	
*/
#define SSD_SYMBOLS (SSD_SYMMBOL_NUM)
const uint8_t gau8_ssd_dataArray[SSD_SYMBOLS] =
    {
        //0bHGFEDCBA
        ~0x3F, //~0b00111111, // 0
        ~0x06, //~0b00000110, // 1
        ~0x5B, //~0b01011011, // 2
        ~0x4F, //~0b01001111, // 3
        ~0x66, //~0b01100110, // 4
        ~0x6D, //~0b01101101, // 5
        ~0x7D, //~0b01111101, // 6
        ~0x07, //~0b00000111, // 7
        ~0xFF, //~0b01111111, // 8
        ~0x6F, //~0b01101111, // 9
        ~0x77, //~0b01110111, // A
        ~0x7C, //~0b01111100, // B
        ~0x39, //~0b00111001, // C
        ~0x5E, //~0b01011110, // D
        ~0x79, //~0b01111001, // E
        ~0x71, //~0b01110001, // F
        ~0x6F, //~0b01101111, // G
        ~0x74, //~0b01110100, // h
        ~0x30, //~0b00110000, // I
        ~0x0E, //~0b00001110, // J
        ~0x00, //~0b00000000, // K---
        ~0x08, //~0b00001000, // 1 dash
        ~0x50, //~0b01010000, // r
        ~0x6D, //~0b01101101, // S
        ~0x78, //~0b01111000, // t---
        ~0x31, //~0b00110001, // R---
        ~0x3E, //~0b00111110, // U
        ~0x37, //~0b00110111, // n---
        ~0x73, //~0b01110011, // P
        ~0x1C, //~0b00011100, // u
        ~0x76, //~0b01110110, // H
        ~0x5E, //~0b01011110, // d
        ~0x38, //~0b00111000, // L
        ~0x7F, //~0b10000000, // dot
        ~0x00, //~0b00000000, // NULL
        ~0x7B, //~0b01111011, // e
        ~0x5F, //~0b01011111, // a
        ~0x49, //~0b01001001, //Triple Dash
        ~0x01, //~0b00000001, //seg a
        ~0x02, //~0b00000010, //seg b
        ~0x04, //~0b00000100, //seg c
        ~0x08, //~0b00001000, //seg d
        ~0x10, //~0b00010000, //seg e
        ~0x20, //~0b00100000, //seg f
        ~0x40, //~0b01000000, //seg g
        ~0xff  //~0b11111111, //ALL_ON
};

typedef struct
{
    ssd_t ssd;
    uint8_t ssdData;
    uint8_t ssdDP;
} ssd_internalHandler_t;

static uint8_t gu8_ssd_internalCounter = 0;
static ssd_internalHandler_t gx_ssd_internalHandler[SSD_DIGITS_NUMBER];

void ssd_init(ssd_t *x_ssd)
{
    uint8_t i = 0;

    for (i = 0; i < SSD_DATA_PINS; i++)
    {
        gx_ssd_internalHandler[gu8_ssd_internalCounter].ssd.ssdDataPort[i] = x_ssd->ssdDataPort[i];
        gx_ssd_internalHandler[gu8_ssd_internalCounter].ssd.ssdDataPin[i] = x_ssd->ssdDataPin[i];
        gpio_pinIOState_set(gx_ssd_internalHandler[gu8_ssd_internalCounter].ssd.ssdDataPort[i], gx_ssd_internalHandler[gu8_ssd_internalCounter].ssd.ssdDataPin[i], GPIO_OUTPUT);
    }

    gx_ssd_internalHandler[gu8_ssd_internalCounter].ssd.ssdDigitPort = x_ssd->ssdDigitPort;
    gx_ssd_internalHandler[gu8_ssd_internalCounter].ssd.ssdDigitPin = x_ssd->ssdDigitPin;
    gx_ssd_internalHandler[gu8_ssd_internalCounter].ssd.ssdID = x_ssd->ssdID;
    gx_ssd_internalHandler[gu8_ssd_internalCounter].ssd.initialState_qValue = x_ssd->initialState_qValue;

    //ssd_data_set(gx_ssd_internalHandler[gu8_ssd_internalCounter].ssd.ssdID);
    /*gpio_pinState_set , gpio_pinIOState_set  --->  Swapped to set value first, then set pin direction with the old data handled in core layer */
    gpio_pinState_set(gx_ssd_internalHandler[gu8_ssd_internalCounter].ssd.ssdDigitPort, gx_ssd_internalHandler[gu8_ssd_internalCounter].ssd.ssdDigitPin, gx_ssd_internalHandler[gu8_ssd_internalCounter].ssd.initialState_qValue);  // 2
    gpio_pinIOState_set(gx_ssd_internalHandler[gu8_ssd_internalCounter].ssd.ssdDigitPort, gx_ssd_internalHandler[gu8_ssd_internalCounter].ssd.ssdDigitPin, GPIO_OUTPUT);															// 1

    gx_ssd_internalHandler[gu8_ssd_internalCounter].ssdData = gau8_ssd_dataArray[SSD_NULL_SYMBOL];
    gx_ssd_internalHandler[gu8_ssd_internalCounter].ssdDP = SSD_DP_OFF;

    gu8_ssd_internalCounter++;
}

void ssd_value_set(uint8_t u8_ssdID, ssd_symbolEnum_t x_symbol)
{
    uint8_t i = 0;

    for (i = 0; i < gu8_ssd_internalCounter; i++)
    {
        if (u8_ssdID == gx_ssd_internalHandler[i].ssd.ssdID)
        {
            gx_ssd_internalHandler[i].ssdData = gau8_ssd_dataArray[x_symbol];
        }
    }
}

void ssd_segment_set(uint8_t u8_ssdID, seg_t x_segment)
{
    uint8_t i = 0;

    for (i = 0; i < gu8_ssd_internalCounter; i++)
    {
        if (u8_ssdID == gx_ssd_internalHandler[i].ssd.ssdID)
        {
            gx_ssd_internalHandler[i].ssdData = ~(x_segment);
        }
    }
}

ssd_symbolEnum_t ssd_value_get(uint8_t u8_ssdID)
{
    uint8_t i = 0;
    ssd_symbolEnum_t ret = SSD_NULL_SYMBOL;

    for (i = 0; i < gu8_ssd_internalCounter; i++)
    {
        if (u8_ssdID == gx_ssd_internalHandler[i].ssd.ssdID)
        {
            ret = gx_ssd_internalHandler[i].ssdData;
        }
    }

    return ret;
}

void ssd_reset(void)
{
    uint8_t i = 0;

    for (i = 0; i < gu8_ssd_internalCounter; i++)
    {

        gx_ssd_internalHandler[i].ssdData = gau8_ssd_dataArray[SSD_NULL_SYMBOL];
    }
}

void ssd_dp_set(uint8_t u8_ssdID, uint8_t u8_dpState)
{
    uint8_t i = 0;

    for (i = 0; i < gu8_ssd_internalCounter; i++)
    {
        if (u8_ssdID == gx_ssd_internalHandler[i].ssd.ssdID)
        {
            gx_ssd_internalHandler[i].ssdDP = u8_dpState;
        }
    }
}

void ssd_data_set(uint8_t u8_ssdID)
{
    uint8_t ssd_data = 0;
    uint8_t i = 0, loc = 0;

    for (i = 0; i < gu8_ssd_internalCounter; i++)
    {
        if (u8_ssdID == gx_ssd_internalHandler[i].ssd.ssdID)
        {
#if (SSD_COM_ANODE == 1)
            if (gx_ssd_internalHandler[i].ssdDP == SSD_DP_OFF)
            {
                ssd_data = gx_ssd_internalHandler[i].ssdData | (1 << 7);
            }
            else if (gx_ssd_internalHandler[i].ssdDP == SSD_DP_ON)
            {
                ssd_data = gx_ssd_internalHandler[i].ssdData & ~(1 << 7);
            }
#elif (SSD_COM_CATHODE == 1)
            if (gx_ssd_internalHandler[i].ssdDP == SSD_DP_OFF)
            {
                ssd_data = ~(gx_ssd_internalHandler[i].ssdData & ~(1 << 7));
            }
            else if (gx_ssd_internalHandler[i].ssdDP == SSD_DP_ON)
            {
                ssd_data = ~(gx_ssd_internalHandler[i].ssdData | (1 << 7));
            }
#endif
            loc = i;
            break;
        }
    }

    for (i = 0; i < SSD_DATA_PINS; i++)
    {
        gpio_pinState_set(gx_ssd_internalHandler[loc].ssd.ssdDataPort[i], gx_ssd_internalHandler[loc].ssd.ssdDataPin[i], ((ssd_data >> i) & 0x01));
    }
}

void ssd_data_clear(uint8_t u8_ssdID)
{
    uint8_t ssd_data = 0;
    uint8_t i = 0, loc = 0;

    for (i = 0; i < gu8_ssd_internalCounter; i++)
    {
        if (u8_ssdID == gx_ssd_internalHandler[i].ssd.ssdID)
        {
#if (SSD_COM_ANODE == 1)
            ssd_data = 0xff;
#elif (SSD_COM_CATHODE == 1)
            ssd_data = 0x00;
#endif
            loc = i;
            break;
        }
    }

    for (i = 0; i < SSD_DATA_PINS; i++)
    {
        gpio_pinState_set(gx_ssd_internalHandler[loc].ssd.ssdDataPort[i], gx_ssd_internalHandler[loc].ssd.ssdDataPin[i], ((ssd_data >> i) & 0x01));
    }
}

void ssd_digit_set(uint8_t u8_ssdID, uint8_t x_state)
{
    uint8_t i = 0;

    for (i = 0; i < gu8_ssd_internalCounter; i++)
    {
        if (u8_ssdID == gx_ssd_internalHandler[i].ssd.ssdID)
        {
            gpio_pinState_set(gx_ssd_internalHandler[i].ssd.ssdDigitPort, gx_ssd_internalHandler[i].ssd.ssdDigitPin, x_state);
        }
    }
}

void ssd_update(void *arg)
{
    static uint8_t gx_ssd_currentSSD = 0;
    uint8_t i = 0;

    for (i = 0; i < gu8_ssd_internalCounter; i++)
    {
        ssd_digit_set(gx_ssd_internalHandler[i].ssd.ssdID, SSD_OFF);
    }

    ssd_data_set(gx_ssd_internalHandler[gx_ssd_currentSSD].ssd.ssdID);
    ssd_digit_set(gx_ssd_internalHandler[gx_ssd_currentSSD].ssd.ssdID, SSD_ON);

    if (gx_ssd_currentSSD >= gu8_ssd_internalCounter)
    {
        gx_ssd_currentSSD = 0;
    }
    else
    {
        gx_ssd_currentSSD++;
    }
}

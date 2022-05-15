#include "app/inc/def.h"
#include "app/inc/config.h"
#include "app/inc/bsp.h"
#include "app/inc/component_id.h"

#include "mcal/mcal.h"



#define SERVO_MODULES_NUM	(3)



typedef enum
{
	Servo_Trigger_LOW ,
	Servo_Trigger_HIGH ,

}Servo_Trigger_t ;




typedef struct
{
    uint8_t activechannel;
    uint8_t Triggerpulse;
    uint8_t startdegree;
    uint8_t enddegree;
} Servo_internalHandler_t;

static uint8_t gu8_servo_internalCounter = 0;
static Servo_internalHandler_t gx_dinputModule_internalHandler[SERVO_MODULES_NUM];





static mcal_pwmConfig_t pwm_a8 ;


void SERVO_vInit(Servo_internalHandler_t * servo_config)
{

    gx_dinputModule_internalHandler[gu8_servo_internalCounter].activechannel = MCAL_PWM_0;


	pwm_a8.freq=50 ;
	pwm_a8.duty=0 ;
	mcal_pwm_channel_set(MCAL_PWM_0,&pwm_a8)  ;
	mcal_pwm_channelState_set(MCAL_PWM_0, ENABLE) ;


}



void SERVO_vSet(ServoID_t servo_num)
{



}

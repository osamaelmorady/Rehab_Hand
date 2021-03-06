#include "utils/utils.h"
#include "utils/STD_TYPES.h"
#include "utils/BIT_MATH.h"

#include "core/STM32F103/system/include/cmsis/stm32f10x.h"

#include "core/STM32F103/MNVIC/MNVIC_Interface.h"
#include "core/STM32F103/MNVIC/MNVIC_Private.h"
#include "core/STM32F103/MNVIC/MNVIC_Config.h"












/********************************************************/
/********************************************************/
/********************************************************/
ErrorStatus	 MNVIC_EnuInit(void)
{
	SCB -> AIRCR = IRQ_SUB_GROUP_DISTRIBUTION ;
	
	return SUCCESS ;
}





/********************************************************/
/********************************************************/
/********************************************************/
ErrorStatus 	MNVIC_EnuEnableIRQ(IRQ_ID Copy_U8INTID)
{
	
	MNVIC -> ISER[ Copy_U8INTID/32 ]  |= ( 1 << ( Copy_U8INTID % 32 ) )  ;
	
	return SUCCESS ;
	
}




/********************************************************/
/********************************************************/
/********************************************************/
ErrorStatus 	MNVIC_EnuDisableIRQ(IRQ_ID Copy_U8INTID)
{
	
	MNVIC -> ICER[ Copy_U8INTID/32 ]  &= ~( 1 << ( Copy_U8INTID % 32 ) )  ;
	
	return SUCCESS ;
	
}








/********************************************************/
/********************************************************/
/********************************************************/
ErrorStatus 	MNVIC_EnuSetPendingIRQ(IRQ_ID Copy_U8INTID)
{
	
	MNVIC -> ISPR[ Copy_U8INTID/32 ]  |= ( 1 << ( Copy_U8INTID % 32 ) )  ;
	
	return SUCCESS ;
	
}




/********************************************************/
/********************************************************/
/********************************************************/
ErrorStatus	 MNVIC_EnuClearPendingIRQ(IRQ_ID Copy_U8INTID)
{

	MNVIC -> ICPR[ Copy_U8INTID/32 ]  &= ~( 1 << ( Copy_U8INTID % 32 ) )  ;
	
	return SUCCESS ;
	
}







/********************************************************/
/********************************************************/
/********************************************************/
ErrorStatus	 MNVIC_EnuGetIRQActiveFlag( IRQ_ID Copy_U8INTID , u8 * Copy_PU8ActiveFlagValue )
{
	
	* Copy_PU8ActiveFlagValue = GET_BIT( MNVIC -> IABR[ Copy_U8INTID/32 ] , ( Copy_U8INTID % 32 ) ) ;
	
	return SUCCESS ;
	
}











/********************************************************/
/********************************************************/
/********************************************************/
ErrorStatus 	MNVIC_EnuSetIRQPriority( IRQ_ID Copy_U8INTID ,u8 Copy_U8GroupPriority , u8 Copy_U8SubPriority)
{
	// GROUP_SUB_STEP = 0 : 4  --->  0 BIT_GROUP TO 4 BIT_GROUP
	u8 Local_U8PriorityValue  = ( Copy_U8SubPriority | (Copy_U8GroupPriority << GROUP_SUB_STEP )) << 4  ;
	
	if (Copy_U8INTID >= 0)
	{
		MNVIC -> IPR[Copy_U8INTID] =  Local_U8PriorityValue ;
		
	}
	else 
	{
		Copy_U8INTID=  -Copy_U8INTID - 4 ;
		
		SCB -> SHPR[Copy_U8INTID/4] = Local_U8PriorityValue ;
	
	}
	
	
	return SUCCESS ;
}
























#include "utils/utils.h"
#include "utils/STD_TYPES.h"
#include "utils/BIT_MATH.h"

#include "core/STM32F103/system/include/cmsis/stm32f10x.h"

#include "core/STM32F103/MSTK/MSTK_Interface.h"
#include "core/STM32F103/MSTK/MSTK_Private.h"
#include "core/STM32F103/MSTK/MSTK_Config.h"


u32 tick_counter;


/****************************************************************************************************/
/****************************************************************************************************/
ErrorStatus  MSTK_EnuTimerInit(void)
{
	/* Disable SysTick ,, Disable INT ,, CLK source = User_defined   */
	MSTK -> CTRL = MSTK_CLKSOURCE     ;
	
	/* Reset Preload Value to 0 ,, Reset Flag to 0 */
	MSTK -> VAL = 0 ;
	
	return SUCCESS ;
}


/****************************************************************************************************/
/****************************************************************************************************/
ErrorStatus  MSTK_EnuTimerPreload(uint32_t period_us)
{
	MSTK -> LOAD = period_us ;

	return SUCCESS ;
}



/****************************************************************************************************/
/****************************************************************************************************/
ErrorStatus  MSTK_EnuStartTimer( void )
{
	/*Start the Timer*/
	SET_BIT( MSTK -> CTRL , 0) ;

	return SUCCESS ;
}




/****************************************************************************************************/
/****************************************************************************************************/
ErrorStatus  MSTK_EnuStopTimer( void )
{
	/*Stop the Timer*/
	CLR_BIT( MSTK -> CTRL , 0) ;
	
	return SUCCESS ;
}




/****************************************************************************************************/
/****************************************************************************************************/
ErrorStatus  MSTK_EnuInterruptStatus( SYS_STATUS_t status )
{
	switch (status)
	{
	case SYS_TICK_INT_DISABLE :
	
		CLR_BIT( MSTK -> CTRL , 1) ;
	
		break;
	case SYS_TICK_INT_ENABLE:

		SET_BIT( MSTK -> CTRL , 1) ;

		break;
	
	}
	
	return SUCCESS ;
}




/****************************************************************************************************/
/****************************************************************************************************/
ErrorStatus  MSTK_EnuClearFlag( void )
{
	/*To Clear the CountFlag ,Read The Flag_Bit */
	u8 LOC_u8ReadFlag = GET_BIT( MSTK -> CTRL , 16 )	;
	
	return SUCCESS ;
}




/****************************************************************************************************/
/****************************************************************************************************/
ErrorStatus  MSTK_EnuGetElapsedTime( u32 * Copy_PU32TimerElapsedValue )
{
	* Copy_PU32TimerElapsedValue =  ( MSTK -> LOAD ) - ( MSTK -> VAL ) ;
	
	return SUCCESS ;
}




/****************************************************************************************************/
/****************************************************************************************************/
ErrorStatus  MSTK_EnuGetRemainingTime( u32 * Copy_PU32TimerRemainingValue )
{
	
	* Copy_PU32TimerRemainingValue =  MSTK -> VAL ;
	
	return SUCCESS ;
}










/****************************************************************************************************/
/****************************************************************************************************/
#define NULL '\0'
static void (*FUN_PTR)(void) = NULL ;

static  u8  MSTK_U32HelperVal = 1 ;
/****************************************************************************************************/
/****************************************************************************************************/

ErrorStatus 	MSTK_EnuSingleInterval   ( u32 Copy_U32TimePeriod , void ( *Copy_PFun )( void ) )
{
	/* Reset And Load */
	CLR_BIT( MSTK -> CTRL , 0) ;
	MSTK -> VAL = 0            ;
	MSTK -> LOAD = Copy_U32TimePeriod  ;
	
	/*Start the Timer*/
	SET_BIT( MSTK -> CTRL , 0) ;
	SET_BIT( MSTK -> CTRL , 1) ;
	
	FUN_PTR = Copy_PFun ;
	
	MSTK_U32HelperVal = MSTK_SINGLE_INTERVAL ;
	
	return SUCCESS ;
}







ErrorStatus 	MSTK_EnuPeriodicInterval ( u32 Copy_U32TimePeriod , void ( *Copy_PFun )( void ) )
{
	/* Reset And Load */
	CLR_BIT( MSTK -> CTRL , 0) ;
	MSTK -> VAL = 0            ;
	MSTK -> LOAD = Copy_U32TimePeriod  ;
	
	/*Start the Timer*/
	SET_BIT( MSTK -> CTRL , 0) ;
	SET_BIT( MSTK -> CTRL , 1) ;
	
	FUN_PTR = Copy_PFun ;
	
	MSTK_U32HelperVal = MSTK_PERIODIC_INTERVAL ;
	
	return SUCCESS ;
} 






//void SysTick_Handler(void)
//{
//	/*To Clear the CountFlag ,Read The Flag_Bit */
//	u8 LOC_u8ReadFlag = GET_BIT( MSTK -> CTRL , 16 )	;
//
//	if ( MSTK_U32HelperVal == MSTK_SINGLE_INTERVAL )
//	{
//		MSTK -> CTRL = MSTK_CLKSOURCE ;
//		MSTK -> VAL  = 0 ;
//		MSTK -> LOAD = 0 ;
//	}
//
//	 tick_counter++ ;
//
//	FUN_PTR() ;
//
//
//}








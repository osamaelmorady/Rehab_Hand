#ifndef		_MSTK_INTERFACE_H_
#define		_MSTK_INTERFACE_H_





typedef enum
{
	SYS_TICK_INT_DISABLE = 0 ,
	SYS_TICK_INT_ENABLE ,

}SYS_STATUS_t ;



ErrorStatus  MSTK_EnuTimerInit(void) ;


ErrorStatus  MSTK_EnuTimerPreload(uint32_t period_us) ;


ErrorStatus  MSTK_EnuStartTimer( void ) ;


ErrorStatus  MSTK_EnuStopTimer( void ) ;


ErrorStatus  MSTK_EnuInterruptStatus( SYS_STATUS_t status ) ;


ErrorStatus  MSTK_EnuClearFlag( void );


ErrorStatus  MSTK_EnuGetElapsedTime( u32 * Copy_PU32TimerElapsedValue ) ;



ErrorStatus  MSTK_EnuGetRemainingTime( u32 * Copy_PU32TimerRemainingValue ) ;







ErrorStatus 	MSTK_EnuSingleInterval   ( u32 Copy_U32TimePeriod , void ( *Copy_PFun )( void ) );




ErrorStatus 	MSTK_EnuPeriodicInterval ( u32 Copy_U32TimePeriod , void ( *Copy_PFun )( void ) );





#endif

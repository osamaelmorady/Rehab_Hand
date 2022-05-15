/***********************************************************************/
/*                                                                     */
/*  FILE        :bit_math.h                                            */
/*  DATE        :Mon, July 14, 2021                                    */
/*  DESCRIPTION :define the bit math operations                        */
/*  CPU GROUP   :  Generic                                             */
/*  AUTHOR      :Osama ElMorady                                        */
/***********************************************************************/



#ifndef _BIT_MATH_H_
#define _BIT_MATH_H_






/* SET BITx in PORTx */
#define SET_BIT(REG,PIN_NUMBER)		(REG|=(1<<PIN_NUMBER))


/* CLEAR BITx in PORTx */
#define CLR_BIT(REG,PIN_NUMBER)		(REG&=~(1<<PIN_NUMBER))


/* TOGGLE BITx in PORTx */
#define TOGGLE_BIT(REG,PIN_NUMBER)		(REG^=(1<<PIN_NUMBER))







#endif
/*_BIT_MATH_H_*/
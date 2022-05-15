/*******************************************************************************
* Title                 :   Data Flash
* Filename              :   mcal_ren33c_dataFlash.c
* Author                :   Abdelaziz Moustafa
* Origin Date           :   08/23/2020
* Version               :   1.0.0
*
*******************************************************************************/

/*******************************************************************************
 * Includes
 *******************************************************************************/
#include "utils/STD_TYPES.h"
#include "mcal/mcal.h"
//#include "core/STM32F103/DF/STM32F103_DF.h"


/*********************************************************************************
*                          Public Function Definitions
*********************************************************************************/

/**
 * @brief Function that Erases an entire flash block.
 * 
 * @param pStr_dataFlash Pointer to the data Flash structure.
 * @return uint8_t  0 : Erase Successful @n
		            1 : Erase error reported by flash control @n
		            2 : Command Sequence Error (locked block, incorrect command, etc)
 */
uint8_t mcal_flashData_erase(mcal_dataFlash_t *pStr_dataFlash)
{
    uint8_t ret_value;

//    ret_value = DF_eEraseBlock(pStr_dataFlash -> dataFlash_block)   ;

    return ret_value;
}
/**
 * @brief Function that writes bytes into flash.
 * 
 * @param pStr_dataFlash Pointer to the data Flash structure.
 * @return uint8_t 0 : Operation Successful @n
		           1 : Write Error reported by flash control register @n
		           2 : Invalid parameter passed @n
		           3 : Command Sequence Error (locked block, incorrect command, etc)
 */
uint8_t mcal_flashData_write(mcal_dataFlash_t *pStr_dataFlash)
{
    uint8_t ret_value;

//    ret_value = DF_eWriteBytes(pStr_dataFlash -> dataFlash_block , 	pStr_dataFlash -> dataFlash_blockAddress,
//								pStr_dataFlash -> dataFlash_dataBuffer,	pStr_dataFlash -> dataFlash_bytes )   ;

    return ret_value;
}
/**
 * @brief Function that reads a Byte from Data Flash.
 * 
 * @param pStr_dataFlash Pointer to the data Flash structure.
 * @return uint8_t  data stored in that Flash address.
 */
uint8_t mcal_flashData_read(mcal_dataFlash_t *pStr_dataFlash)
{
    uint8_t data;

//    data = DF_eWriteBytes(pStr_dataFlash -> dataFlash_block , 	pStr_dataFlash -> dataFlash_blockAddress,
//								pStr_dataFlash -> dataFlash_dataBuffer,	pStr_dataFlash -> dataFlash_bytes )   ;

    return data;
}

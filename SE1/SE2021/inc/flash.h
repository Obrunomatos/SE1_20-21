/**
* @file		flash.h
* @brief	Contains the flash API.
* @version	1.0
* @date		18 Jan 2021
* @author	Bruno Matos
*
* Copyright(C) 2020-2021, Bruno Matos
* All rights reserved.
*
*/


#ifndef FLASH_H_
#define FLASH_H_

/** @defgroup FLASH FLASH
 * This package provides the core capabilities for flash functions.
 * @{
 */

/** @defgroup FLASH_Public_Functions FLASH Public Functions
 * @{
 */

/**
 * @brief	Erases sectors of flash memory.
 * @param 	startSector: Determines the initial start of the sector to erase.
 * @param 	endSector: Determines the final sector to erase.
 */
unsigned int FLASH_EraseSectors(unsigned int startSector, unsigned int endSector);

/**
 * @brief	Writes data to determined space in flash memory.
 * @param 	dstAddr: Address to which space is going to be written.
 * @param 	srcAddr: Adress of the data to be written.
 * @param	size: Size of the srcAddr parameter.
 */
unsigned int FLASH_WriteData(void *dstAddr, void *srcAddr, unsigned int size);

/**
 * @brief	Compares two memory addresses given a size.
 * @param 	dstAddr: Address to which space in memory to compare.
 * @param 	srcAddr: Address to which space in memory to compare.
 * @param	size: Size of the srcAddr parameter.
 */
unsigned int FLASH_VerifyData(void *dstAddr, void *srcAddr, unsigned int size);

/**
 * @}
 */


/**
 * @}
 */

#endif /* FLASH_H_ */

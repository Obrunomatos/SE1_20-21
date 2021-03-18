/**
* @file		spi.h
* @brief	Contains the spi API.
* @version	1.0
* @date		18 Jan 2021
* @author	Bruno Matos
*
* Copyright(C) 2020-2021, Bruno Matos
* All rights reserved.
*
*/


#ifndef SPI_H_
#define SPI_H_


/** @defgroup ADXL345 ADXL345
 * This package provides the core capabilities for adxl345 functions.
 * @{
 */

/** @defgroup ADXL345_Public_Functions ADXL345 Public Functions
 * @{
 */

/**
 * @brief	Initializes the spi API.
 * @note	This function must be called prior to any other spi functions.
 */
void SPI_Init(void);

/**
 * @brief	Configures the way spi is going to transfer data
 * @param	frequency: Frequency of my spi, which divided by the system clock should be an even number bigger then 8.
 * @param	bitData: Specifies the number of bits im going to transfer.
 * @param	mode: Chooses the spi mode, specified in the first two bits. 1=cpha, 2=cpol,3=cpha|cpol.
 */
void SPI_ConfigTransfer(int frequency, int bitData, int mode);

/**
 * @brief	Transfers bits in wich the spi is in contact to.
 * @param	txBuffer: Buffer containing the data to the slave.
 * @param	rxBuffer: Buffer containing the slave answer.
 * @param	lenght: Size of txBuffer.
 */
int SPI_Transfer(unsigned short *txBuffer, short *rxBuffer, int lenght);

/**
 * @}
 */

/**
 * @}
 */
#endif /* SPI_H_ */

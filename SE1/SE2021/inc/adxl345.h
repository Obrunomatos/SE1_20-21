/**
* @file		adxl345.h
* @brief	Contains the adxl345 API.
* @version	1.0
* @date		18 Jan 2021
* @author	Bruno Matos
*
* Copyright(C) 2020-2021, Bruno Matos
* All rights reserved.
*
*/


#ifndef ADXL345_H_
#define ADXL345_H_

/** @defgroup ADXL345 ADXL345
 * This package provides the core capabilities for adxl345 functions.
 * @{
 */

/** @defgroup ADXL345_Public_Functions ADXL345 Public Functions
 * @{
 */

/**
 * @brief	Initializes the adxl345 API to be aware of the the accelerometer.
 * @note	This function must be called prior to any other ADXL345 functions.
 */

int Adxl345_Init(void);

/**
 * @brief	Gets the 2 byte X values of the accelerometer.
 */
short Adxl345_GetX(void);
/**
 * @brief	Gets the 2 byte Y values of the accelerometer.
 */
short Adxl345_GetY(void);
/**
 * @brief	Gets the 2 byte Z values of the accelerometer.
 */
short Adcl345_GetZ(void);
/**
 * @}
 */


/**
 * @}
 */


#endif /* ADXL345_H_ */

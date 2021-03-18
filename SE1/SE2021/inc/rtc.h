/**
* @file		rtc.h
* @brief	Contains the rtc API.
* @version	1.0
* @date		18 Jan 2021
* @author	Bruno Matos
*
* Copyright(C) 2020-2021, Bruno Matos
* All rights reserved.
*
*/


#ifndef RTC_H_
#define RTC_H_


#include <time.h>

/** @defgroup RTC RTC
 * This package provides the core capabilities for rtc functions.
 * @{
 */

/** @defgroup RTC_Public_Functions RTC Public Functions
 * @{
 */

/**
 * @brief	Initializes the rtc API to initiate the time.
 * @note	This function must be called prior to any other RTC functions.
 */
void RTC_Init(time_t seconds);

/**
 * @brief	Gets the current time available in the rtc.
 * @param	dateTime: Output value which contains the current time.
 */
void RTC_GetValue(struct tm *dateTime);

/**
 * @brief	Sets the rtc to a specific date passed trough parameter.
 * @param	dateTime: Struct which cointains the current time to update the rtc.
 */
void RTC_SetValue(struct tm *dateTime);

/**
 * @brief	Initializes the adxl345 API to be aware of the the accelerometer.
 * @param	seconds: Struct which cointains the current time to update the rtc.
 */
void RTC_SetSeconds(time_t seconds);

/**
 * @brief	Gets the current time in second since 00:00:00 UTC, January the 1st, 1970.
 */
time_t RTC_GetSeconds(void);

/**
 * @}
 */

/**
 * @}
 */
#endif /* RTC_H_ */

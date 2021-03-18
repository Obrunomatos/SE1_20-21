/**
* @file		led.h
* @brief	Contains the led API.
* @version	1.0
* @date		18 Jan 2021
* @author	Bruno Matos
*
* Copyright(C) 2020-2021, Bruno Matos
* All rights reserved.
*
*/
#ifndef LED_H_
#define LED_H_

#include <stdbool.h>

/** @defgroup LED LED
 * This package provides the core capabilities for LED functions.
 * @{
 */

/** @defgroup LED_Public_Functions LED Public Functions
 * @{
 */


/**
 * @brief	Initializes the LED so it can be accessible.
 * @param 	state: Determines if the LED starts on or off, true if on.
 */
void LED_Init(bool state);

/**
 * @brief	Finds if the LED is turned on or off.
 * @return 	Returns the state of the LED, true if on or false if off.
 */
bool LED_GetState(void);

/**
 * @brief	Puts the LED in the active state.
 */
void LED_On(void);

/**
 * @brief	Puts the LED in the off state.
 */
void LED_Off(void);


/**
 * @}
 */


/**
 * @}
 */


#endif /* LED_H_ */

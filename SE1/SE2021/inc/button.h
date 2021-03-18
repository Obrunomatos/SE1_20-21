/**
* @file		button.h
* @brief	Contains the button API.
* @version	1.0
* @date		03 Nov 2020
* @author	Bruno Matos
*
* Copyright(C) 2020-2020, Bruno Matos
* All rights reserved.
*
*/

#ifndef BUTTON_H_
#define BUTTON_H_

/** @defgroup BUTTON BUTTON
 * This package provides the core capabilities for button functions.
 * @{
 */

/** @defgroup BUTTON_Public_Functions BUTTON Public Functions
 * @{
 */

/**
 * @brief	Initializes the wait API to be aware of the button.
 * @note	This function must be called prior to any other BUTTON functions.
 */
void BUTTON_Init(void);

/**
 * @brief Non-blocking function that reads the button pressing.
 * @return 0 if no button has been pressed, or the bitmap of the pressed button.
 */
int BUTTON_Hit(void);

/**
 * @brief blocking function that waits for the button to be pressed.
 * @return the bitmap of the pressed button.
 */
int BUTTON_Read(void);

/**
 * @brief function that returns the state of the button
 * @return the state of the button. (pressed, released or repeat)
 */
int BUTTON_GetButtonsEvents(void);

/**
 * @}
 */


/**
 * @}
 */

#endif /* BUTTON_H_ */

/**
* @file		ui.h
* @brief	Contains the UI.
* @version	1.1
* @date		10 Out 2017
* @author	Bruno Matos
*
* Copyright(C) 2015-2020, Bruno Matos
* All rights reserved.
*
*/

#ifndef UI_H_
#define UI_H_

/** @defgroup UI UI
 * This package provides the core capabilities for UI functions.
 * @{
 */

/** @defgroup UI_Public_Functions UI Public Functions
 * @{
 */

/**
 * @brief	Initializes the UI API .
 * @note	This function must be called prior to any other UI functions.
 */
void UI_init();

/**
 * @brief	Function to evaluate certain time, determines if the game should enter control mode.
 */
int UI_shouldEnterManut();
/**
 * @brief	Waits for the user to stop presseing any button.
 */
void UI_waitForNoInput();
/**
 * @brief	Cleans the LCD.
 */
void UI_resetScreen();
/**
 * @brief	Show the dynamic menu and evaluates which control function to do.
 */
void UI_manutMode();
/**
 * @brief	Switches between the calendar menu, and the best player menu. .
 */
void UI_showMenus();
/**
 * @brief	Enters the game mode. .
 */
void UI_gameMode();

/**
 * @}
 */

/**
 * @}
 */
#endif /* UI_H_ */

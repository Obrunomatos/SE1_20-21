/**
* @file		lcd.h
* @brief	Contains the lcd API.
* @version	1.0
* @date		18 Jan 2021
* @author	Bruno Matos
*
* Copyright(C) 2020-2021, Bruno Matos
* All rights reserved.
*
*/
#ifndef LCD_H_
#define LCD_H_

/** @defgroup LCD LCD
 * This package provides the core capabilities for LCD functions.
 * @{
 */

/** @defgroup LCD_Public_Functions LCD Public Functions
 * @{
 */

/**
 * @brief	Initiliazes the communication with the display using lines and 16 rows.
 */
void LCDText_Init(void);

/**
 * @brief	Writes a character to the display in the cursor position.
 * @param 	ch: Character to be written
 */
void LCDText_WriteChar(char ch);

/**
 * @brief	Writes a string (word) to the display in the cursor position.
 * @param 	str: Word to be written.
 */
void LCDText_WriteString(char *str);

/**
 * @brief	Moves the cursor to the position received in arguments.
 * @param 	row: Positions the cursor in this row of the display.
 * @param 	column: Positions the cursor in this column of the display.
 */
void LCDText_Locate(int row, int column);

/**
 * @brief	Clears the display using the command in the display API.
 */
void LCDText_Clear(void);

/**
 * @brief	Creates a new character to the display.
 * @param 	location: Place where the new character is going to be.
 * @param	charmap[]: Bitmap representation of the pixels witch represents the new character.
 */

void LCDText_CreateChar(unsigned char location, unsigned char charmap[]);

/**
 * @brief	Writes in the LCD in similar way that the c printf does.
 * @param	fmt: The format in which the rest of the args must correspond to, see how
 * 				printf is called, it works the same way.
 * @param	...: The arguments to be printed.
 */
void LCDText_Printf(char *fmt, ...);


/**
 * @}
 */


/**
 * @}
 */

#endif /* LCD_H_ */

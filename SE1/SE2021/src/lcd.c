/*
 * lcd.c
 *
 *  Created on: 17/11/2020
 *      Author: obrun
 */

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include "lcd.h"
#include "wait.h"
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#define HIGH_END	16
#define GPIO_IO	3
#define ENABLE	21
#define RS	22
#define DATA_4	23
#define DATA_5	24
#define DATA_6	25
#define DATA_7	26
#define ROW_2	40
#define MAX_LINES 8

#define ENABLE_SEL	( GPIO_IO << ((ENABLE - HIGH_END) * 2))
#define ENABLE_RS	( GPIO_IO << ((RS - HIGH_END) * 2))
#define ENABLE_DATA_4	( GPIO_IO << ((DATA_4- HIGH_END) * 2))
#define ENABLE_DATA_5	( GPIO_IO << ((DATA_5- HIGH_END) * 2))
#define ENABLE_DATA_6	( GPIO_IO << ((DATA_6- HIGH_END) * 2))
#define ENABLE_DATA_7	( GPIO_IO << ((DATA_7- HIGH_END) * 2))

unsigned int lin = 1;
unsigned int col = 0;

static void write_5bit(unsigned short rs, unsigned short data){
	LPC_GPIO0->FIOCLR = ((1 << RS) | (1 << ENABLE) | (1 << DATA_4 ) | (1 << DATA_5 ) | (1 << DATA_6 ) | (1 << DATA_7 ));
	LPC_GPIO0->FIOSET = ((rs << RS) | (data << DATA_4));
	WAIT_ChronoUs(10);
	LPC_GPIO0->FIOSET = (1 << ENABLE);
	WAIT_ChronoUs(10);
	LPC_GPIO0->FIOCLR = (1 << ENABLE);
	WAIT_ChronoUs(10);
}

static void write_9bit(unsigned short rs, unsigned short data){
	unsigned short highEnd = data >> 4;
	unsigned short lowEnd = data & 15;
	write_5bit(rs,highEnd);
	write_5bit(rs,lowEnd);
	WAIT_ChronoUs(10);
}

static void write_Cmd(unsigned short cmd){
	write_9bit(0, cmd);
}

static void write_Data(unsigned short data){
	write_9bit(1,data);
}

void LCDText_Init(void){
	LPC_PINCON->PINSEL1 &= ~(ENABLE_SEL | ENABLE_RS | ENABLE_DATA_4 | ENABLE_DATA_5 | ENABLE_DATA_6 | ENABLE_DATA_7 );
	LPC_GPIO0->FIODIR |= ((1 << RS) | (1 << ENABLE) | (1 << DATA_4 )| (1 << DATA_5 )| (1 << DATA_6 ) | (1 << DATA_7 ));
	WAIT_Milliseconds(16);
	write_5bit(0,3);
	WAIT_Milliseconds(5);
	write_5bit(0,3);
	WAIT_ChronoUs(105);
	write_Cmd((3 << 4) | 2);
	WAIT_ChronoUs(39);
	write_Cmd((2 << 4) | 15);
	WAIT_ChronoUs(39);
	write_Cmd(8);
	WAIT_ChronoUs(39);
	write_Cmd(1);
	WAIT_ChronoUs(6000);
	write_Cmd(6);
	WAIT_ChronoUs(39);
	write_Cmd(15);
	WAIT_ChronoUs(39);
	lin = 0;
	col =0;
}

void LCDText_Locate(int row, int column){
	lin = row;
	col = column;
	if(row == 2){
		write_Cmd(0xC0 | column);
		WAIT_ChronoUs(39);
	}else{
		write_Cmd(0x80 | column);
		WAIT_ChronoUs(39);
	}
}

void incrementColumn(){
	if(col >= 15){
		if(lin > 1){
			col = 0;
			lin = 1;
			LCDText_Locate(lin,col);
		}
		else{
			col = 0;
			lin = 2;
			LCDText_Locate(lin,col);
		}
	}
	else{
		col++;
	}
}

void LCDText_WriteChar(char ch){
	write_Data(ch);
	WAIT_ChronoUs(43);
	incrementColumn();
}

void LCDText_WriteString(char *str){
		for(int i=0; i< strlen(str); i++){
			LCDText_WriteChar(str[i]);
		}
}

void LCDText_Clear(void){
	write_Cmd(1);
	WAIT_ChronoUs(6000);
	write_Cmd(2);
	WAIT_ChronoUs(6000);
}

void LCDText_CreateChar(unsigned char location, unsigned char charmap[]){
	write_Cmd((4 << 4) | location);
	WAIT_ChronoUs(39);
	for(int i=0; i < MAX_LINES; i++){
		write_Data(charmap[i]);
		WAIT_ChronoUs(43);
	}
	write_Cmd(2);
	WAIT_ChronoUs(6000);
}


void LCDText_Printf(char *fmt, ...){
	char buffer[256];
	va_list pointer;
	va_start(pointer, fmt);

	vsprintf(buffer,fmt,pointer);

	va_end(pointer);
	LCDText_WriteString(buffer);
}



/*
===============================================================================
 Name        : Lab_0.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#include "wait.h"
#include "button.h"
#include "led.h"
#include "lcd.h"
#include "rtc.h"
#include "adxl345.h"
#include "flash.h"
#endif

#include <cr_section_macros.h>

#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include "system_LPC17XX.h"

// TODO: insert other include files here

// TODO: insert other definitions and declarations here

void HardFault_Handler(void)
{
	while(1) {
		LPC_GPIO0->FIOSET = 1<<22;
}
}

int main(void) {


	char name[256] = "SE2021";
	int *sect1 = 0x00078000;
	int f = FLASH_WriteData(sect1, name,256);
	FLASH_EraseSectors(29, 29);
	char *word = (char *) sect1;
	printf("----- %s ------\n", word);
	printf("%d", f);

	/*WAIT_Init();
	AC_Init();
	//printf("DEVICE ID: %d\n", AC_GetDeviceId());
	while(1){
	printf("x: %d y:%d  z:%d\n", AC_GetX(),AC_GetY(),AC_GetZ());
	WAIT_Milliseconds(500);
	}*/
	//LPC_GPIO0->FIODIR |= 1<<22;
	//LPC_GPIO0->FIOCLR = 1<<22;
	//char buf[80];
	//time_t seconds = time(0);
	//struct tm aux = *localtime(&seconds);
	//printf(" c month %d\n",aux.tm_mon);
	//RTC_Init(seconds);

	//LCDText_Init();
	//printf(" rtc month %d\n", LPC_RTC->MONTH);

	//struct tm nowTime;
	//RTC_GetValue(&nowTime);
	//strftime(buf, sizeof(buf), "%a %Y-%m-%d %H:%M:%S %Z", &nowTime);
	//printf("%s\n", buf);
	//printf("mes %d\n", nowTime.tm_mon+1);
	//LCDText_Printf("%dh:%d:%d %d-%d-%d", nowTime.tm_hour,nowTime.tm_min,nowTime.tm_sec,nowTime.tm_mday,nowTime.tm_mon+1,nowTime.tm_year+1900);
	//LCDText_WriteString(" B");

	//WAIT_Milliseconds(5000);
	//LCDText_CleanWriteString("Hello this is embedded systems ");
	//LCDText_WriteString("B");
	//LCDText_WriteString("");
	//LCDText_Printf("day: %d",nowTime.tm_wday);
	/*unsigned char car[8] = {0x00,0x10,0x1A,0x1F,0x1F,0x1A,0x10,0x00};


	LCDText_Printf("Number: %d",13);
	unsigned char location = 0;
	LCDText_CreateChar(0,car);
	LCDText_WriteString("Hello this is embedded systems ");
	LCDText_WriteChar(location);
	*/
	//LCDText_Locate(1,4);
	//WAIT_Milliseconds(5000);
	//LCDText_Clear();
	/*WAIT_ChronoUs(5000000);
	printf("5 seconds\n");
	WAIT_ChronoUs(5000000);
	printf("5 seconds\n");

	while(BUTTON_Read() == 0 ){
		x |= 0;
	}

	while(1){
		x = BUTTON_Hit();
		if(x>0) printf("ola\n");
	}

	BUTTON_Init();
	unsigned int x;
	while(1){
		x = BUTTON_GetButtonsEvents();
		if((x & 3) == 0) printf("button-S\n");
		if((x & (3<<2)) == 0) printf("button-L\n");
		if((x & (3<<4)) == 0) printf("button-R\n");
	}*/
	/*

	LPC_GPIO0->FIODIR  = (1<<22);
    LPC_GPIO0->FIOCLR = (1<<22);

    while(1){
    for(int i=0 ; i<5000000; i++)
    	LPC_GPIO0->FIOSET = (1<<22);
    for(int i=0 ; i<5000000; i++)
    	LPC_GPIO0->FIOCLR = (1<<22);
    }

    while(1){
    	WAIT_Milliseconds(500);
    	LPC_GPIO0->FIOSET = (1<<22);
    	WAIT_Milliseconds(500);
    	LPC_GPIO0->FIOCLR = (1<<22);
    }
    return 0 ;
	LED_Init(true);
	LED_On();
	bool x = LED_GetState();


	BUTTON_Init();
	WAIT_Init();
	LED_Init(false);
	while(1){
		unsigned int x = BUTTON_Read();
		if(x == 4){
			printf("button 4\n");
		}
		if(x == 2){
			printf("button 2\n");
		}
		if(x == 1){
			printf("button 1\n");
		}
	}*/
}

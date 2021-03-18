/*
===============================================================================
 Name        : Car_Runner.c
 Author      : $Bruno Matos
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include <cr_section_macros.h>

#include <stdio.h>
#include "lcd.h"
#include "wait.h"
#include "ui.h"
#include "led.h"
#include "rtc.h"
#include "button.h"
#include <time.h>
#include <ui.h>

#define TIMER_MENU		5000
#define	TIME_TO_MOVE	3000



void game(){
	UI_waitForNoInput();
	UI_resetScreen();
	UI_gameMode();
	UI_waitForNoInput();
	UI_resetScreen();
}


void manut(){
	UI_waitForNoInput();
    UI_manutMode();
    UI_waitForNoInput();
}



int main(void) {
	UI_init();
	while(1){
		UI_showMenus(TIMER_MENU);
		if(UI_shouldEnterManut()){
			manut();
			UI_resetScreen();
		}
		if(BUTTON_Hit() == 4){
			game();
		}
	}
    return 0 ;
}

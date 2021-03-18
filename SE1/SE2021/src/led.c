/*
 * led.c
 *
 *  Created on: 10/11/2020
 *      Author: obrun
 */

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include <stdbool.h>
#include "led.h"

void LED_Init(bool state){
	LPC_GPIO0->FIODIR  = (1<<22);
	if(state) LPC_GPIO0->FIOSET = (1<<22);
	else LPC_GPIO0->FIOCLR = (1<<22);
}

bool LED_GetState(void){
	unsigned int aux = LPC_GPIO0->FIOPIN;
	aux = aux >> 22;
	if((aux & 1) == 0) return false;
	else return true;
}

void LED_On(void){
	LPC_GPIO0->FIOSET = (1<<22);
}

void LED_Off(void){
	LPC_GPIO0->FIOCLR = (1<<22);
}


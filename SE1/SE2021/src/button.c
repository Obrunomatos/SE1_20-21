/*
 * button.c
 *
 *  Created on: 03/11/2020
 *      Author: obrun
 */

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include "wait.h"
#include "button.h"

#define BUTTON_1	10
#define BUTTON_2	8
#define BUTTON_3	7

#define LOW_END		0
#define HIGH_END	16

#define GPIO_SEL	3

/**
 * @brief defines the buttons to be input mode
 */
#define BTN1_CFG_PIN	(GPIO_SEL << (BUTTON_1 * 2 - LOW_END))
#define BTN2_CFG_PIN	(GPIO_SEL << (BUTTON_2 * 2 - LOW_END))
#define BTN3_CFG_PIN	(GPIO_SEL << (BUTTON_3 * 2 - LOW_END))


#define PULLUP	3
#define PULLDOWN	1

/**
 * @brief defines pull up to the button, for it to me connected to ground
 */
#define PULLUP_CFG_BUTTON_1	((PULLUP << (BUTTON_1 * 2)) - 0)
#define PULLUP_CFG_BUTTON_2	((PULLUP << (BUTTON_2 * 2)) - 0)
#define PULLUP_CFG_BUTTON_3	((PULLUP << (BUTTON_3 * 2)) - 0)
unsigned int stateBtn1 = 1;
unsigned int stateBtn2 = 1;
unsigned int stateBtn3 = 1;

void BUTTON_Init(void){
	LPC_PINCON->PINSEL4 &= ~(BTN1_CFG_PIN | BTN2_CFG_PIN | BTN3_CFG_PIN);
	LPC_PINCON->PINMODE4 &= ~(PULLUP_CFG_BUTTON_1 | PULLUP_CFG_BUTTON_2 | PULLUP_CFG_BUTTON_3);
	LPC_GPIO2->FIODIR &= ~((1<<BUTTON_3) | (1<<BUTTON_2) | (1 << BUTTON_1));
}

int BUTTON_Hit(void){
	unsigned int i = 0;
	unsigned int aux = LPC_GPIO2->FIOPIN;
	aux = aux >> 7;
	if((aux & 8) == 0) i|=4;
	if((aux & 2) == 0) i|=2;
	if((aux & 1) == 0) i|=1;
	return i;
}

int BUTTON_Read(void){
	unsigned int i = 0;
	int aux;
	//aux = aux >> 7;
	while(i==0){
		aux = LPC_GPIO2->FIOPIN;
		aux = aux >> 7;
		if((aux & 8) == 0) i|=4;
		if((aux & 2) == 0) i|=2;
		if((aux & 1) == 0) i|=1;
	}
	return i;
}

int BUTTON_GetButtonsEvents(void){
	unsigned int i = 0;
	unsigned int aux = 0;
	aux = LPC_GPIO2->FIOPIN;
	aux = aux >> 7;

	if((aux & 1) == 0){
		if((stateBtn1 & 1) == 0) i |= 2;
		else{
			stateBtn1 = 0;
			i |= 0;
		}
	}
	else{
		if((stateBtn1 & 1) == 0){
			stateBtn1 = 1;
			i |= 1;
		}
		else i |= 2;
	}
	i = i << 2;
	if((aux & 2) == 0){
		if((stateBtn2 & 1) == 0) i |= 2;
		else{
			stateBtn2 = 0;
			i |= 0;
		}
	}
	else{
		if((stateBtn2 & 1) == 0){
			stateBtn2 = 1;
			i |= 1;
		}
		else i |= 2;
	}
	i = i << 2;
	if((aux & 8) == 0){
		if((stateBtn3 & 1) == 0) i |= 2;
		else{
			stateBtn3 = 0;
			i |= 0;
		}
	}
	else{
		if((stateBtn3 & 1) == 0){
			stateBtn3 = 1;
			i |= 1;
		}
		else i |= 2;
	}
	return i;
}

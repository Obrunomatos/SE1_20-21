/*
 * wait.c
 *
 *  Created on: 10 Out 2017
 *      Author: psampaio and BMatos
 */

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include "wait.h"


#define SYSTICK_FREQ (SystemCoreClock / 1000)
#define TIMER0_PCLK_MICRO	((SystemCoreClock/4)-1)/1000000

static volatile uint32_t __ms;

void SysTick_Handler(void)
{
	__ms++;
}

void WAIT_Milliseconds(uint32_t millis)
{
	uint32_t start = __ms;
	while ((__ms - start) < millis) {
		__WFI();
	}
}

int32_t WAIT_Init(void)
{
	LPC_TIM0->CTCR = 0;
	LPC_SC->PCLKSEL0 &= ~(3<<2);
	LPC_TIM0->PR = TIMER0_PCLK_MICRO;
	LPC_TIM0->MCR = 5;
    SystemCoreClockUpdate();
    if (SysTick_Config(SYSTICK_FREQ) == 1) return -1;
    return 0;
}

uint32_t WAIT_GetElapsedMillis(uint32_t start)
{
	return __ms - start;
}

void WAIT_ChronoUs(uint32_t waitUs){
	LPC_TIM0->TCR = 2;
	LPC_TIM0->MR0 = waitUs;
	LPC_TIM0->TCR = 1;
	while((LPC_TIM0->IR & 1) == 0);
	LPC_TIM0->IR = 1;
	return;
}

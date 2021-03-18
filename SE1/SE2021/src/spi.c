/*
 * spi.c
 *
 *  Created on: 05/01/2021
 *      Author: obrun
 */

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#define SPIF (1<<7)
#define ERROR_FLAGS (15<<3)
#define SCK		30
#define	MISO	2
#define MOSI	4
#define ENABLE	2
#define CPHA	3
#define CPOL	4
#define MASTER	5
#define BITS	8

unsigned int dummy;


void SPI_Init(void){
	LPC_SC->PCONP |= (1<<8);
	LPC_SC->PCLKSEL0 &= ~(3<<16);
	LPC_PINCON->PINSEL0 &= ~(3<<SCK);//LIMPAR O REGISTO NO SITIO DE SCK
	LPC_PINCON->PINSEL0 |= (3<<SCK);
	LPC_PINCON->PINSEL1 &= ~(3<<MISO | 3<<MOSI);//LIMPAR O REGISTO NO SITIO DE MOSI E MISO
	LPC_PINCON->PINSEL1 |= (3<<MISO | 3<<MOSI);
	LPC_PINCON->PINMODE0 &= ~(3<<SCK);
	LPC_PINCON->PINMODE1 &= ~(3<<MISO | 3<<MOSI);
}

// mode = cpha | cpol (1st bit cpha, 2nd bit cpol)
void SPI_ConfigTransfer(int frequency, int bitData, int mode){
	if(bitData < 8) bitData = 0;
	if(bitData > 15) bitData = 15;
	int clk = SystemCoreClock / frequency;
	if((clk % 2) == 0){
		if(clk<8)clk = 8;
	}
	else{
		if(clk <8)clk = 8;
		else clk++;
	}
	LPC_SPI->SPCCR = clk;
	int cpha = mode & 1;
	int cpol = ((mode >> 1) & 1);
	LPC_SPI->SPCR &= 0; //LSBF FORCED TO BE ZERO
	LPC_SPI->SPCR |= ((1<<ENABLE) | (cpha<<CPHA) | (cpol<<CPOL) | (1<<MASTER) | (bitData<<BITS));
	dummy = LPC_SPI->SPSR;
	dummy = LPC_SPI->SPDR;
}


int SPI_Transfer(unsigned short *txBuffer, short *rxBuffer, int lenght){
	volatile int spsr;
	for(int i=0; i<lenght; i++){
		LPC_SPI->SPDR = txBuffer[i];
		while(1){
			spsr = LPC_SPI->SPSR;
			if(spsr & SPIF) break;
			if(spsr & ERROR_FLAGS) return 1;
		}
		dummy = LPC_SPI->SPSR; //clear flags;
		if(rxBuffer != 0)
			rxBuffer[i] = LPC_SPI->SPDR;
		else dummy = LPC_SPI->SPDR;
	}
	return 0;
}

/*
 * adxl345.c
 *
 *  Created on: 11/01/2021
 *      Author: obrun
 */


#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif


#include "spi.h"
#include "adxl345.h"
#define READ_MODE	1<<7
#define MB			1<<6
#define CS	24

#define READ_DEV_ID	0x80
#define BW_RATE	0x2c
#define POWER_CTL	0x2d
#define DATA_FORMAT	0x31
#define DATA_X0	0x32
#define DATA_X1	0x33
#define DATA_Y0	0x34
#define DATA_Y1	0x35
#define DATA_Z0	0x36
#define DATA_Z1	0x37
#define DEV_ID	229

unsigned short bw_rate_arr[] = {BW_RATE, 0x0c};
unsigned short power_ctl_arr[] = {POWER_CTL, 0x08};
unsigned short data_format_arr[] = {DATA_FORMAT, 0x00};

unsigned short getx_arr[] = {(READ_MODE | MB | DATA_X0), 0x00, 0x00};
unsigned short gety_arr[] = {(READ_MODE | MB | DATA_Y0), 0x00, 0x00};
unsigned short getz_arr[] = {(READ_MODE | MB | DATA_Z0), 0x00, 0x00};

unsigned short getid_arr[] = {READ_DEV_ID, 0x00};
void activeCs(){LPC_GPIO2->FIOCLR = (1<<12);}
void inactiveCs(){LPC_GPIO2->FIOSET = (1<<12);}
void setCs(){
	LPC_PINCON->PINSEL4 &= ~(3<<CS);
	LPC_PINCON->PINMODE4 &= ~(3<<CS);
	LPC_GPIO2->FIODIR |= (1<<12);
	LPC_GPIO2->FIOSET = (1<<12);
}

int AC_GetDeviceId(){
	short temp_vals[2] = {0,0};
	activeCs();
	SPI_Transfer(getid_arr,temp_vals,2);
	inactiveCs();
	return temp_vals[1];
}
void config_bw_rate(unsigned short *arr){
	activeCs();
	SPI_Transfer(arr,0,2);
	inactiveCs();
}
void config_data_format(unsigned short *arr){
	activeCs();
	SPI_Transfer(arr,0,2);
	inactiveCs();
}
void config_power_ctl(unsigned short *arr){
	activeCs();
	SPI_Transfer(arr,0,2);
	inactiveCs();
}


int Adxl345_Init(void){
	SPI_Init();
	setCs();
	SPI_ConfigTransfer(1000,8,3);
	if(AC_GetDeviceId() != DEV_ID)return 0;
	config_bw_rate(bw_rate_arr);
	config_data_format(data_format_arr);
	config_power_ctl(power_ctl_arr);
	return 1;
}





short Adxl345_GetX(){
	short temp_vals[3] = {0,0,0};
	activeCs();
	SPI_Transfer(getx_arr,temp_vals,3);
	inactiveCs();
	short xVal = 0;
	xVal |= temp_vals[2];
	xVal = xVal << 8;
	xVal |= temp_vals[1];
	return xVal;
}

short Adxl345_GetY(){
	short temp_vals[3] = {0,0,0};
	activeCs();
	SPI_Transfer(gety_arr,temp_vals,3);
	inactiveCs();
	short yVal = 0;
	yVal |= temp_vals[2];
	yVal = yVal << 8;
	yVal |= temp_vals[1];
	return yVal;
}

short Adcl345_GetZ(){
	short temp_vals[4] = {0,0,0};
	activeCs();
	SPI_Transfer(getz_arr,temp_vals,3);
	inactiveCs();
	short zVal = 0;
	zVal |= temp_vals[2];
	zVal = zVal << 8;
	zVal |= temp_vals[1];
	return zVal;
}

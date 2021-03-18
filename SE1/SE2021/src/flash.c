/*
 * flash.c
 *
 *  Created on: 12/01/2021
 *      Author: obrun
 */

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include "flash.h"

#define IAP_LOCATION 0x1FFF1FF1
#define ERASE_SECTOR	52
#define	COPY_TO_FLASH	51
#define PREPARE_WRITE	50
#define COMPARE			56
#define SECTOR_SIZE		30
const unsigned int sectors[] = {0x0000000,
								0x00001000,
								0x00002000,
								0x00003000,
								0x00004000,
								0x00005000,
								0x00006000,
								0x00007000,
								0x00008000,
								0x00009000,
								0x0000A000,
								0x0000B000,
								0x0000C000,
								0x0000D000,
								0x0000E000,
								0x0000F000,
								0x00010000,
								0x00018000,
								0x00020000,
								0x00028000,
								0x00030000,
								0x00038000,
								0x00040000,
								0x00048000,
								0x00050000,
								0x00058000,
								0x00060000,
								0x00068000,
								0x00070000,
								0x00078000};
unsigned int command[5];
unsigned int output[5];
typedef void (*IAP)(unsigned int [],unsigned int[]);
IAP iap_entry = (IAP) IAP_LOCATION;

unsigned int prepare_wr(unsigned int startSector, unsigned int endSector){
	command[0] = PREPARE_WRITE;
	command[1] = startSector;
	command[2] = endSector;
	iap_entry(command,output);
	return output[0];
}

unsigned int FLASH_EraseSectors(unsigned int startSector, unsigned int endSector){
	if(prepare_wr(startSector,endSector) != 0)return output[0];
	command[0] = ERASE_SECTOR;
	command[1] = startSector;
	command[2] = endSector;
	command[3] = SystemCoreClock / 1000;
	iap_entry(command,output);
	return output[0];
}

unsigned int FLASH_WriteData(void *dstAddr, void *srcAddr, unsigned int size){
	unsigned int startSector = 0;
	for(int i = 0; i<SECTOR_SIZE; i++){
		if(dstAddr <= (void *) sectors[i]){
			break;
		}
		startSector ++;
	}
	if(prepare_wr(startSector,startSector) != 0)return output[0];
	command[0] = COPY_TO_FLASH;
	command[1] = (unsigned int) dstAddr;
	command[2] = (unsigned int) srcAddr;
	command[3] = size;
	command[4] = SystemCoreClock / 1000;
	iap_entry(command,output);
	return output[0];
}

unsigned int FLASH_VerifyData(void *dstAddr, void *srcAddr, unsigned int size){
	command[0] = COMPARE;
	command[1] = (unsigned int)dstAddr;
	command[2] = (unsigned int)srcAddr;
	command[3] = size;
	iap_entry(command,output);
	if(output[0] == 10)return output[1];
	return output[0];
}

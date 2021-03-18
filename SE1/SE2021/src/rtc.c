/*
 * rtc.c
 *
 *  Created on: 14/12/2020
 *      Author: obrun
 */

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include "rtc.h"
#include <time.h>


void RTC_SetSeconds(time_t seconds){
	struct tm time_stamp = *localtime(&seconds);
		LPC_RTC->SEC 	= time_stamp.tm_sec;
		LPC_RTC->MIN 	= time_stamp.tm_min;
		LPC_RTC->HOUR 	= time_stamp.tm_hour;
		LPC_RTC->DOM 	= time_stamp.tm_mday;
		LPC_RTC->DOW 	= time_stamp.tm_wday;
		LPC_RTC->DOY 	= time_stamp.tm_yday+1;
		LPC_RTC->MONTH 	= time_stamp.tm_mon+1;
		LPC_RTC->YEAR 	= time_stamp.tm_year+1900;
		LPC_RTC->CCR = 1;
}

void RTC_Init(time_t seconds){
	LPC_RTC->CCR = 2;
	LPC_RTC->AMR = 0;
	LPC_RTC->CIIR = 0;
	RTC_SetSeconds(seconds);
}

void RTC_GetValue(struct tm *dateTime){
	while(1){
		unsigned int time = LPC_RTC->CTIME0;
		if(time == LPC_RTC->CTIME0){
			dateTime->tm_sec	= LPC_RTC->SEC;
			dateTime->tm_min	= LPC_RTC->MIN;
			dateTime->tm_hour	= LPC_RTC->HOUR;
			dateTime->tm_mday	= LPC_RTC->DOM;
			dateTime->tm_wday	= LPC_RTC->DOW;
			dateTime->tm_yday	= LPC_RTC->DOY-1;
			dateTime->tm_mon	= LPC_RTC->MONTH-1;
			dateTime->tm_year	= LPC_RTC->YEAR-1900;
			break;
		}
	}
}

void RTC_SetValue(struct tm *dateTime){
		LPC_RTC->CCR = 0;
		LPC_RTC->AMR = 0;
		LPC_RTC->CIIR = 0;
		LPC_RTC->SEC 	= dateTime->tm_sec;
		LPC_RTC->MIN	= dateTime->tm_min;
		LPC_RTC->HOUR 	= dateTime->tm_hour;
		LPC_RTC->DOM 	= dateTime->tm_mday;
		LPC_RTC->DOW 	= dateTime->tm_wday;
		LPC_RTC->DOY 	= dateTime->tm_yday+1;
		LPC_RTC->MONTH 	= dateTime->tm_mon+1;
		LPC_RTC->YEAR 	= dateTime->tm_year+1900;
		LPC_RTC->CCR = 1;
}

time_t RTC_GetSeconds(void){
	struct tm time;
	RTC_GetValue(&time);
	return mktime(&time);
}

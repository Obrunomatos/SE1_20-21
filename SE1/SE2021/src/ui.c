/*
 * ui.c
 *
 *  Created on: 19/12/2020
 *      Author: obrun
 */

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include "ui.h"
#include "wait.h"
#include "lcd.h"
#include "rtc.h"
#include "flash.h"
#include "spi.h"
#include "adxl345.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <button.h>

#define BTN3_POSITION	3
#define BTN2_POSITION	12
#define BTN1_POSITION	48
#define MAX_OBS			5
#define	TIME_TO_MOVE	3000
#define NUMBER_OF_SCORES	3
unsigned int timeOnTran = 0;
unsigned int carPos = 7;
unsigned int timeCounter = 0;
unsigned int flipMenuTimer = 0;
unsigned int positionsToBeEvaluated[MAX_OBS];
unsigned int randomPositions[MAX_OBS];
int *sectorAddr = 0x00078000;
const int sectorAddr_val = 0x00078000;
struct tm myTime = {.tm_sec=0,
		.tm_min=0,
		.tm_hour=0,
		.tm_mday=1,
		.tm_wday=0,
		.tm_yday=0,
		.tm_mon=0,
		.tm_year = 2020 - 1900,
		.tm_isdst=0
};
char topObs[17] = {' ',' ' ,' ', ' ',' ',' ',' ',' ' ,' ' ,' ' , ' ',' ' ,' ' ,' ' ,' ' ,' ',0 };
char botObs[17] = {' ',' ' ,' ', ' ',' ',' ',' ',' ' ,' ' ,' ' , ' ',' ' ,' ' ,' ' ,' ' ,' ' ,0};
char letters[27] = {'A' ,'B' ,'C' ,'D' ,'E' ,'F' ,'G' ,'H' ,'I','J' ,'K' ,'L' ,'M' ,'N' ,'O' ,'P' ,'Q' ,'R' ,'S' ,'T','U','V','W','X', 'Y', 'Z',0};
struct PlayerStruct {
	char name[3];
	int score;
}playerStruct;

struct PlayerStruct dummyPlayer = { .name ="AAA", .score=0};

struct PlayerStruct playerScores[NUMBER_OF_SCORES];

struct PlayerStruct *flashPlayerScores = (struct PlayerStruct*)sectorAddr_val;

struct PlayerStruct currentPlayer = { .name = "AAA", .score = 0};


void decHour(struct tm *nowTime){
	if(nowTime->tm_hour == 0){
		nowTime->tm_hour = 23;
	}
	else nowTime->tm_hour--;
}

void decMin(struct tm* nowTime){
	if(nowTime->tm_min == 0){
		nowTime->tm_min = 59;
	}
	else nowTime->tm_min--;
}

void decSec(struct tm* nowTime){
	if(nowTime->tm_sec == 0){
		nowTime->tm_sec = 59;
	}
	else nowTime->tm_sec--;
}

void decDay(struct tm* nowTime){
	if(nowTime->tm_mon == 3 || nowTime->tm_mon == 5
			|| nowTime->tm_mon == 8 || nowTime->tm_mon == 10){
		if(nowTime->tm_mday == 1){
			nowTime->tm_mday = 30;
		}
		else nowTime->tm_mday--;
	}
	else if(nowTime->tm_mon == 5){
		unsigned int year = nowTime->tm_year + 1900;
		if(((year % 400) == 0) || (((year % 4) == 0) && ((year % 100) != 0))){
			if(nowTime->tm_mday == 1){
				nowTime->tm_mday = 29;
			}
			else nowTime->tm_mday--;
		}
		else{
			if(nowTime->tm_mday == 1){
			nowTime->tm_mday = 28;
			}
			else nowTime->tm_mday--;
		}
	}
	else{
		if(nowTime->tm_mday == 1){
			nowTime->tm_mday = 31;
		}
		else nowTime->tm_mday--;
	}
}

void decMon(struct tm* nowTime){
	if(nowTime->tm_mon == 0){
		nowTime->tm_mon = 11;
	}
	else nowTime->tm_mon--;
}

void decYear(struct tm* nowTime){
	if(nowTime->tm_year == 0){
		nowTime->tm_year = 999;
	}
	else nowTime->tm_year--;
}

void incHour(struct tm *nowTime){
	if(nowTime->tm_hour == 23){
		nowTime->tm_hour = 0;
	}
	else nowTime->tm_hour++;
}

void incMin(struct tm* nowTime){
	if(nowTime->tm_min == 59){
		nowTime->tm_min = 0;
	}
	else nowTime->tm_min++;
}
void incSec(struct tm* nowTime){
	if(nowTime->tm_sec == 59){
		nowTime->tm_sec = 0;
	}
	else nowTime->tm_sec++;
}
void incDay(struct tm* nowTime){
	if(nowTime->tm_mon == 3 || nowTime->tm_mon == 5
			|| nowTime->tm_mon == 8 || nowTime->tm_mon == 10){
		if(nowTime->tm_mday == 30){
			nowTime->tm_mday = 1;
		}
		else  nowTime->tm_mday++;
	}
	else if(nowTime->tm_mon == 5){
		unsigned int year = nowTime->tm_year + 1900;
		if(((year % 400) == 0) || (((year % 4) == 0) && ((year % 100) != 0))){
			if(nowTime->tm_mday == 29){
				nowTime->tm_mday = 1;
			}
			else nowTime->tm_mday++;
		}
		else{
			if(nowTime->tm_mday == 28){
			nowTime->tm_mday = 1;
			}
			else nowTime->tm_mday++;
		}
	}
	else{
		if(nowTime->tm_mday == 31){
			nowTime->tm_mday = 1;
		}
		else nowTime->tm_mday++;
	}
}
void incMon(struct tm* nowTime){
	if(nowTime->tm_mon == 11){
		nowTime->tm_mon = 0;
	}
	else nowTime->tm_mon++;
}
void incYear(struct tm* nowTime){
	if(nowTime->tm_year == 999){
		nowTime->tm_year = 0;
	}
	else nowTime->tm_year++;
}

void UI_resetScreen(){
	LCDText_Clear();
}

static int getTimeSinceClick(){
    unsigned int time = 0;
    if(timeOnTran == 0) timeOnTran = WAIT_GetElapsedMillis(0);
    else time = WAIT_GetElapsedMillis(timeOnTran);
    return time;
}

int containsSame(unsigned int *positions, int count, int src){
	for(int i = 0; i<count; i++){
		if(positions[i] == src)return 1;
	}
	return 0;
}

void getRandomPositions(unsigned int *positions, int min, int max, int count){
	srand(WAIT_GetElapsedMillis(0));
	int num;
	for(int i=0; i<count;i++){
		num = ((rand() % (max - min + 1)) + min);
		while(containsSame(positions,i,num)){
			num = ((rand() % (max - min + 1)) + min);
		}
		positions[i] = num;
	}
}

void setRandomPositions(){
	getRandomPositions(randomPositions, 0,15,MAX_OBS);
}

void setTopObs(){
	for(int i=0; i<16 ;i++){
		if(containsSame(randomPositions,MAX_OBS,i)){
			topObs[i] = '*';
		}
		else topObs[i] = ' ';
	}
}

void copyIntArray(unsigned int *dst, unsigned int *src, int size){
	for(int i=0; i<size; i++){
		dst[i]= src[i];
	}
}

void setBotObs(){
	copyIntArray(positionsToBeEvaluated, randomPositions,MAX_OBS);
	strncpy(botObs,topObs,16);
}

void showObstacles(){
	LCDText_Locate(2, 0);
	LCDText_WriteString(botObs);
	LCDText_Locate(1, 0);
	LCDText_WriteString(topObs);
}

void printTime(struct tm *nowTime){
	UI_resetScreen();
	LCDText_Locate(1,0);
	if(nowTime->tm_hour > 9) LCDText_Printf("%d:", nowTime->tm_hour);
	else LCDText_Printf("0%d:", nowTime->tm_hour);
	if(nowTime->tm_min > 9) LCDText_Printf("%d:", nowTime->tm_min);
	else LCDText_Printf("0%d:", nowTime->tm_min);
	if(nowTime->tm_sec > 9) LCDText_Printf("%d", nowTime->tm_sec);
	else LCDText_Printf("0%d", nowTime->tm_sec);
	LCDText_Locate(2,0);
	LCDText_Printf("%d-",nowTime->tm_year+1900);
	if((nowTime->tm_mon+1) > 9) LCDText_Printf("%d-",nowTime->tm_mon+1);
	else LCDText_Printf("0%d-",nowTime->tm_mon+1);
	if(nowTime->tm_mday > 9) LCDText_Printf("%d",nowTime->tm_mday);
	else  LCDText_Printf("0%d",nowTime->tm_mday);
}

void UI_setObstacles(){
	setRandomPositions();
	setBotObs();
	setTopObs();
	showObstacles();
	timeCounter = 0;
}

int UI_evalTimeOfObstacles(){
	int counter = 0;
	if(timeCounter == 0) timeCounter = WAIT_GetElapsedMillis(0);
	else counter = WAIT_GetElapsedMillis(timeCounter);
	return counter;
}
int evalTimeToFlip(){
	int counter = 0;
	if(flipMenuTimer == 0) flipMenuTimer = WAIT_GetElapsedMillis(0);
	else counter = WAIT_GetElapsedMillis(flipMenuTimer);
	return counter;
}
void UI_showTime(){
	struct tm nowTime;
	RTC_GetValue(&nowTime);
	printTime(&nowTime);
	WAIT_Milliseconds(500);
}
void writePlayers(){
	LCDText_Locate(1,0);
	LCDText_Printf("P%s", flashPlayerScores[0].name);
	LCDText_Locate(2,0);
	LCDText_Printf("S%d", flashPlayerScores[0].score);
	LCDText_Locate(1,5);
	LCDText_Printf("P%s", flashPlayerScores[1].name);
	LCDText_Locate(2,5);
	LCDText_Printf("S%d", flashPlayerScores[1].score);
	LCDText_Locate(1,10);
	LCDText_Printf("P%s", flashPlayerScores[2].name);
	LCDText_Locate(2,10);
	LCDText_Printf("S%d", flashPlayerScores[2].score);
	WAIT_Milliseconds(500);
}
void UI_showBestPlayer(){
	UI_resetScreen();
	writePlayers();
}

void UI_showMenus(int timeWhenFlip){
	if(evalTimeToFlip() < timeWhenFlip){
		UI_showTime();
	}
	else UI_showBestPlayer();
	if(evalTimeToFlip() > (2*timeWhenFlip)){
		flipMenuTimer = 0;
	}

}

void UI_resetObstacles(){
	char tempObs[16] = {' ',' ' ,' ', ' ',' ',' ',' ',' ' ,' ' ,' ' , ' ',' ' ,' ' ,' ' ,' ' ,' ' };
	strncpy(topObs,tempObs,16);
	strncpy(botObs,tempObs,16);
	timeCounter = 0;
}

int UI_shouldEnterManut(){
    if(BUTTON_Hit() == 3){
        if(getTimeSinceClick() > 2000){
            timeOnTran = 0;
            return 1;
        }
        return 0;
    }
    timeOnTran = 0;
    return 0;
}





void UI_createCar(){
	unsigned char car[8] = {0x00,0x10,0x1A,0x1F,0x1F,0x1A,0x10,0x00};
	LCDText_CreateChar(0,car);
}

#define AXIS_REPEAT	2
#define	AXIS_MOVE	0
#define AXIS_CHANGE	1
unsigned int leftState = AXIS_MOVE;
unsigned int rightState = AXIS_MOVE;



int getXStateRight(){
	short x = Adxl345_GetX();
	if(x<-110){
		if(rightState == AXIS_MOVE){
			return AXIS_REPEAT;
		}
		else {
			rightState = AXIS_MOVE;
			return rightState;
		}
	}
	else{
		if(rightState == AXIS_CHANGE){
			return AXIS_REPEAT;
		}
		else{
			rightState = AXIS_CHANGE;
			return rightState;
		}
	}
}


int getXStateLeft(){
	short x = Adxl345_GetX();
	if(x>110){
		if(leftState == AXIS_MOVE){
			return AXIS_REPEAT;
		}
		else {
			leftState = AXIS_MOVE;
			return leftState;
		}
	}
	else{
		if(leftState == AXIS_CHANGE){
			return AXIS_REPEAT;
		}
		else{
			leftState = AXIS_CHANGE;
			return leftState;
		}
	}
}


void UI_moveCar(){
	LCDText_Locate(2,carPos);
	LCDText_WriteChar(0);
	int events = BUTTON_GetButtonsEvents();
	int xRight = getXStateRight();
	int xLeft = getXStateLeft();
	if(((events & 48) == 0) || (xRight == AXIS_MOVE) ){
		 if(carPos == 15){
			 LCDText_Locate(2,carPos);
			 LCDText_WriteChar(0);
		 }
		 else{
			 LCDText_Locate(2,carPos);
			 LCDText_WriteString(" ");
			 carPos++;
			 LCDText_Locate(2,carPos);
			 LCDText_WriteChar(0);
		 }
	}
	if(((events & (3<<2)) == 0) || (xLeft == AXIS_MOVE )){
		if(carPos == 0){
			LCDText_Locate(2,carPos);
			LCDText_WriteChar(0);
		}
		else{
			LCDText_Locate(2,carPos);
			LCDText_WriteString(" ");
			carPos--;
			LCDText_Locate(2,carPos);
			LCDText_WriteChar(0);
		}
	}
}
void UI_erasePlayers(){
	UI_waitForNoInput();
	LCDText_Clear();
	for(int i = 0; i<NUMBER_OF_SCORES;i++){
		memmove(&(playerScores[i]),&dummyPlayer,sizeof(struct PlayerStruct));
	}
	FLASH_EraseSectors(29, 29);
	FLASH_WriteData(sectorAddr, &playerScores, 256);
	LCDText_Locate(1, 0);
	LCDText_WriteString("ERASING MEMORY");
	WAIT_Milliseconds(1500);
	return;
}

void writeManutMenu(){
	UI_resetScreen();
	LCDText_Locate(1, 0);
	LCDText_WriteString("1-Fix Clock 2-MM");
	LCDText_Locate(2, 0);
	LCDText_WriteString("3-Exit ");
	LCDText_WriteChar(0);
}
void UI_updateCalendar(){
	struct tm nowTime;
	RTC_GetValue(&nowTime);
	UI_resetScreen();
	printTime(&nowTime);
	unsigned int cursor = 0;
	LCDText_Locate(1,1);
	int line[] = {1,1,1,2,2,2};
	int col[] = {1,4,7,3,6,9};
	unsigned int events;
	while(1){
		events = BUTTON_GetButtonsEvents();
		 if((events & BTN3_POSITION) == 0){
			if(cursor == 5) break;
			cursor++;
			LCDText_Locate(line[cursor],col[cursor]);
		 }
		 if((events & BTN1_POSITION) == 0){
			 switch(cursor){
				 case 0:
					 incHour(&nowTime);
					 break;
				 case 1:
					 incMin(&nowTime);
					 break;
				 case 2:
					 incSec(&nowTime);
					 break;
				 case 3:
					 incYear(&nowTime);
					 break;
				 case 4:
					 incMon(&nowTime);
					 break;
				 case 5:
					 incDay(&nowTime);
					 break;
				 }
			 printTime(&nowTime);
			 LCDText_Locate(line[cursor],col[cursor]);

		 }
		 if((events & (3<<2)) == 0){
			 switch(cursor){
				 case 0:
					 decHour(&nowTime);
					 break;
				 case 1:
					 decMin(&nowTime);
					 break;
				 case 2:
					 decSec(&nowTime);
					 break;
				 case 3:
					 decYear(&nowTime);
					 break;
				 case 4:
					 decMon(&nowTime);
					 break;
				 case 5:
					 decDay(&nowTime);
					 break;
				 }
			 printTime(&nowTime);
			 LCDText_Locate(line[cursor],col[cursor]);
		 }
	}
	RTC_SetValue(&nowTime);
}


void UI_manutMode(){
	unsigned int events;
	writeManutMenu();
	int line[] = {1,1,2};
	int col[] = {0,12,0};
	int cursor = 0;
	LCDText_Locate(1, 0);
	while(1){

		events = BUTTON_GetButtonsEvents();
		if((events & BTN3_POSITION) == 0){
			switch(cursor){
			case 0:
				UI_updateCalendar();
				break;

			case 1:
				UI_erasePlayers();
				break;
			case 2:
				return;
			}
			writeManutMenu();
			LCDText_Locate(line[cursor], col[cursor]);
		}
		if((events & BTN1_POSITION) == 0){
			switch(cursor){
			case 0:
				cursor++;
				LCDText_Locate(line[cursor], col[cursor]);
				break;

			case 1:
				cursor++;
				LCDText_Locate(line[cursor], col[cursor]);
				break;

			case 2:
				cursor = 0;
				LCDText_Locate(line[cursor], col[cursor]);
				break;
			}
		}
		if((events & (3<<2)) == 0){
			switch(cursor){
			case 0:
				cursor=2;
				LCDText_Locate(line[cursor], col[cursor]);
				break;

			case 1:
				cursor--;
				LCDText_Locate(line[cursor], col[cursor]);
				break;

			case 2:
				cursor--;
				LCDText_Locate(line[cursor], col[cursor]);
				break;
			}
		}

	}
}



void UI_waitForNoInput(){
	while(BUTTON_Hit() != 0);
}

void setHighScore(int index){
	UI_waitForNoInput();
	UI_resetScreen();
	int letterCounter = 0;
	LCDText_Locate(1,0);
	LCDText_Printf("Name:%c%c%c",letters[letterCounter],
			letters[letterCounter],letters[letterCounter]);
	int cursor = 5;
	LCDText_Locate(1,cursor);
	unsigned int events;
	while(cursor < 8){
		events = BUTTON_GetButtonsEvents();
		 if((events & BTN3_POSITION) == 0){
			if(cursor == 5)currentPlayer.name[0] = letters[letterCounter];
			if(cursor == 6)currentPlayer.name[1] = letters[letterCounter];
			if(cursor == 7)currentPlayer.name[2] = letters[letterCounter];
			cursor++;
			letterCounter = 0;
			LCDText_Locate(1,cursor);
		 }
		 if((events & BTN1_POSITION) == 0){
			 if(letterCounter == 25)letterCounter = 0;
			 else letterCounter++;
			 LCDText_Printf("%c",letters[letterCounter]);
			 LCDText_Locate(1,cursor);
		 }
		 if((events & (3<<2)) == 0){
			 if(letterCounter == 0)letterCounter = 25;
			 else letterCounter--;
			 LCDText_Printf("%c",letters[letterCounter]);
			 LCDText_Locate(1,cursor);
		 }
	}
	memmove(playerScores,sectorAddr,(sizeof(struct PlayerStruct))*3);
	memmove(&(playerScores[index]),&currentPlayer,sizeof(struct PlayerStruct));
	FLASH_EraseSectors(29, 29);
	FLASH_WriteData(sectorAddr, &playerScores, 256);
	UI_waitForNoInput();
	UI_resetScreen();
	LCDText_WriteString("NEW HIGH SCORE");
}

int evalScore(){
	int index = 0;
	int scoreTmp = flashPlayerScores[0].score;
	for(int i=0; i<NUMBER_OF_SCORES;i++){
		if(flashPlayerScores[i].score < scoreTmp){
			scoreTmp = flashPlayerScores[i].score;
			index = i;
		}
	}
	if(flashPlayerScores[index].score < currentPlayer.score) return index;
	return -1;
}

void showScore(){
	int possibleScoreToErase = evalScore();
	if(possibleScoreToErase < 0){
	UI_waitForNoInput();
	UI_resetScreen();
	LCDText_Locate(1, 0);
	LCDText_Printf("score: %d", currentPlayer.score);
	WAIT_Milliseconds(3000);
	}
	else{
		setHighScore(possibleScoreToErase);
	}
}

int evalLoss(){
	if(botObs[carPos] == '*') return 1;
	return 0;
}

void UI_gameMode(){
	while(1){
		if(UI_evalTimeOfObstacles() >= TIME_TO_MOVE){
			UI_setObstacles();
			if(evalLoss()){
				showScore();
				break;
			}
			else
				currentPlayer.score++;
		}
		if(evalLoss()){
			showScore();
			break;
		}
		UI_moveCar();
	}
	currentPlayer.score = 0;
	char tmp[3] = "AAA";
	strcpy(currentPlayer.name,tmp);
	UI_resetObstacles();
}

void UI_init(){
	WAIT_Init();
	LCDText_Init();
	BUTTON_Init();
	Adxl345_Init();
	RTC_Init(0);
	RTC_SetValue(&myTime);
	UI_createCar();
}


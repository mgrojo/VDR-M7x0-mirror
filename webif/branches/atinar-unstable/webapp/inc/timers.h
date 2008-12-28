/*
* 
* This source-code is licensed under GPL v2.
* See ../../LICENSE for details
* 
* (c) Christian Kelinski <k@kille.cx>
* Please checkout the README file!
* 
* Originally written for the open7x0.org VDR-FW project:
* www.open7x0.org
* 
* Modified for http://vdr-m7x0.foroactivo.com.es by:
* atinar <atinar1@hotmail.com>
* 
* You will need the KLONE web application development framework
* from www.koanlogic.com Version 2.
* 
*/

#ifndef __TIMERS_H__
#define __TIMERS_H__

enum timerType {
	UNDEFINED  = 0,
	ONE_TIME = 1,
	REGULAR  = 2
};

//Channelliste kurz
typedef struct timerEntry {
 	time_t start;
	time_t stop;
	enum timerType type;
	int priority;
	int lifetime;
	int active;
	int ID;
	char reg_timer[8];
	char * title;
	char * aux;
	int channelNum;
	char channelName[50]; //TODO Remove
	char mux[50];         //TODO Remove
	char * newt;
} timerEntry;

void initTE(timerEntry * o);
void freeTE(timerEntry o);
void freeTimerList(timerEntry * o, int max);
timerEntry * getTimerList(int * max, int sortBy, int sortDirection);
int checkForTimer(timerEntry * timerList, int maxTimer, int channelNum, time_t startTime, time_t endTime, int duration);
//TODO addTimer's return value inconsistent with editTimer and deleTimer
int addTimer(const char * newt);
int editTimer(int timerID, char * oldTimer, char * newTimer);
int deleTimer(int timerID, char * timer);

#endif

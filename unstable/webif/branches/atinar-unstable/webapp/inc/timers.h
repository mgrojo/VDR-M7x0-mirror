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

#include "channels.h"
#include "conf.h"

enum timerFlags_e { 
	TF_NONE = 0x0000,
	TF_ACTIVE = 0x0001,
	TF_INSTANT = 0x0002,
	TF_VPS = 0x0004,
	TF_RECORDING = 0x0008,
	TF_ALL = 0xFFFF
};

typedef enum timerType_e {
	TT_UNDEFINED = 0,
	TT_ONE_TIME = 1,
	TT_REGULAR = 2
} timerType_t;

enum timerFields_e {
	TF_TITLE=1,
	TF_AUX=2,
	TF_CHANNEL=4,
	TF_TIMER_STR=8,
};

typedef struct vdrTimer_s {
	int my;
	int id;
	int hostId;
 	time_t start;
	time_t stop;
	//TODO time_t eventStart;
	//TODO time_t eventStop;
	timerType_t type;
	int priority;
	int lifetime;
	uint flags;
	char wdays[8];
	char *title;
	char *aux;
	int channelNum;
	channel_t const *channel;
	char *timerStr;
	int count; //to create different html id's in program.kl1
} vdrTimer_t;

typedef struct timerList_s {
	int length;
	vdrTimer_t *entry;
} timerList_t;

void initTimer(vdrTimer_t *const entry);
boolean_t initTimerFromEvent(context_t *ctx, vdrTimer_t *const timer, hostConf_t *host, const int channelNum, const int eventId);
boolean_t initTimerFromArgs(vdrTimer_t *const timer, vars_t *args, context_t *ctx);
void freeTimer(vdrTimer_t *const entry);
void initTimerList(timerList_t *const list);
void freeTimerList(timerList_t *const list);
void getTimerList(timerList_t *const timers, channelList_t const *const channels, const sortField_t sortBy, const sortDirection_t sortDirection);
boolean_t addTimer(context_t *ctx, hostConf_t *host, const char *newTimerStr);
boolean_t editTimer(context_t *ctx, hostConf_t *host, int id, const char *oldTimerStr, const char *newTimerStr);
boolean_t deleteTimer(context_t *ctx, hostConf_t *host, int id, const char *oldTimerStr);
boolean_t parseTimer(const char *line, vdrTimer_t *const timer);
char *makeRegularTimerStr(uint flags,int channelNum,const char *wdays,time_t start,time_t stop,int priority,int lifetime,char *title,const char *aux);
char *makeOneTimeTimerStr(uint flags,int channelNum,time_t start,time_t stop,int priority,int lifetime,char *title,const char *aux);
char *makeTimerStr(vdrTimer_t *const timer);
void printTimerForm(context_t *ctx, vdrTimer_t *const timer, channelList_t const *const channels);
void printTimerBars(context_t *ctx, timerList_t *const timers, const int channelNum
	, const time_t startTime, const time_t duration,const char *TimerEdit,boolean_t wrapPBWithA);

#endif
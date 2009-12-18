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

#ifndef __RECORDINGS_H__
#define __RECORDINGS_H__

#include <klone/io.h>
#include <klone/request.h>
#include <klone/response.h>
#include "epg.h"
#include "misc.h"

enum recFields_e {
	RF_NAME=1,
	RF_PATH=2,
};

enum recFlags_e {
	RE_NEW=1,
	RE_DIRECT=2,
	RE_EDITED=4,
	RE_DELETED=8,
	RE_REMOTE_INFO_PENDING=16
};

typedef struct audioList_s {
	int length;
	char **entry;
} audioList_t;

typedef struct rec_s {
	int my;
	int hostId;
	int id;
	char * name;
	char * path;
	int flags;
	epgEvent_t event;
	videoType_t video;
	audioList_t audio;
} rec_t;

typedef struct recList_s {
	int length;
	rec_t *entry;
} recList_t;

void initRec(rec_t * const rec);
boolean_t initRecFromArgs(context_t *ctx, rec_t * const rec, vars_t *args);
void freeRec(rec_t * const rec);
void initRecList(recList_t  * const list);
void freeRecList(recList_t  * const list);
void getRecList(recList_t * const list, sortField_t sortBy, sortDirection_t sortDirection);
void sortRecList(recList_t * const list, sortField_t sortBy, sortDirection_t sortDirection);
boolean_t editRec(context_t *ctx, const rec_t *rec, const char *oldName);
boolean_t deleteRec(context_t *ctx, const rec_t *rec);
boolean_t getRecInfo(rec_t *rec);
void printRecInfo(context_t *ctx, const rec_t * const rec);
void printRecPlayLink(context_t *ctx, const rec_t *rec, boolean_t direct);
boolean_t printRecPlaylist(context_t *ctx, rec_t *rec);
void printRecControls(context_t *ctx,const rec_t *rec,const char *Play,const char *Edit,const char *Delete);
void printRecEditForm(context_t *ctx, rec_t *rec);

#endif
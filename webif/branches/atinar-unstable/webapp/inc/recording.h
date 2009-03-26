/*
* 
* This source-code is licensed under GPL v2.
* See ../../LICENSE for details
* 
* Originally written for http://vdr-m7x0.foroactivo.com.es by:
* atinar <atinar1@hotmail.com>
* 
* You will need the KLONE web application development framework
* from www.koanlogic.com Version 2.
* 
*/

#ifndef __RECORDING_H__
#define __RECORDING_H__

#include <klone/session.h>
#include "misc.h"

typedef struct fragmentEntry_s {
  char * path;
  uint64_t start;
  uint64_t end;
  uint64_t size;
} fragmentEntry_t;

typedef struct fragmentList_s {
	int length;
	int fragNum;
	uint64_t fragPos;
	uint64_t totalSize;
	fragmentEntry_t *entry;
} fragmentList_t;

void initFE(fragmentEntry_t *const entry);
void freeFE(fragmentEntry_t *const entry);
void initFL(fragmentList_t *const list);
void freeFL(fragmentList_t *const list);
boolean_t seekFragment(fragmentList_t *list, uint64_t totalPos);
boolean_t getFragmentList(fragmentList_t * const list, const char *recPath, int recId);

#endif
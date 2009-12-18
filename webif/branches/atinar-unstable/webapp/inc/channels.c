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

#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <u/libu.h>

#include "svdrp_comm.h"
#include "channels.h"

void initChannel(channel_t * const channel){
	memset(channel,0,sizeof(channel_t));
	channel->channelId=NULL;
	channel->channelName=NULL;
	channel->multiplexName=NULL;
	channel->parameter=NULL;
	channel->source=NULL;
}

void freeChannel(channel_t * const channel){
	free(channel->channelId);
	free(channel->channelName);
	free(channel->multiplexName);
	free(channel->parameter);
	free(channel->source);
	initChannel(channel);
}

void initChannelList(channelList_t * const list){
	list->length=0;
	list->channel=NULL;
}

void freeChannelList(channelList_t * const list){
	int i;
	channel_t *channel;
	for (i=0,channel=list->channel;i<list->length;i++,channel++){
		freeChannel(channel);
	}
	free(list->channel);
	list->length=0;
	list->channel=NULL;
}

void parseChannel(char * line, channel_t * channel) {
	char *r;
	int k,l;

	r=line;
	channel->channelNum=strtol(r,&r,10);
	r+=strspn(r," ");
	for(k=0;k<13 && r[0];k++) {
		l=strcspn(r,":");
		switch(k){
			case  0:
			{
				int l2=strcspn(r,",;:");
				crit_goto_if((channel->channelName=strndup(r,l2))==NULL,outOfMemory);
				if (r[l2]!=':') {
					char *r2=r+l2+1;
					l2=strcspn(r2,":");
					crit_goto_if((channel->multiplexName=strndup(r2,l2))==NULL,outOfMemory);
				} else {
					channel->multiplexName=strdup("");
				}
				break;
			}
			case  1: channel->frequency=strtol(r,NULL,10); break;
			case  2: crit_goto_if((channel->parameter=strndup(r,l))==NULL,outOfMemory); break;
			case  3: crit_goto_if((channel->source=strndup(r,l))==NULL,outOfMemory);    break;
			case  5: channel->vpid=strtol(r,NULL,10); break;
			case  8: channel->caid=strtol(r,NULL,10); break;
			case  9: channel->sid =strtol(r,NULL,10); break;
			case 10: channel->nid =strtol(r,NULL,10); break;
			case 11: channel->tid =strtol(r,NULL,10); break;
			case 12: channel->rid =strtol(r,NULL,10); break;
		}
		r+=l;
		if (r[0]!=':') break;
		r++; 
	}
	if( channel->rid ){
		crit_goto_if(asprintf(&channel->channelId,"%s-%d-%d-%d-%d",channel->source,channel->nid,channel->tid,channel->sid,channel->rid)<0,outOfMemory);
	} else {
		crit_goto_if(asprintf(&channel->channelId,"%s-%d-%d-%d",channel->source,channel->nid,channel->tid,channel->sid)<0,outOfMemory);
	}
	return;
outOfMemory:
	crit("Out of memory");
	exit(1);
}

int compareChannels(const channel_t *ca, const channel_t *cb, sortField_t sortBy, sortDirection_t sortDirection) {
	int result;
	switch (sortBy) {
		case SF_MUX:
			result=strcasecmp(ca->multiplexName,cb->multiplexName)*sortDirection;
			if (result) return result;
		case SF_NAME: 
			result=strcasecmp(ca->channelName,cb->channelName)*sortDirection;
			if (result) return result;
		case SF_CH_NUMBER: 
			return (ca->channelNum-cb->channelNum)*sortDirection;
		default: 
			return 0;
	}
}

void sortChannelList(channelList_t * const list, const sortField_t sortBy, const sortDirection_t sortDirection) {
	int compare(const void * a, const void * b) {
		return compareChannels((const channel_t*)a,(const channel_t*)b,sortBy,sortDirection);
	}
	if (list->length>0 && sortBy!=SF_NONE) {
		qsort(list->channel,list->length,sizeof(channel_t),compare);
	}
}

void getChannelList(hostConf_t *host, channelList_t * const list, sortField_t sortBy, sortDirection_t sortDirection) {
	initChannelList(list);
	char *data=execSvdrp(host,"LSTC");
	if (data){
		char *p;
		for(p=strtok(data,"\r\n");p!=0;p=strtok(0,"\r\n")) {
			if (atoi(p)==SVDRP_CMD_OK){
				crit_goto_if((list->channel=(channel_t *)realloc(list->channel,(++list->length)*sizeof(channel_t)))==NULL,outOfMemory);
				channel_t *channel=list->channel+list->length-1;
				initChannel(channel);
				parseChannel(p+4,channel);
			}
		}
		free(data);
		sortChannelList(list,sortBy,sortDirection);
	}
	return;
outOfMemory:
	crit("Out of memory");
	exit(1);
}

boolean_t getChannel(hostConf_t *host, int channelNum, channel_t * const channel) {
	char cmd[10];

	initChannel(channel);
	if (channelNum<1) {
		sprintf(cmd,"CHAN");
	} else {
		sprintf(cmd,"CHAN %d",channelNum);
	}
	boolean_t result=BT_FALSE;
	char *data=execSvdrp(host,cmd);
	if (data) {
		char *r;
		int code=strtol(data,&r,10);
		if (code==SVDRP_CMD_OK) {
			r++;
			channel->channelNum=strtol(r,&r,10);
			r++;
			int l=strcspn(r,"\r\n");
			channel->channelName=strndup(r,l);
			result=BT_TRUE;
		}
		free(data);
	}
	return result;
}

void printChannelListSelect(context_t *ctx,const char *id, const char *name,
	const channelList_t *const channels, int channelNum, const char *onchange)
{
	int i;
	channel_t *channel;
	ctx_printfn(ctx,"<select id=\"%s\" name=\"%s\" size=\"1\"",0,1,(id)?id:name,name);
	if (onchange!=NULL){
		ctx_printf(ctx," onchange=\"%s\"",onchange);
	}
	ctx_printf(ctx,">\n");
	for (i=0,channel=channels->channel;i<channels->length;i++,channel++) {
		ctx_printf0(ctx,"<option value=\"%d\" %s>%d - %s</option>\n"
			,channel->channelNum,selected[boolean(channel->channelNum==channelNum)]
			,channel->channelNum,channel->channelName);
		}
	ctx_printfn(ctx,"</select>\n",-1,0);
}

void printChannelControls(context_t *ctx,const channel_t *channel,const char *Epg,const char *LiveStream){
	ctx_printfn(ctx,"<ul class=\"controls\"><!--\n",0,1);
	if (Epg) {
		ctx_printfn(ctx,"--><li class=\"control\">\n",0,1);
		ctx_printf0(ctx,"<a href=\"epg.kl1?channelNum=%d\" class=\"epg control button-i ui-state-default\" title=\"%s\">"
				"<span class=\"ui-icon ui-icon-clock\">%s</span>"
			"</a>\n",channel->channelNum,Epg,Epg);
		ctx_printfn(ctx,"</li><!--\n",-1,0);
	}
	if (LiveStream) {
		boolean_t isTv=boolean(channel->vpid>1);
		ctx_printfn(ctx,"--><li class=\"control\">\n",0,1);
		ctx_printf0(ctx,"<a href=\"live.kl1?channelNum=%d\" class=\"live control button-i ui-state-default\" title=\"%s\">"
				"<span class=\"ui-icon ui-icon-%s\">%s</span>"
			"</a>\n",channel->channelNum,LiveStream,(isTv)?"tv":"radio",LiveStream);
		ctx_printfn(ctx,"</li><!--\n",-1,0);
	}
	ctx_printfn(ctx,"--></ul>\n",-1,0);
}

char *ctxChannelDisplayName(context_t *ctx,const channel_t *channel){
	if (strchr(channel->channelName,'.')){
		CTX_CHK_BUFFER(strlen(channel->channelName));
		strcpy(ctx->buffer,channel->channelName);
		char *c;
		while ((c=strchr(ctx->buffer,'.'))!=NULL) *c=' ';
		return ctx->buffer;
	} else {
		return channel->channelName;
	}
}


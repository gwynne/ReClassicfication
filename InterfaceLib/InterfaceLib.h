//
//  InterfaceLib.h
//  ReClassicfication
//
//  Created by Gwynne Raskind on 2/20/13.
//  Copyright (c) 2013 Uli Kusterer. All rights reserved.
//

#ifndef __INTERFACELIB__
#define __INTERFACELIB__

#include <sys/types.h>
#include <inttypes.h>

// These are data structures maintained by the emulation layer.

typedef struct {
	int16_t LM_memErr; // TODO: find original LM address
	void * LM_appZone;
	void * LM_sysZone;
} LMGlobals;

typedef struct {
	LMGlobals globals;
	void *memoryMgrPrivate;
	// QD globals go here too
} InterfaceLibContext;

extern InterfaceLibContext *CurrentContext(void);

#endif

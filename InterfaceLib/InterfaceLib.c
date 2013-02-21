//
//  InterfaceLib.c
//  ReClassicfication
//
//  Created by Gwynne Raskind on 2/20/13.
//  Copyright (c) 2013 Uli Kusterer. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <dispatch/dispatch.h>
#include "InterfaceLib.h"

InterfaceLibContext *CurrentContext(void)
{
	static InterfaceLibContext *context = NULL;
	static dispatch_once_t predicate = 0;
	
	dispatch_once(&predicate, ^ {
		context = calloc(1, sizeof(InterfaceLibContext));
		// initialize the values of the globals here?
	});
	return context;
}

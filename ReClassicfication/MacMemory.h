/*	같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같�	PROJECT:	FakeHandles		FILE:		MacMemory.h		PURPOSE:	Simulate Handles on machines which only have ANSI-C to easily				port some of the more simple Macintosh code fragments to other				platforms.			COPYRIGHT:	(C) Copyright 1998 by M. Uli Kusterer, all rights reserved.					REACH ME AT:				E-MAIL:		witness@weblayout.com				COMPUSERVE:	101646,3646 / custos				URL:		http://www.weblayout.com/witness			REVISIONS:		98-08-30	UK		Created.					같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같 */#/* 金金金金金金金金金金金金金金金金金金金金金金金金金金金金金金金金金金金金金金金金	Constants:   金金金金金金金金金金金金金金金金金金金金金金金金金金金金金金金金金金金金金金� */#ifndef NULL  #define NULL	0L#endif#define NewHandle			NewFakeHandle#define DisposeHandle		DisposeFakeHandle#define SetHandleSize		SetFakeHandleSize#define	GetHandleSize		GetFakeHandleSize/* 金金金金金金金金金金金金金金金金金金金金金金金金金金金金金金金金金金金金金金金金	Data Types:   金金金金金金金金金金金金金金金金金金金金金金金金金金金金金金金金金金金金金金� */// Data types special to Mac:typedef	char**			Handle;typedef unsigned char	Boolean;
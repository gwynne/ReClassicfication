//
//  Memory.c
//  ReClassicfication
//
//  Created by Gwynne Raskind on 2/20/13.
//  Copyright (c) 2013 Uli Kusterer. All rights reserved.
//

#include "InterfaceLib.h"
#include "Memory.h"

typedef struct {
	THz currentZone;
	THz tempZone;
} MemoryManagerPrivate;

static inline MemoryManagerPrivate *_MemGetPrivate(void)
{
	return CurrentContext()->memoryMgrPrivate;
}

GrowZoneUPP NewGrowZoneUPP(GrowZoneProcPtr userRoutine)
{
	return userRoutine;
}

PurgeUPP NewPurgeUPP(PurgeProcPtr userRoutine)
{
	return userRoutine;
}

UserFnUPP NewUserFnUPP(UserFnProcPtr userRoutine)
{
	return userRoutine;
}

void DisposeGrowZoneUPP(GrowZoneUPP userUPP)
{
}

void DisposePurgeUPP(PurgeUPP userUPP)
{
}

void DisposeUserFnUPP(UserFnUPP userUPP)
{
}

long InvokeGrowZoneUPP(Size cbNeeded, GrowZoneUPP userUPP)
{
	return userUPP(cbNeeded);
}

void InvokePurgeUPP(Handle blockToPurge, PurgeUPP userUPP)
{
	userUPP(blockToPurge);
}

void InvokeUserFnUPP(void * parameter, UserFnUPP userUPP)
{
	userUPP(parameter);
}

OSErr MemError(void)
{
	OSErr err = LMGetMemErr();
	LMSetMemErr(noErr);
	return err;
}

SInt16 LMGetMemErr(void)
{
	return CurrentContext()->globals.LM_memErr;
}

void LMSetMemErr(SInt16 value)
{
	CurrentContext()->globals.LM_memErr = value;
}

Handle NewHandle(Size byteCount)
{
	Handle h = NewEmptyHandle();
	
	if (!h)
		return NULL;
	ReallocateHandle(h, byteCount);
	return h;
}

Handle NewHandleClear(Size byteCount)
{
	Handle h = NewHandle(byteCount);
	
	BlockZero(*h, byteCount); // no need to HLock(), no one knows about it yet
	return h;
}

static Boolean _IsRelocatableBlock(Ptr p);

Handle RecoverHandle(Ptr p)
{
	if (_IsRelocatableBlock(p))
		return &p;
	return NULL;
}

static Ptr _NewPtrInZone(Size byteCount, THz zone);

Ptr NewPtr(Size byteCount)
{
	return _NewPtrInZone(byteCount, _MemGetPrivate()->currentZone);
}

Ptr NewPtrClear(Size byteCount)
{
	Ptr p = NewPtr(byteCount);
	
	BlockZero(p, byteCount);
	return p;
}

long MaxBlock(void)
{
	return LMGetApplZone()->minCBFree;
}

long StackSpace(void)
{
	return 0; // LMGetStackBase() - LMGetApplZone()->bkLim
}

static Ptr _AllocateMasterPointerInZone(THz zone);

Handle NewEmptyHandle(void)
{
	Ptr p = _AllocateMasterPointerInZone(_MemGetPrivate()->currentZone);
	
	HSetState(&p, 0);
	return &p;
}

void HLock(Handle h)
{
	HSetState(h, HGetState(h) | kHandleLockedMask);
}

void HLockHi(Handle h)
{
	HLock(h);
}

void HUnlock(Handle h)
{
	HSetState(h, HGetState(h) & ~kHandleLockedMask);
}

void HPurge(Handle h)
{
	HSetState(h, HGetState(h) | kHandlePurgeableMask);
}

void HNoPurge(Handle h)
{
	HSetState(h, HGetState(h) & ~kHandlePurgeableMask);
}

Handle TempNewHandle(Size logicalSize, OSErr * resultCode)
{
	Ptr p = _AllocateMasterPointerInZone(_MemGetPrivate()->tempZone);
	
	HSetState(&p, 0);
	*resultCode = noErr;
	return &p;
}

Size TempMaxMem(Size * grow)
{
	
}

long TempFreeMem(void);
Size CompactMem(Size cbNeeded);
void PurgeMem(Size cbNeeded);
long FreeMem(void);
Size MaxMem(Size * grow);
void SetGrowZone(GrowZoneUPP growZone);
GrowZoneUPP GetGrowZone(void);
void MoveHHi(Handle h);
void DisposePtr(Ptr p);
Size GetPtrSize(Ptr p);
void SetPtrSize(Ptr p, Size newSize);
void DisposeHandle(Handle h);
void SetHandleSize(Handle h, Size newSize);
Size GetHandleSize(Handle h);
void ReallocateHandle(Handle h, Size byteCount);
void EmptyHandle(Handle h);
void HSetRBit(Handle h);
void HClrRBit(Handle h);
SInt8 HGetState(Handle h);
void HSetState(Handle h, SInt8 flags);
void BlockMove(const void *srcPtr,void *destPtr,Size byteCount);
void BlockMoveData(const void *srcPtr,void *destPtr,Size byteCount);
void BlockMoveUncached(const void *srcPtr,void *destPtr,Size byteCount);
void BlockMoveDataUncached(const void *srcPtr,void *destPtr,Size byteCount);
void BlockZero(void *destPtr,Size byteCount);
void BlockZeroUncached(void *destPtr,Size byteCount);
OSErr HandToHand(Handle * theHndl);
OSErr PtrToXHand(const void * srcPtr, Handle dstHndl, long size);
OSErr PtrToHand(const void * srcPtr, Handle * dstHndl, long size);
OSErr HandAndHand(Handle hand1, Handle hand2);
OSErr PtrAndHand(const void * ptr1, Handle hand2, long size);
void MoreMasters(void);
void MoreMasterPointers(UInt32 inCount);
void TempHLock(Handle h, OSErr * resultCode);
void TempHUnlock(Handle h, OSErr * resultCode);
void TempDisposeHandle(Handle h, OSErr * resultCode);
Ptr TempTopMem(void);
OSErr HoldMemory(void * address, unsigned long count);
OSErr UnholdMemory(void * address, unsigned long count);
OSErr MakeMemoryResident(void * address, unsigned long count);
OSErr ReleaseMemoryData(void * address, unsigned long count);
OSErr MakeMemoryNonResident(void * address, unsigned long count);
OSErr FlushMemory(void * address, unsigned long count);
Handle GZSaveHnd(void);
Ptr TopMem(void);
void ReserveMem(Size cbNeeded);
void PurgeSpace(long * total, long * contig);
long PurgeSpaceTotal(void);
long PurgeSpaceContiguous(void);
Boolean CheckAllHeaps(void);
Boolean IsHeapValid(void);
Boolean IsHandleValid(Handle h);
Boolean IsPointerValid(Ptr p);
THz LMGetSysZone(void);
void LMSetSysZone(THz value);
THz LMGetApplZone(void);
void LMSetApplZone(THz value);

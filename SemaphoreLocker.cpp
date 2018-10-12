//---------------------------------------------------------------------------

#pragma hdrstop

#include "SemaphoreLocker.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

SemaphoreLocker::SemaphoreLocker(HANDLE hSem) : hSemaphore(hSem) {
	WaitForSingleObject(hSemaphore, INFINITE);
}

SemaphoreLocker::~SemaphoreLocker() {
    ReleaseSemaphore(hSemaphore, 1, NULL);
}
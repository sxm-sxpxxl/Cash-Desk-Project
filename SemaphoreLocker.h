//---------------------------------------------------------------------------

#ifndef SemaphoreLockerH
#define SemaphoreLockerH
//---------------------------------------------------------------------------
#include <windows.h>

class SemaphoreLocker {
private:
	HANDLE hSemaphore;
public:
	SemaphoreLocker(HANDLE);
    ~SemaphoreLocker();
};

#endif

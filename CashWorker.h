//---------------------------------------------------------------------------

#ifndef CashWorkerH
#define CashWorkerH
//---------------------------------------------------------------------------
#include <queue>
#include <System.hpp>
#include <System.SysUtils.hpp>
#include "SemaphoreLocker.h"

class CashWorker {
private:
	HANDLE hThread;
	HANDLE hStopEvent;
	HANDLE hFreeEvent;

	static HANDLE hMutex;

	static HANDLE hUpdateEvent;
	static HANDLE hSemaphore;

	TDateTime timeStartService;
	TDateTime timeCurrentDurationService;
	TDateTime timeEndService;

	static std::queue<int> clientQueue;
	static int countCashWorker;
	static volatile long numberOfClient;

	void update();
	static bool isQueueEmpty();
    static TDateTime addTimeInSec(TDateTime targetTime, unsigned long addedSec, bool isAddedTargetTimeSec);
	static unsigned short getSecInDateTime(TDateTime dateTime);
	static DWORD WINAPI ThreadProc(LPVOID pvParam);
public:
	CashWorker();
	~CashWorker();

	void start();
	void stop();
	static bool isUpdate();
    static void resetUpdate() { ResetEvent(CashWorker::hUpdateEvent); }
	bool isFree();
	static int getNumberOfClient() { return numberOfClient; }
	static int getSizeQueue() { return clientQueue.size(); }
	static void setNumberOfCashier(int value);
	static void addClientToQueue();
	unsigned short getTimeToEndServiceInSec();

//	int getTimeToFullFilledInSec();
//	static int GetNumberOfFillingCar();
//    bool isStop();
//    static bool IsUpdate();
//	static void ResetUpdate();
};

#endif

//---------------------------------------------------------------------------

#pragma hdrstop

#include "CashWorker.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

std::queue<int> CashWorker::clientQueue;
int CashWorker::countCashWorker = 0;
volatile long CashWorker::numberOfClient = 0;

HANDLE CashWorker::hSemaphore = INVALID_HANDLE_VALUE;
HANDLE CashWorker::hMutex = CreateMutex(NULL, FALSE, NULL);
HANDLE CashWorker::hUpdateEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

CashWorker::CashWorker() {
	hThread = INVALID_HANDLE_VALUE;
	hStopEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	hFreeEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

    countCashWorker++;
	if (countCashWorker == 1) {
		CashWorker::hSemaphore = CreateSemaphore(NULL, 3, 3, NULL);
	}
}

CashWorker::~CashWorker() {
	stop();
	CloseHandle(hStopEvent);
	CloseHandle(hFreeEvent);

	countCashWorker--;
	if (countCashWorker == 0) {
		CloseHandle(CashWorker::hSemaphore);
		CashWorker::hSemaphore = INVALID_HANDLE_VALUE;
	}
}

void CashWorker::start() {
    if (hThread != INVALID_HANDLE_VALUE) return;

	ResetEvent(hStopEvent);
	ResetEvent(hUpdateEvent);
    hThread = CreateThread(NULL, NULL, ThreadProc, (LPVOID)this, NULL, NULL);
}

void CashWorker::stop() {
    if (hThread == INVALID_HANDLE_VALUE) return;

	SetEvent(hStopEvent);
	if (WaitForSingleObject(hThread, 1000) == WAIT_TIMEOUT) {
		TerminateThread(hThread, 0);
	}
	CloseHandle(hThread);
	hThread = INVALID_HANDLE_VALUE;
}

bool CashWorker::isUpdate() {
    return WaitForSingleObject(CashWorker::hUpdateEvent, 0) == WAIT_OBJECT_0;
}

bool CashWorker::isFree() {
    return WaitForSingleObject(this->hFreeEvent, 0) == WAIT_OBJECT_0;
}

void CashWorker::addClientToQueue() {
	CashWorker::clientQueue.push(1);
	SetEvent(CashWorker::hUpdateEvent);
}

// DANGER!   можно вызвать только до старта
void CashWorker::setNumberOfCashier(int value) {
	if (CashWorker::hSemaphore != INVALID_HANDLE_VALUE)
		CloseHandle(CashWorker::hSemaphore);
	CashWorker::hSemaphore = CreateSemaphore(NULL, value, value, NULL);
}

DWORD WINAPI CashWorker::ThreadProc(LPVOID pvParam) {
	CashWorker* _this = (CashWorker*) pvParam;
	if (!_this) return 1;

	SemaphoreLocker semLocker(hSemaphore);
	while (WaitForSingleObject(_this->hStopEvent, 0) == WAIT_TIMEOUT) {
		if (CashWorker::isQueueEmpty()) {
			if (!_this->isFree()) SetEvent(_this->hFreeEvent);
			continue;
		}
		else if (_this->isFree()) ResetEvent(_this->hFreeEvent);

		CashWorker::clientQueue.pop();
		InterlockedIncrement(&numberOfClient);
		_this->update();

		_this->timeStartService = Now();
		_this->timeEndService = addTimeInSec(Now(), 3, true);
		while(WaitForSingleObject(_this->hStopEvent, 1) == WAIT_TIMEOUT) {
			_this->timeCurrentDurationService =
				addTimeInSec(_this->timeStartService,
							 CashWorker::getSecInDateTime(Now()) -
							 CashWorker::getSecInDateTime(
								_this->timeStartService), false
				);
			_this->update();

			if (getSecInDateTime(_this->timeCurrentDurationService) >=
				getSecInDateTime(_this->timeEndService) -
				getSecInDateTime(_this->timeStartService)) {
				break;
			}
		}

		InterlockedDecrement(&numberOfClient);
		_this->update();
	}
	return 0;
}

bool CashWorker::isQueueEmpty() {
	WaitForSingleObject(hMutex, 10);
	bool isEmpty = CashWorker::clientQueue.empty();
	ReleaseMutex(hMutex);
	return isEmpty;
}

void CashWorker::update() {
	SetEvent(CashWorker::hUpdateEvent);
	while (WaitForSingleObject(CashWorker::hUpdateEvent, 0) == WAIT_OBJECT_0 &&
		   WaitForSingleObject(CashWorker::hStopEvent, 0) == WAIT_TIMEOUT) { }
}

TDateTime CashWorker::addTimeInSec(TDateTime targetTime, unsigned long addedSec, bool isAddedTargetTimeSec) {
	unsigned short hour, min, sec, msec;
	targetTime.DecodeTime(&hour, &min, &sec, &msec);

	if (isAddedTargetTimeSec) {
		if (sec + addedSec >= 60) {
			min++;
            sec = sec + addedSec - 60;
		} else sec += addedSec;
	} else sec = addedSec;

	TDateTime endTime(hour, min, sec, msec);
	return endTime;
}

unsigned short CashWorker::getSecInDateTime(TDateTime dateTime) {
	unsigned short hour, min, sec, msec;
	dateTime.DecodeTime(&hour, &min, &sec, &msec);
	return sec;
}

unsigned short CashWorker::getTimeToEndServiceInSec() {
	return (CashWorker::getSecInDateTime(timeEndService) - CashWorker::getSecInDateTime(timeStartService)) -
			CashWorker::getSecInDateTime(timeCurrentDurationService);
}

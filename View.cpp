//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "View.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMainForm *MainForm;
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
	: TForm(Owner) {}
//---------------------------------------------------------------------------
void __fastcall TMainForm::UpdateTimer(TObject *Sender)
{
    ThreadInfoListBox->Clear();
	for (size_t i = 0; i < cashierVec.size(); i++) {
		ThreadInfoListBox->Items->Add(L"Thread #" + IntToStr((int)(i + 1)) + L": ");
		if (!cashierVec[i]->isFree()) {
			ThreadInfoListBox->Items->Add(L"Free: False | Time to end service the client: " +
											IntToStr(cashierVec[i]->getTimeToEndServiceInSec()));
		} else ThreadInfoListBox->Items->Add(L"Free: True");
		ThreadInfoListBox->Items->Add(EmptyStr);
	}

	if (CashWorker::isUpdate()) {
		NumberOfServicedClientsLabel->Caption = IntToStr(CashWorker::getNumberOfClient());
		SizeQueueLabel->Caption = IntToStr(CashWorker::getSizeQueue());
		CashWorker::resetUpdate();
	}
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::StartButtonClick(TObject *Sender)
{
    StartButton->Enabled = false;
	StopButton->Enabled = true;

	startWork();
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::AddClientButtonClick(TObject *Sender)
{
	CashWorker::addClientToQueue();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::StopButtonClick(TObject *Sender)
{
	StartButton->Enabled = true;
	StopButton->Enabled = false;

	for (size_t i = 0; i < cashierVec.size(); i++) delete cashierVec[i];
    cashierVec.clear();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::AddToQueueTimer(TObject *Sender)
{
    CashWorker::addClientToQueue();
}
//---------------------------------------------------------------------------

void TMainForm::startWork() {
    int countCashier = CountCashierRadioGroup->ItemIndex + 1;

	for(int i = 0; i < countCashier; i++) {
		CashWorker* pCashWorker = new CashWorker();
		cashierVec.push_back(pCashWorker);
		pCashWorker->start();
	}
}

void __fastcall TMainForm::CountCashierRadioGroupClick(TObject *Sender)
{
	if (StartButton->Enabled) return;

	for (size_t i = 0; i < cashierVec.size(); i++) delete cashierVec[i];
	cashierVec.clear();

	CashWorker::setNumberOfCashier(CountCashierRadioGroup->ItemIndex);

	startWork();
}
//---------------------------------------------------------------------------


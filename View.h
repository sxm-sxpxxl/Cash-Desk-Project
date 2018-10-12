//---------------------------------------------------------------------------

#ifndef ViewH
#define ViewH
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.StdCtrls.hpp>
//---------------------------------------------------------------------------
#include <vector>
#include "CashWorker.h"

class TMainForm : public TForm
{
__published:	// IDE-managed Components
	TLabel *Label1;
	TLabel *NumberOfServicedClientsLabel;
	TLabel *Label3;
	TLabel *SizeQueueLabel;
	TTimer *Update;
	TButton *AddClientButton;
	TButton *StartButton;
	TRadioGroup *CountCashierRadioGroup;
	TButton *StopButton;
	TTimer *AddToQueue;
	TListBox *ThreadInfoListBox;
	void __fastcall UpdateTimer(TObject *Sender);
	void __fastcall StartButtonClick(TObject *Sender);
	void __fastcall AddClientButtonClick(TObject *Sender);
	void __fastcall StopButtonClick(TObject *Sender);
	void __fastcall AddToQueueTimer(TObject *Sender);
	void __fastcall CountCashierRadioGroupClick(TObject *Sender);

private:	// User declarations
	std::vector<CashWorker*> cashierVec;

	void startWork();
public:		// User declarations
	__fastcall TMainForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif

//---------------------------------------------------------------------------

#ifndef BilliardH
#define BilliardH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Samples.Gauges.hpp>
//---------------------------------------------------------------------------
class TFormTable : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TGauge *GaugePower;
	TTimer *TimerB;
	TLabel *Label1;
	TButton *ButtonStart;
	void __fastcall FormMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall FormMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall FormMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall ButtonStartClick(TObject *Sender);
	void __fastcall TimerBTimer(TObject *Sender);



private:	// User declarations
public:		// User declarations
    bool ifMouseL;
	__fastcall TFormTable(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormTable *FormTable;
//---------------------------------------------------------------------------
#endif

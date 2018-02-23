//---------------------------------------------------------------------------

#ifndef TShowBorderH
#define TShowBorderH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>

#include "impulse.hpp"
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TShowBorder : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TSpeedButton *ZoomInButton;
	TLabel *ScaleLabel;
	TSpeedButton *ZoomOutButton;
	TImage *Image;
	TStatusBar *StatusBar1;
	TSpeedButton *SpeedButton1;
	TSpeedButton *SpeedButton2;
	void __fastcall FormPaint(TObject *Sender);
	void __fastcall FormClick(TObject *Sender);
	void __fastcall FormDblClick(TObject *Sender);
	void __fastcall ZoomInButtonClick(TObject *Sender);
	void __fastcall ZoomOutButtonClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall ImageClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
         EWhatShow  whatShow;
         double     ScaleShow;       // масштаб вывода на экран
         double     MaxValue;
         double     deltaF;
         int        QEquLine;
		 int        CurrPersent;
		 HDC		PaintDC;

	__fastcall TShowBorder(TComponent* Owner);
	void __fastcall ClearPicture(void);
};
//---------------------------------------------------------------------------
extern PACKAGE TShowBorder *ShowBorderArrange;
extern PACKAGE TShowBorder *ShowBorderPhisic;
extern PACKAGE TShowBorder *ShowEquL;
extern PACKAGE TShowBorder *ShowEquU;
extern PACKAGE TShowBorder *ShowEquV;
extern PACKAGE TShowBorder *ShowEquJ;
extern PACKAGE TShowBorder *ShowChannel;
extern PACKAGE TShowBorder *ShowCalculate;

//---------------------------------------------------------------------------
#endif

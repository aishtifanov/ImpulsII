//---------------------------------------------------------------------------

#ifndef TPressWinH
#define TPressWinH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>

#define NUM_IN_ARR_EPSILON    5000

#include "impulse.hpp"

//---------------------------------------------------------------------------
class TPressWin : public TForm
{
__published:	// IDE-managed Components
	TImage *Image;
	TPanel *Panel1;
	TSpeedButton *SpeedButton1;
	TSpeedButton *SpeedButton2;
	TStatusBar *StatusBar1;
	TSpeedButton *btnPrev;
	TSpeedButton *btnNext;
	TSpeedButton *btnStop;
	TTimer *Timer1;
	void __fastcall FormPaint(TObject *Sender);
	void __fastcall btnPrevClick(TObject *Sender);
	void __fastcall btnNextClick(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall btnStopClick(TObject *Sender);
	void __fastcall Timer1Timer(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TPressWin(TComponent* Owner);
	__fastcall ~TPressWin();


		 int iH, iW, iX, iY;
		 double CoeffH, CoeffW, MaxPt, MaxTime, iCoeffH;
		 int numLineX, numLineY;
		 HFONT hFont;

		 float *arrPress[NUM_IN_ARR_EPSILON];
		 int   N;
		 int   NumIter;
		 int   CurrGR;

		 void __fastcall Init(int timeTotal, int N);
		 void __fastcall Halt();

		 void __fastcall DrawAxes(HDC PDC);
		 void __fastcall DrawGraphic(HDC PDC, BOOL Gray);
		 void __fastcall DrawOneMomentPress(HDC PDC);
		 void __fastcall DrawIntegralPress(HDC PDC);

		 void __fastcall Read(ifstream &fr);
		 void __fastcall Write(ofstream &fw);

};
//---------------------------------------------------------------------------
extern PACKAGE TPressWin *PressWin;
//---------------------------------------------------------------------------
#endif

//---------------------------------------------------------------------------

#ifndef TCalcWindowH
#define TCalcWindowH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>

#include "impulse.hpp"
#include <ComCtrls.hpp>
#include <Buttons.hpp>

//---------------------------------------------------------------------------
class TCalcWindow : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TImage *Image;
	TStatusBar *StatusBar1;
	TSpeedButton *SpeedButton1;
	TSpeedButton *SpeedButton2;
	void __fastcall FormPaint(TObject *Sender);
private:	// User declarations
public:		// User declarations
		 int iH, iW, iX, iY;
		 double CoeffH, CoeffW, MaxPt, MaxTime, iCoeffH;
		 int numLineX, numLineY;

		 float arrEps[5000];
		 int   arrNum[5000];
		 int   cntME;
		 bool  CalcDOIT;

	__fastcall TCalcWindow(TComponent* Owner);
	 void __fastcall DrawEps(double Eps);
	 void __fastcall DrawAxes(HDC PDC);
	 void __fastcall SetZero();
	 void __fastcall SetFields(String ATitle, double _MaxTime = 1000);
	 void __fastcall Read(ifstream &fr);
	 void __fastcall Write(ofstream &fw);

};
//---------------------------------------------------------------------------
extern PACKAGE TCalcWindow *CalcWindow;
extern PACKAGE TCalcWindow *CalcP1;
extern PACKAGE TCalcWindow *CalcP2;
extern PACKAGE TCalcWindow *CalcEp;
extern PACKAGE TCalcWindow *CalcEk;

//---------------------------------------------------------------------------
#endif

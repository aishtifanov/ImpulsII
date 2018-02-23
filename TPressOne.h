//---------------------------------------------------------------------------

#ifndef TPressOneH
#define TPressOneH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>

#include "impulse.hpp"
//---------------------------------------------------------------------------
class TPressOne : public TForm
{
__published:	// IDE-managed Components
	TImage *Image;
	void __fastcall FormPaint(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TPressOne(TComponent* Owner);
	__fastcall ~TPressOne();

	 int iH, iW, iX, iY;
	 double CoeffH, CoeffW, MaxPt, MaxTime, iCoeffH;
	 int numLineX, numLineY;
	 HFONT hFont;

	 float arrEps[10000];
	 int   cntME;

	 void __fastcall DrawAxes(HDC PDC);
	 void __fastcall SetZero();
	 void __fastcall Read(ifstream &fr);
	 void __fastcall Write(ofstream &fw);
};
//---------------------------------------------------------------------------
extern PACKAGE TPressOne *PressOne;
//---------------------------------------------------------------------------
#endif

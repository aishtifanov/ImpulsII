//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "TShowBorder.h"
#include "TModConf.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

const int OX = 130;
const int OY = 20;
const int HANDREDPERSENT = 100;
int EPlus[100];
BOOL bBlackWhite = TRUE;

TShowBorder *ShowBorderArrange=NULL;
TShowBorder *ShowBorderPhisic=NULL;
TShowBorder *ShowEquL=NULL;
TShowBorder *ShowEquU=NULL;
TShowBorder *ShowEquV=NULL;
TShowBorder *ShowEquJ=NULL;
TShowBorder *ShowChannel=NULL;
TShowBorder *ShowCalculate=NULL;

//---------------------------------------------------------------------------
__fastcall TShowBorder::TShowBorder(TComponent* Owner)
	: TForm(Owner)
{
  
  ScaleShow = 1.0;       // масштаб вывода на экран
  QEquLine = 100;
  CurrPersent = 100;
  MaxValue = 0.0;
  whatShow = -1;
}
//---------------------------------------------------------------------------
void __fastcall TShowBorder::FormPaint(TObject *Sender)
{
  if (whatShow == SHOW_CALCULATE ) {
	 return;
  }

  PaintDC = Image->Canvas->Handle;
  MathModel->SetMaxValue();

  switch(whatShow) {
   	 case SHOW_CALCULATE:
	 case SHOW_EQULINES_PSI:  MaxValue = MathModel->MaxValue_Psi;
	 break;
	 case SHOW_EQULINES_U:    MaxValue = MathModel->MaxValue_U;
	 break;
	 case SHOW_EQULINES_V:    MaxValue = MathModel->MaxValue_V;
							  // CurrPersent = 1;
	 break;
	 case SHOW_EQULINES_J:    MaxValue = MathModel->MaxValue_J;
	 break;
	 case SHOW_CHANNEL:       MaxValue = MathModel->MaxValue_J;
							  // MaxValue = MathModel->MaxValue_Psi;
	 break;
  }

  deltaF = MaxValue / QEquLine;

  switch(whatShow) {
	 case SHOW_ARRANGE_BORDER: MaxValue = 0.0;
			MathModel->ShowArrangeBorder(PaintDC, ScaleShow);
	 break;
	 case SHOW_PHISIC_BORDER:  MaxValue = 0.0;
			MathModel->ShowPhisicBorder(PaintDC, ScaleShow);
	 break;
     case SHOW_EQULINES_PSI:    
     case SHOW_EQULINES_U:
     case SHOW_EQULINES_V:
     case SHOW_EQULINES_J:
     case SHOW_CHANNEL:   MathModel->ShowEquLines(PaintDC, whatShow,
						  MaxValue, deltaF, ScaleShow, CurrPersent);
	 break;
	 case SHOW_3D_SURFACE:  MathModel->Show3DSurface(PaintDC);
	 break;
  }

}
//---------------------------------------------------------------------------
void __fastcall TShowBorder::FormClick(TObject *Sender)
{
// ScaleShow += 1;
Canvas->Refresh();
// Refresh();
}
//---------------------------------------------------------------------------

void __fastcall TShowBorder::FormDblClick(TObject *Sender)
{
// ScaleShow -= 1;
// Repaint();
}
//---------------------------------------------------------------------------

void __fastcall TShowBorder::ZoomInButtonClick(TObject *Sender)
{
  ScaleShow += 1;
  char str[6];
  wsprintf(str, "%1d:1", round(ScaleShow));
  ScaleLabel->Caption = str;
  ClearPicture();
}
//---------------------------------------------------------------------------

void __fastcall TShowBorder::ZoomOutButtonClick(TObject *Sender)
{
  ScaleShow -= 1;
  char str[6];
  wsprintf(str, "%1d:1", round(ScaleShow));
  ScaleLabel->Caption = str;
  ClearPicture();

}
//---------------------------------------------------------------------------
void __fastcall TShowBorder::ClearPicture(void)
{
  // RECT r;
  TRect tr;
  tr.Left = 1;
  tr.Top = 1;
  tr.Right = Image->Width;
  tr.Bottom = Image->Height;
  Image->Canvas->Brush->Style = bsSolid;
  Image->Canvas->FillRect(tr);
  Image->Canvas->Brush->Style = bsClear;
  Image->Invalidate();

}
void __fastcall TShowBorder::FormClose(TObject *Sender, TCloseAction &Action)
{
	if (MathModel == NULL)	{
		Action = caFree;
	}
}


//---------------------------------------------------------------------------


void __fastcall TShowBorder::FormKeyDown(TObject *Sender, WORD &Key,
	  TShiftState Shift)
{
 int Delta = atoi(dataParameter.sAutoSaveIter);
 switch(Key)  {
	case VK_LEFT: CurrPersent--;
				  if (CurrPersent<1) CurrPersent = HANDREDPERSENT;
				  Image->Invalidate();
	break;
	case VK_RIGHT:CurrPersent++;
				  if (CurrPersent>HANDREDPERSENT) CurrPersent=1;
				  Image->Invalidate();
	break;
	case VK_PRIOR:CurrPersent-=Delta;
				  if (CurrPersent<1) CurrPersent = HANDREDPERSENT;
				  Image->Invalidate();
	break;
	case VK_NEXT: CurrPersent+=Delta;
				  if (CurrPersent>HANDREDPERSENT) CurrPersent=1;
				  Image->Invalidate();
	break;
	case VK_HOME: CurrPersent=1;
				  Image->Invalidate();
	break;
	case VK_END:  CurrPersent=HANDREDPERSENT;
				  Image->Invalidate();
	break;
	case VK_SPACE: EPlus[CurrPersent] = 1 - EPlus[CurrPersent];
	break;
	case VK_TAB:   bBlackWhite = !bBlackWhite;
				   Image->Invalidate();
	break;
	case VK_F9: /*HDC DC=GetDC(HWindow);
				for( int c=1; c<=QEquLine; c++)
					MathModel->ShowEquLines(DC, whatShow,
											 MaxValue, deltaF, ScaleShow, c);
				ReleaseDC(HWindow, DC);
				InvalidateRect(HWindow, NULL, TRUE);
				*/
	break;
 }
}
//---------------------------------------------------------------------------

void __fastcall TShowBorder::ImageClick(TObject *Sender)
{
	Image->Invalidate();
}
//---------------------------------------------------------------------------


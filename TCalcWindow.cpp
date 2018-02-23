//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "TCalcWindow.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TCalcWindow *CalcWindow = NULL;
TCalcWindow *CalcP1 = NULL;
TCalcWindow *CalcP2 = NULL;
TCalcWindow *CalcEp = NULL;
TCalcWindow *CalcEk = NULL;

const int OX = 130;
const int OY = 20;
// const int HANDREDPERSENT = 100;
// int EPlus[100];
// BOOL bBlackWhite = TRUE;

//---------------------------------------------------------------------------
__fastcall TCalcWindow::TCalcWindow(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TCalcWindow::SetFields(String ATitle, double _MaxTime)
{
  this->Caption = ATitle;

  iH = 300;
  iW = (int)_MaxTime;
  iX = OX;
  iY = 0;
  numLineX = 20;
  numLineY = 20;
  MaxPt = 0.2;
  MaxTime = _MaxTime*1e-6;
  CoeffH = (double)iH/MaxPt;
  CoeffW = (double)iW/MaxTime;

  iCoeffH = (double)iH/50; // (double)MathModel->N;

  SetZero();
}

void __fastcall TCalcWindow::SetZero()
{
  cntME = 0;
  for (int i=0; i<5000; i++)  {
     arrEps[i] = 0.0;
     arrNum[i] = 0;
  }
  CalcDOIT = FALSE;
}
//---------------------------------------------------------------------------
void __fastcall TCalcWindow::FormPaint(TObject *Sender)
{
  HDC PDC = Image->Canvas->Handle;

  MaxPt = 0.0;
  int MaxI = 0, cntr=0;
  for (int i=1; i<cntME; i++)  {
//     if (arrEps[i] < 0)    arrEps[i] = 0.0;
     if (arrEps[i] > MaxPt)  {
         MaxPt = arrEps[i];   MaxI = arrNum[i];
     }
  }
  if (MaxPt>0.0) CoeffH = (double)iH/MaxPt;

  DrawAxes(PDC);

  iY = (int)ceil(arrEps[0]*CoeffH);
  iX = OX;
  MoveToEx(PDC, iX, iH-iY, NULL);

  double deltaT=0.0;
  if (MathModel!=NULL)
	 deltaT = MathModel->GetTau();
  for (int i=1; i<cntME; i++)  {
	 iY = (int)ceil(arrEps[i]*CoeffH);
	 iX = (int)ceil(i*deltaT*CoeffW) + OX;
	 LineTo(PDC, iX, iH-iY);
  }

  HPEN hpen, hpenOld;
  hpen = CreatePen(PS_SOLID, 1, BGIColor[LIGHTRED]);
  hpenOld = SelectPen(PDC, hpen);
  if(MathModel!=NULL) {
	iCoeffH = (iH*1.0)/(MathModel->N*1.0);
    cntr = MathModel->N/2;
  }

  iX = OX;
  iY = (int)ceil(arrNum[0]*iCoeffH);
  MoveToEx(PDC, iX, iH-iY, NULL);
  for (int i=1; i<cntME; i++)  {
     iY = (int)ceil(arrNum[i]*iCoeffH);
     iX = (int)ceil(i*deltaT*CoeffW) + OX;
     LineTo(PDC, iX, iH-iY);
  }

  SelectPen(PDC, hpenOld);
  DeletePen(hpen);

  char str[20];
  sprintf(str, "Imax = %d(%d)", MaxI, MaxI-cntr);
  TextOut(PDC, 160, iH+30, str, lstrlen(str));
  sprintf(str, "Pmax = %.3f", MaxPt);
  TextOut(PDC, 260, iH+30, str, lstrlen(str));
}
//---------------------------------------------------------------------------


void __fastcall TCalcWindow :: DrawEps(double d)
{
  // int OffX = Scroller->XPos*Scroller->XUnit;
  // int OffY = Scroller->YPos*Scroller->YUnit;

  HDC hDC =  Image->Canvas->Handle;

//   HDC hDC = GetDC(HWindow);
  iY = d*CoeffH; // + OffY;
  SetPixel(hDC, iX, iH-iY, BGIColor[BLACK]);
  iX++;

//  ReleaseDC(HWindow, hDC);  
}


void __fastcall TCalcWindow :: DrawAxes(HDC PDC)
{
 HPEN hpen, hpenOld;
 hpen = CreatePen(PS_SOLID, 1, BGIColor[LIGHTGRAY]);
 hpenOld = SelectPen(PDC, hpen);

 iX = OX;
 iY = 0;

 MoveToEx(PDC, iX, iY, NULL);
 LineTo(PDC, iX, iH);

 MoveToEx(PDC, iX, iH, NULL);
 LineTo(PDC, iW+iX, iH);

// TextOut(PDC, iX+5, iY, Title, lstrlen(Title));
 TextOut(PDC, 25, iH+10, "0", 1);
 TextOut(PDC, iW/2, iH+25, "t, мкс", 6);

 char str[20];
 // горизонтальные линии сетки 
 double step = MaxPt/numLineY;
 double fY = step;
 for (int i=1; i<=numLineY; i++) {
    iY = floor(fY*CoeffH);
	MoveToEx(PDC, iX, iH-iY, NULL);
    LineTo(PDC, iW+OX, iH-iY);
    sprintf(str, "%.3f", fY);
    TextOut(PDC, 1, iH-iY, str, lstrlen(str));
    fY += step;
 }

 iY = 0;
 // вертикальные линии сетки
 step = MaxTime/numLineX;
 double fX = step;
 for (int i=1; i<=numLineX; i++) {
    iX = floor(fX*CoeffW)+OX;
	MoveToEx(PDC, iX, iH, NULL);
    LineTo(PDC, iX, iY);
    sprintf(str, "%d", (int)ceil(fX*1e6));
    TextOut(PDC, iX-5, iH+10, str, lstrlen(str));
    fX += step;
 }
 
 SelectPen(PDC, hpenOld);
 DeletePen(hpen);

 double istep = 0;
 iX = OX;
 if (MathModel!=NULL) {
    istep = (double)MathModel->N/(double)numLineY;
    iCoeffH = (double)iH/(double)MathModel->N;
    int inputX1=0, inputX2=0;
    MathModel->GetInputBorder(inputX1, inputX2, 1);
    SelectBrush(PDC, GetStockBrush(LTGRAY_BRUSH));
    inputX1 = iH-ceil(inputX1*iCoeffH);
    inputX2 = iH-ceil(inputX2*iCoeffH);
    Rectangle(PDC, iX, inputX1, iW+iX, inputX2);
    if (MathModel->GetInputBorder(inputX1, inputX2, 2))  {
       inputX1 = iH-ceil(inputX1*iCoeffH);
       inputX2 = iH-ceil(inputX2*iCoeffH);
       Rectangle(PDC, iX, inputX1, iW+iX, inputX2);
    }
 }

 hpen = CreatePen(PS_DASHDOT, 1, BGIColor[LIGHTRED]);
 hpenOld = SelectPen(PDC, hpen);

 double nY = istep;
 for (int i=1; i<=numLineY; i++) {
    iY = floor(nY*iCoeffH);
    sprintf(str, "%d", (int)nY);
    TextOut(PDC, 100, iH-iY, str, lstrlen(str));
    nY += istep;
 }

 iX = OX;
 MoveToEx(PDC, iX, iH/2, NULL);
 LineTo(PDC, iW+iX, iH/2);
 SelectPen(PDC, hpenOld);
 DeletePen(hpen);

// iY = floor(inputX1*iCoeffH);
}


void __fastcall TCalcWindow :: Read(ifstream &fr)
{
  fr.read((char *)&cntME, sizeof(cntME));
  int sz = sizeof(arrEps[0])*cntME;
  fr.read((char *)arrEps, sz);
  sz = sizeof(arrNum[0])*cntME;
  fr.read((char *)arrNum, sz);
}


void __fastcall TCalcWindow :: Write(ofstream &fw)
{
  fw.write((char *)&cntME, sizeof(cntME));
  int sz = sizeof(arrEps[0])*cntME;
  fw.write((char *)arrEps, sz);
  sz = sizeof(arrNum[0])*cntME;
  fw.write((char *)arrNum, sz);
}


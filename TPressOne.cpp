//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "TPressOne.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TPressOne *PressOne;

const int OX = 80;
const int OY = 20;

//---------------------------------------------------------------------------
__fastcall TPressOne::TPressOne(TComponent* Owner)
	: TForm(Owner)
{

  iH = 300;
  iW = 500;
  iX = OX;
  iY = 0;
  numLineX = 20;
  numLineY = 20;
  MaxPt = 0.2;

  CoeffH = (double)iH/MaxPt;

  iCoeffH = (double)iH/50; // (double)MathModel->N;
  LOGFONT lf;
  _fmemset(&lf, 0, sizeof(LOGFONT));
  lstrcpy ((LPSTR)&lf.lfFaceName[0], "Times New Roman Cyr");
  lf.lfHeight = 17;
  // lf.lfWidth = 0;
  lf.lfWeight = FW_EXTRABOLD;
  hFont = CreateFontIndirect( &lf);

  SetZero();

}

__fastcall TPressOne :: ~TPressOne()
{
  DeleteObject(hFont);
}

void __fastcall TPressOne :: SetZero()
{
  cntME = 0;
  for (int i=0; i<2000; i++)  {
	 arrEps[i] = 0.0;
//     arrNum[i] = 0;
  }
}


//---------------------------------------------------------------------------
void __fastcall TPressOne::FormPaint(TObject *Sender)
{
  HDC PDC = Image->Canvas->Handle;

  MaxPt = 0.0;
  int MaxI = 0, cntr=0;
  for (int i=1; i<cntME; i++)  {
//     if (arrEps[i] < 0)    arrEps[i] = 0.0;
     if (arrEps[i] > MaxPt)  {
         MaxPt = arrEps[i];   //MaxI = arrNum[i];
     }
  }
  if (MaxPt>0.0) CoeffH = (double)iH/MaxPt;

  SelectObject(PDC, hFont);
  DrawAxes(PDC);

  HPEN hpen, hpenOld;
  hpen = CreatePen(PS_SOLID, 2, BGIColor[BLACK]);
  hpenOld = SelectPen(PDC, hpen);

//  iY = (int)ceil(arrEps[0]*CoeffH);
  iY = OY;
  iX = OX;
  MoveToEx(PDC, OX, iH+OY, NULL);

//  double deltaT=0.0;
//  if (MathModel!=NULL) deltaT = MathModel->GetTau();
  for (int i=1; i<cntME; i++)  {
     iY = (int)ceil(arrEps[i]*CoeffH);
     iX = (int)ceil(i*CoeffW);
     LineTo(PDC, iX+OX, iH+OY-iY);
  }
  SelectPen(PDC, hpenOld);
  DeletePen(hpen);

  /*
  char str[20];
  sprintf(str, "Pmax = %.3f", MaxPt);
  TextOut(PDC, 260, iH+30, str, lstrlen(str));
  */
}


void __fastcall TPressOne :: DrawAxes(HDC PDC)
{
 HPEN hpen, hpenOld;
// hpen = CreatePen(PS_SOLID, 1, BGIColor[LIGHTGRAY]);
 hpen = CreatePen(PS_SOLID, 1, BGIColor[BLACK]);
 hpenOld = SelectPen(PDC, hpen);

 iX = OX;
 iY = OY;

 MoveToEx(PDC, iX, iY, NULL);
 LineTo(PDC, iX, iH+OY);

 MoveToEx(PDC, iX, iH+OY, NULL);
 LineTo(PDC, iW+iX, iH+OY);


 TextOut(PDC, iX-10, iH+OY+10, "0", 1);
// TextOut(PDC, iW+OX+20, iH+OY+10, "X, мм", 5);
 TextOut(PDC, iW+OX+20, iH+OY+10, "t, мс", 5);

 SetTextAlign(PDC, TA_RIGHT | TA_TOP);
 TextOut(PDC, iX-10, 1, "P(t), MПa", 9);
// TextOut(PDC, iX-10, 1, "P*", 2);

 char str[20];
 // горизонтальные линии сетки
 double step = MaxPt/numLineY;
 double fY = step;
 double P0 = atof(dataParameter.sBeginPressing);
 int off = 0;
 for (int i=1; i<=numLineY; i++) {
    iY = floor(fY*CoeffH);
    if (off) {
       sprintf(str, "%.3f", fY/P0);
       TextOut(PDC, iX-10, iH+OY-iY-5, str, lstrlen(str));
	MoveToEx(PDC, iX, iH+OY-iY, NULL);
    LineTo(PDC, iW+OX, iH+OY-iY);
    }
    off = 1 - off;
    fY += step;
 }

 SetTextAlign(PDC, TA_CENTER | TA_TOP);
 iY = OY;
 // вертикальные линии сетки
 double deltaT=0.0;
 if (MathModel!=NULL) deltaT = MathModel->GetTau()*1e6;
// double cnt=2000.0/deltaT;
 double Ttotal = atof(dataParameter.sTtotal);
 double cnt=Ttotal/deltaT;
 CoeffW = (double)iW/cnt; // cntME;
 step = cnt/*cntME*//(double)numLineX;
 double fX = step;
 off = 0;
 for (int i=1; i<=numLineX; i++) {
    iX = floor(fX*CoeffW)+OX;
    if (off) {
       if (Ttotal>1000)  sprintf(str, "%.2f", fX*deltaT/1000.0);
       else sprintf(str, "%.0f", fX*deltaT);
       TextOut(PDC, iX, iH+OY+10, str, lstrlen(str));
    MoveToEx(PDC, iX, iH+OY, NULL);
    LineTo(PDC, iX, iY);
    }
    off = 1 - off;
    fX += step;
 }
 
 SelectPen(PDC, hpenOld);
 DeletePen(hpen);

}


void __fastcall TPressOne :: Read(ifstream &fr)
{
  fr.read((char *)&cntME, sizeof(cntME));
  int sz = sizeof(arrEps[0])*cntME;
  fr.read((char *)arrEps, sz);
//  sz = sizeof(arrNum[0])*cntME;
//  fr.read((char *)arrNum, sz);
}


void __fastcall TPressOne :: Write(ofstream &fw)
{
  fw.write((char *)&cntME, sizeof(cntME));
  int sz = sizeof(arrEps[0])*cntME;
  fw.write((char *)arrEps, sz);
//  sz = sizeof(arrNum[0])*cntME;
//  fw.write((char *)arrNum, sz);
}



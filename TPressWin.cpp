//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "TPressWin.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TPressWin *PressWin;

const int OX = 130;
const int OY = 30;

static float faPress[1000];
static int LineType[5] = { PS_SOLID, PS_DASH, PS_DOT, PS_DASHDOT, PS_DASHDOTDOT };
static int currLT = 0;
static int SelectLine[5];
static double tau, tmax;
static int iBegX, iEndX, plus=0;


//---------------------------------------------------------------------------
__fastcall TPressWin::TPressWin(TComponent* Owner)
	: TForm(Owner)
{
  CurrGR = 0;
  N = 0;
  NumIter = 0;
  iH = 300;
  iW = 300;
  iX = OX;
  iY = 0;
  numLineX = 20;
  numLineY = 20;
  MaxPt = 0.2;
  CoeffH = (double)iH/MaxPt;
  CoeffW = 0; // (double)MathModel->N;

  LOGFONT lf;
  _fmemset(&lf, 0, sizeof(LOGFONT));
  lstrcpy ((LPSTR)&lf.lfFaceName[0], "Times New Roman Cyr");
  lf.lfHeight = 17;
  // lf.lfWidth = 0;
  lf.lfWeight = FW_EXTRABOLD;
  hFont = CreateFontIndirect( &lf);
}

__fastcall TPressWin :: ~TPressWin()
{
  DeleteObject(hFont);
  Halt();
}

void __fastcall TPressWin :: Init(int _NumIter, int _N)
 {
  N = _N;
  NumIter = _NumIter;
  CoeffW = (double)iH/(double)N;
//if (NumIter>NUM_IN_ARR_EPSILON) NumIter=NUM_IN_ARR_EPSILON;
  for (int i=0; i<NumIter; i++)  {
     arrPress[i] = new float [N+1];
	 for (int j=0; j<=N; j++)
         arrPress[i][j]=0.0;
  }
}

void __fastcall TPressWin :: Halt()
{
 if (NumIter!=0) {
    for (int i=0; i<NumIter; i++)
       delete arrPress[i];
    CurrGR = 0;
    N = 0;
    NumIter = 0;
 }
}

//---------------------------------------------------------------------------
void __fastcall TPressWin::FormPaint(TObject *Sender)
{
  HDC PDC = Image->Canvas->Handle;

  if (MathModel==NULL)  { 
	 tau = MathModel->Parameters.h/MathModel->Parameters.a0;
     iBegX = 0;
     iEndX = N;
  }
  else {
     tau=MathModel->GetTau();
	 iBegX = MathModel->Parameters.xCoord - MathModel->rModel.left;
     iEndX = MathModel->Parameters.yCoord - MathModel->rModel.left;
  }
  tmax = MathModel->Parameters.tmax;

  MaxPt = 0.0;
  for (int n=0; n<NumIter; n++)  {
     for (int i=0; i<=N; i++)  {
        if (arrPress[n][i] > MaxPt)
            MaxPt = arrPress[n][i];
     }
  }
  if (MaxPt>0.0) CoeffH = (double)iH/MaxPt;

  SelectObject( PDC, hFont);
  DrawAxes(PDC);

//  for (CurrGR=0; CurrGR<NumIter; CurrGR++)  {

  DrawGraphic(PDC, FALSE);
//  }
  int oldCurrGR=CurrGR;
  char str[20];

  HPEN hpen, hpenOld;
  hpen = CreatePen(LineType[0], 2, BGIColor[BLACK]);
  hpenOld = SelectPen(PDC, hpen);

  if (currLT) {
      // SetTextAlign(PDC, TA_LEFT | TA_BOTTOM);
      int stepTxt = iH/5;
      int iYtxt = OY+iH-stepTxt;
      for (int ic=0; ic<=currLT; ic++) {
         CurrGR = SelectLine[ic];
         DrawGraphic(PDC, FALSE);
         // sprintf(str, "t%d = %d мкс", ic+1, (int)ceil(CurrGR*tau*1e6));
         if (plus)
           sprintf(str, "t%d* = %.2f", (currLT+plus)-ic+1, CurrGR*tau/tmax);
         else
           sprintf(str, "t%d* = %.2f", ic+1, CurrGR*tau/tmax);
         TextOut(PDC, iW+OX+15, iYtxt, str, lstrlen(str));


         SelectPen(PDC, hpenOld);
		 MoveToEx(PDC, iW+OX+10, iYtxt+10, NULL);
         int i=iEndX-(iEndX-iBegX)/2.3;
         iY = (int)ceil(arrPress[CurrGR][i]*CoeffH);
         iX = (int)ceil((i-iBegX)*CoeffW) + OX;
         LineTo(PDC, iX, iH+OY-iY);
         SelectPen(PDC, hpen);

         iYtxt -= stepTxt;
     }

  }

  SelectPen(PDC, hpenOld);
  DeletePen(hpen);
  
  CurrGR = oldCurrGR;

  /*
  char str[20];
  sprintf(str, "Imax = %d(%d)", MaxI, MaxI-cntr);
  TextOut(PDC, 160, iH+30, str, lstrlen(str));
  sprintf(str, "Pmax = %.3f", MaxPt);
  TextOut(PDC, 260, iH+30, str, lstrlen(str));
  */
}
//---------------------------------------------------------------------------


void __fastcall TPressWin :: DrawGraphic(HDC PDC, BOOL Gray)
{
 HPEN hpen, hpenOld;
 if (Gray) {
    hpen = CreatePen(PS_SOLID, 1, BGIColor[LIGHTGRAY]);
    hpenOld = SelectPen(PDC, hpen);
 }

 iY = (int)ceil(arrPress[CurrGR][0]*CoeffH);
 iX = OX;
 MoveToEx(PDC, iX, iH+OY-iY, NULL);

 for (int i=iBegX; i<=iEndX; i++)  {
    iY = (int)ceil(arrPress[CurrGR][i]*CoeffH);
    iX = (int)ceil((i-iBegX)*CoeffW) + OX;
    LineTo(PDC, iX, iH+OY-iY);
 }

 if (Gray) {
    SelectPen(PDC, hpenOld);
    DeletePen(hpen);
 }

 char str[20];
 sprintf(str, "t*=%0.2f    ", CurrGR*tau/tmax);
 TextOut(PDC, 5, 30, str, lstrlen(str));
}


void __fastcall TPressWin :: DrawOneMomentPress(HDC PDC)
{
 MaxPt = 0.0;
 for (int n=0; n<NumIter; n++)  {
    for (int i=0; i<=N; i++)  {
       if (arrPress[n][i] > MaxPt)
           MaxPt = arrPress[n][i];
    }
 }
 if (MaxPt>0.0) CoeffH = (double)iH/MaxPt;

 DrawAxes(PDC);

 for (int i=1; i<=N; i++)  {
    double MaxI = 0.0;
    for (int n=0; n<NumIter; n++)  
       if (MaxI<arrPress[n][i]) MaxI = arrPress[n][i];
    iY = (int)ceil(MaxI*CoeffH);
    iX = (int)ceil(i*CoeffW) + OX;
	MoveToEx(PDC, iX, iH+OY, NULL);
    LineTo(PDC, iX, iH+OY-iY);
 }

 iX = OX;
 iY = 0;
}


void __fastcall TPressWin :: DrawIntegralPress(HDC PDC)
{
 double IntegralI;

 for (int i=1; i<=N; i++)  {
    IntegralI = 0.0;
    for (int n=0; n<NumIter; n++)  
       IntegralI += arrPress[n][i];
    if (MaxPt<IntegralI) MaxPt = IntegralI;
 }

 if (MaxPt>0.0) CoeffH = (double)iH/MaxPt;
 DrawAxes(PDC);

 for (int i=1; i<=N; i++)  {
    IntegralI = 0.0;
    for (int n=0; n<NumIter; n++)  
       IntegralI += arrPress[n][i];
    iY = (int)ceil(IntegralI*CoeffH);
    iX = (int)ceil(i*CoeffW) + OX;
	MoveToEx(PDC, iX, iH+OY, NULL);
    LineTo(PDC, iX, iH+OY-iY);
 }
 iX = OX;
 iY = 0;
}


void __fastcall TPressWin :: DrawAxes(HDC PDC)
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
 TextOut(PDC, iW+OX+20, iH+OY+10, "L*", 2);

 SetTextAlign(PDC, TA_RIGHT | TA_TOP);
// TextOut(PDC, iX-10, 1, "P(t), ПА", 8);
 TextOut(PDC, iX-10, 1, "P*", 2);
 char str[20];
 // горизонтальные линии сетки 
 double step = MaxPt/numLineY;
 double fY = step;
 double P0 = MathModel->Parameters.P0;
 int off = 0;
 for (int i=1; i<=numLineY; i++) {
    iY = floor(fY*CoeffH);
    if (off) {
       sprintf(str, "%.3f", fY/P0);
       //sprintf(str, "%.3f", fY);
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
 int Nn = iEndX - iBegX;
 step = (double)Nn/(double)numLineY;
 CoeffW = (double)iH/(double)Nn;
 double fX = step;
 double Interval = MathModel->Parameters.h*1000;
 double Diameter = MathModel->Parameters.w;
 off = 0;
 int off2 = 1;
 for (int i=1; i<=numLineX; i++) {
    iX = floor(fX*CoeffW)+OX;
    if (off) {
       //if( off2) sprintf(str, "%.1f", (fX+iBegX)*Interval);
       //else
//       sprintf(str, "%.0f", (fX+iBegX)*Interval);
       //off2 = 1 - off2;
       sprintf(str, "%.1f", (fX+iBegX)*Interval/Diameter);  //?????????????????
       TextOut(PDC, iX, iH+OY+10, str, lstrlen(str));
	MoveToEx(PDC, iX, iH+OY, NULL);
    LineTo(PDC, iX, iY);
    }
    off = 1 - off;
    fX += step;
 }

 SelectPen(PDC, hpenOld);
 DeletePen(hpen);

 SetTextAlign(PDC, TA_LEFT | TA_TOP);
 
 if (MathModel!=NULL)  {

    int inputX1=0, inputX2=0;
    MathModel->GetInputBorder(inputX1, inputX2, 1);
//    SelectBrush(PDC, GetStockBrush(LTGRAY_BRUSH));
    SelectBrush(PDC, GetStockBrush(WHITE_BRUSH));
    inputX1 = ceil((inputX1-iBegX)*CoeffW)+OX;
    inputX2 = ceil((inputX2-iBegX)*CoeffW)+OX;
/*
    int inputX1=0, inputX2=0;
    MathModel->GetInputBorder(inputX1, inputX2, 1);
    SelectBrush(PDC, GetStockBrush(WHITE_BRUSH));
    inputX2 = inputX1 + 10;
    inputX1 -= 10;
    inputX1 = ceil(inputX1*CoeffW)+OX;
    inputX2 = ceil(inputX2*CoeffW)+OX;
*/

    Rectangle(PDC, inputX1, iY, inputX2, iH+OY);
    TextOut(PDC, inputX1+5, iY-25, "1", 1);
	MoveToEx(PDC, inputX1+5, iY-7, NULL);
    LineTo(PDC, inputX1+1, iY-1);

    if (MathModel->GetInputBorder(inputX1, inputX2, 2)) {
       inputX1 = ceil((inputX1-iBegX)*CoeffW)+OX;
       inputX2 = ceil((inputX2-iBegX)*CoeffW)+OX;
       Rectangle(PDC, inputX1, iY, inputX2, iH+OY);
       TextOut(PDC, inputX1+5, iY-25, "2", 1);
    }
 }
 
 hpen = CreatePen(PS_DASHDOT, 1, BGIColor[LIGHTRED]);
 hpenOld = SelectPen(PDC, hpen);
 iY = OY;
 MoveToEx(PDC, iW/2+OX, iY, NULL);
 LineTo(PDC, iW/2+OX, iH+OY);
 SelectPen(PDC, hpenOld);
 DeletePen(hpen);
}


void __fastcall TPressWin::btnPrevClick(TObject *Sender)
{
 if (btnPrev->Down) {
	 if (!Timer1->Enabled) {
		Timer1->Enabled = true;
	 }
 }
 
 /// HDC PDC = GetDC(HWindow);
 HDC PDC =  Image->Canvas->Handle;
 DrawGraphic(PDC, TRUE);
 CurrGR--;
 if (CurrGR<1) CurrGR=NumIter-1;
// InvalidateRect(HWindow, NULL, TRUE);
 DrawGraphic(PDC, FALSE);
 // ReleaseDC(HWindow, PDC);
 Image->Invalidate();
}
//---------------------------------------------------------------------------
void __fastcall TPressWin::btnNextClick(TObject *Sender)
{
 if (btnNext->Down) {
	 if (!Timer1->Enabled) {
		Timer1->Enabled = true; 
	 }
 }
 // HDC PDC = GetDC(HWindow);
 HDC PDC =  Image->Canvas->Handle;
 DrawGraphic(PDC, TRUE);
 CurrGR++;
 if (CurrGR>=NumIter) CurrGR=1;
// InvalidateRect(HWindow, NULL, TRUE);
 DrawGraphic(PDC, FALSE);
 // ReleaseDC(HWindow, PDC);
 Image->Invalidate();
}
//---------------------------------------------------------------------------
void __fastcall TPressWin::FormKeyDown(TObject *Sender, WORD &Key,
	  TShiftState Shift)
{
 int Delta = MathModel->Parameters.AutoSaveIter;
 switch(Key)  {
	case VK_LEFT:  btnPrevClick(Sender);
	break;
	case VK_RIGHT: btnNextClick(Sender);
	break;
	case VK_PRIOR: CurrGR-=Delta;
                   if (CurrGR<1) CurrGR=NumIter-1;
				   btnPrevClick(Sender);
    break;
    case VK_NEXT:  CurrGR+=Delta;
                   if (CurrGR>=NumIter) CurrGR=1;
				   btnNextClick(Sender);
    break;
    case VK_HOME:  CurrGR=1;
                   btnNextClick(Sender);
    break;
    case VK_END:   CurrGR=NumIter-1;
				   btnPrevClick(Sender);
    break;
    case VK_SPACE: SelectLine[currLT] = CurrGR;
                   if (currLT<4) currLT++;
    break;
    case VK_BACK: for (int ic=0; ic<=currLT; ic++)
                     SelectLine[ic] = 0;
                  currLT = 0;
    break;
    case VK_ADD:  plus+=4; 
    break;
    case VK_SUBTRACT:  plus=0;
    break;
 }
}
//---------------------------------------------------------------------------


void __fastcall TPressWin :: Read(ifstream &fr)
{
  fr.read((char *)&N, sizeof(N));
  fr.read((char *)&NumIter, sizeof(NumIter));
  Init(NumIter, N);
  int szF = sizeof(float)*(N+1);
  for (int i=0; i<NumIter; i++)  {
	 fr.read((char *)faPress, szF);
	 for (int j=0; j<=N; j++)
		 arrPress[i][j] = faPress[j];
  }
  CurrGR=0;
}


void __fastcall TPressWin :: Write(ofstream &fw)
{
  fw.write((char *)&N, sizeof(N));
  fw.write((char *)&NumIter, sizeof(NumIter));
  int szF = sizeof(float)*(N+1);
  for (int i=0; i<NumIter; i++)  {
     for (int j=0; j<=N; j++)
          faPress[j] = arrPress[i][j];
     fw.write((char *)faPress, szF);
  }
}
void __fastcall TPressWin::btnStopClick(TObject *Sender)
{
	Timer1->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TPressWin::Timer1Timer(TObject *Sender)
{
	if (btnPrev->Down) {
		btnPrevClick(Sender);
	} else if (btnNext->Down) {
		btnNextClick(Sender);
    }
}
//---------------------------------------------------------------------------

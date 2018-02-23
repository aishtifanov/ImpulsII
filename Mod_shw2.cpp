// ПРОЕКТ:     Математическая модель ИМПУЛЬС
// ВЕРСИЯ:     1.0
// ФАЙЛ:       Mod_Shw2.CPP
// ДАТА:       3/97
// АВТОР:      Штифанов А.И.
// СОДЕРЖАНИЕ: Функции отображения эквипотенциальных линий

#include "impulse.hpp"
#include <stdio.h>
#include "TShowBorder.h"
#include "TCalcWindow.h"
#include "TPressOne.h"

HBITMAP BMW_U3, BMW_D3;
const int StartPosX = 10, StartPosY = 100;

void CModel2D :: BeginShowWave()
 {
  HDC DC, MemDC_U3, MemDC_D3;

  // формирование рисунка в памяти
  DC = GetDC(0);
  BMW_U3 = CreateCompatibleBitmap(DC, N+1, M+1);
  MemDC_U3 = CreateCompatibleDC(DC);
  BMW_D3 = CreateCompatibleBitmap(DC, N+1, M+1);
  MemDC_D3 = CreateCompatibleDC(DC);
  ReleaseDC(0, DC);

  SelectObject(MemDC_U3, BMW_U3);
  SelectObject(MemDC_D3, BMW_D3);
  PatBlt(MemDC_U3, 0, 0, N+1, M+1, WHITENESS);
  PatBlt(MemDC_D3, 0, 0, N+1, M+1, WHITENESS);

  for (DWORD j=0; j<=M; j++)  {
     DWORD jN1 = j*N1;
     for (DWORD i=0; i<=N; i++) {
        switch(Knots[jN1+i].eArrange)  {
	   case IT_LEFT_BORDER:
	   case IT_RIGHT_BORDER:
	   case IT_TOP_BORDER:
	   case IT_BOTTOM_BORDER: 
                   SetPixel(MemDC_U3, i, M-j, BGIColor[BLACK]);
                   SetPixel(MemDC_D3, i, M-j, BGIColor[BLACK]);
           break;
        }

     }
  }

  //  HDC CalcWinDC = ShowCalculate->Image->Canvas->Handle;
  HDC CalcWinDC = GetDC(ShowCalculate->Handle);
  StretchBlt(CalcWinDC, StartPosX, StartPosY, (N+1)*ShowCalculate->ScaleShow,
			(M+1)*ShowCalculate->ScaleShow,
			MemDC_U3, 0, 0, N+1, M+1, SRCCOPY);
  StretchBlt(CalcWinDC, (N+1)*ShowCalculate->ScaleShow+50+StartPosX, StartPosY,
			(N+1)*ShowCalculate->ScaleShow,
			(M+1)*ShowCalculate->ScaleShow,
			MemDC_D3, 0, 0, N+1, M+1, SRCCOPY);

  ReleaseDC(ShowCalculate->Handle, CalcWinDC);

  DeleteDC(MemDC_U3);
  DeleteDC(MemDC_D3);
 }



void CModel2D :: ShowWave(DWORD CurrIter)
 {

  DWORD j, jN1, i, index, imax_U3, jmax_U3, imax_D3, jmax_D3;
  double MaxValue_U3 = 0.0, MaxValue_D3 = 0.0, Value = 0.0;
  int WidthShow = (N+1)*ShowCalculate->ScaleShow;
  int HeigthShow = (M+1)*ShowCalculate->ScaleShow;
  char str[40];

  for (j=0; j<=M; j++)  {
	 jN1 = j*N1;
	 for (i=0; i<=N; i++) {
		DWORD index = jN1+i;
		if (Knots[index].ePhisic == IT_POINT_CENTER) {
		 if (MaxValue_U3 < Knots[index].U3) {
		 MaxValue_U3 = Knots[index].U3;
			 imax_U3 = i; jmax_U3 = j;
		 }
         if (MaxValue_D3 < Knots[index].D3) {
	    MaxValue_D3 = Knots[index].D3;
            imax_D3 = i; jmax_D3 = j;
         }
        }
     }
  }

  double deltaF =  MaxValue_U3 / Parameters.QEquLine;
  double deltaF_D3 =  MaxValue_D3 / Parameters.QEquLine;

  COLORREF color = BGIColor[WHITE];
  HDC DC, MemDC_U3,MemDC_D3;

  // формирование рисунка в памяти
  DC = GetDC(0);
  MemDC_U3 = CreateCompatibleDC(DC);
  MemDC_D3 = CreateCompatibleDC(DC);
  ReleaseDC(0, DC);

  SelectObject(MemDC_U3, BMW_U3);
  SelectObject(MemDC_D3, BMW_D3);

  for (j=0; j<=M; j++)  {
     jN1 = j*N1;
     for (i=0; i<=N; i++)  {
        if (Knots[jN1+i].ePhisic == IT_POINT_CENTER) {
           Value = Knots[jN1+i].U3;
           if (Value > 0.0)  {
              int ni = (int)ceil(Value  / deltaF);
              if (ni % 2) color = BGIColor[BLACK];
              else        color = BGIColor[WHITE];
           }
           else if (Value == 0.0) color = BGIColor[YELLOW];
           else color = BGIColor[LIGHTRED];
           SetPixel(MemDC_U3, i, M-j, color);
           
           Value = Knots[jN1+i].D3;
           if (Value > 0.0)  {
              int ni = (int)ceil(Value  / deltaF_D3);
              if (ni % 2) color = BGIColor[BLACK];
              else        color = BGIColor[WHITE];
           }
           else if (Value == 0.0) color = BGIColor[YELLOW];
	   else color = BGIColor[LIGHTRED];
           SetPixel(MemDC_D3, i, M-j, color);
           

        }
        else if (Knots[jN1+i].ePhisic == IT_HARD_BORDER) {
	        SetPixel(MemDC_U3, i, M-j, BGIColor[CYAN]);
      	        SetPixel(MemDC_D3, i, M-j, BGIColor[CYAN]);
             }
             else {
	        SetPixel(MemDC_U3, i, M-j, BGIColor[YELLOW]);
                SetPixel(MemDC_D3, i, M-j, BGIColor[YELLOW]);
			 }
	 }
  }

  // вывод графика давления P1 на основание

  jN1 = Parameters.NumLevel*N1;
  int minheight = min(N, M);
  double Max_P1 = CalcP1->arrEps[CurrIter];
  if (Max_P1 > 0.0) {
	 double Coeff = (double)minheight/Max_P1;
	 for (i=0; i<N; i++)  {
		if (Knots[jN1+i].ePhisic == IT_POINT_CENTER ) {
		   int length = (int)ceil(Knots[jN1+i].P1*Coeff);
		   SetPixel(MemDC_U3, i, M-length, BGIColor[LIGHTRED]);
		}
	 }
  }

  // вывод графика давления P2 на основание
  float Max_P2 = CalcP2->arrEps[CurrIter];;
  j=1;
  jN1 = j*N1;
  int l=21, r=44, t=54;
  if (Max_P2 > 0.0) {
	 double Coeff = t/Max_P2;
	 for (i=l; i<=r; i++)  {
		int length = (int)ceil(Knots[jN1+i].P2*Coeff);
		SetPixel(MemDC_D3, i, M-length, BGIColor[LIGHTRED]);
	 }
  }

  SetPixel(MemDC_U3, imax_U3, M-jmax_U3, BGIColor[LIGHTGREEN]);
  SetPixel(MemDC_D3, imax_D3, M-jmax_D3, BGIColor[LIGHTGREEN]);

  // HDC CalcWinDC = ShowCalculate->Image->Canvas->Handle;
  HDC CalcWinDC = GetDC(ShowCalculate->Handle);
  StretchBlt(CalcWinDC, StartPosX, StartPosY, WidthShow, HeigthShow, MemDC_U3, 0, 0, N+1, M+1, SRCCOPY);
  StretchBlt(CalcWinDC, WidthShow+50+StartPosX, StartPosY, WidthShow, HeigthShow, MemDC_D3, 0, 0, N+1, M+1, SRCCOPY);

  sprintf(str, "deltaU3 = %.5f   ", deltaF);
  TextOut(CalcWinDC, StartPosX, HeigthShow+StartPosY, str, lstrlen(str));
  sprintf(str, "deltaV = %.5f   ", deltaF_D3);
  TextOut(CalcWinDC, StartPosX+WidthShow+50, HeigthShow+StartPosY, str, lstrlen(str));

  sprintf(str, "P1max = %.3f   ", Max_P1);
  TextOut(CalcWinDC, StartPosX, StartPosY+HeigthShow+30, str, lstrlen(str));
  sprintf(str, "P2max = %.3f   ", Max_P2);
  TextOut(CalcWinDC, StartPosX+WidthShow+50, StartPosY+HeigthShow+30, str, lstrlen(str));

  sprintf(str, "Epmax = %.3f   ", CalcEp->arrEps[CurrIter]);
  TextOut(CalcWinDC, StartPosX, StartPosY+HeigthShow+50, str, lstrlen(str));
  sprintf(str, "Ekmax = %.3f   ", CalcEk->arrEps[CurrIter]);
  TextOut(CalcWinDC, StartPosX+WidthShow+50, StartPosY+HeigthShow+50, str, lstrlen(str));

  ReleaseDC(ShowCalculate->Handle, CalcWinDC);

  DeleteDC(MemDC_U3);
  DeleteDC(MemDC_D3);

  /*
	if (GetAsyncKeyState(VK_RETURN)) {
	  char FileName[13];
	  wsprintf(FileName, "U%d.txt", CurrIter);
	  Write(FileName, SHOW_EQULINES_U3);
	  wsprintf(FileName, "V%d.txt", CurrIter);
	  Write(FileName, SHOW_EQULINES_V);

	  wsprintf(FileName, "U%d.bmp", CurrIter);

	  Image image = Image(BMW_U3, N+1, M+1);
	  BMPImage ibmp;
	  ibmp.image_data(&image);
	  ibmp.write(FileName);

	  wsprintf(FileName, "V%d.bmp", CurrIter);

	  // занесение рисунка в буфер обмена
	  OpenClipboard(winIMPULSE->HWindow);
	  EmptyClipboard();
	  SetClipboardData(CF_BITMAP, BMW_V);
	  CloseClipboard();
  }
  */
 }


void CModel2D :: EndShowWave()
 {
  DeleteObject(BMW_U3);
  DeleteObject(BMW_D3);
 }


void CModel2D :: Show3DSurface(HDC hDC)
 {
 //
 }
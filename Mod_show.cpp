// ПРОЕКТ:     Математическая модель ИМПУЛЬС
// ВЕРСИЯ:     1.0
// ФАЙЛ:       Mod_Show.CPP
// ДАТА:       8/96
// АВТОР:      Штифанов А.И.
// СОДЕРЖАНИЕ: Функции отображения эквипотенциальных линий


#include "impulse.hpp"
//#include "imagebmp.hpp"
#include <stdio.h>

// #define NHALF N

void DrawKnot(HDC DC, int x, int y, double R, COLORREF Color, double Scale);
void Legenda(HDC DC, int x, int y, char *str, COLORREF Color);

struct SNaprMax {
   float Vmax;
   DWORD im;
   DWORD jm;
};

struct SAllNapr {
   float midNapr;
   int nel;
};

static SNaprMax Napr[105];
static SAllNapr allNapr[105];
int Ntrub = 1;
extern int EPlus[];
extern BOOL bBlackWhite;
static char str[100];
int SqElLine[100], SumEPlus = 0;

int DJ;
int FlagMsg = FALSE;


void CModel2D :: ShowEquLines(HDC hDC, EWhatShow ews, double MaxValue,
							  double deltaF, double ScaleShow, int CurrPersent)
{
  HCURSOR prev = SetCursor(LoadCursor(0, IDC_WAIT));
  GetAsyncKeyState(VK_ESCAPE);
  GetAsyncKeyState(VK_RBUTTON);
//!!!!!!!!!!!!!!!!!  SelectObject(hDC, State.hFont);

  int dX = rModel.right - rModel.left;
  int dY = rModel.bottom - rModel.top;
  RECT rModelN = { rModel.left, rModel.top, rModel.right, rModel.bottom };
  int x, y;
  double r = Interval/2.0;
  COLORREF color;
  double  MinValue = 0.0, Value;
  DWORD j, jN1, i;
  // int deltaColor = 500  / (int)(MaxValue / deltaF);
  // int green1 = 0, red1 = 0;
  // bBlackWhite = FALSE;

  // ===========================================================================
  if (ews == SHOW_CHANNEL) {
	 ShowChannel(hDC, ews, MaxValue, deltaF, ScaleShow, CurrPersent);
	 SetCursor(prev);
	 return;
  }
  // ===========================================================================

  int ni, maxni = 0;
  for (j=0; j<=M; j++)  {
	 jN1 = j*N1;
	 if (GetAsyncKeyState(VK_ESCAPE) ||
		 GetAsyncKeyState(VK_RBUTTON)) return;
	 for (i=0; i<=N; i++)  {
		color = BGIColor[WHITE];
		Value = 0.0;

		switch(ews)  {
		   case SHOW_EQULINES_PSI: Value = Knots[jN1+i].Psi;
		   break;
		   case SHOW_EQULINES_U:   // Value = Knots[jN1+i].Ep;
								   Value = Knots[jN1+i].U3;
		   break;
		   case SHOW_EQULINES_V:   Value = Knots[jN1+i].V;
		   break;
		   case SHOW_EQULINES_J:   Value = Knots[jN1+i].J;
		   break;
		}

		if(Value != 0.0 && Value  < MaxValue )  {
		   ni = (int)ceil(Value  / deltaF);

		   if (bBlackWhite) {
			  if (ni % 2) color = BGIColor[BLACK];
			  else        color = BGIColor[WHITE];
		   }
		   else {
			   color = BGIColor2[ni];
			   if (ni > maxni)  maxni = ni;

			  /*
			  if (ni % 2) color = BGIColor[WHITE];
			  else        color = BGIColor[BLACK];
			  */
		   }

		}

		x = rModelN.left + i*Interval;
		y = rModelN.bottom - j*Interval;
		DrawKnot(hDC, x, y, r, color, ScaleShow);
	 }
  }

  /*
  RECT rc = { (rModelN.left - Interval)*ScaleShow,
			  (rModelN.top - Interval)*ScaleShow,
		 (rModelN.right + Interval)*ScaleShow,
		 (rModelN.bottom + Interval)*ScaleShow
  };

  int step = M / 10;
  for (j=0; j<=M; j+=step) {
	 int Flag = TRUE;
	 jN1 = j*N1;
	 for (i=N; i>0 && Flag; i--) {
		DWORD index5 = jN1+i;
		if (Knots[index5].ePhisic == IT_POINT_CENTER) {
		   Flag = FALSE;
		   x = rModelN.left + i*Interval;
		   y = rModelN.bottom - j*Interval;
		   MoveToEx(hDC, x*ScaleShow, y*ScaleShow, NULL);
		   //LineTo(hDC, x*ScaleShow + 20, y*ScaleShow);
		   double Value;
		   switch(ews)  {
			  case SHOW_EQULINES_PSI: Value = Knots[index5].Psi;
			  break;
			  case SHOW_EQULINES_U:  // Value = Knots[index5].Ep;
									  Value = Knots[jN1+i].U3;
			  break;
			  case SHOW_EQULINES_V:   Value = Knots[index5].V;
			  break;
			  case SHOW_EQULINES_J:   Value = Knots[jN1+i].J;
			  break;
		   }
		   int ni = (int)ceil(Value  / deltaF);
		   double Low = deltaF * ni;
		   double High = deltaF * (ni+1);
		   sprintf (str, "[%6.3f; %6.3f]", Low, High);
		   TextOut(hDC, x*ScaleShow + 20, y*ScaleShow - 10, str, lstrlen(str));
		} // if
	 } // for i
  }
  */

  x = rModelN.right + 20;
  y = rModelN.top;

  HPEN    hPenLocal, hOrigPen;
  HBRUSH  hBrushLocal, hOrigBrush;
  for (ni=1; ni<=Parameters.QEquLine; ni++)	{
	 color = BGIColor2[ni];
	 hPenLocal   = CreatePen(PS_SOLID, 6, color);
	 // hBrushLocal = CreateSolidBrush(Color);
	 hOrigPen = (HPEN)SelectObject(hDC, hPenLocal);
//	 hOrigBrush = (HBRUSH)SelectObject(DC, hBrushLocal);

	 MoveToEx(hDC, x*ScaleShow, y*ScaleShow + 10, NULL);
	 LineTo(hDC, x*ScaleShow + 20, y*ScaleShow + 10);

	 SelectObject(hDC, hOrigPen);
 //	 SelectObject(hDC, hOrigBrush);

	 DeleteObject(hPenLocal);
//	 DeleteObject(hBrushLocal);


	 double Low = deltaF * ni;
	 double High = deltaF * (ni+1);
	 if (ni == Parameters.QEquLine) {
		 High = Low;
	 }

	 sprintf (str, "[%6.3f; %6.3f]", Low, High);
	 TextOut(hDC, x*ScaleShow + 50, y*ScaleShow, str, lstrlen(str));
	 y += 20;
  }
 
  x = rModelN.left*ScaleShow;
  y = (rModelN.bottom+10)*ScaleShow;


  // ==========================================================================
  if (ews == SHOW_EQULINES_V) {
	 ShowEquLines_V(hDC, ews, MaxValue, deltaF, ScaleShow, CurrPersent);
  }
  // ==========================================================================

  color = BGIColor[BLACK];

  x = rModelN.left*ScaleShow;

  sprintf (str, "Fmin = %.4lf   Fmax = %.4lf", MinValue, MaxValue);
  TextOut(hDC, x, y, str, lstrlen(str));

  y +=20;
  sprintf (str, "dF = %.4lf", deltaF); //  (диапазон приращения функции)
  TextOut(hDC, x, y, str, lstrlen(str));
  /*
  y +=20;
  sprintf (str, "ni = %d (maxni)", maxni);
  TextOut(hDC, x, y, str, lstrlen(str));
  */
  listBorder->DrawAllList(hDC, ScaleShow);

  SetCursor(prev);
}


void CModel2D :: ShowPhisicBorder(HDC hDC, double ScaleShow)
 {
  HCURSOR prev = SetCursor(LoadCursor(0, IDC_WAIT));

  SetParameters();
  int l = rModel.left/Interval;
  int b = rModel.bottom/Interval;
  int x, y;
  double r = Interval/2;

  //  listBorder->DrawAllList(hDC);
  for (DWORD j=0; j<=M; j++)  {
     DWORD jN1 = j*N1;
     if (GetAsyncKeyState(VK_ESCAPE)) return;
     for (DWORD i=0; i<=N; i++) {
     	COLORREF color = BGIColor[WHITE];
		switch(Knots[jN1+i].ePhisic)  {
	   case IT_HARD_BORDER: color = BGIColor[LIGHTBLUE];
           break;
	   case IT_FREE_BORDER: color = BGIColor[LIGHTCYAN];
           break;
	   case IT_INPUT_BORDER : color = BGIColor[LIGHTRED];
           break;
	   case IT_OUTPUT_BORDER : color = BGIColor[LIGHTGREEN];
           break;
	   case IT_POINT_CENTER: color = BGIColor[BLACK];
           break;
		}
//        x = rModel.left + i*Interval;
//        y = rModel.bottom - j*Interval;
		x = l + i;
        y = b - j;
        DrawKnot(hDC, x, y, r, color, ScaleShow);
     }
  }
 /*
  x = rModel.left;
  y = (rModel.bottom + 20)*ScaleShow;
  for (int i=1; i<=5; i++) {
	 DrawKnot(hDC, x, y, r, BGIColor[BLACK], ScaleShow);
     x += Interval;
  }
  TextOut(hDC, x*ScaleShow+15, y-5, str, lstrlen(str));

  x = rModel.left;
//  y = rModel.bottom + 40;
  y+=20;
  for (i=1; i<=5; i++) {
     DrawKnot(hDC, x, y, r, BGIColor[LIGHTBLUE], ScaleShow);
     x += Interval;
  }
  lstrcpy(str, "Узлы лежат на жестких границах");
  TextOut(hDC, x*ScaleShow+15, y-5, str, lstrlen(str));

  x = rModel.left;
//  y = rModel.bottom + 60;
  y+=20;
  for (i=1; i<=5; i++) {
     DrawKnot(hDC, x, y, r, BGIColor[LIGHTRED], ScaleShow);
     x += Interval;
  }
  lstrcpy(str, "Узлы лежат на входе");
  TextOut(hDC, x*ScaleShow+15, y-5, str, lstrlen(str));

  x = rModel.left;
//  y = rModel.bottom + 80;
  y+=20;
  for (i=1; i<=5; i++) {
	 DrawKnot(hDC, x, y, r, BGIColor[LIGHTGREEN], ScaleShow);
     x += Interval;
  }
  lstrcpy(str,"Узлы лежат на выходе");
  TextOut(hDC, x*ScaleShow+15, y-5, str, lstrlen(str));
 */
  SetCursor(prev);
}


void CModel2D :: ShowArrangeBorder(HDC hDC, double ScaleShow)
{
  //HCURSOR prev = SetCursor(LoadCursor(0, IDC_WAIT));
  SetParameters();
  int x, y;
  int l = rModel.left/Interval;
  int b = rModel.bottom/Interval;
  double r = Interval/2;

 // listBorder->DrawAllList(hDC);
  for (DWORD j=0; j<=M; j++)  {
     DWORD jN1 = j*N1;
     if (GetAsyncKeyState(VK_ESCAPE)) return;
     for (DWORD i=0; i<=N; i++) {
     	COLORREF color = BGIColor[WHITE];
        switch(Knots[jN1+i].eArrange)  {
	   case IT_LEFT_BORDER: color = BGIColor[LIGHTGREEN];
           break;
	   case IT_RIGHT_BORDER: color = BGIColor[LIGHTRED];
           break;
	   case IT_TOP_BORDER: color = BGIColor[LIGHTBLUE];
           break;
	   case IT_BOTTOM_BORDER: color = BGIColor[BLACK];
           break;
        }
//        x = rModel.left + i*Interval;
//        y = rModel.bottom - j*Interval;
          x = l + i;
          y = b - j;
          DrawKnot(hDC, x, y, r, color, ScaleShow);
     }
  }

  x = l;
  y = (b + 20)*ScaleShow;
  Legenda(hDC, x, y, "Нижняя граница", BGIColor[BLACK]);
  y += 20;
  Legenda(hDC, x, y, "Верхняя граница", BGIColor[LIGHTBLUE]);
  y += 20;
  Legenda(hDC, x, y, "Правая граница", BGIColor[LIGHTRED]);
  y += 20;
  Legenda(hDC, x, y, "Левая граница", BGIColor[LIGHTGREEN]);

  //SetCursor(prev);
}


void DrawKnot(HDC DC, int x, int y, double R, COLORREF Color, double Scale)
 {
  int x_1 = (int)(x*Scale);
  int y_1 = (int)(y*Scale);
  int r_1 = (int)(R*Scale);

  if (r_1 == 0) SetPixel(DC, x, y, Color);
  else  {
	 // r_1++;
	 HPEN    hPenLocal, hOrigPen;
	 HBRUSH  hBrushLocal, hOrigBrush;

	 hPenLocal   = CreatePen(PS_SOLID, 1, Color);
	 hBrushLocal = CreateSolidBrush(Color);

	 hOrigPen = (HPEN)SelectObject(DC, hPenLocal);
	 hOrigBrush = (HBRUSH)SelectObject(DC, hBrushLocal);

	 Ellipse(DC, x_1-r_1, y_1-r_1, x_1+r_1, y_1+r_1);

	 SelectObject(DC, hOrigPen);
	 SelectObject(DC, hOrigBrush);

	 DeleteObject(hPenLocal);
	 DeleteObject(hBrushLocal);
  }
 }


void CModel2D :: SetMaxValue()
 {
  DWORD j, jN1, i;
  MaxValue_Psi = MaxValue_U = MaxValue_V = MaxValue_J = 0.0;
  for (j=0; j<=M; j++)  {
     jN1 = j*N1;
     for (i=0; i<=N; i++) {
         DWORD index = jN1+i;
         if (MaxValue_Psi < Knots[index].Psi) MaxValue_Psi = Knots[index].Psi;
//         if (MaxValue_U < Knots[index].Ep) MaxValue_U = Knots[index].Ep;
         if (MaxValue_U < Knots[index].U3) MaxValue_U = Knots[index].U3;
         if (MaxValue_V < Knots[index].V) MaxValue_V = Knots[index].V;
         if (MaxValue_J < Knots[index].J) MaxValue_J = Knots[index].J;
     }
  }
 }


void Legenda(HDC hDC, int x, int y, char *str, COLORREF Color)
{
 int i;
 for (i=x; i<=x+10; i++) SetPixel(hDC, i, y, Color);
 TextOut(hDC, i+15, y-5, str, lstrlen(str));

}



void CModel2D :: ShowChannel(HDC hDC, EWhatShow ews, double MaxValue,
							  double deltaF, double ScaleShow, int CurrPersent)
{
	 DWORD j, jN1, i;
	 double  MinValue = 0.0, Value;
	 int x, y;
	 double r = Interval/2.0;
	 COLORREF color;
	 int dX = rModel.right - rModel.left;
	 int dY = rModel.bottom - rModel.top;
	 RECT rModelN = { rModel.left, rModel.top, rModel.right, rModel.bottom };

	 SetMaxValue();

	 // !!!!!!!Ntrub = atoi(ParamCalc.sNtrub);
	 float Delitel = 1; // !!!!!!!!!! atof(ParamCalc.sDelitel);


	 for (int j=0; j<=M; j++)  {
		jN1 = j*N1;
		for (i=0; i<=N; i++)  {
		   Value = Knots[jN1+i].J;
		   if (Value != 0.0 && Value < MaxValue_J )
			  Knots[jN1+i].NumEquLine = (int)ceil(Value / deltaF);
		}
	 }

	 int AllEquLine = ceil(MaxValue_J/deltaF);
	 double xf, yf, l, Napr, h=Interval; // Parameters.h;
	 double Ex, Ey, E;
	 double SummNapr, MaxMidNapr=0.0, secondMaxMidNapr=0.0;
	 int CountNapr, MaxNaprLine = -1, secondMaxNaprLine = -1;
	 for (int nel=0; nel<=AllEquLine; nel++)   {
		SummNapr = 0.0;
		CountNapr = 0;
		for (j=1; j<=M; j++)   {
		   jN1 = j*N1;
		   for (i=1; i<=N/Delitel; i++)   {
			  if (Knots[jN1+i].NumEquLine == nel)  {
			  /*
				 yf = labs(j-jElectr)*h;
				 Ey = fabs(Knots[elIndex].Psi - Knots[jN1+i].Psi)/yf;
				 xf = labs(i-iElectr)*h;
				 Ex = fabs(Knots[elIndex].Psi - Knots[jN1+i].Psi)/xf;
				 E = sqrt (Ex*Ex + Ey*Ey);
			  */
			  //if (Knots[jN1+i].eArrange != IT_BOTTOM_BORDER && Knots[jN1+i].eArrange != IT_RIGHT_BORDER) {
			  if (Knots[jN1+i].eArrange != IT_RIGHT_BORDER) {
				 Ex = (Knots[jN1+i+1].Psi - Knots[jN1+i].Psi)/h;
				 Ey = 0.0;
				 // Ey = (Knots[(j-1)*N1+i].Psi - Knots[jN1+i].Psi)/h;
				 E = sqrt(Ex*Ex + Ey*Ey);
				 SummNapr += E;
				 CountNapr++;
			  }
			  }
		   }
		}

		if (CountNapr > 0) Napr = SummNapr / CountNapr;
		else               Napr = -9999.0;
		allNapr[nel].midNapr = Napr;
//  fprintf(fw, "%d = %f ", nel, Napr);
//  MessageBox(Application->Handle, str, "Отладка", MB_ICONASTERISK|MB_OK);
		if (MaxMidNapr < Napr) {
		   MaxMidNapr = Napr;
		   MaxNaprLine = nel;
		}
	 }
	 //fclose(fw);

	 color = BGIColor[LIGHTRED];
	 for (j=1; j<=M; j++)   {
		jN1 = j*N1;
		for (i=1; i<=N; i++)   {
		   if (Knots[jN1+i].NumEquLine == MaxNaprLine)  {
			  x = rModelN.left + i*Interval;
			  y = rModelN.bottom - j*Interval;
			  DrawKnot(hDC, x, y, r, color, ScaleShow);
		   }
		}
	 }

	 color = BGIColor[GREEN];

	 for (int nel=MaxNaprLine+1; nel<=MaxNaprLine+Ntrub; nel++)   {
		for (j=1; j<=M; j++)   {
		   jN1 = j*N1;
		   for (i=1; i<=N; i++)   {
			  if (Knots[jN1+i].NumEquLine == nel)  {
				 x = rModelN.left + i*Interval;
				 y = rModelN.bottom - j*Interval;
				 DrawKnot(hDC, x, y, r, color, ScaleShow);
			  }
		   }
		}
	 }

	 for (int nel=MaxNaprLine-1; nel>=MaxNaprLine-Ntrub; nel--)   {
		for (j=1; j<=M; j++)   {
		   jN1 = j*N1;
		   for (i=1; i<=N; i++)   {
			  if (Knots[jN1+i].NumEquLine == nel)  {
				 x = rModelN.left + i*Interval;
				 y = rModelN.bottom - j*Interval;
				 DrawKnot(hDC, x, y, r, color, ScaleShow);
			  }
		   }
		}
	 }

	 SummNapr = 0.0;
	 int L=0;
	 jN1 = M*N1;
	 for (int nel=MaxNaprLine-Ntrub; nel<=MaxNaprLine+Ntrub; nel++)   {
		 SummNapr += allNapr[nel].midNapr;
		 for (i=0; i<=N/Delitel; i++)   {
			if (Knots[jN1+i].NumEquLine == nel)
			   L++;
		 }
	 }
	 double StreamE = SummNapr*L;

	 i = N/Delitel;
	 x = rModelN.left + i*Interval;
	 color = BGIColor[YELLOW];
	 for (j=1; j<=M; j++)   {
		jN1 = j*N1;
		y = rModelN.bottom - j*Interval;
		DrawKnot(hDC, x, y, r, color, ScaleShow);
	 }

	 color = BGIColor[LIGHTBLUE];
	 // DJ = atoi(dataParameter.sTimeSwitch);
	 /*x = rModelN.left;
	 y = rModelN.bottom;
	 DrawKnot(hDC, x, y, r, color, ScaleShow);
	 */
	 int xt = rModelN.left;
	 int yt = (rModelN.bottom+10)*ScaleShow;
	 wsprintf (str, "[%d%% ... %d%%]", CurrPersent-1, CurrPersent);
	 TextOut(hDC, xt*ScaleShow, yt-20, str, lstrlen(str));

	 sprintf (str, "Масштаб=%d%%   Количество линий =%d", (int)ceil(ScaleShow*100), AllEquLine);
	 TextOut(hDC, xt*ScaleShow, yt, str, lstrlen(str));
	 yt+=20;


	 for (int nel=1; nel<AllEquLine; nel++)   {
		 float Persent = allNapr[nel].midNapr/MaxMidNapr*100.0;
		 if (CurrPersent-1<Persent && Persent<=CurrPersent) {
			for (j=1; j<=M; j++)   {
			   jN1 = j*N1;
			   for (i=1; i<=N; i++)   {
				  if (Knots[jN1+i].NumEquLine == nel)  {
					 x = rModelN.left + i*Interval;
					 y = rModelN.bottom - j*Interval;
					 DrawKnot(hDC, x, y, r, color, ScaleShow);
				  }
			   }
			}
			sprintf (str, "N%d     Ecp=%.3f    (%.3f%% от Emax)", nel, allNapr[nel].midNapr, Persent);
			TextOut(hDC, xt*ScaleShow, yt, str, lstrlen(str));
			yt+=20;
		 }
	 }

	 sprintf (str, "Es=%.3lf   L=%d  Ф=%.3lf", SummNapr, L, StreamE);
	 TextOut(hDC, xt*ScaleShow, yt, str, lstrlen(str));
	 yt+=20;
	 
	 listBorder->DrawAllList(hDC, ScaleShow);
}



void CModel2D :: ShowEquLines_V(HDC hDC, EWhatShow ews, double MaxValue,
							  double deltaF, double ScaleShow, int CurrPersent)
{
  int dX = rModel.right - rModel.left;
  int dY = rModel.bottom - rModel.top;
  RECT rModelN = { rModel.left, rModel.top, rModel.right, rModel.bottom };
  int x, y;
  double r = Interval/2.0;
  COLORREF color;
  double  MinValue = 0.0, Value;
  DWORD j, jN1, i;

	 // SetMaxValue();

	 int AllEquLine = ceil(MaxValue_V/deltaF);
/*     if (CurrPersent > AllEquLine) CurrPersent = AllEquLine;
	 else if (CurrPersent < 1) CurrPersent = 0;
*/
	 color = BGIColor[LIGHTGREEN];

	 long int iElectr = 10; // !!!!!!!!!!!!!! atoi(ParamCalc.xCoord) - rModel.left;
	 long int jElectr = 10; // !!!!!!!!!!!!!! rModel.bottom - atoi(ParamCalc.yCoord);
	 DWORD elIndex = (M-jElectr)/2*N1 + iElectr;

	 for (j=0; j<=M; j++)  {
		jN1 = j*N1;
		for (i=0; i<=N; i++)  {
		   Value = Knots[jN1+i].V;
		   if (Value != 0.0 && Value < MaxValue_V )
			  Knots[jN1+i].NumEquLine = (int)ceil(Value / deltaF);
		}
	 }

	 // int ElLine = Knots[elIndex].NumEquLine;

	 color = BGIColor[LIGHTRED];
	 for (j=1; j<=M; j++)   {
		jN1 = j*N1;
		for (i=1; i<=N; i++)   {
//           if (Knots[jN1+i].NumEquLine == ElLine)  {
		   if (Knots[jN1+i].NumEquLine == CurrPersent)  {
			  x = rModelN.left + i*Interval;
			  y = rModelN.bottom - j*Interval;
			  DrawKnot(hDC, x, y, r, color, ScaleShow);
		   }
		}
	 }


	 float Delitel = 1; // !!!!!!!!!!!!!!!!!! atof(ParamCalc.sDelitel);
	 SqElLine[CurrPersent] = 0;
	 for (j=1; j<=M; j++)   {
		jN1 = j*N1;
		for (i=1; i<=N/Delitel; i++)
//           if (Knots[jN1+i].NumEquLine == ElLine)
		   if (Knots[jN1+i].NumEquLine == CurrPersent)
			  SqElLine[CurrPersent]++;
	 }

	 i = N/Delitel;
	 x = rModelN.left + i*Interval;
	 color = BGIColor[YELLOW];
	 for (j=1; j<=M; j++)   {
		jN1 = j*N1;
		y = rModelN.bottom - j*Interval;
		DrawKnot(hDC, x, y, r, color, ScaleShow);
	 }

	 x = rModelN.left*ScaleShow;
	 y = (rModelN.bottom+10)*ScaleShow;

//     wsprintf (str, "N%d   Sn = %d", ElLine, SqElLine[CurrPersent]);
	 wsprintf (str, "N%d   Sn = %d", CurrPersent, SqElLine[CurrPersent]);
	 TextOut(hDC, x, y, str, lstrlen(str));
	 y +=20;

//     sprintf (str, "[Fn...Fn+1] = [%.4f...%.4f]", ElLine*deltaF, (ElLine+1)*deltaF);
	 sprintf (str, "[Fn...Fn+1] = [%.4f...%.4f]", CurrPersent*deltaF, (CurrPersent+1)*deltaF);
	 TextOut(hDC, x, y, str, lstrlen(str));
	 y +=20;

	 SumEPlus = 0;
	 for (int k=1; k<AllEquLine; k++) {
		if (EPlus[k])   {
		   SumEPlus += SqElLine[k];
		   sprintf (str, "%d=%d", k, SqElLine[k]);
		   TextOut(hDC, x, y, str, lstrlen(str));
		   x+=50;
		}
	 }

	 x = rModelN.left*ScaleShow;
	 y +=20;
	 wsprintf (str, "Summa = %d", SumEPlus);
	 TextOut(hDC, x, y, str, lstrlen(str));
	 y +=20;


}


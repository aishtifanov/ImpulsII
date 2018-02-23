// ПРОЕКТ:     Математическая модель ИМПУЛЬС
// ВЕРСИЯ:     1.0
// ФАЙЛ:       Mod_Conf.CPP
// ДАТА:       8/93
// АВТОР:      Штифанов А.И.
// СОДЕРЖАНИЕ: Functions:1. CModel2D :: Init
//                       2. CModel2D :: Organise
//                       3. CModel2D :: Destroy

#include "impulse.hpp"
#include <stdio.h>
#include "TParams.h"

// #define ON  TRUE
// #define OFF FALSE

#define INTERIOR_BORDER TRUE
#define EXTERIOR_BORDER FALSE

const double increment = M_PI/90;

void center(double x[], double y[], double *xc, double *yc, double *r);
void swap(double *x, double *y);
void rotate (double xin, double yin, double *x, double *y, double angle);
EBorderArrange GetArrangmentPoint(double xc, double yc, double x1, double y1, BOOL IsInterior);

// #define  U[j][i]      U[i+j*N]    U[j*N+i]

// вместо конструктора
void CModel2D :: Init(CDrawList *alistBorder)
 {
  SetParameters();

  listBorder = alistBorder;
  Knots = NULL;

  listBorder->GetRectPicture(&rModel);
  Interval =  Parameters.h*1000;
  N    = abs(rModel.left - rModel.right) / Interval;
  M    = abs(rModel.top - rModel.bottom) / Interval;
  N1    = N+1;
  WhatCalc = 'P';
 }


// организация массивов
void CModel2D :: Organise()
 {
  int sf = sizeof(SKnot);
  DWORD cbAlloc = (DWORD)(M+2)*(N+2)*sf;
  /*
  char str[100];
  wsprintf(str, "%lu", cbAlloc);
  winIMPULSE->StatusWin->TextStatusOut( STATUS_INSTRUMENT, str, TRUE);
  Form1->StatusBar1->Panels->Items[0]->Text = str;

  DWORD cbFree = GlobalCompact(0L);

  wsprintf(str, "M=%d; N=%d; sf=%d; cbAlloc=%lu; free=%lu",
                M, N, sf, cbAlloc, cbFree);
  MessageBox(winIMPULSE->HWindow, str, "Отладка", MB_ICONASTERISK|MB_OK);

  wsprintf(str, "char = %d; EBorderArrange = %d; EBorderPhisic = %d",
                 sizeof(char), sizeof(EBorderArrange), sizeof(EBorderPhisic));
  MessageBox(winIMPULSE->HWindow, str, "Отладка", MB_ICONASTERISK|MB_OK);

  wsprintf(str, "Free Space before = %lu", GetFreeSpace(0));
  MessageBox(winIMPULSE->HWindow, str, "Отладка", MB_ICONASTERISK|MB_OK);
  */

  if (Knots==NULL)  {
     hMemKnots = GlobalAlloc (GHND, cbAlloc);
     if (!hMemKnots)  {
        MessageBox(Application->Handle,"Нехватка памяти для Knots.",
                            "Ошибка", MB_ICONSTOP|MB_OK);
        SendMessage (Application->Handle, WM_DESTROY, 0, 0L);
     }
     else {
        Knots = (SKnot /*huge*/ *)GlobalLock(hMemKnots);
        DWORD size = GlobalSize(hMemKnots);
        /*
        wsprintf(str, "size = %lu; M=%d; N=%d; double= %d; OO = %lu",
	              size, M, N, sizeof(double), cbAlloc);
        MessageBox(Application->Handle, str, "Отладка", MB_ICONASTERISK|MB_OK);
        wsprintf(str, "Free Space do = %lu", GetFreeSpace(0));
        MessageBox(Application->Handle, str, "Отладка", MB_ICONASTERISK|MB_OK);
        */
     }
  }



  // присвоение "неопределенного" числа всем точкам сетки
  // здесь можно проделать интерполяцию
  /*
  for (int j=0; j<=M; j++)
     for (int i=0; i<=N; i++)
           U[i+j*N] = Psi+1.0;
  */
 /*
 HGLOBAL hMemInt = GlobalAlloc (GHND, cbAlloc);
 int huge *iHUGE = (int huge *)GlobalLock(hMemInt);

 for (DWORD j=0; j<=M; j++)
     for (DWORD i=0; i<=N; i++) {
          DWORD index = i+j*(DWORD)N1;
          iHUGE[index] = 1;
 }

 HGLOBAL hMemdouble = GlobalAlloc (GHND, cbAlloc);
 */

// MessageBox(Application->Handle,"Organise success", "Отладка", MB_ICONASTERISK|MB_OK);

 }


// освобождение памяти
void CModel2D :: Destroy()
 {
  if (hMemKnots)  {
     GlobalUnlock(hMemKnots);
     GlobalFree(hMemKnots);
	 hMemKnots=0;
	 Knots=NULL;
  }
 }


// установка граничных линий
void CModel2D :: Set(int type=1)
 {
  // присвоение "неопределенного" числа всем точкам сетки
  // здесь можно проделать интерполяцию
  char str[10];
  DWORD index;

  for (DWORD j=0; j<=M; j++)  {
	 DWORD jN1 = j*N1;

	 wsprintf(str, "%d", j);
	 ModelConf->StatusBar1->Panels->Items[0]->Text = str;

	 for (DWORD i=0; i<=N; i++) {
		 index = jN1+i;
		 Knots[index].eArrange = IT_NO_BORDER;
		 Knots[index].ePhisic  = IT_UNDEFINE;
		 Knots[index].Psi  = 0.0;
		 Knots[index].U1  = 0.0;
		 Knots[index].U2  = 0.0;
		 Knots[index].U3  = 0.0;
		 Knots[index].V  = 0.0;
		 Knots[index].Ep  = 0.0;
		 Knots[index].Ek  = 0.0;
		 Knots[index].P1  = 0.0;
		 Knots[index].P2  = 0.0;
	 }
  }
//  MessageBox(Application->Handle,"1 SetBorder success", "Отладка", MB_ICONASTERISK|MB_OK);

  int Amount = listBorder->Count();
  CDrawElement *DrawElement;
  for (int k=0; k<Amount; k++)   {
	 DrawElement = (CDrawElement *)listBorder->Get(k);
	 switch (DrawElement->whatIt)  {
		case IT_PIECE: SetLineBorder(DrawElement);
		break;
		case IT_CIRCLE: SetCircleBorder(DrawElement);
		break;
		case IT_NOTCH: SetNotchBorder(DrawElement);
	 }
  } // for k

  switch (type) {
	case 1:
		  for (DWORD j = 0; j<=M; j++)  {
			 DWORD jN1 = j*N1;
			 int FlagLeft=0;
			 for (DWORD i = 0; i<=N; i++)  {
				index = jN1+i;
				if (Knots[index].ePhisic!=IT_INPUT_BORDER) {
				   switch(Knots[index].eArrange) {
					  case IT_LEFT_BORDER:  FlagLeft++;
					  break;
					  case IT_RIGHT_BORDER: FlagLeft--;
					  break;
				   }
				   if (FlagLeft>0) {
				  if (Knots[index].eArrange==IT_NO_BORDER)
						 Knots[index].ePhisic = IT_POINT_CENTER;
				   }
				}
			 }
		  }

		  for (DWORD i = 0; i<=N; i++)  {
			 int FlagTop=0;
			 for (DWORD j = M; j>0; j--)  {
				index = j*N1+i;
				if (Knots[index].ePhisic!=IT_INPUT_BORDER) {
				   switch(Knots[index].eArrange) {
					  case IT_TOP_BORDER:
					 FlagTop=1;
					  break;
					  case IT_BOTTOM_BORDER:
					 FlagTop=0;
					  break;
				   }
				   if (FlagTop>0) {
				  if (Knots[index].eArrange == IT_NO_BORDER)  {
						 Knots[index].ePhisic = IT_POINT_CENTER;
					  }
				   }
				}
			 }
		  }
	break;

	case 2:
		  for (DWORD j = 0; j<=M; j++)  {
			 DWORD jN1 = j*N1;
			 int FlagLeft=0;
			 for (DWORD i = 0; i<=N; i++)  {
				index = jN1+i;
				if (Knots[index].ePhisic!=IT_INPUT_BORDER) {
				   switch(Knots[index].eArrange) {
					  case IT_LEFT_BORDER:  FlagLeft=1; // FlagLeft++;
					  break;
					  case IT_RIGHT_BORDER: FlagLeft=0; // FlagLeft--;
					  break;
				   }
				   if (FlagLeft>0) {
				  if (Knots[index].eArrange==IT_NO_BORDER)
						 Knots[index].ePhisic = IT_POINT_CENTER;
				   }
				}
			 }
		  }
	break;

	case 3:
			 for (DWORD j = 0; j<=M; j++)  {
			 DWORD jN1 = j*N1;
			 int FlagLeft=0, kpLeft = 0, kpRight= 0;
			 for (DWORD i = 0; i<=N; i++)  {
				index = jN1+i;
				if (Knots[index].ePhisic!=IT_INPUT_BORDER) {
				   switch(Knots[index].eArrange) {
					  case IT_TOP_BORDER:  if (!kpLeft&&!kpRight) FlagLeft=1;
										   if (kpLeft&&kpRight) FlagLeft=0;
					  break;
					  case IT_LEFT_BORDER:  FlagLeft=1;
											kpLeft = 1;
					  break;
					  case IT_RIGHT_BORDER: FlagLeft=0;
											kpRight = 1;
					  break;
				   }
				   if (FlagLeft) {
				  if (Knots[index].eArrange==IT_NO_BORDER)
						 Knots[index].ePhisic = IT_POINT_CENTER;
				   }
				   else {
				  if (Knots[index].eArrange==IT_NO_BORDER)
						 Knots[index].ePhisic = IT_UNDEFINE;
				   }
				}
			 }
		  }
	break;

	case 4:
		  for (DWORD j = 0; j<=M; j++)  {
			 DWORD jN1 = j*N1;
			 int FlagLeft=0;
			 for (DWORD i = 0; i<=N; i++)  {
				index = jN1+i;
				if (Knots[index].ePhisic!=IT_INPUT_BORDER) {
				   switch(Knots[index].eArrange) {
					  case IT_LEFT_BORDER:  FlagLeft++;
					  break;
					  case IT_RIGHT_BORDER: FlagLeft--;
					  break;
				   }
				   if (FlagLeft>0) {
				  if (Knots[index].eArrange==IT_NO_BORDER)
						 Knots[index].ePhisic = IT_POINT_CENTER;
				   }
				}
			 }
		  }
	break;
  }
  
  setBGIColor2(Parameters.QEquLine);

/*
  int inputX1=39, inputX2=41;
  inputX1 = (inputX1 - rModel.left) / Interval;
  inputX2 = (inputX2 - rModel.left) / Interval;
//  MathModel->GetInputBorder(inputX1, inputX2, 1);
//  MathModel->GetInputBorder(inputX1, inputX2, 2);
  int inputY1=20, inputY2=22;
  inputY1 = (rModel.bottom - inputY1) / Interval;
  inputY2 = (rModel.bottom - inputY2) / Interval;

  int xmin = min(inputX1, inputX2);
  int xmax = max(inputX1, inputX2);
  int ymin = min(inputY1, inputY2);
  int ymax = max(inputY1, inputY2);
  for (DWORD m = ymin; m <= ymax; m++)
	 for (DWORD n = xmin; n <= xmax; n++) {
		index = m*N1+n;
		Knots[index].eArrange = IT_LEFT_BORDER;
		Knots[index].ePhisic = IT_INPUT_BORDER;
		Knots[index].U1  = 0.000001;
		Knots[index].U2  = 0.000001;
		Knots[index].U3  = 0.000001;
  }
*/

//  MessageBox(Application->Handle,"SetBorder success", "Отладка", MB_ICONASTERISK|MB_OK);
}

 void CModel2D :: SetParameters()
 {
	  Parameters.h = StrToFloat(ParametersDlg->sStep->Text);
	  Interval =  Parameters.h*1000;
	  Parameters.Rau = StrToFloat(ParametersDlg->sDensity->Text);
	  Parameters.a0 = StrToFloat(ParametersDlg->sSoundSpeed->Text);
	  Parameters.P0 = StrToFloat(ParametersDlg->sBeginPressing->Text);
	  Parameters.tmax = StrToFloat(ParametersDlg->sTimeMax->Text)*1e-6;
	//  Parameters.tetta = StrToFloat(ParametersDlg->sTimeTetta)*1e-6;
	  Parameters.tp = StrToFloat(ParametersDlg->sTimeSwitch->Text)*1e-6;
	//  Parameters.Psi = 50.0;  // значение потенциала на источнике
	//  Parameters.dPsi = 2.0; // "толщина" эквипотенциальной линии
	  Parameters.Eps = StrToFloat(ParametersDlg->sEpsilon->Text);  // погрешность вычислений
	  Parameters.w = StrToFloat(ParametersDlg->sOmega->Text);    // ускоряющий коэффициент [1..2]
	  Parameters.Ttotal = StrToFloat(ParametersDlg->sTtotal->Text)*1e-6;
	//  Parameters.QEquLine = (int)ceil(Parameters.Psi/Parameters.dPsi);
	  Parameters.QEquLine = StrToInt(ParametersDlg->sQEquLine->Text);
	  Parameters.AutoSaveIter = StrToInt(ParametersDlg->sAutoSaveIter->Text);

	  Parameters.bLeftRight = ParametersDlg->bLeftRight->Checked;
	  Parameters.bRightLeft = ParametersDlg->bRightLeft->Checked;
	  Parameters.bFromCenter = ParametersDlg->bFromCenter->Checked;
	  Parameters.bToCenter = ParametersDlg->bToCenter->Checked;
	  Parameters.bTwoWhile = ParametersDlg->bTwoWhile->Checked;

	  Parameters.xCoord = StrToInt(ParametersDlg->xCoord->Text);
	  Parameters.yCoord = StrToInt(ParametersDlg->yCoord->Text);
	  Parameters.Ntrub = StrToInt(ParametersDlg->sNtrub->Text);
	  Parameters.Delitel = StrToInt(ParametersDlg->sDelitel->Text);

	  Parameters.Model2D = ParametersDlg->Model2D->Checked;
	  Parameters.ModelFiZR = ParametersDlg->ModelFiZR->Checked;
	  Parameters.NumLevel = StrToInt(ParametersDlg->NumLevel->Text);


 }

 void CModel2D :: SetParametersAsStr()
 {
	  ParametersDlg->sStep->Text = FloatToStrF (Parameters.h, ffFixed, 5, 5);
	  ParametersDlg->sDensity->Text = FloatToStrF (Parameters.Rau, ffFixed, 1, 0);
	  ParametersDlg->sSoundSpeed->Text = FloatToStrF (Parameters.a0, ffFixed, 1, 0);
	  ParametersDlg->sBeginPressing->Text = FloatToStrF (Parameters.P0, ffFixed, 1, 0);
	  ParametersDlg->sTimeMax->Text = FloatToStrF (Parameters.tmax/1e-6, ffFixed, 1, 0);
	  ParametersDlg->sTimeSwitch->Text = FloatToStrF (Parameters.tp/1e-6, ffFixed, 1, 0);
	  ParametersDlg->sEpsilon->Text = FloatToStrF (Parameters.Eps, ffFixed, 3, 3);
	  ParametersDlg->sOmega->Text = FloatToStrF (Parameters.w, ffFixed, 1, 1);
	  ParametersDlg->sTtotal->Text = FloatToStrF (Parameters.Ttotal/1e-6, ffFixed, 1, 0);
	  ParametersDlg->sQEquLine->Text = IntToStr(Parameters.QEquLine);
	  ParametersDlg->sAutoSaveIter->Text = IntToStr(Parameters.AutoSaveIter);

	 ParametersDlg->bLeftRight->Checked = Parameters.bLeftRight;
	 ParametersDlg->bRightLeft->Checked = Parameters.bRightLeft;
	 ParametersDlg->bFromCenter->Checked = Parameters.bFromCenter;
	 ParametersDlg->bToCenter->Checked = Parameters.bToCenter;
	 ParametersDlg->bTwoWhile->Checked = Parameters.bTwoWhile;

	 ParametersDlg->xCoord->Text =	IntToStr(Parameters.xCoord);
	 ParametersDlg->yCoord->Text =	IntToStr(Parameters.yCoord);
	 ParametersDlg->sNtrub->Text =	IntToStr(Parameters.Ntrub);
	 ParametersDlg->sDelitel->Text = IntToStr(Parameters.Delitel);

	 ParametersDlg->Model2D->Checked = Parameters.Model2D;
	 ParametersDlg->ModelFiZR->Checked = Parameters.ModelFiZR;
	 ParametersDlg->NumLevel->Text = IntToStr(Parameters.NumLevel);
 }


 void CModel2D :: SetZero()
 {
  DWORD jN1, i, j, index5;
  for (j=0; j<=M; j++)  {
     jN1 = j*N1;
     for (i=0; i<=N; i++)  {
        index5 = jN1+i; // ссылка на центр "креста"
        Knots[index5].D3 = 0.0;
        Knots[index5].D2 = 0.0;
        Knots[index5].D1 = 0.0;
        switch (Knots[index5].ePhisic)  {
           case IT_POINT_CENTER:
           case IT_HARD_BORDER:
           case IT_OUTPUT_BORDER:
              Knots[index5].U3 = 0.0;
              Knots[index5].U2 = 0.0;
              Knots[index5].U1 = 0.0;
           break;
           case IT_INPUT_BORDER:
              Knots[index5].U3 = 0.00001;
              Knots[index5].U2 = 0.00001;
              Knots[index5].U1 = 0.00001;
           break;
        }
     }
  }
 }

void CModel2D :: SetLineBorder(CDrawElement *DrawElement)
 {
  int    x1, y1, x2, y2;
  EBorderArrange eArrange;
  EBorderPhisic  ePhisic;
  double  BegValue;
  DWORD index;

  CPiece *cpBorder = (CPiece *)DrawElement;
  x1    = (cpBorder->X1 - rModel.left) / Interval;
  y1    = (rModel.bottom - cpBorder->Y1) / Interval;
  x2    = (cpBorder->X2 - rModel.left) / Interval;
  y2    = (rModel.bottom - cpBorder->Y2) / Interval;
  eArrange = cpBorder->eArrange;
  ePhisic  = cpBorder->ePhisic;
  BegValue = cpBorder->BegPsi;

  // горизонтальные границы
  if (y1==y2)  {
     int xmin = min(x1, x2);
     int xmax = max(x1, x2);
     for (DWORD n = xmin; n <= xmax; n++) {
        index = y1*N1+n;
        Knots[index].eArrange = eArrange;
        Knots[index].ePhisic = ePhisic;
        Knots[index].Psi  = BegValue;
        Knots[index].U1  = BegValue;
        Knots[index].U2  = BegValue;
        Knots[index].U3  = BegValue;
        Knots[index].D1  = BegValue;
        Knots[index].D2  = BegValue;
        Knots[index].D3  = BegValue;
     }
  }
  // вертикальные границы
  else if (x1==x2)  {
     int ymin = min(y1, y2);
     int ymax = max(y1, y2);
     for (DWORD n = ymin; n <= ymax; n++) {
        index = n*N1+x1;
        Knots[index].eArrange = eArrange;
        Knots[index].ePhisic = ePhisic;
        Knots[index].Psi  = BegValue;
        Knots[index].U1  = BegValue;
        Knots[index].U2  = BegValue;
        Knots[index].U3  = BegValue;
        Knots[index].D1  = BegValue;
        Knots[index].D2  = BegValue;
        Knots[index].D3  = BegValue;
     }
  }
  // наклонные границы
  else  {
     int dx = x2-x1,   dy = y2-y1,
     ix = abs(dx), iy = abs(dy),
     plotx = x1,   ploty = y1,
     x = 0,        y = 0,
     inc = max(ix, iy),
     plot = FALSE;
     index = ploty*N1+plotx;
     Knots[index].eArrange = eArrange;
     Knots[index].ePhisic = ePhisic;
     Knots[index].Psi  = BegValue;
     Knots[index].U1  = BegValue;
     Knots[index].U2  = BegValue;
     Knots[index].U3  = BegValue;
     Knots[index].D1  = BegValue;
     Knots[index].D2  = BegValue;
     Knots[index].D3  = BegValue;

     for (int n = 0; n<=inc; n++) {
        x += ix;
        y += iy;
        plot = FALSE;
        if (x>inc) {
           plot = TRUE;
           x -= inc;
           plotx += sign(dx);
        }
        if (y>inc) {
           plot = TRUE;
           y -= inc;
           ploty += sign(dy);
        }
        if (plot) {
           index = ploty*N1+plotx;
           Knots[index].eArrange = eArrange;
           Knots[index].ePhisic = ePhisic;
           Knots[index].Psi  = BegValue;
           Knots[index].U1  = BegValue;
           Knots[index].U2  = BegValue;
           Knots[index].U3  = BegValue;
           Knots[index].D1  = BegValue;
           Knots[index].D2  = BegValue;
           Knots[index].D3  = BegValue;
        } // if plot
     } // for n
  } // else
 }

void center(double x[], double y[], double *xc, double *yc, double *r)
 {
  double x2[2], xh[2], y2[2], yk[2];
  double x2y2[2], xnyn, ykn;

  x2[0] = x[0]*x[0] - x[1]*x[1];
  xh[0] = 2*x[0] - 2*x[1];
  y2[0] = y[0]*y[0] - y[1]*y[1];
  yk[0] = 2*y[0] - 2*y[1];
  x2[1] = x[1]*x[1] - x[2]*x[2];
  xh[1] = 2*x[1] - 2*x[2];
  y2[1] = y[1]*y[1] - y[2]*y[2];
  yk[1] = 2*y[1] - 2*y[2];

  x2y2[0] = x2[0] + y2[0];
  x2y2[1] = x2[1] + y2[1];

  xnyn = x2y2[0];
  ykn = yk[0];

  x2y2[0] *= xh[1];
  yk[0] *= xh[1];

  x2y2[1] *= xh[0];
  yk[1] *= xh[0];

  *yc = (x2y2[0] - x2y2[1]) / (yk[0] - yk[1]);
  *xc = (xnyn - *yc*ykn) / xh[0];

  x[0] -= *xc;
  y[0] -= *yc;

  *r = sqrt(x[0]*x[0] + y[0]*y[0]);
 }

int round(double number)
 {
   double fraction, integer;
   int    newnum;
   fraction = modf(number, &integer);
   if (fraction >= 0.5) newnum = (int)ceil(number);
   else 		newnum = (int)floor(number);
   return newnum;
 }


void rotate (double xin, double yin, double *x, double *y, double angle)
 {
  *x = xin*cos(angle) - yin*sin(angle);
  *y = xin*sin(angle) + yin*cos(angle);
 }

void swap(double *x, double *y)
 {
   double t = *x;
   *x = *y;
   *y = t;
 }

EBorderArrange GetArrangmentPoint(double xc, double yc, double x1, double y1, BOOL IsInterior)
 {
  double dx = fabs(xc - x1);
  double dy = fabs(yc - y1);
  EBorderArrange eArrange = IT_NO_BORDER;

  if (dx >= dy) {
     if (x1 < xc)  {
        if (IsInterior) eArrange = IT_LEFT_BORDER;
        else 		eArrange = IT_RIGHT_BORDER;
     }
     else {
        if (IsInterior) eArrange = IT_RIGHT_BORDER;
        else 	 	eArrange = IT_LEFT_BORDER;
     }
  }
  else {
     if (y1 < yc) {
        if (IsInterior) eArrange = IT_TOP_BORDER;
        else		eArrange = IT_BOTTOM_BORDER;
     }
     else {
        if (IsInterior) eArrange = IT_BOTTOM_BORDER;
        else 		eArrange = IT_TOP_BORDER;
     }
  }

  return eArrange;
 }


void CModel2D :: SetCircleBorder(CDrawElement *DrawElement)
 {
	CCircle *Circle = (CCircle *)DrawElement;
	double xc = Circle->X1;
	double yc = Circle->Y1;
	double r  = Circle->R;
	double lastx = r, lasty = 0, xrot, yrot;

	CPiece *Piece = new CPiece(0, 0, 0, 0, "", "", 0);
	Piece->eArrange = Circle->eArrange;
	Piece->ePhisic  = Circle->ePhisic;
	Piece->BegPsi   = Circle->BegPsi;
//	Circle->IsInterior = INTERIOR_BORDER;

	for (double inc_angle = 0; inc_angle < 2*M_PI; inc_angle += increment)  {
		 rotate(r, 0, &xrot, &yrot, inc_angle);
		 Piece->X1 = round(lastx+xc);
		 Piece->Y1 = round(lasty+yc);
		 Piece->X2 = round(xrot+xc);
		 Piece->Y2 = round(yrot+yc);
		 Piece->eArrange = GetArrangmentPoint(xc, yc, Piece->X1, Piece->Y1, Circle->IsInterior);
		 SetLineBorder(Piece);
		 // linef (lastx+xc, lasty+yc, xrot+xc, yrot+yc, ON);
		 lastx = xrot;
		 lasty = yrot;
	}
	Piece->X1 = round(lastx+xc);
	Piece->Y1 = round(lasty+yc);
	Piece->X2 = round(r+xc);
	Piece->Y2 = round(yc);
	Piece->eArrange = GetArrangmentPoint(xc, yc, Piece->X1, Piece->Y1, Circle->IsInterior);       Piece->eArrange = GetArrangmentPoint(xc, yc, Piece->X1, Piece->Y1, Circle->IsInterior);
	SetLineBorder(Piece);
	// linef (lastx+xc, lasty+yc, r+xc, 0+yc, ON);
	delete Piece;
 }


void CModel2D :: SetNotchBorder(CDrawElement *DrawElement)
 {
  double xc, yc, r, x_list[3], y_list[3];
  double angle[3], angle_a, angle_b, max_angle, min_angle;
  double inc_angle;
  double xrot, yrot, lastx, lasty;
  double local_min, local_max;
  int i;

  CNotch *Notch = (CNotch *)DrawElement;
  xc = Notch->X1;
  yc = Notch->Y1;
  r  = Notch->R;
  x_list[0] = Notch->X3;
  y_list[0] = Notch->Y3;
  x_list[1] = Notch->X2;
  y_list[1] = Notch->Y2;

  CPiece *Piece = new CPiece(0, 0, 0, 0, "", "", 0);
  Piece->eArrange = Notch->eArrange;
  Piece->ePhisic  = Notch->ePhisic;
  Piece->BegPsi   = Notch->BegPsi;
  Notch->IsInterior = INTERIOR_BORDER;

  if (r!=0) {
     x_list[2] = x_list[1];
     y_list[2] = y_list[1];
  }
  else center(x_list, y_list, &xc, &yc, &r);

  // переход в локальную систему координат
  // и расчет углов
  for (i=0; i<=2; i++)  {
     y_list[i] = yc - y_list[i];
     x_list[i] = x_list[i] - xc;
     // angle[i] = atan2(yc-y_list[i], x_list[i]-xc);
     if (x_list[i] == 0) {
        if (y_list[i]>0) angle[i] = M_PI_2;
        else angle[i] = 3*M_PI_2;
     }
     else {
        angle[i] = atan2(y_list[i], x_list[i]);
//        if( sign(angle[i]) == -1) angle[i] += 2*M_PI;
     }
  }
  /*
  if (r==0) {

     angle_a = max(angle[0], angle[1]);
     angle_b = max(angle[1], angle[2]);
     max_angle = max(angle_a, angle_b);

     angle_a = min(angle[0], angle[1]);
     if (angle_a == angle[1])  {
        swap(x_list+0, x_list+1);
        swap(y_list+0, y_list+1);
     }

     angle_b = min(angle[1], angle[2]);
     if (angle_b == angle[2])  {
        swap(x_list+1, x_list+2);
        swap(y_list+1, y_list+2);
	 }

     min_angle = min(angle_a, angle_b);
  }
  else {
     max_angle = max(angle[0], angle[1]);
     min_angle = min(angle[0], angle[1]);
     if (angle[0] > angle[1]) {
        swap(x_list+0, x_list+1);
        swap(y_list+0, y_list+1);
     }
 } */

  lastx = x_list[0];
  lasty = y_list[0];
  local_min = 0;
  if (angle[0]<0.0 && angle[1]>0.0) {
     local_max = fabs((M_PI+angle[0]) + (M_PI-angle[1]));
  }
  else local_max = fabs(angle[0] - angle[1]);
  // local_max = max_angle - min_angle;
  /*
  double ab = x_list[0]*x_list[1] + y_list[0]*y_list[1];
  double a_b = x_list[0]*y_list[1] - y_list[0]*x_list[1];
  local_max = fabs(atan2(a_b, ab));
  */
  for (inc_angle = local_min; inc_angle <= local_max; inc_angle += increment)  {
      rotate(x_list[0], y_list[0], &xrot, &yrot, -inc_angle);
      Piece->X1 = round(lastx+xc);
      Piece->Y1 = round(yc-lasty);
      Piece->X2 = round(xrot+xc);
      Piece->Y2 = round(yc-yrot);
      Piece->eArrange = GetArrangmentPoint(xc, yc, Piece->X1, Piece->Y1, Notch->IsInterior);
      //Piece->ePhisic = IT_HARD_BORDER;
      //Piece->ePhisic = IT_FREE_BORDER;
      SetLineBorder(Piece);
      //linef (lastx+xc, lasty+yc, xrot+xc, yrot+yc, OFF);
      lastx = xrot;
      lasty = yrot;
  }
  rotate(x_list[0], y_list[0], &xrot, &yrot, -inc_angle);
  Piece->X1 = round(lastx+xc);
  Piece->Y1 = round(yc-lasty);
  Piece->X2 = round(xrot+xc);
  Piece->Y2 = round(yc-yrot);
  //Piece->ePhisic = IT_HARD_BORDER;
//  Piece->ePhisic = IT_FREE_BORDER;
  Piece->eArrange = GetArrangmentPoint(xc, yc, Piece->X1, Piece->Y1, Notch->IsInterior);
  SetLineBorder(Piece);
 // linef (lastx+xc, lasty+yc, xrot+xc, yrot+yc, OFF);
}




/**
*  Функция для заполнения массива цветов  (красный - минимальный, синий максимальный)
*  1. 255     0..255   0
*  2. 255..0  255      0
*  3. 0       255      0..255
*  4. 0       255..0   255
*/
void setBGIColor2invert(int num)
{
  int i, j, red, green, blue;
  for (i=0; i <= 1000; i++) {
	BGIColor2[i] = RGB(0,0,0); //BLACK
  }

  int kol_lines = num/4;
  if (num % 4 > 0) {
	  kol_lines += 1;
  }

  j = 0;
  int delta = 255/kol_lines;

  red = 255;  green=0;  blue =0;
  for (i=0; i < kol_lines; i++) {
		BGIColor2[j++] = RGB(red, green, blue);
		green += delta;
		if (green > 255) green = 255;
  }

  red = 255;  green=255;  blue =0;
  for (i=0; i < kol_lines; i++) {
		BGIColor2[j++] = RGB(red, green, blue);
		red -= delta;
		if (red < 0) red = 0;
  }

  red = 0;  green=255;  blue =0;
  for (i=0; i < kol_lines; i++) {
		BGIColor2[j++] = RGB(red, green, blue);
		blue += delta;
		if (blue > 255) blue = 255;
  }

  red = 0;  green=255;  blue =255;
  for (i=0; i < kol_lines; i++) {
		BGIColor2[j++] = RGB(red, green, blue);
		green -= delta;
		if (green < 0) green = 0;
  }

  BGIColor2[j] = RGB(255, 0, 0);
}


/**
*  Функция для заполнения массива цветов  (красный - максимальный, синий - минимальный)
*  1. 0       0..255   255
*  2. 0       255      255..0
*  3. 0..255  255      0
*  4. 255     255..0   0
*/
void setBGIColor2(int num)
{
  int i, j, red, green, blue;
  for (i=0; i <= 1000; i++) {
	BGIColor2[i] = RGB(0,0,0); //BLACK
  }

  int kol_lines = num/4;
  if (num % 4 > 0) {
	  kol_lines += 1;
  }

  j = 0;
  int delta = 255/kol_lines;

  red = 0;  green=0;  blue = 255;
  for (i=0; i < kol_lines; i++) {
		BGIColor2[j++] = RGB(red, green, blue);
		green += delta;
		if (green > 255) green = 255;
  }

  red = 0;  green=255;  blue = 255;
  for (i=0; i < kol_lines; i++) {
		BGIColor2[j++] = RGB(red, green, blue);
		blue -= delta;
		if (blue < 0) blue = 0;
  }

  red = 0;  green=255;  blue =0;
  for (i=0; i < kol_lines; i++) {
		BGIColor2[j++] = RGB(red, green, blue);
		red += delta;
		if (red > 255) red = 255;
  }

  red = 255;  green=255;  blue = 0;
  for (i=0; i < kol_lines; i++) {
		BGIColor2[j++] = RGB(red, green, blue);
		green -= delta;
		if (green < 0) green = 0;
  }
  BGIColor2[j] = RGB(255, 0, 0);
}






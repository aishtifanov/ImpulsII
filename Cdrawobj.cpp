// ПРОЕКТ:     Математическая модель ИМПУЛЬС
// ВЕРСИЯ:     1.0
// ФАЙЛ:       CDrawObj.CPP
// ДАТА:       6/94
// АВТОР:      Штифанов А.И.
// СОДЕРЖАНИЕ:

#include "impulse.hpp"

BOOL  IsPiecePiece(int x1, int y1, int x2, int y2,
                 int x1_, int y1_, int x2_, int y2_);

BOOL  IsPieceCircle(int x1, int y1, int x2, int y2,
                   int x, int y, int R);

BOOL  IsCircleCircle(int x1, int y1, int R1,
                     int x2, int y2, int R2);

// -----------------------------------------------------

BOOL  IsPiecePiece(int x1, int y1, int x2, int y2,
                 int x1_, int y1_, int x2_, int y2_)
 {
  BOOL ret=FALSE;
  double A1, B1, C1;
  double A2, B2, C2;
  double x0=9999.0, y0=9999.0, D=0.0;

  A1 = y2-y1;
  B1 = x1-x2;
  C1 = double(y1)*double((x2-x1)) - double(x1)*double((y2-y1));

  A2 = y2_-y1_;
  B2 = x1_-x2_;
  C2 = double(y1_)*double((x2_-x1_)) - double(x1_)*double((y2_-y1_));

//   | A1  B1 |
//   | A2  B2 |
  D = double(A1)*double(B2) - double(A2)*double(B1);
  if ( -0.00000001 < D && D < 0.00000001) ret=FALSE;
  else {

//   | -C1  B1 |     | A1  -C1 |
//   | -C2  B2 |     | A2  -C2 |
     x0 = (B1*C2 - B2*C1)/D;
     y0 = (A2*C1 - A1*C2)/D;

//         __________________________             d1    d2
//   d = \/ (x2 - x1)^2 + (y2 - y1)^2          |------|-----|
//                                             |------d-----|
     double sqrX = (x0-x1)*(x0-x1);
     double sqrY = (y0-y1)*(y0-y1);
     double d1 = sqrt(sqrX + sqrY);

     sqrX = (x0-x2)*(x0-x2);
     sqrY = (y0-y2)*(y0-y2);
     double d2 = sqrt(sqrX + sqrY);

     sqrX = (double)(x1-x2)*(double)(x1-x2);
     sqrY = (double)(y1-y2)*(double)(y1-y2);
     double d = sqrt(sqrX + sqrY);

     if (d>d1 && d>d2) {
        sqrX = (x0-x1_)*(x0-x1_);
        sqrY = (y0-y1_)*(y0-y1_);
        d1 = sqrt(sqrX + sqrY);

        sqrX = (x0-x2_)*(x0-x2_);
        sqrY = (y0-y2_)*(y0-y2_);
        d2 = sqrt(sqrX + sqrY);

        sqrX = (double)(x1_-x2_)*(double)(x1_-x2_);
        sqrY = (double)(y1_-y2_)*(double)(y1_-y2_);
        d = sqrt(sqrX + sqrY);
        if (d>d1 && d>d2) ret=TRUE;
     }
  }

  return ret;
 }


BOOL  IsPieceCircle(int x1, int y1, int x2, int y2,
                    int x, int y, int R)
 {
  RECT rC = { x-R, y-R, x+R, y+R };
  RECT rP, lPtn;
  if (x2 > x1) { rP.left = x1; rP.right=x2; }
  else         { rP.left = x2; rP.right=x1; }
  if (y2 > y1) { rP.top  = y1; rP.bottom = y2; }
  else         { rP.top  = y2; rP.bottom = y1; }

  BOOL ret=FALSE;

  if (x2 == x1) { 
     if ( x1-3 <= x && x <= x1+3) {
        if ( rP.top <= y && y <= rP.bottom)
	   ret = TRUE;
     }
  }
  else if (y2 == y1) {
     if ( y1-3 <= y && y <= y1+3) {
        if (rP.left <= x && x <= rP.right)
	   ret = TRUE;
     }
  }
  else if ((x1==x && y1==y) || (x2==x && y2==y)) ret = TRUE;
  else if (IntersectRect(&lPtn, &rC, &rP)) {
     double sqrX = (double)(x-x1)*(double)(x-x1);
     double sqrY = (double)(y-y1)*(double)(y-y1);
     double b = sqrt(sqrX + sqrY);

     sqrX = (double)(x-x2)*(double)(x-x2);
     sqrY = (double)(y-y2)*(double)(y-y2);
     double c = sqrt(sqrX + sqrY);

     sqrX = (double)(x1-x2)*(double)(x1-x2);
     sqrY = (double)(y1-y2)*(double)(y1-y2);
     double a = sqrt(sqrX + sqrY);

     double CosC = (a*a + b*b - c*c)/(2*a*b);
     double ha = b*sqrt(1-CosC*CosC);

     if (ha < R && (b>R || c>R)) ret = TRUE;
  }
  return ret;
 }


BOOL  IsCircleCircle(int x1, int y1, int R1,
                     int x2, int y2, int R2)
 {
  RECT rC1 = { x1-R1, y1-R1, x1+R1, y1+R1 };
  RECT rC2 = { x2-R2, y2-R2, x2+R2, y2+R2 };
  RECT lPtn;

  BOOL ret=FALSE;

  if (IntersectRect(&lPtn, &rC1, &rC2)) {
     double sqrX = (double)(x2-x1)*(double)(x2-x1);
     double sqrY = (double)(y2-y1)*(double)(y2-y1);
     double G = sqrt(sqrX + sqrY);

     double RR = R1+R2;
     if (RR < G) ret=FALSE;
     else if ( (R1>R2 && R1>(R2+G)) || (R2>R1 && R2>(R1+G))) ret=FALSE;
     else ret = TRUE;
  }
  return ret;
 }


// КЛАСС: CPoint ------------------------
void CPoint :: DrawThickPoint(HDC DC, double Scale)
 {
  HPEN    hPenLocal, hOrigPen;
  HBRUSH  hBrushLocal, hOrigBrush;

  hPenLocal   = CreatePen(PS_SOLID, 1, PenColor);
  hBrushLocal = CreateSolidBrush(PenColor);

  hOrigPen = (HPEN)SelectObject(DC, hPenLocal);
  hOrigBrush = (HBRUSH)SelectObject(DC, hBrushLocal);

  int x_1 = (int)(X1*Scale);
  int y_1 = (int)(Y1*Scale);
  Ellipse(DC, x_1-R, y_1-R, x_1+R, y_1+R);
  SetTextAlign(DC, TA_CENTER);
  SetTextColor(DC, PenColor);
  SetBkMode(DC, TRANSPARENT);

//  SelectObject(DC, State.hFont);
  TextOut(DC, x_1, y_1+R+3, NamePoint, lstrlen(NamePoint));

  SelectObject(DC, hOrigPen);
  SelectObject(DC, hOrigBrush);

  DeleteObject(hPenLocal);
  DeleteObject(hBrushLocal);
 }


void CPoint :: Draw(HDC DC, double Scale)
 {
  DrawThickPoint(DC, Scale);
 }


BOOL CPoint :: Belong(int xc, int yc, POINT *pnt)
 {
  RECT rE = { xc-3, yc-3, xc+3, yc+3 };
  RECT rP = { X1-3, Y1-3, X1+3, Y1+3 };

  for ( int xb = rE.left; xb <= rE.right; xb++)
     for ( int yb = rE.top; yb <= rE.bottom; yb++)
         if ( xb >= rP.left && xb <= rP.right &&
              yb >= rP.top  && yb <= rP.bottom ) {
              if (pnt!=NULL) { pnt->x = X1; pnt->y = Y1; }
              return TRUE;
         }
  return FALSE;
 }

void CPoint :: Change(int Ox, int Oy)
 {
  X1 += Ox; Y1+=Oy;
 }

void CPoint :: Read(ifstream &fr)
 {
//  fr.read((char *)&whatIt, sizeof(whatIt));
//  char ch; fr.read(&ch, sizeof(ch));
  fr.read((char *)&X1, sizeof(X1));
  fr.read((char *)&Y1, sizeof(Y1));
  fr.read((char *)&PenColor, sizeof(PenColor));
  fr.read(NamePoint, 4);
  fr.read((char *)&R, sizeof(R));
 }

void CPoint :: Write(ofstream &fw)
 {
  fw.write((char *)&whatIt, sizeof(whatIt));
  fw.write((char *)&X1, sizeof(X1));
  fw.write((char *)&Y1, sizeof(Y1));
  fw.write((char *)&PenColor, sizeof(PenColor));
  fw.write(NamePoint, 4);
  fw.write((char *)&R, sizeof(R));
 }

CDrawElement *CPoint :: CreateCopy()
 {
  CDrawElement *cd;
  cd = new CPoint(X1, Y1, PenColor, NamePoint, R);
  return cd;
 }

BOOL CPoint :: IsIntersection(CDrawElement *cde)
 {
  BOOL ret = FALSE;
  WORD dX, dY;

  switch (cde->whatIt)  {
     case IT_POINT:  if (X1==cde->X1 && Y1==cde->Y1) ret = TRUE;
     break;          
	  case IT_PIECE:{ CPiece *cdeI = (CPiece *)cde;
							ret = IsPieceCircle(cdeI->X1, cdeI->Y1, cdeI->X2, cdeI->Y2,
													  X1, Y1, R);
	  }break;
	  case IT_CIRCLE:{CCircle *cdeC  = (CCircle *)cde;
							ret = IsCircleCircle(cdeC->X1, cdeC->Y1, cdeC->R,
														X1, Y1, R);
	  }break;
  }
  return ret;
 }


// КЛАСС: CInfinity ------------------------
void CInfinity :: Draw(HDC DC, double Scale)
 {
  HPEN hPenLocal = CreatePen(PS_SOLID, (int)Scale, PenColor);
  HPEN hOrigPen  = SelectPen(DC, hPenLocal);

  int x_1 = ceil(X1*Scale);
  int y_1 = ceil(Y1*Scale);
  int x_2 = ceil(X2*Scale);
  int y_2 = ceil(Y2*Scale);
  MoveToEx(DC, x_1, y_1, NULL);
  LineTo(DC, x_2, y_2);

  SelectPen(DC, hOrigPen);
  DeletePen(hPenLocal);
 }


BOOL CInfinity :: Belong(int xc, int yc, POINT *pnt)
 {
  BOOL ret = IsPieceCircle(X1, Y1, X2, Y2, xc, yc, 2/*State.RPoint+3*/);

  if (ret && pnt!=NULL)  {

     pnt->x = xc;
     pnt->y = yc;

     RECT rE = { xc-3, yc-3, xc+3, yc+3 };
     if (X2 == X1) {
        if (X1 >= rE.left && X2 <= rE.right) {
           if (pnt!=NULL) { pnt->x = xc; pnt->y = yc; }
           ret = TRUE;
        }
     }
     else  {
        double a = (double)(Y2 - Y1)/(double)(X2 - X1);
        double b = Y1 - a*X1;
        double yb[35], xb[35];
        int i = 0, index = 1;
        for ( double x = rE.left; x <= rE.right; x+=0.5)  {
            yb[++i] = a*x + b;
            xb[i] = x;
        }

        // находим минимальное расстояние до цетра курсора
        double min, d_2;
        min = (xb[1]-xc)*(xb[1]-xc) + (yb[1]-yc)*(yb[1]-yc);
        for (int j = 1; j<=i; j++) {
           d_2 = (xb[j]-xc)*(xb[j]-xc) + (yb[j]-yc)*(yb[j]-yc);
           if (d_2 < min) {
              index = j;
              min = d_2;
           }
        }
        pnt->x = round(xb[index]);
        pnt->y = round(yb[index]);
     }
  }

  return ret;
 }


void CInfinity :: Change(int Ox, int Oy)
 {
   X1 += Ox; Y1+=Oy;
   X2 += Ox; Y2+=Oy;
 }

void CInfinity :: Read(ifstream &fr)
 {
//  fr.read((char *)&whatIt, sizeof(whatIt));
  fr.read((char *)&X1, sizeof(X1));
  fr.read((char *)&Y1, sizeof(Y1));
  fr.read((char *)&X2, sizeof(X2));
  fr.read((char *)&Y2, sizeof(Y2));
  fr.read((char *)&PenColor, sizeof(PenColor));
  fr.read(NamePoint, 4);
  fr.read(NamePoint2, 4);
 }

void CInfinity :: Write(ofstream &fw)
 {
  fw.write((char *)&whatIt, sizeof(whatIt));
  fw.write((char *)&X1, sizeof(X1));
  fw.write((char *)&Y1, sizeof(Y1));
  fw.write((char *)&X2, sizeof(X2));
  fw.write((char *)&Y2, sizeof(Y2));
  fw.write((char *)&PenColor, sizeof(PenColor));
  fw.write(NamePoint, 4);
  fw.write(NamePoint2, 4);
 }

CDrawElement *CInfinity :: CreateCopy()
 {
  CInfinity *cd;
  cd = new CInfinity(X1, Y1, X2, Y2, NamePoint, NamePoint2, PenColor);
  return cd;
 }

BOOL CInfinity :: IsIntersection(CDrawElement *cde)
 {
  CPiece cdI(X1, Y1, X2, Y2, NamePoint, NamePoint2, PenColor);
  return cdI.IsIntersection(cde);
 }


// КЛАСС: CPiece ------------------------
CPiece :: CPiece (int _x1, int _y1, int _x2, int _y2,
                 char *sNP1, char *sNP2, COLORREF _cr)
		 : CDrawElement(_cr)
{
 X1 = _x1; Y1 = _y1;
 X2 = _x2; Y2 = _y2;
 Point1 = Point2 = NULL;
 lstrcpy(NamePoint,  sNP1);
 lstrcpy(NamePoint2, sNP2);
 whatIt = IT_PIECE;
 eArrange = IT_LEFT_BORDER;
 ePhisic = IT_HARD_BORDER;
 BegPsi = 0.0;
}

void CPiece :: Draw(HDC DC, double Scale)
{
  HPEN hPenLocal = CreatePen(PS_SOLID, (int)Scale, PenColor);
  HPEN hOrigPen  = SelectPen(DC, hPenLocal);

  int x_1 = ceil(X1*Scale);
  int y_1 = ceil(Y1*Scale);
  int x_2 = ceil(X2*Scale);
  int y_2 = ceil(Y2*Scale);
  MoveToEx(DC, x_1, y_1, NULL);
  LineTo(DC, x_2, y_2);

  SelectPen(DC, hOrigPen);
  DeletePen(hPenLocal);
}


BOOL CPiece :: Belong(int xc, int yc, POINT *pnt)
 {
  BOOL ret = IsPieceCircle(X1, Y1, X2, Y2, xc, yc, 3/*State.RPoint+3*/);

  if (ret && pnt!=NULL)  {

     pnt->x = xc;
     pnt->y = yc;

     RECT rE = { xc-3, yc-3, xc+3, yc+3 };
     if (X2 == X1) {
        if (X1 >= rE.left && X1 <= rE.right) {
           if (pnt!=NULL) { pnt->x = xc; pnt->y = yc; }
           ret = TRUE;
        }
     }
     else  {
        double a = (double)(Y2 - Y1)/(double)(X2 - X1);
        double b = Y1 - a*X1;
        double yb[35], xb[35];
        int i = 0, index = 1;
        for ( double x = rE.left; x <= rE.right; x+=0.2)  {
            yb[++i] = a*x + b;
            xb[i] = x;
        }

        // находим минимальное расстояние до цетра курсора
        double min, d_2;
        min = (xb[1]-xc)*(xb[1]-xc) + (yb[1]-yc)*(yb[1]-yc);
        for (int j = 2; j<=i; j++) {
           d_2 = (xb[j]-xc)*(xb[j]-xc) + (yb[j]-yc)*(yb[j]-yc);
           if (d_2 < min) {
              index = j;
              min = d_2;
           }
        }
        pnt->x = (int)xb[index] + 1;
        pnt->y = (int)yb[index] + 1;
     }
  }

  return ret;
 }


void CPiece :: Change(int Ox, int Oy)
 {
   X1 += Ox; Y1+=Oy;
   X2 += Ox; Y2+=Oy;
 }

void CPiece :: Read(ifstream &fr)
 {
//  fr.read((char *)&whatIt, sizeof(whatIt));
//  char ch; fr.read(&ch, sizeof(ch));
  fr.read((char *)&X1, sizeof(X1));
  fr.read((char *)&Y1, sizeof(Y1));
  fr.read((char *)&X2, sizeof(X2));
  fr.read((char *)&Y2, sizeof(Y2));
  fr.read((char *)&PenColor, sizeof(PenColor));
  fr.read(NamePoint, 4);
  fr.read(NamePoint2, 4);
  fr.read((char *)&eArrange, sizeof(eArrange));
  fr.read((char *)&ePhisic, sizeof(ePhisic));
  /*
  float fBpsi;
  fr.read((char *)&fBpsi, sizeof(fBpsi));
  BegPsi=fBpsi;
  */
  fr.read((char *)&BegPsi, sizeof(BegPsi));
  Point1=Point2=NULL;
 }

void CPiece :: Write(ofstream &fw)
 {
  fw.write((char *)&whatIt, sizeof(whatIt));
  fw.write((char *)&X1, sizeof(X1));
  fw.write((char *)&Y1, sizeof(Y1));
  fw.write((char *)&X2, sizeof(X2));
  fw.write((char *)&Y2, sizeof(Y2));
  fw.write((char *)&PenColor, sizeof(PenColor));
  fw.write(NamePoint, 4);
  fw.write(NamePoint2, 4);
  fw.write((char *)&eArrange, sizeof(eArrange));
  fw.write((char *)&ePhisic, sizeof(ePhisic));
  fw.write((char *)&BegPsi, sizeof(BegPsi));
}

CDrawElement *CPiece :: CreateCopy()
 {
  CDrawElement *cd;
  cd = new CPiece(X1, Y1, X2, Y2,  NamePoint, NamePoint2, PenColor);
  return cd;
 }

   
BOOL CPiece :: IsIntersection(CDrawElement *cde)
 {
  BOOL ret = FALSE;
  long int dX, dY, dX_, dY_;

  switch (cde->whatIt)  {
     case IT_POINT:  ret = cde->IsIntersection(this);
     break;
	  case IT_PIECE:{ CPiece *cdeI = (CPiece *)cde;
							ret = IsPiecePiece(cdeI->X1, cdeI->Y1,
													 cdeI->X2, cdeI->Y2,
													 X1, Y1, X2, Y2);
	  }break;
	  case IT_CIRCLE:{ CCircle *cdeC  = (CCircle *)cde;
							ret = IsPieceCircle(X1, Y1, X2, Y2,
													  cdeC->X1, cdeC->Y1, cdeC->R);
     }break;
  }
  return ret;
 }


// КЛАСС: CCircle ------------------------
CCircle :: CCircle(int _x1, int _y1, int _r,
                   char *sNP, COLORREF _cr, BOOL isIn) :
		   CDrawElement(_cr)
 {
  X1 = _x1; Y1 = _y1; R = _r;
  whatIt = IT_CIRCLE;
  lstrcpy(NamePoint,  sNP);
  eArrange = IT_LEFT_BORDER;
  ePhisic = IT_HARD_BORDER;
  BegPsi = 0.0;
  IsInterior=isIn;
 }

void CCircle :: Draw(HDC DC, double Scale)
{
  HPEN hPenLocal = CreatePen(PS_SOLID, (int)Scale, PenColor);
  HPEN hOrigPen  = SelectPen(DC, hPenLocal);

  SelectBrush(DC, GetStockBrush(NULL_BRUSH));

  int x_1 = ceil(X1*Scale);
  int y_1 = ceil(Y1*Scale);
  int r_  = ceil(R*Scale);
  Ellipse(DC, x_1-r_, y_1-r_, x_1+r_, y_1+r_);

  SelectPen(DC, hOrigPen);
  DeletePen(hPenLocal);
}


BOOL CCircle :: Belong(int xc, int yc, POINT *pnt)
 {
  BOOL ret = IsCircleCircle(X1, Y1, R, xc, yc, 3/*State.RPoint+1*/);

  if (ret && pnt!=NULL)  {

     pnt->x = xc;
     pnt->y = yc;

     RECT rE = { xc-3, yc-3, xc+3, yc+3 };

     double Ro  = (double)R;
     double xo  = (double)X1;
     double yo  = (double)Y1;
     int step = 1;

     for (double x=xc; x>=rE.left && x<=rE.right; x+=step)  {

         if (step>0) step++;
         else        step--;
         step *= -1;
          
         double b = -2.0*yo;
         double c = x*x - 2.0*x*xo + xo*xo - Ro*Ro + yo*yo;
         double D = b*b - 4*c;

         double yb1 = 0.0, yb2 = 0.0;
         if (D >= 0.0) {
            yb1 = (-b + sqrt(D))/2.0;
            yb2 = (-b - sqrt(D))/2.0;
            if (yb1 >= rE.top && yb1 <= rE.bottom)  {
               if (pnt!=NULL) { pnt->x = (int)x; pnt->y = (int)yb1; }
               ret = TRUE;
               break;
            }
            if (yb2 >= rE.top && yb2 <= rE.bottom)  {
               if (pnt!=NULL) { pnt->x = (int)x; pnt->y = (int)yb2; }
               ret = TRUE;
               break;
            }
         }
     }
  }
  return ret;
 }

void CCircle :: Change(int Ox, int Oy)
 {
  X1 += Ox; Y1+=Oy;
 }

void CCircle :: Read(ifstream &fr)
 {
//  fr.read((char *)&whatIt, sizeof(whatIt));
  fr.read((char *)&X1, sizeof(X1));
  fr.read((char *)&Y1, sizeof(Y1));
  fr.read((char *)&R, sizeof(R));
  fr.read((char *)&PenColor, sizeof(PenColor));
  fr.read(NamePoint, 4);
  fr.read((char *)&eArrange, sizeof(eArrange));
  fr.read((char *)&ePhisic, sizeof(ePhisic));
  /*
  float fBpsi;
  fr.read((char *)&fBpsi, sizeof(fBpsi));
  BegPsi=fBpsi;
  */
  fr.read((char *)&BegPsi, sizeof(BegPsi));
 }

void CCircle :: Write(ofstream &fw)
 {
  fw.write((char *)&whatIt, sizeof(whatIt));
  fw.write((char *)&X1, sizeof(X1));
  fw.write((char *)&Y1, sizeof(Y1));
  fw.write((char *)&R, sizeof(R));
  fw.write((char *)&PenColor, sizeof(PenColor));
  fw.write(NamePoint, 4);
  fw.write((char *)&eArrange, sizeof(eArrange));
  fw.write((char *)&ePhisic, sizeof(ePhisic));
  fw.write((char *)&BegPsi, sizeof(BegPsi));
 }

CDrawElement *CCircle :: CreateCopy()
 {
  CDrawElement *cd;
  cd = new CCircle(X1, Y1, R, NamePoint, PenColor);
  return cd;
 }


BOOL CCircle :: IsIntersection(CDrawElement *cde)
 {
  BOOL ret = 0;

  switch (cde->whatIt)  {
     case IT_POINT:  ret = cde->IsIntersection(this);
     break;
     case IT_PIECE:  ret = cde->IsIntersection(this);
     break;
     case IT_CIRCLE: CCircle *cdeC  = (CCircle *)cde;
                     ret = IsCircleCircle(cdeC->X1, cdeC->Y1, cdeC->R,
                                          X1, Y1, R);
     break;
  }
  return ret;
 }


// КЛАСС: CNotch ------------------------
CNotch :: CNotch(int _x1, int _y1, int _x2, int _y2,
                int _x3, int _y3,
                int _r, char *sNP, COLORREF _cr) : CDrawElement(_cr)
 {
  X1 = _x1; Y1 = _y1;
  X2 = _x2; Y2 = _y2;
  X3 = _x3; Y3 = _y3;
  lstrcpy(NamePoint, sNP);
  R = _r;
  whatIt = IT_NOTCH;
  eArrange = IT_LEFT_BORDER;
  ePhisic = IT_HARD_BORDER;
  BegPsi = 0.0;
 };

void CNotch :: Draw(HDC DC, double Scale)
{
  int x_1 = ceil(X1*Scale);
  int y_1 = ceil(Y1*Scale);
  int x_2 = ceil(X2*Scale);
  int y_2 = ceil(Y2*Scale);
  int x_3 = ceil(X3*Scale);
  int y_3 = ceil(Y3*Scale);
  int r_  = ceil(R*Scale);

  int xLeft = x_1-r_;
  int yTop  = y_1-r_;
  int xRight= x_1+r_;
  int yBot  = y_1+r_;

  HPEN hPenLocal = CreatePen(PS_SOLID, (int)Scale, PenColor);
  HPEN hOrigPen  = SelectPen(DC, hPenLocal);

  SelectBrush(DC, GetStockBrush(NULL_BRUSH));

  Arc(DC, xLeft, yTop, xRight, yBot, x_2, y_2, x_3, y_3);

  SelectPen(DC, hOrigPen);
  DeletePen(hPenLocal);
}


double CNotch :: GetAngle(int Xn, int Yn)
 {
  int Oy = 1000;
  int localYn = Oy - Yn;
  int localY1 = Oy - Y1;

  double x = (double)(Xn-X1);
  double y = (double)(localYn-localY1);
  double arctan = atan2(abs(y), abs(x));
  double Angle = 0.0;

       if ( x > 0 && y > 0 ) Angle = arctan;
  else if ( x < 0 && y > 0 ) Angle = M_PI - arctan;
  else if ( x < 0 && y < 0 ) Angle = M_PI + arctan;
  else if ( x > 0 && y < 0 ) Angle = 2*M_PI - arctan;

  return Angle;
 }


BOOL CNotch :: Belong(int x, int y, POINT *pnt)
 {
    CCircle cc(X1, Y1, R, NamePoint, BGIColor[WHITE]);
    BOOL ret = cc.Belong(x, y);
    return ret;
 }

void  CNotch :: Change(int Ox, int Oy)
 {
  X1 += Ox; Y1 += Oy;
  X2 += Ox; Y2 += Oy;
  X3 += Ox; Y3 += Oy;
 }

void CNotch :: Read(ifstream &fr)
 {
//   fr.read((char *)&whatIt, sizeof(whatIt));
  fr.read((char *)&X1, sizeof(X1));
  fr.read((char *)&Y1, sizeof(Y1));
  fr.read((char *)&X2, sizeof(X2));
  fr.read((char *)&Y2, sizeof(Y2));
  fr.read((char *)&X3, sizeof(X3));
  fr.read((char *)&Y3, sizeof(Y3));
  fr.read((char *)&R,  sizeof(R));
  fr.read((char *)&PenColor, sizeof(PenColor));
  fr.read(NamePoint, 4);
  fr.read((char *)&eArrange, sizeof(eArrange));
  fr.read((char *)&ePhisic, sizeof(ePhisic));
  /*
  float fBpsi;
  fr.read((char *)&fBpsi, sizeof(fBpsi));
  BegPsi=fBpsi;
  */
  fr.read((char *)&BegPsi, sizeof(BegPsi));
 }

void CNotch :: Write(ofstream &fw)
 {
  fw.write((char *)&whatIt, sizeof(whatIt));
  fw.write((char *)&X1, sizeof(X1));
  fw.write((char *)&Y1, sizeof(Y1));
  fw.write((char *)&X2, sizeof(X2));
  fw.write((char *)&Y2, sizeof(Y2));
  fw.write((char *)&X3, sizeof(X3));
  fw.write((char *)&Y3, sizeof(Y3));
  fw.write((char *)&R,  sizeof(R));
  fw.write((char *)&PenColor, sizeof(PenColor));
  fw.write(NamePoint, 4);
  fw.write((char *)&eArrange, sizeof(eArrange));
  fw.write((char *)&ePhisic, sizeof(ePhisic));
  fw.write((char *)&BegPsi, sizeof(BegPsi));
 }


CDrawElement *CNotch :: CreateCopy()
 {
  CDrawElement *cd;
  cd = new CNotch(X1, Y1, X2, Y2, X3, Y3, R, NamePoint, PenColor);
  return cd;
 }


 BOOL CNotch :: IsIntersection(CDrawElement *cde)
 {
  CCircle cc(X1, Y1, R, NamePoint, BGIColor[WHITE]);
  BOOL ret = cc.IsIntersection(cde);
  return ret;
 }



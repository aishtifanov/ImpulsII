// œ–Œ≈ “:     Ã‡ÚÂÏ‡ÚË˜ÂÒÍ‡ˇ ÏÓ‰ÂÎ¸ »Ãœ”À‹—
// ¬≈–—»ﬂ:     1.0
// ‘¿…À:       CDrawList.CPP
// ƒ¿“¿:       6/95
// ¿¬“Œ–:      ÿÚËÙ‡ÌÓ‚ ¿.».
// —Œƒ≈–∆¿Õ»≈:

#include "impulse.hpp"

BOOL  IsPiecePiece(int x1, int y1, int x2, int y2,
                 int x1_, int y1_, int x2_, int y2_);

BOOL  IsPieceCircle(int x1, int y1, int x2, int y2,
                   int x, int y, int R);

BOOL  IsCircleCircle(int x1, int y1, int R1,
                     int x2, int y2, int R2);
BOOL GetPiecePieceIntersect (CDrawElement *_DE[], int &xc, int &yc);
BOOL GetCirclePieceIntersect (CDrawElement *_DE[], int &xc, int &yc);
BOOL GetCircleCircleIntersect (CDrawElement *_DE[], int &xc, int &yc);

// double sign(double s) {  return s<0.0 ? -1.0 : 1.0; }

BOOL GetPiecePieceIntersect (CDrawElement *_DE[], int &xc, int &yc)
 {
  BOOL ret=FALSE;
  double A1, B1, C1;
  double A2, B2, C2;
  double D=0.0;
  int x1, y1, x2, y2;
  int x1_, y1_, x2_, y2_;

  CPiece *pc1 = (CPiece *)_DE[0];
  CPiece *pc1_ = (CPiece *)_DE[1];
  x1 = pc1->X1;   y1 = pc1->Y1;
  x2 = pc1->X2;   y2 = pc1->Y2;
  x1_ = pc1_->X1; y1_ = pc1_->Y1;
  x2_ = pc1_->X2; y2_ = pc1_->Y2;

  A1 = y2-y1;
  B1 = x1-x2;
  C1 = double(y1)*double((x2-x1)) - double(x1)*double((y2-y1));

  A2 = y2_-y1_;
  B2 = x1_-x2_;
  C2 = double(y1_)*double((x2_-x1_)) - double(x1_)*double((y2_-y1_));

  D = double(A1)*double(B2) - double(A2)*double(B1);
  if ( -0.00000001 < D && D < 0.00000001) ret=FALSE;
  else {
     double xo = (B1*C2 - B2*C1)/D;
     double yo = (A2*C1 - A1*C2)/D;
     xc = (int)ceil(xo);
     yc = (int)ceil(yo);
     ret= TRUE;
  }
  return ret;
 }


BOOL GetCirclePieceIntersect (CDrawElement *_DE[], int &xc, int &yc)
 {
  BOOL ret = FALSE;

  CCircle *cir1 = (CCircle *)_DE[0];
  CPiece *pc2 = (CPiece *)_DE[1];

  ret = IsPieceCircle(pc2->X1, pc2->Y1, pc2->X2, pc2->Y2,
                      cir1->X1, cir1->Y1, cir1->R);
  if (!ret) return ret;

  double Ro = (double)cir1->R;
  double xo = (double)cir1->X1;
  double yo = (double)cir1->Y1;

  double x1 = (double)pc2->X1 - xo;
  double y1 = (double)pc2->Y1 - yo;
  double x2 = (double)pc2->X2 - xo;
  double y2 = (double)pc2->Y2 - yo;

  double xi = xc - xo;
  double yi = yc - yo;
  double fa, fb, fc;
  double a, b, Eps = 0.01;
  double c, x, y, step;

  if (x1==x2) {
     y = sign(yi)*sqrt(Ro*Ro - x1*x1);
     xc = (int)ceil(x1 + xo);
     yc = (int)ceil(y + yo);
     ret = TRUE;
  }

  else if (y1==y2) {
     x = sign(xi)*sqrt(Ro*Ro - y1*y1);
     xc = (int)ceil(x + xo);
     yc = (int)ceil(y1 + yo);
     ret = TRUE;
  }

  else  {
     if (yi<0) {
        a = yi - 5;
        b = yi + 5;
        step = 0.1;
     }
     else {
        a = yi + 5;
        b = yi - 5;
        step = -0.1;
     }

     for(int j = 1; j<=100; j++) {
        if (fabs(a) >= Ro) a+=step;
        else break;
     }

     if (yi>0) {
       double tmp = a;
       a = b;
       b = tmp;
     }

     fa = (sign(xi)*sqrt(Ro*Ro - a*a) - x1)*(y2 - y1) - (a - y1)*(x2 - x1);
     fb = (sign(xi)*sqrt(Ro*Ro - b*b) - x1)*(y2 - y1) - (b - y1)*(x2 - x1);

     for (int i=1; i<1000; i++)  {
        c = (a+b)/2;
        fc = (sign(xi)*sqrt(Ro*Ro - c*c) - x1)*(y2 - y1) - (c - y1)*(x2 - x1);
        if (fa*fc <= 0.0) { b=c; fb=fc;}
        else { a=c; fa=fc; }

        if (fabs(b-a) < Eps)  {
           ret = TRUE;
           y = (a+b)/2;
           break;
        }
     }

     if (ret) {
        x = sign(xi)*sqrt(Ro*Ro - y*y);
        xc = (int)ceil(x + xo);
        yc = (int)ceil(y + yo);
     }

  }
  return ret;
}

double Func(double sig, double x, double Ro1, double Xo, double Yo, double Ro)
 {
  double _1 = sig*sqrt(Ro1*Ro1 - x*x) - Xo;
  double _2 = x - Yo;
  double func = _1*_1 + _2*_2 - Ro*Ro;
  return func;
 }

BOOL GetCircleCircleIntersect (CDrawElement *_DE[], int &xc, int &yc)
 {
  BOOL ret = FALSE;

  CCircle *cir1 = (CCircle *)_DE[0];
  CCircle *cir2 = (CCircle *)_DE[1];

  double Ro1 = (double)cir1->R;
  double Xo1 = (double)cir1->X1;
  double Yo1 = (double)cir1->Y1;

  double Ro2 = (double)cir2->R;
  double Xo2 = (double)cir2->X1 - Xo1;
  double Yo2 = (double)cir2->Y1 - Yo1;

  double xi = xc - Xo1;
  double yi = yc - Yo1;
  double fa, fb, fc;
  double a, b, Eps = 0.01;
  double c, x, y, step;

  if (yi<0) {
     a = yi - 5;
     b = yi + 5;
     step = 0.1;
  }
  else {
     a = yi + 5;
     b = yi - 5;
     step = -0.1;
  }

  for(int j = 1; j<=100; j++) {
     if (fabs(a) >= Ro1) a+=step;
     else break;
  }

  if (yi>0) {
    double tmp = a;
    a = b;
    b = tmp;
  }

  fa = Func(sign(xi), a, Ro1, Xo2, Yo2, Ro2);
  fb = Func(sign(xi), b, Ro1, Xo2, Yo2, Ro2);

  for (int i=1; i<1000; i++)  {
     c = (a+b)/2;
     fc = Func(sign(xi), c, Ro1, Xo2, Yo2, Ro2);
     if (fa*fc <= 0.0) { b=c; fb=fc;}
     else { a=c; fa=fc; }

     if (fabs(b-a) < Eps)  {
        ret = TRUE;
        y = (a+b)/2;
        break;
     }
  }

  if (ret) {
     x = sign(xi)*sqrt(Ro1*Ro1 - y*y);
     xc = (int)ceil(x + Xo1);
     yc = (int)ceil(y + Yo1);
  }

  return ret;
}


//  À¿——: CDrawList ------------------------
void CDrawList :: DrawAllList(HDC DC, double Scale)
 {
  CDrawElement *tElement;
  for (CDrawElement *element = (CDrawElement *)first; element; )  {
     tElement = (CDrawElement *)element;
     tElement->Draw(DC, Scale);
     element = (CDrawElement *)element->Next();
  }
 }

void CDrawList :: DrawElement(HDC DC, int index)
 {
  CDrawElement *tElement = (CDrawElement *)Get(index);
  tElement->Draw(DC);
 }

void CDrawList :: Remove(int index)
 {
  CDrawElement *tElement = (CDrawElement *)Get(index);
  Subtract(tElement);
 }


BOOL CDrawList :: FindAndRemove(HDC DC, int xc, int yc)
 {
   BOOL ret = FALSE;
   int OffX = 0;//State.currCanvas->Scroller->XPos*State.currCanvas->Scroller->XUnit;
   int OffY = 0;//State.currCanvas->Scroller->YPos*State.currCanvas->Scroller->YUnit;
   int xb = xc + OffX;
   int yb = yc + OffY;

         if (!Count()) ret = FALSE;
         else {

         CDrawElement *DrawElement;
         for (CDrawElement *element = (CDrawElement *)first; element; )  {
            DrawElement = (CDrawElement *)element;
            if (DrawElement->Belong(xb, yb))  {
               DrawElement->Change(-OffX, -OffY);
               DrawElement->PenColor = BGIColor[WHITE];
               DrawElement->Draw(DC);
               Subtract(DrawElement);
               ret = TRUE;
               goto end;
            }
            element = (CDrawElement *)element->Next();
         }
         }
   end:
     return ret;
 }



BOOL CDrawList :: FindPoint(int &xc, int &yc, char *np)
 {
  CDrawElement *DrawElement;
  DrawElement = FindGmtryObject(xc, yc);

  if (DrawElement == NULL) return FALSE;
  switch(DrawElement->whatIt)  {
     case IT_CIRCLE: //ptr = new CCircle(whatIt);
     break;
     case IT_NOTCH:  //ptr = new CNotch(whatIt);
     break;
     case IT_PIECE:  {
         CPiece *Piece = (CPiece *)DrawElement;
         long int dx = abs(xc - Piece->X1);
         long int dy = abs(yc - Piece->Y1);
         double dist = sqrt(dx*dx+dy*dy);
         double mindist = dist;
         dx = abs(xc - Piece->X2);
         dy = abs(yc - Piece->Y2);
         dist = sqrt(dx*dx+dy*dy);
         if (mindist > dist) {
             xc = Piece->X2; yc = Piece->Y2;
         }
         else  {
             xc = Piece->X1; yc = Piece->Y1;
         }
     break; }
  }
   return TRUE;
}


void CDrawList :: ChangeCoords(int Ox, int Oy)
 {
   CDrawElement *DrawElement;
   for (CDrawElement *element = (CDrawElement *)first; element; )  {
      DrawElement = (CDrawElement *)element;
      DrawElement->Change(Ox, Oy);
      element = (CDrawElement *)element->Next();
   }
 }

void CDrawList :: DeleteLast(HDC DC)
 {
  /*
  CDrawElement *DrawElement = (CDrawElement *)State.drawList->First();
  int OffX = State.currCanvas->Scroller->XPos*State.currCanvas->Scroller->XUnit;
  int OffY = State.currCanvas->Scroller->YPos*State.currCanvas->Scroller->YUnit;

  if (DrawElement) {
     DrawElement->Change(-OffX, -OffY);
     DrawElement->PenColor = BGIColor[WHITE];
     DrawElement->Draw(DC);
     Subtract(DrawElement);
  }
  */
 }


CDrawElement *CDrawList :: FindGmtryObject(int &xc, int &yc)
 {
   POINT pnt = { -1, -1 };
   CDrawElement *_DE = NULL, *DrawElement;

   if (!Count()) _DE = NULL;
   else {
      for (CDrawElement *element = (CDrawElement *)first; element; )  {
         DrawElement = (CDrawElement *)element;
         if (DrawElement->Belong(xc, yc, &pnt))
             _DE = DrawElement;

         element = (CDrawElement *)element->Next();
      }
   }
   return _DE;

 }

 /*
   int OffX = 0; //State.currCanvas->Scroller->XPos*State.currCanvas->Scroller->XUnit;
   int OffY = 0; // State.currCanvas->Scroller->YPos*State.currCanvas->Scroller->YUnit;
   int xb = (xc + OffX)/1; //State.ScaleShow;
   int yb = (yc + OffY)/1; //State.ScaleShow;
   POINT pnt = { -1, -1 }, AllPnt[10];
   CDrawElement *_DE = NULL, *DrawElement, *AllDE[10];
   int countDE=0, mini=0;

   if (!Count()) _DE = NULL;
   else {
      for (CDrawElement *element = (CDrawElement *)first; element; )  {
         DrawElement = (CDrawElement *)element;
         if (DrawElement->whatIt!=IT_POINT && DrawElement->Belong(xb, yb, &pnt))  {
             AllPnt[countDE].x = pnt.x - OffX;
             AllPnt[countDE].y = pnt.y - OffY;
             AllDE[countDE] = DrawElement;
             countDE++;
            // goto end;
         }
         element = (CDrawElement *)element->Next();
      }
      if (countDE==0) goto end;
      else if (countDE==1) mini = 0;
      else if (countDE>1) {
              double mindist=1000.0;
              for (int i=0; i<countDE; i++)  {
                 long int dx = abs(xc/State.ScaleShow - AllPnt[i].x);
                 long int dy = abs(yc/State.ScaleShow - AllPnt[i].y);
                 double dist = sqrt(dx*dx+dy*dy);
                 if (mindist > dist) {
                     mindist = dist;
                     mini = i;
                 }
              }
           }
      xc = AllPnt[mini].x - OffX;
      yc = AllPnt[mini].y - OffY;
      _DE =  AllDE[mini];

   }
   end:
   return _DE;
  */


void CDrawList :: Read(ifstream &fr)
 {
  Destroy();

  short cnt = 0;
  fr.read((char *)&cnt, sizeof(cnt));

  EWhatIt    whatIt;
  CDrawElement *ptr;
  for (short i=1; i<=cnt; i++)  {
      fr.read((char *)&whatIt, sizeof(whatIt));
      switch(whatIt)  {
         case IT_POINT:  ptr = new CPoint(whatIt);
         break;
         case IT_CIRCLE: ptr = new CCircle(whatIt);
         break;
         case IT_NOTCH:  ptr = new CNotch(whatIt);
         break;
         case IT_PIECE:  ptr = new CPiece(whatIt);
         break;
         case IT_INFINITY: ptr = new CInfinity(whatIt);
         break;
         default: return;
      }
      ptr->Read(fr);
      Add(ptr);
  }
 }



void CDrawList :: Write(ofstream &fw)
 {
  short cnt = Count();
  fw.write((char *)&cnt, sizeof(cnt));

  CDrawElement *tElement;
  for (CDrawElement *element = (CDrawElement *)first; element; )  {
     tElement = (CDrawElement *)element;
     tElement->Write(fw);
     element = (CDrawElement *)element->Next();
  }
 }


BOOL CDrawList :: FindIntersection(int &xc, int &yc)
 {
   BOOL ret = FALSE;
   int OffX = 0; //State.currCanvas->Scroller->XPos*State.currCanvas->Scroller->XUnit;
   int OffY = 0; //State.currCanvas->Scroller->YPos*State.currCanvas->Scroller->YUnit;
   int xb = xc + OffX;
   int yb = yc + OffY;
   CDrawElement *_DE[2];
   int countDE = 0;
   CDrawElement *DrawElement;

   _DE[0] = NULL;
   _DE[1] = NULL;
   if (!Count()) _DE[0] = NULL; //ret = FALSE;
   else {
      for (CDrawElement *element = (CDrawElement *)first; element; )  {
         DrawElement = (CDrawElement *)element;
         if (DrawElement->whatIt!=IT_POINT) {
            if (DrawElement->Belong(xb, yb)) {
               _DE[countDE++] = DrawElement;
               if (countDE>1) goto end;
            }
         }
         element = (CDrawElement *)element->Next();
      }
    }
   end:
   if (_DE[0] == NULL || _DE[1] == NULL) ret = FALSE;
   else {
      switch (_DE[0]->whatIt)  {
         case IT_CIRCLE: case IT_NOTCH:
             switch(_DE[1]->whatIt)  {
                case IT_CIRCLE: case IT_NOTCH:
                   ret = GetCircleCircleIntersect (_DE, xb, yb);
                break;
                case IT_PIECE:
                   ret = GetCirclePieceIntersect (_DE, xb, yb);
                break;
             }
         break;
         case IT_PIECE:
             switch(_DE[1]->whatIt)  {
					 case IT_CIRCLE: case IT_NOTCH: {
						 CDrawElement *tmpDE = _DE[0];
						 _DE[0] = _DE[1];
						 _DE[1] = tmpDE;
						 ret = GetCirclePieceIntersect (_DE, xb, yb);
					 }break;
                case IT_PIECE:
                   ret = GetPiecePieceIntersect (_DE, xb, yb);
                break;
             }
         break;
     }
     xc = xb - OffX;
     yc = yb - OffY;
   }

  return ret;
 }


CDrawElement **CDrawList :: GetArray()
{
 int count = Count();
 int i = 1, j;
 int newCount = 0;

 CDrawElement **cdeArray = new CDrawElement *[count+2];

 CDrawElement *element;
 for (element = (CDrawElement *)first; element;
     element = (CDrawElement *)element->Next()) {
     if (element->whatIt == IT_INFINITY) element->whatIt = IT_PIECE;
     cdeArray[i++] = (CDrawElement *)element;
 }

 newCount = i-1;

 cdeArray[0] = NULL;
 cdeArray[newCount+1] = NULL;

 return cdeArray;
}



BOOL CDrawList :: FindNamePoint(int &xc, int &yc, char *np)
 {
   BOOL ret = FALSE;
   if (!Count()) ret = FALSE;
   else {
      CDrawElement *DrawElement;
      for (CDrawElement *element = (CDrawElement *)first; element; )  {
         DrawElement = (CDrawElement *)element;
         if (DrawElement->whatIt==IT_POINT &&
             xc == DrawElement->X1 && yc == DrawElement->Y1)  {
             lstrcpy(np, DrawElement->NamePoint);
             ret = TRUE;
             goto end;
         }
         element = (CDrawElement *)element->Next();
      }
   }
   end: return ret;
 }


void CDrawList :: SetNameObject()
 {
  CDrawElement *cdeTHIS;
  for (cdeTHIS = (CDrawElement *)first;
       cdeTHIS;
       cdeTHIS = (CDrawElement *)cdeTHIS->Next())   {
        switch(cdeTHIS->whatIt)  {
            case IT_CIRCLE:
               FindNamePoint(cdeTHIS->X1, cdeTHIS->Y1, cdeTHIS->NamePoint);
            break;
            case IT_NOTCH:
               FindNamePoint(cdeTHIS->X1, cdeTHIS->Y1, cdeTHIS->NamePoint);
            break;
				case IT_PIECE:{
					CPiece *cdeP = (CPiece *)cdeTHIS;
					FindNamePoint(cdeP->X1, cdeP->Y1, cdeP->NamePoint);
					FindNamePoint(cdeP->X2, cdeP->Y2, cdeP->NamePoint2);
				}break;
				case IT_INFINITY:{
					CInfinity *cdeI = (CInfinity *)cdeTHIS;
					FindNamePoint(cdeI->X1, cdeI->Y1, cdeI->NamePoint);
					FindNamePoint(cdeI->X2, cdeI->Y2, cdeI->NamePoint2);
				}break;
            default:
            break;
         }
  }
}


void CDrawList :: GetRectPicture(RECT *r)
 {
  CDrawElement *element;
  r->left = 32000;
  r->top  = 32000;
  r->right= 0;
  r->bottom=0;
  for (element = (CDrawElement *)first; element;
       element = (CDrawElement *)element->Next())  {
	  switch(element->whatIt)  {
		 case IT_POINT:
			if (element->X1 < r->left)  r->left = element->X1;
			if (element->X1 > r->right) r->right = element->X1;
			if (element->Y1 < r->top)   r->top = element->Y1;
			if (element->Y1 > r->bottom) r->bottom = element->Y1;
		 break;
		 case IT_CIRCLE: {
			CCircle *cdeC = (CCircle *)element;
			int xr = cdeC->X1-cdeC->R;
			int yr = cdeC->Y1-cdeC->R;
			if (xr < r->left)   r->left = xr;
			if (yr < r->top)    r->top = yr;

			xr = cdeC->X1+cdeC->R;
			yr = cdeC->Y1+cdeC->R;
				if (xr > r->right)  r->right = xr;
				if (yr > r->bottom) r->bottom = yr;
			}
			break;
			case IT_NOTCH: {
				CNotch *cdeN = (CNotch *)element;
				int xr = cdeN->X1-cdeN->R;
				int yr = cdeN->Y1-cdeN->R;
				if (xr < r->left)   r->left = xr;
				if (yr < r->top)    r->top = yr;

				xr = cdeN->X1+cdeN->R;
				yr = cdeN->Y1+cdeN->R;
				if (xr > r->right)  r->right = xr;
				if (yr > r->bottom) r->bottom = yr;
			}
			break;
			case IT_PIECE: {
				CPiece *cdeP = (CPiece *)element;
				if (cdeP->X1 < r->left)  r->left = cdeP->X1;
				if (cdeP->X1 > r->right) r->right = cdeP->X1;
				if (cdeP->Y1 < r->top)   r->top = cdeP->Y1;
				if (cdeP->Y1 > r->bottom) r->bottom = cdeP->Y1;
				if (cdeP->X2 < r->left)  r->left = cdeP->X2;
				if (cdeP->X2 > r->right) r->right = cdeP->X2;
				if (cdeP->Y2 < r->top)   r->top = cdeP->Y2;
				if (cdeP->Y2 > r->bottom) r->bottom = cdeP->Y2;
			}
			break;
			case IT_INFINITY:  {
				CInfinity *cdeI = (CInfinity *)element;
				if (cdeI->X1 < r->left)  r->left = cdeI->X1;
				if (cdeI->X1 > r->right) r->right = cdeI->X1;
				if (cdeI->Y1 < r->top)   r->top = cdeI->Y1;
				if (cdeI->Y1 > r->bottom) r->bottom = cdeI->Y1;
				if (cdeI->X2 < r->left)  r->left = cdeI->X2;
				if (cdeI->X2 > r->right) r->right = cdeI->X2;
				if (cdeI->Y2 < r->top)   r->top = cdeI->Y2;
				if (cdeI->Y2 > r->bottom) r->bottom = cdeI->Y2;
		 }
			break;
			default:
			break;
	  }
 }
 /*
 r->left -= 10;
 r->right += 10;
 r->top -= 10;
 r->bottom += 30;
 */
}

BOOL CDrawList :: GetCoordsBorder(EBorderPhisic eBP, int &X1, int &X2, int Num)
 {
  int currNum=1;
  CDrawElement *element;
  for (element = (CDrawElement *)first; element;
      element = (CDrawElement *)element->Next())  {
      if (element->whatIt == IT_PIECE) {
         CPiece *cdeP = (CPiece *)element;
         if (cdeP->ePhisic == eBP) {
            X1 = cdeP->X1;
			X2 = cdeP->X2;
            if (currNum==Num) return TRUE;
            else currNum++;
         }
      }
 }
 return FALSE;
}

void CDrawList :: DelAllPoint()
 {
  CDrawElement *tElement;
  for (CDrawElement *element = (CDrawElement *)first; element; )  {
	 tElement = (CDrawElement *)element;
	 element = (CDrawElement *)element->Next();
	 if (tElement->whatIt==IT_POINT) Subtract(tElement);
  }
 }


void CDrawList :: PrintAllPoint()
 {
  FILE *f = fopen("D:\\drawlist.txt", "w");

  for (CDrawElement *element = (CDrawElement *)first; element; )  {
		switch(element->whatIt)  {
		 case IT_POINT:
			fprintf (f, "IT_POINT: %d %d %s\n", element->X1, element->Y1, element->NamePoint);
		 break;
		 case IT_CIRCLE: {
			CCircle *cdeC = (CCircle *)element;
			fprintf (f, "IT_CIRCLE: %d %d %d %s\n", cdeC->X1, cdeC->Y1, cdeC->R, cdeC->NamePoint);
			}
		 break;
		 case IT_NOTCH:

		 break;
		 case IT_PIECE:  {
			CPiece *cde = (CPiece *)element;
			fprintf (f, "IT_PIECE: %d %d %d %d %s\n", cde->X1, cde->Y1, cde->X2, cde->Y2, cde->NamePoint);
			/*
			if (cde->X1 > 10 ) {
				cde->X1 *= 3;
			}
			if (cde->X2 > 10 ) {
				cde->X2 *= 3;
			}
			if (cde->Y1 > 10 ) {
				cde->Y1 *= 3;
			}
			if (cde->Y2 > 10 ) {
				cde->Y2 *= 3;
			}
			*/

			if (cde->X1 > 30 && cde->X1 < 200) {
				cde->X1 += 20;
			}
			if (cde->X2 > 30 && cde->X2 < 200) {
				cde->X2 += 20;
			}


/*
			if (cde->Y1 > 400 && cde->Y1 < 450) {
				cde->Y1 -= 50;
			}
			if (cde->Y2 > 400 && cde->Y2 < 450) {
				cde->Y2 -= 50;
			}
*/
		   //	cde->X1 += 200;
			// cde->X2 += 200;
		}
		 break;
		 case IT_INFINITY:	{
			CInfinity *cde = (CInfinity *)element;
			fprintf (f, "IT_INFINITY: %d %d %d %d %s\n", cde->X1, cde->Y1, cde->X2, cde->Y2, cde->NamePoint);
		}
			break;
			default:
			break;
	  }
	 element = (CDrawElement *)element->Next();
  }
   fclose(f);
   DelAllPoint();
 }

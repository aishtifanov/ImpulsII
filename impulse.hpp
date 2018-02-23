// ПРОЕКТ:     Математическая 2D-модель волновых процессов
// ВЕРСИЯ:     2.0
// ФАЙЛ:       Impulse.HPP
// ДАТА:       11/94; 07/98
// АВТОР:      Штифанов А.И.
// СОДЕРЖАНИЕ: Описание классов и структур данных

#ifndef _IMPULSEH_
#define _IMPULSEH_

#include <vcl\vcl.h>
#include <windows.h>
#include <windowsx.h>
#include <iostream.h>
#include <fstream.h>
#include <iomanip.h>
#include <math.h>

#define max(a,b)    (((a) > (b)) ? (a) : (b))
#define min(a,b)    (((a) < (b)) ? (a) : (b))
#define sign(x) ((x) > 0 ? 1 : ((x) == 0 ? 0 : (-1)))

// ПЕРЕЧИСЛЕНИЕ БАЗОВЫХ ЦВЕТОВ
enum EColors {
    BLACK,          /* dark colors */
    BLUE,
    GREEN,
    CYAN,
    RED,
    MAGENTA,
    BROWN,
	LIGHTGRAY,
    DARKGRAY,           /* light colors */
    LIGHTBLUE,
    LIGHTGREEN,
    LIGHTCYAN,
    LIGHTRED,
    LIGHTMAGENTA,
    YELLOW,
    WHITE
};

 // КОДЫ ГРАФИЧЕСКИХ ОБЪЕКТОВ
enum EWhatIt {
   IT_NO,
   IT_POINT,
   IT_CIRCLE,
   IT_NOTCH,
   IT_PIECE,
   IT_INFINITY,
   IT_CANVAS,
   IT_TASK,
   IT_ANALYS,
   IT_SELECT
};

enum EWhatShow {
   SHOW_ARRANGE_BORDER,
   SHOW_PHISIC_BORDER,
   SHOW_EQULINES_PSI,
   SHOW_EQULINES_U3,
   SHOW_EQULINES_V,
   SHOW_EQULINES_U,
   SHOW_3D_SURFACE,
   SHOW_CHANNEL,
   SHOW_EQULINES_J,
   SHOW_CALCULATE
};


// СТРУКТУРА: Описывает графический прямоугольник
struct SRect {
   int x, y,  // координата верхнего левого угла
       w, h,  // ширина и высота прямоугольника
	   r, b;  // координата правого нижнего угла
   void operator= (SRect &rSrc)  {
       x = rSrc.x;   y = rSrc.y;
       w = rSrc.w;   h = rSrc.h;
       r = x + w;    b = y + h;
   }
/*   
   void SetSRect(TWindowAttr &rSrc)  {
	   x = rSrc.X;   y = rSrc.Y;
       w = rSrc.W;   h = rSrc.H;
       r = x + w;    b = y + h;
   }
   void GetSRect(TWindowAttr &rSrc)  {
       rSrc.X = x;  rSrc.Y = y;
       rSrc.W = w;  rSrc.H = h;
   }
*/
   void InitRect(int _x, int _y, int _w, int _h)  {
      x = _x;   y = _y;   w = _w;   h = _h;
      r = _x + _w;
      b = _y + _h;
   }

};

extern COLORREF  BGIColor2[];
extern COLORREF  BGIColor[];
extern COLORREF  GmtryColor[];

#include "model.hpp"
#include "clist.hpp"
#include "tmodconf.h"

extern int                 jEmax[];

LPSTR GetFileName(LPSTR FilePath);
HMENU AppendBitmapWindowMenu(HMENU hMenu, UINT numItem);
int   round(double number);
BOOL  FindColon(ifstream &fr);
void setBGIColor2invert(int num);
void setBGIColor2(int num);

#endif


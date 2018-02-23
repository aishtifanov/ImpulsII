// ПРОЕКТ:     Математическая 2D-модель волновых процессов
// ВЕРСИЯ:     1.0
// ФАЙЛ:       CList.HPP
// ДАТА:       25.02.95
// АВТОР:      Штифанов А.И.
// СОДЕРЖАНИЕ: Описание классов, организующих спимок
//             геометрических примитиво

#ifndef CListHPP
#define CListHPP

class CElement  {
   protected:
	CElement *previous, *next;
        friend class CList;
   public:
	CElement(void) : previous(NULL), next(NULL) { }
	virtual ~CElement(void) { }
	CElement *Next(void) { return (next); }
	CElement *Previous(void) { return (previous); }
};


class CDrawElement :  public CElement {
  public:
         friend class CDrawList;
         short        X1, Y1;
         COLORREF   PenColor;
         EWhatIt    whatIt;
         char       NamePoint[4];
         EBorderArrange eArrange;
         EBorderPhisic  ePhisic;
         double 	BegPsi;

         CDrawElement(void) { };

         CDrawElement(EWhatIt _wIt)   {
            whatIt = _wIt;
         };

         CDrawElement(COLORREF _cr)   {
            PenColor = _cr;
            whatIt = IT_NO;
         };
         ~CDrawElement(void) { };
         virtual void Draw(HDC DC, double Scale = 1.0) { };
         virtual BOOL Belong(int xc, int yc, POINT *pnt = NULL) { return FALSE; };
         virtual void Change(int Ox, int Oy) { };
         virtual void Read(ifstream &fr)  { };
         virtual void Write(ofstream &fw)  { };
         virtual BOOL IsIntersection(CDrawElement *cde)  {  return FALSE; };
         virtual CDrawElement *CreateCopy(void)  { return NULL; };
        // задание граничной линии
         virtual void Set(SKnot *aKnots, EBorderArrange eArrange,
                          EBorderPhisic  ePhisic, double Value)  { };
         void    SetWhitePen() { PenColor = BGIColor[WHITE]; }
};

class CPoint : public CDrawElement  {
  public:
         short        R;

         CPoint(EWhatIt _wIt) : CDrawElement(_wIt) { }
	 CPoint(int _x1, int _y1, COLORREF _cr, char _NP[], int _R) : CDrawElement(_cr)
           { X1 = _x1; Y1 = _y1; whatIt = IT_POINT;
             lstrcpy(NamePoint, _NP);  R=_R;};
         ~CPoint(void) {};
         virtual void Draw(HDC DC, double Scale = 1.0);
         virtual BOOL Belong(int xc, int yc, POINT *pnt = NULL);
         virtual void Change(int Ox, int Oy); 
         virtual void Read(ifstream &fr);
         virtual void Write(ofstream &fw);
         virtual BOOL IsIntersection(CDrawElement *cde);
         virtual CDrawElement *CreateCopy(void);
         void    DrawThickPoint(HDC DC, double Scale=1.0);
};

class CInfinity : public CDrawElement
{
public:
         short  X2, Y2;
         char NamePoint2[4];
          
         CInfinity (EWhatIt _wIt) : CDrawElement(_wIt) { }
         CInfinity (int _x1, int _y1, int _x2, int _y2,
                    char *sNP1, char *sNP2, COLORREF _cr) :
                   CDrawElement(_cr)  {
                   X1 = _x1; Y1 = _y1;
                   X2 = _x2; Y2 = _y2;
                   lstrcpy(NamePoint,  sNP1);
                   lstrcpy(NamePoint2, sNP2);
                   whatIt = IT_INFINITY;
         };
         ~CInfinity() {};
         virtual void Draw(HDC DC, double Scale = 1.0);
         virtual BOOL Belong(int xc, int yc, POINT *pnt = NULL);
         virtual void Change(int Ox, int Oy);
         virtual void Read(ifstream &fr);
         virtual void Write(ofstream &fw);
         virtual BOOL IsIntersection(CDrawElement *cde);
         virtual CDrawElement *CreateCopy(void);

};

class CPiece : public CDrawElement  {
public:
         short  X2, Y2;
         char   NamePoint2[4];
         CPoint *Point1;
         CPoint *Point2;
public:
         CPiece (EWhatIt _wIt) : CDrawElement(_wIt) { }
         CPiece (int _x1, int _y1, int _x2, int _y2,
                 char *sNP1, char *sNP2, COLORREF _cr);
         ~CPiece() {};
         virtual void Draw(HDC DC, double Scale = 1.0);
         virtual BOOL Belong(int xc, int yc, POINT *pnt = NULL);
         virtual void Change(int Ox, int Oy);
         virtual void Read(ifstream &fr);
         virtual void Write(ofstream &fw);
         virtual BOOL IsIntersection(CDrawElement *cde);
         virtual CDrawElement *CreateCopy(void);
};


class CCircle :  public CDrawElement  {
public:
         short  R;
         BOOL IsInterior;
public:
         CCircle(EWhatIt _wIt) : CDrawElement(_wIt) { }
         CCircle(int _x1, int _y1, int _r, char *sNP, COLORREF _cr, BOOL isIn=TRUE);
         ~CCircle () {}
         virtual void Draw(HDC DC, double Scale = 1.0);
         virtual BOOL Belong(int xc, int yc, POINT *pnt=NULL);
         virtual void Change(int Ox, int Oy);
         virtual void Read(ifstream &fr);
         virtual void Write(ofstream &fw);
         virtual BOOL IsIntersection(CDrawElement *cde);
         virtual CDrawElement *CreateCopy(void);
};

class CNotch : public CDrawElement
{
public:
         short  R;
         short  X2, Y2, X3, Y3;
         BOOL IsInterior;
public:
         CNotch(EWhatIt _wIt) : CDrawElement(_wIt) { }
         CNotch(int _x1, int _y1, int _x2, int _y2,
                int _x3, int _y3,
                int _r, char *sNP, COLORREF _cr);
         ~CNotch() {};
         virtual void Draw(HDC DC, double Scale = 1.0);
         virtual BOOL Belong(int xc, int yc, POINT *pnt=NULL);
         virtual void Change(int Ox, int Oy);
         virtual void Read(ifstream &fr);
         virtual void Write(ofstream &fw);
         virtual BOOL IsIntersection(CDrawElement *cde);
         virtual CDrawElement *CreateCopy(void);
         double  GetAngle(int Xn, int Yn);
};


class  CList   {
protected:
        CElement *first, *last, *current;
public:
        CList(void) : first(NULL), last(NULL), current(NULL) { }
	virtual ~CList(void) { Destroy(); }

        CElement *First(void) { return (first); }
	CElement *Last(void) { return (last); }
	CElement *Current(void) { return (current); }

	CElement *Add(CElement *newElement);
	CElement *Add(CElement *element, CElement *newElement);
        CElement *Subtract(CElement *element);

	void Destroy(void);
        int  Count(void);
	int  Index(const CElement *element);
	CElement *Get(int index);

	CList &operator+(CElement *element) { Add(element); return (*this); }
	CList &operator-(CElement *element) { Subtract(element); return (*this); };
};


class CDrawList : public CList  {
      HWND hWin;
   public:
      CDrawList () : CList () {}
      ~CDrawList() { };
      void DrawAllList(HDC DC, double Scale = 1.0);
      void DrawElement(HDC DC, int index);
      void Remove(int index);
      BOOL FindAndRemove(HDC DC, int xc, int yc);
      BOOL FindPoint(int &xc, int &yc, char *np);
      CDrawElement *FindGmtryObject(int &xc, int &yc);
      BOOL FindIntersection(int &xc, int &yc);
      void ChangeCoords(int Ox, int Oy);
      void SetListWindow(HWND hW) { hWin = hW; }
      void DeleteLast(HDC DC);
      void Read(ifstream &fr);
      void Write(ofstream &fw);
      CDrawElement **GetArray();
      void SetNameObject();
      BOOL FindNamePoint(int &xc, int &yc, char *np);
      void GetRectPicture(RECT *r);
      BOOL GetCoordsBorder(EBorderPhisic eBP, int &X1, int &X2, int Num);
	  void DelAllPoint();
	  void PrintAllPoint();
};

#endif

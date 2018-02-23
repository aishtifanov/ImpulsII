// ПРОЕКТ:     Математическая модель ИМПУЛЬС
// ВЕРСИЯ:     1.0
// ФАЙЛ:       Model.HPP
// ДАТА:       8/93; 7/96
// АВТОР:      Штифанов А.И.
// СОДЕРЖАНИЕ: Описание объектов математической модели.

// inline int sign (int x)  {  return ((x<0) ? -1 : ((x==0) ? 0 : 1));  }

// const int MASK_ARRANGE = 0x000F;
// const int MASK_PHISICS = 0x0F00;
#define FIELDLENGHT 10

// Признаки расположения границы
enum EBorderArrange {
   IT_LEFT_BORDER      = 'l',
   IT_RIGHT_BORDER     = 'r',
   IT_TOP_BORDER       = 't',
   IT_BOTTOM_BORDER    = 'b',
   IT_NO_BORDER        = 'n'
};

// Признаки расчета границы
enum EBorderPhisic {
   IT_HARD_BORDER      = 'h',  // производная на границе равна 0
   IT_FREE_BORDER      = 'f',  // на границе сохраняется постоянный потенциал
   IT_INPUT_BORDER     = 'i',  // границ входа
   IT_OUTPUT_BORDER    = 'o',  // граница выхода
   IT_POINT_CENTER     = 'p',  // расчитываемая точка лежит между границами
   IT_SYMMETRIC        = 's',  // расчитываемая точка лежит между границами
   IT_MODIFY           = 'm',  // граница для модифицированной явной схемы
   IT_UNDEFINE         = 'u'   // граница не опрделена
};

struct SParameterInDlg {
   char sStep[FIELDLENGHT];
   char sDensity[FIELDLENGHT];
   char sSoundSpeed[FIELDLENGHT];
   char sBeginPressing[FIELDLENGHT];
   char sTimeMax[FIELDLENGHT];
//   char sTimeTetta[FIELDLENGHT];
   char sTimeSwitch[FIELDLENGHT];
   char sEpsilon[FIELDLENGHT];
   char sTtotal[FIELDLENGHT];
   char sOmega[FIELDLENGHT];
   char sQEquLine[FIELDLENGHT];
   char sAutoSaveIter[FIELDLENGHT];
};

struct SParameter {
   double h;   // шаг по координате (0.001).
   double Rau; // плотность газа (1.293 кг/м3).
   double a0;  // скорость звука в газе (331.6 м/с).
   double P0;  // начальное давление (2000000);
   double tmax;  //  время изменения давления в источнике (15 мкс).
   double tp;  //  время изменения давления в источнике (15 мкс).
   double Ttotal; // время расчета в мкс
//   double Psi; // значение потенциала на источнике
//   double dPsi;// "толщина" эквипотенциальной линии
   double Eps; // погрешность вычислений (0.01)
   double w;   // ускоряющий коэффициент [1..2]
   int   QEquLine; // количество выводимых эквипотенциальных линий
   int   AutoSaveIter; //  шаг записи результатов расчета в файл (10).

	////// struct SParamCalc
   BOOL bLeftRight;
   BOOL bRightLeft;
   BOOL bFromCenter;
   BOOL bToCenter;
   BOOL bTwoWhile;
   int  xCoord;
   int  yCoord;
   int  Ntrub;
   int  Delitel;

   ///// struct SChoicePlane
   BOOL Model2D;
   BOOL ModelFiZR;
   int  NumLevel;
   // BOOL KindBorder;
   // BOOL KindSign;
   // BOOL KindEquiLine;
};

/*
struct SParameter {
   double Rau; // плотность газа (1.293 кг/м3).
   double a0;  // скорость звука в газе (331.6 м/с).
   double P0;  // начальное давление (2000000);
//---------------------------------------------------
   double h;   // шаг по координате (0.001)в м.
   double dt;  // шаг по времени (1e-7) в с.
//---------------------------------------------------
   double tmax;   //  время изменения давления в источнике (15 мкс).
   double tetta;  //  время изменения давления в источнике (15 мкс).
   double tp;     //  время переключения разностной схемы (15 мкс).
   double Ttotal; // время расчета в мкс
//---------------------------------------------------
   double Eps; // погрешность вычислений (0.01)
   double w;   // ускоряющий коэффициент [1..2]
//---------------------------------------------------
   int   QEquLine; // количество выводимых эквипотенциальных линий
   int   AutoSaveIter; //  шаг записи результатов расчета в файл (10).
};
*/



struct SReport {
   char sTitle[100];
   char sWidth[15];
   char sHeight[15];
   char sDate[15];
   char sTime[15];
   char sNameReport[100];
};

struct SPeriodInDlg {
   char sFrom[FIELDLENGHT];
   char sTo[FIELDLENGHT];
   char sStep[FIELDLENGHT];
   char sTime[FIELDLENGHT];
};


struct SState {
   // TDrawTool  *DrawTool;
   HBITMAP    BitMap;
   int        PenSize;
   COLORREF   PenColor;
   int        RPoint;
   // CDrawList  *drawList;
   // TCanvas    *currCanvas;
   HFONT      hFont;
   double     ScaleShow;
   BOOL       OSnapPoint;
};


struct SKnot {
   float  Psi; // используется для расчета потенциала при решении ур-я Лапласа
   double U1;  // значение потенциала на k-1 шаге
   double U2;  // значение потенциала на k шаге
   double U3;  // значение потенциала на k+1 шаге
   double D1;  // значение потенциала на k-1 шаге (дополнительный слой)
   double D2;  // значение потенциала на k шаге   (дополнительный слой)
   double D3;  // значение потенциала на k+1 шаге (дополнительный слой)
   float  V;   // скорость
   float  Ep;  // потенциальная энергия
   float  Ek;  // кинетическая энергия
   float  P1;  // давление P1
   float  P2;  // давление P2
   EBorderArrange eArrange;
   EBorderPhisic  ePhisic;
   COLORREF color;
   int    NumEquLine;
   float  J;  // ток
   char   Reserved[44];
};


// Класс, описывающий агрегат в котором расчитывается
// электромагнитное поле
class CModel2D {
   public:
      DWORD  N,  // количество точек по Ox
             M;  // количество точек по Oy
	  DWORD  N1;  // величина, равная N+1

      //int Ox, Oy, MaxX, MinY;
      RECT rModel;
      double Interval;

      SKnot /*huge*/ *Knots; // двумерный динамический массив,
                         // предназначенный для хранения значения
                         // узлов сетки
      HGLOBAL hMemKnots; // дискриптор блока памяти для U

      // геометрические парметры границы
      friend class CDrawList;
      friend class CDrawElement;
      CDrawList *listBorder;

      double      MaxValue_Psi;
      double      MaxValue_V;
      double      MaxValue_U;
	  double      MaxValue_J;

	  char        WhatCalc;
   public:
      SParameter Parameters;
      char   IMPFileName[80]; // имя файла с исходными данными

      CModel2D(CDrawList *alistBorder)  { Init(alistBorder); }
      ~CModel2D() { Destroy(); }

      void Init(CDrawList *alistBorder);
      void Organise();
      void Destroy();

	  // установка граничных условий
      void Set(int type);
      void SetParameters();
      void SetParametersAsStr();
      void SetZero();
      void SetLineBorder(CDrawElement *DrawElement);
      void SetCircleBorder(CDrawElement *DrawElement);
      void SetNotchBorder(CDrawElement *DrawElement);
      // расчет уравнения Лапласа по методу Либмана
      int  CalcLaplas(void);
      int  ProgonkaLibmana(void);
      // расчет волнового уравнения
      int  CalcWaveProcess(void);
      void CalcSwitch(void);
      void CalcSwitchDopSloy(void);
      int  CalcPressure(DWORD CurrIter);

      void ShowArrangeBorder(HDC hDC, double ScaleShow);
      void ShowPhisicBorder(HDC hDC, double ScaleShow);
	  void ShowEquLines(HDC hDC, EWhatShow ews,double MaxValue,
						double deltaF, double ScaleShow,int CurrPersent);
	  void ShowChannel(HDC hDC, EWhatShow ews,double MaxValue,
						double deltaF, double ScaleShow,int CurrPersent);
	  void ShowEquLines_V(HDC hDC, EWhatShow ews,double MaxValue,
						double deltaF, double ScaleShow,int CurrPersent);

      void SetMaxValue();
      void BeginShowWave();
      void ShowWave(DWORD CurrIter);
      void EndShowWave();
      void Show3DSurface(HDC hDC);
      // чтение модели из файла
      int Read(ifstream &fr);
      // запись модели в бинарный файл
      void Write(ofstream &fw);
      // запись модели в текстовый файл
	  void Write(char *FileName, EWhatShow ews);

      int  ReadJ(ifstream &fr);
      void WriteJ(ofstream &fw);

      double GetMaxFunction(double a, double b, int whatFunc);
      double GetTau();
      double GetPt(double t, int whatFunc);
      BOOL   GetInputBorder(int &X1, int &X2, int Num);
};

// extern CModel2D  *Models[];
extern SState              State;
extern SReport             Report;
extern SPeriodInDlg        Period;
// extern SParamCalc          ParamCalc;
// extern SChoicePlane        ChoicePlane;
extern SParameterInDlg     dataParameter;
extern CModel2D  		   *MathModel;
extern HGLOBAL   		   HGModels[];
extern int       		   icA;
extern int       		   activeModel;



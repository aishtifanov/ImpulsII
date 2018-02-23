// ������:     �������������� ������ �������
// ������:     1.0
// ����:       Model.HPP
// ����:       8/93; 7/96
// �����:      �������� �.�.
// ����������: �������� �������� �������������� ������.

// inline int sign (int x)  {  return ((x<0) ? -1 : ((x==0) ? 0 : 1));  }

// const int MASK_ARRANGE = 0x000F;
// const int MASK_PHISICS = 0x0F00;
#define FIELDLENGHT 10

// �������� ������������ �������
enum EBorderArrange {
   IT_LEFT_BORDER      = 'l',
   IT_RIGHT_BORDER     = 'r',
   IT_TOP_BORDER       = 't',
   IT_BOTTOM_BORDER    = 'b',
   IT_NO_BORDER        = 'n'
};

// �������� ������� �������
enum EBorderPhisic {
   IT_HARD_BORDER      = 'h',  // ����������� �� ������� ����� 0
   IT_FREE_BORDER      = 'f',  // �� ������� ����������� ���������� ���������
   IT_INPUT_BORDER     = 'i',  // ������ �����
   IT_OUTPUT_BORDER    = 'o',  // ������� ������
   IT_POINT_CENTER     = 'p',  // ������������� ����� ����� ����� ���������
   IT_SYMMETRIC        = 's',  // ������������� ����� ����� ����� ���������
   IT_MODIFY           = 'm',  // ������� ��� ���������������� ����� �����
   IT_UNDEFINE         = 'u'   // ������� �� ���������
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
   double h;   // ��� �� ���������� (0.001).
   double Rau; // ��������� ���� (1.293 ��/�3).
   double a0;  // �������� ����� � ���� (331.6 �/�).
   double P0;  // ��������� �������� (2000000);
   double tmax;  //  ����� ��������� �������� � ��������� (15 ���).
   double tp;  //  ����� ��������� �������� � ��������� (15 ���).
   double Ttotal; // ����� ������� � ���
//   double Psi; // �������� ���������� �� ���������
//   double dPsi;// "�������" ����������������� �����
   double Eps; // ����������� ���������� (0.01)
   double w;   // ���������� ����������� [1..2]
   int   QEquLine; // ���������� ��������� ����������������� �����
   int   AutoSaveIter; //  ��� ������ ����������� ������� � ���� (10).

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
   double Rau; // ��������� ���� (1.293 ��/�3).
   double a0;  // �������� ����� � ���� (331.6 �/�).
   double P0;  // ��������� �������� (2000000);
//---------------------------------------------------
   double h;   // ��� �� ���������� (0.001)� �.
   double dt;  // ��� �� ������� (1e-7) � �.
//---------------------------------------------------
   double tmax;   //  ����� ��������� �������� � ��������� (15 ���).
   double tetta;  //  ����� ��������� �������� � ��������� (15 ���).
   double tp;     //  ����� ������������ ���������� ����� (15 ���).
   double Ttotal; // ����� ������� � ���
//---------------------------------------------------
   double Eps; // ����������� ���������� (0.01)
   double w;   // ���������� ����������� [1..2]
//---------------------------------------------------
   int   QEquLine; // ���������� ��������� ����������������� �����
   int   AutoSaveIter; //  ��� ������ ����������� ������� � ���� (10).
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
   float  Psi; // ������������ ��� ������� ���������� ��� ������� ��-� �������
   double U1;  // �������� ���������� �� k-1 ����
   double U2;  // �������� ���������� �� k ����
   double U3;  // �������� ���������� �� k+1 ����
   double D1;  // �������� ���������� �� k-1 ���� (�������������� ����)
   double D2;  // �������� ���������� �� k ����   (�������������� ����)
   double D3;  // �������� ���������� �� k+1 ���� (�������������� ����)
   float  V;   // ��������
   float  Ep;  // ������������� �������
   float  Ek;  // ������������ �������
   float  P1;  // �������� P1
   float  P2;  // �������� P2
   EBorderArrange eArrange;
   EBorderPhisic  ePhisic;
   COLORREF color;
   int    NumEquLine;
   float  J;  // ���
   char   Reserved[44];
};


// �����, ����������� ������� � ������� �������������
// ���������������� ����
class CModel2D {
   public:
      DWORD  N,  // ���������� ����� �� Ox
             M;  // ���������� ����� �� Oy
	  DWORD  N1;  // ��������, ������ N+1

      //int Ox, Oy, MaxX, MinY;
      RECT rModel;
      double Interval;

      SKnot /*huge*/ *Knots; // ��������� ������������ ������,
                         // ��������������� ��� �������� ��������
                         // ����� �����
      HGLOBAL hMemKnots; // ���������� ����� ������ ��� U

      // �������������� �������� �������
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
      char   IMPFileName[80]; // ��� ����� � ��������� �������

      CModel2D(CDrawList *alistBorder)  { Init(alistBorder); }
      ~CModel2D() { Destroy(); }

      void Init(CDrawList *alistBorder);
      void Organise();
      void Destroy();

	  // ��������� ��������� �������
      void Set(int type);
      void SetParameters();
      void SetParametersAsStr();
      void SetZero();
      void SetLineBorder(CDrawElement *DrawElement);
      void SetCircleBorder(CDrawElement *DrawElement);
      void SetNotchBorder(CDrawElement *DrawElement);
      // ������ ��������� ������� �� ������ �������
      int  CalcLaplas(void);
      int  ProgonkaLibmana(void);
      // ������ ��������� ���������
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
      // ������ ������ �� �����
      int Read(ifstream &fr);
      // ������ ������ � �������� ����
      void Write(ofstream &fw);
      // ������ ������ � ��������� ����
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



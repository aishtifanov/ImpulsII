// ПРОЕКТ:     Математическая модель ИМПУЛЬС
// ВЕРСИЯ:     1.0
// ФАЙЛ:       Mod_Data.CPP
// ДАТА:       8/96
// АВТОР:      Штифанов А.И.
// СОДЕРЖАНИЕ: Functions:

#include "impulse.hpp"

extern double Ot, Ou;

// чтение из IMP-файла
int CModel2D :: Read(ifstream &fr)
 {
  HCURSOR prev = SetCursor(LoadCursor(0, IDC_WAIT));

  // чтение констант
  fr.read((char *)&N, sizeof(N));
  fr.read((char *)&M, sizeof(M));

  // fr.read((char *)&Parameters, sizeof(Parameters));

  // SetParametersAsStr();

  // чтение расчитанных данных
  DWORD j, jN1, i;
  int sz = sizeof (Knots[1]);
  for (j = 0; j <= M; j++)  {
     jN1 = j*N1;
     for (i = 0; i <= N; i++)
        fr.read((char *)(Knots+jN1+i), sz);
  }

  // расчет скоростей
  for (j=0; j<=M; j++)   {
      jN1 = j*N1;
      for (i = 0; i<=N; i++)   {
          switch (Knots[jN1+i].ePhisic)  {
              case IT_POINT_CENTER:
                 double Vx = (Knots[jN1+i+1].Psi - Knots[jN1+i].Psi)/Parameters.h;
                 double Vy = (Knots[(j+1)*N1+i].Psi - Knots[jN1+i].Psi)/Parameters.h;
                 Knots[jN1+i].V = sqrt(Vx*Vx + Vy*Vy);
              break;
         }
     }
  }


  SetCursor(prev);

  SetMaxValue();
  /*
  if (winIMPULSE->ShowEquV != NULL) {
	  winIMPULSE->ShowEquV->MaxValue = MaxValue_V;
	  winIMPULSE->ShowEquV->QEquLine = MaxValue_V/winIMPULSE->ShowEquV->deltaF;
  }
  */
 }


// запись в IMP-файл 
void CModel2D :: Write(ofstream &fw)
 {
  HCURSOR prev = SetCursor(LoadCursor(0, IDC_WAIT));
  // запись констант
  fw.write((char *)&N, sizeof(N));
  fw.write((char *)&M, sizeof(M));

  // fw.write((char *)&Parameters, sizeof(Parameters));

  // запись расчитанных данных
  DWORD j, jN1, i;
  int sz = sizeof (Knots[1]);
  for (j = 0; j <= M; j++)  {
     jN1 = j*N1;
     for (i = 0; i <= N; i++)
        fw.write((char *)(Knots+jN1+i), sz);
  }
  SetCursor(prev);
 }

void CModel2D :: Write(char *FileName, EWhatShow ews)
 {
  ofstream fw(FileName);

  DWORD j, jN1, i;
  for (j = M; j>0; j--)   {
     jN1 = j*N1;
     for (i = 0; i<=N; i++)   {
        if (Knots[jN1+i].ePhisic == IT_UNDEFINE)  {
           fw.width(6);
           fw.setf(ios::right, ios::adjustfield);
           fw << "XXXXXX";
        }
        else   {
           fw.width(6);
           fw.setf(ios::right, ios::adjustfield);
           fw << setprecision(3);
           switch(ews)  {
              case SHOW_EQULINES_U3: fw << Knots[jN1+i].U3;
              break;
              case SHOW_EQULINES_V:  fw << Knots[jN1+i].V;
              break;
           }
        }
     }
     fw << endl;
  }
  fw.close();
 }


double CModel2D :: GetMaxFunction(double a, double b, int whatFunc)
 {
  double ret=0.0, Pt;
  SetParameters();

  double tau = GetTau();

  for (double t=a; t<=b; t+=tau) {
     Pt = GetPt(t,whatFunc);
     if (ret < Pt)  ret = Pt;
  }

  return ret;
 }

double CModel2D :: GetTau()
 {
  double tau;
  if (Parameters.Model2D)
     tau = Parameters.Eps;
     // tau = Parameters.h/(Parameters.a0*sqrt(2.0));
     // tau = Parameters.h/Parameters.a0;
  else
     tau = Parameters.h/Parameters.a0;
  return tau;
 }


double CModel2D :: GetPt(double t, int whatFunc)
 {
  double  ret=0.0;

  double P0 = Parameters.P0;
  double tmax = Parameters.tmax;
  double Rau= Parameters.Rau;
  double tau = Parameters.h/Parameters.a0;
  double P0Exp1Rau = (P0*exp(1))/Rau;
  double tetta = Parameters.w*1e-6;
  double tp = Parameters.tp;

  switch(whatFunc)  {
     case 1: if (t<tp)
                ret = P0*exp(-t/tetta);
                // ret = P0*(t/tetta)*exp(1 - t/tetta);
             else {
             
                double P_T = P0*((t-tp)/tmax)*exp(1 - (t-tp)/tmax);
                // double P_T = P0*(t/tmax)*exp(1 - t/tmax);
                // ret = (P_T*tau)/Rau;
                ret = P_T;
             }
     break;
     case 2:if (t<tp) {
               // ret = P0Exp1Rau*(tetta-(tetta+t)*exp(-t/tetta));
               ret = P0*tetta/Rau*(1-exp(-t/tetta));
               Ou = ret;
            }
            else  {
               Ot = t - tp;
               ret = P0Exp1Rau*(tmax-(tmax+Ot)*exp(-Ot/tmax));
            // ret = P0Exp1Rau*(tmax-(tmax+t)*exp(-t/tmax));
               ret += Ou;
            }
     break;
  }
  return ret;
 }

BOOL CModel2D :: GetInputBorder(int &X1, int &X2, int Num)
 {
  BOOL ret;
  ret = listBorder->GetCoordsBorder(IT_INPUT_BORDER, X1, X2, Num);
  if (ret) {
     X1    = (X1 - rModel.left) / Interval;
     X2    = (X2 - rModel.left) / Interval;
  }
  return ret;
 }


int CModel2D :: ReadJ(ifstream &fr)
 {
  HCURSOR prev = SetCursor(LoadCursor(0, IDC_WAIT));

  // чтение констант
  int NJ, MJ;
  fr.read((char *)&NJ, sizeof(int));
  fr.read((char *)&MJ, sizeof(int));

  if (NJ!=N && MJ!=M) MessageBox(Application->Handle,
                      "Габаритные размеры не совпадают.",
                      "Модель", MB_OK | MB_ICONSTOP);
  else {
     // чтение расчитанных данных
     DWORD j, jN1, i;
     float fJ;
     int sz = sizeof (fJ);
     for (j = 0; j <= M; j++)  {
        jN1 = j*N1;
        for (i = 0; i <= N; i++) {
           fr.read((char *)&fJ, sz);
           Knots[jN1+i].J = fJ;
        }
     }
  }

  SetCursor(prev);
 }


// запись в IMP-файл 
void CModel2D :: WriteJ(ofstream &fw)
 {
  HCURSOR prev = SetCursor(LoadCursor(0, IDC_WAIT));
  // запись констант
  fw.write((char *)&N, sizeof(N));
  fw.write((char *)&M, sizeof(M));

  // запись расчитанных данных
  DWORD j, jN1, i;
  float fJ;
  int sz = sizeof (fJ);
  for (j = 0; j <= M; j++)  {
     jN1 = j*N1;
     for (i = 0; i <= N; i++) {
        fJ = Knots[jN1+i].Psi;
        fw.write((char *)&fJ, sz);
     }
  }
  SetCursor(prev);
 }

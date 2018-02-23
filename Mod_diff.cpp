// ПРОЕКТ:     Математическая модель ИМПУЛЬС
// ВЕРСИЯ:     1.0
// ФАЙЛ:       Mod_Diff.CPP
// ДАТА:       8/96
// АВТОР:      Штифанов А.И.
// СОДЕРЖАНИЕ: Решение уравнение Лапласа методом Либмана

#include <stdio.h>
#include <dos.h>

#include "impulse.hpp"
#include "TShowBorder.h"

int  jEmax[500];
static int  asIt;

// расчет уравнения Лапласа по методу Либмана
int CModel2D :: CalcLaplas()
 {
  GetAsyncKeyState(VK_ESCAPE);
  char str[60];

  // константы, используемые при расчете значений потенциала
  double _w_4 = Parameters.w / 4.0;
  double _1_w= 1-Parameters.w;

  double d;
  double unew, resid;
  double Epsilon = Parameters.Eps;
  asIt = Parameters.AutoSaveIter;

  DWORD index5, index4, index6, index8, index2;
  DWORD jN1;

  DWORD i, j;
  // итерационный метод Либмана
  int CurrIter = 0;  // счетчик итераций
  SetParameters();

  struct time tBeg, tEnd;

  gettime(&tBeg);

  wsprintf(str, "%2d:%02d:%02d.%02d",
		  tBeg.ti_hour, tBeg.ti_min,
		  tBeg.ti_sec, tBeg.ti_hund);
 AnsiString AText = AnsiString(str);
 // CalcWindow->StatusBar1->Panels->Items[0]->Text = AText;
 ShowCalculate->StatusBar1->Panels->Items[0]->Text = AText;

 ShowCalculate->QEquLine = Parameters.QEquLine;
 
  do  {
	 Application->ProcessMessages();

	 d = 0.0; // наибольшая разность значений неизвестных,
			  // полученных при последовательных итерациях
	 // циклы по всем точкам сетки
	 for (j = 0; j<=M; j++)   {
		Application->ProcessMessages();
		jN1 = j*N1;
		for (i = 0; i<=N; i++)   {
		   Application->ProcessMessages();
		   index5 = jN1+i;
		   switch (Knots[index5].ePhisic)  {
			  // расчет центральных точек
			  case IT_POINT_CENTER:
				 index6 = jN1+(i+1);
				 index4 = jN1+(i-1);
				 index2 = (j-1)*N1+i;
                 index8 = (j+1)*N1+i;
                 unew = _w_4 * (Knots[index8].Psi + Knots[index2].Psi +
                                Knots[index4].Psi + Knots[index6].Psi)
                        + _1_w * Knots[index5].Psi;
                 if (unew<0.0) resid = 0.0;
                 resid = fabs(unew - Knots[index5].Psi);
                 if (resid > d) d = resid;
                 Knots[index5].Psi = unew;
              break;

              // расчет жестких границ
              case IT_HARD_BORDER:
	         switch (Knots[index5].eArrange)  {
                    // левая граница
                    case IT_LEFT_BORDER:
						   index6 = jN1+(i+1);
						   Knots[index5].Psi = Knots[index6].Psi;
					break;
					// правая граница
					case IT_RIGHT_BORDER:
						   index4 = jN1+(i-1);
						   Knots[index5].Psi = Knots[index4].Psi;
					break;
					// верхняя граница
					case IT_TOP_BORDER:
						   index2 = (j-1)*N1+i;
						   Knots[index5].Psi = Knots[index2].Psi;
					break;
					// нижняя граница
					case IT_BOTTOM_BORDER:
						   index8 = (j+1)*N1+i;
						   Knots[index5].Psi = Knots[index8].Psi;
                }
              break;


              case IT_SYMMETRIC:
	         switch (Knots[index5].eArrange)  {
                    // левая граница
                    case IT_LEFT_BORDER:
                       index6 = jN1+(i+1);
                       index4 = index6;
                       switch (Knots[index6].eArrange) {
						  case IT_TOP_BORDER:
                               index2 = (j-1)*N1+i;
                               index8 = index2;
                          break;
                          case IT_BOTTOM_BORDER:
                               index8 = (j+1)*N1+i;
                               index2 = index8;
                          break;
                          default:
                               index2 = (j-1)*N1+i;
                               index8 = (j+1)*N1+i;
                       }
                    break;
                    // правая граница
                    case IT_RIGHT_BORDER:
                       index4 = jN1+(i-1);
                       index6 = index4;
                       switch (Knots[index4].eArrange) {
		          		  case IT_TOP_BORDER:
                               index2 = (j-1)*N1+i;
                               index8 = index2;
                          break;
                          case IT_BOTTOM_BORDER:
                               index8 = (j+1)*N1+i;
                               index2 = index8;
                          break;
                          default:
                               index2 = (j-1)*N1+i;
                               index8 = (j+1)*N1+i;
                       }   
                    break;
                    // верхняя граница
                    case IT_TOP_BORDER:
                       index2 = (j-1)*N1+i;
                       index8 =  index2;
                       switch (Knots[index2].eArrange) {
                          case IT_LEFT_BORDER:
                               index6 = jN1+(i+1);
                               index4 = index6;
                          break;
                          case IT_RIGHT_BORDER:
                               index4 = jN1+(i-1);
                               index6 = index4;
                          break;
                          default:
							   index6 = jN1+(i+1);
                               index4 = jN1+(i-1);
                       }
                    break;
                    // нижняя граница
                    case IT_BOTTOM_BORDER:
                       index8 = (j+1)*N1+i;
                       index2 = index8;
                       switch (Knots[index8].eArrange)  {
                          case IT_LEFT_BORDER:
                               index6 = jN1+(i+1);
                               index4 = index6;
                          break;
                          case IT_RIGHT_BORDER:
                               index4 = jN1+(i-1);
                               index6 = index4;
                          break;
                          default:
							   index6 = jN1+(i+1);
                               index4 = jN1+(i-1);
                       }
                    break;
                }

                 unew = _w_4 * (Knots[index8].Psi + Knots[index2].Psi +
                                Knots[index4].Psi + Knots[index6].Psi)
                        + _1_w * Knots[index5].Psi;
                 if (unew<0.0) resid = 0.0;
                 resid = fabs(unew - Knots[index5].Psi);
                 if (resid > d) d = resid;
                 Knots[index5].Psi = unew;
              break;

              case IT_UNDEFINE:
              case IT_FREE_BORDER:
			  case IT_INPUT_BORDER:
              case IT_OUTPUT_BORDER:
              break;

              default:
                  wsprintf(str, "Неопознанный признак: i=%d, j=%d pr=%c", i, j, Knots[index5].ePhisic);
                  MessageBox(Application->Handle, str, "Ошибка расчета",
                                 MB_OK | MB_ICONEXCLAMATION);

           }  // switch
        }  // for i
	 } // for j
//   winIMPULSE->CalcWin->arrEps[CurrIter] = d;
   CurrIter++;
   if (GetAsyncKeyState(VK_ESCAPE)) {
	  //winIMPULSE->CalcWin->cntME = CurrIter;
	  break;
   }
   if (CurrIter == asIt)  {
	   //  winIMPULSE->CalcWin->DrawEps(d);
	   wsprintf(str, "%2d", CurrIter);
	   AText = AnsiString(str);
	   // CalcWindow->StatusBar1->Panels->Items[0]->Text = AText;
		ShowCalculate->StatusBar1->Panels->Items[1]->Text = AText;

	 //  winIMPULSE->StatusWin->TextStatusOut( STATUS_CURSOR, str, FALSE);
	 //  ModelConf->StatusBar1->Panels->Items[0]->Text = str;
	   sprintf(str, "%.6f", d);
	//   winIMPULSE->StatusWin->TextStatusOut( STATUS_CURSOR2, str, TRUE);
	   ShowCalculate->StatusBar1->Panels->Items[2]->Text = str;

	  asIt += Parameters.AutoSaveIter;
	  ShowCalculate->Image->Invalidate();
   }
   Application->ProcessMessages();
  }
  // проверка на сходимость
  while(d > Epsilon);

  gettime(&tEnd);
  /*
  wsprintf(str, "%2d:%02d:%02d.%02d",
          tEnd.ti_hour, tEnd.ti_min,
          tEnd.ti_sec, tEnd.ti_hund);
  */
  if (tEnd.ti_hund < tBeg.ti_hund) tBeg.ti_sec++;
  if (tEnd.ti_sec < tBeg.ti_sec) tBeg.ti_min++;
  if (tEnd.ti_min < tBeg.ti_min) tBeg.ti_hour++;

  tBeg.ti_hund = 100-tBeg.ti_hund+tEnd.ti_hund;
  tBeg.ti_sec  =  60-tBeg.ti_sec+tEnd.ti_sec;
  tBeg.ti_min  =  60-tBeg.ti_min+tEnd.ti_min;
  tBeg.ti_hour =  24-tBeg.ti_hour+tEnd.ti_hour;

  if (tBeg.ti_hund >= 100)tBeg.ti_hund = tBeg.ti_hund-100;
  if (tBeg.ti_sec >= 60)  tBeg.ti_sec = tBeg.ti_sec-60;
  if (tBeg.ti_min >= 60)  tBeg.ti_min = tBeg.ti_min-60;
  if (tBeg.ti_hour >= 24) tBeg.ti_hour = tBeg.ti_hour-24;

  wsprintf(str, "%2d:%02d:%02d.%02d",
          tBeg.ti_hour, tBeg.ti_min,
          tBeg.ti_sec, tBeg.ti_hund);
  // winIMPULSE->StatusWin->TextStatusOut( STATUS_INSTRUMENT, str, TRUE);
  ShowCalculate->StatusBar1->Panels->Items[3]->Text = str;

  // winIMPULSE->CalcWin->cntME = CurrIter;

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

  // расчет максимальной напряженности
  /*
  long int Emax=0L, Vk;
  for (i = 0; i<=N; i++)   {
     jEmax[i] = 0;
     Emax=0L;
     // for (j=M; j>1; j--)   {
     for (j=0; j<=M; j++)   {
         jN1 = j*N1;
         switch (Knots[jN1+i].ePhisic)  {
              case IT_POINT_CENTER:
                 Vk = (long int)ceil(Knots[jN1+i].V*10000.0);
                 if (Vk > Emax) {
                    Emax=Vk;
                    jEmax[i]=j;
                 }
              break;
         }
     }
  }
  */
  float Emax=0.0, Vk;
  for (j = 0; j<=M; j++)   {
     jEmax[j] = 0;
     Emax=0.0;
     jN1 = j*N1;
     for (i=0; i<=N; i++)   {
         switch (Knots[jN1+i].ePhisic)  {
              case IT_POINT_CENTER:
                 Vk = Knots[jN1+i].V;
                 if (Vk > Emax) {
                    Emax=Vk;
                    jEmax[j]=i;
                 }
              break;
         }
     }
  }
  // расчет потециальной энергии в абсолютных  координатах // относительных величинах
  double e0 = 8.85e-12;
  for (j=0; j<=M; j++)   {
      jN1 = j*N1;
      for (i = 0; i<=N; i++)   {
          switch (Knots[jN1+i].ePhisic)  {
              case IT_POINT_CENTER:
                   double V_2  = Knots[jN1+i].V*Knots[jN1+i].V;
		   Knots[jN1+i].Ep = e0*V_2/2.0;
              break;
         }
     }
  }
  
  /*
  double max = Knots[1].Ep;
  for (j=0; j<=M; j++)   {
      jN1 = j*N1;
      for (i = 0; i<=N; i++)   {
          switch (Knots[jN1+i].ePhisic)  {
              case IT_POINT_CENTER:
                   if (Knots[jN1+i].Ep > max) max = Knots[jN1+i].Ep;
              break;
         }
     }
  }

  for (j=0; j<=M; j++)   {
	  jN1 = j*N1;
	  for (i = 0; i<=N; i++)   {
		  switch (Knots[jN1+i].ePhisic)  {
			  case IT_POINT_CENTER:
				   Knots[jN1+i].Ep = Knots[jN1+i].Ep / max;
			  break;
		 }
	 }
  }
  */

  SetMaxValue();

//  Write("energy.txt", SHOW_EQULINES_V);
  ShowCalculate->Refresh();
  
  return 1;
 }



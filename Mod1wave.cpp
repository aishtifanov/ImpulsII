// ������:     �������������� ������ �������
// ������:     1.0
// ����:       Mod_Wave.CPP
// ����:       1/97
// �����:      �������� �.�.
// ����������: ������� ��������� ��������� ������� ��������

#include "impulse.hpp"
#include <stdio.h>
#include <dos.h>
#include "TShowBorder.h"
#include "TCalcWindow.h"
#include "TPressOne.h"
#include "TPressWin.h"

static char   FileName[15];
static DWORD index5, index4, index6, index8, index2;
static DWORD jN1;
static int  asIt;
static double a0, P0, h, tmax, tetta, tp, Rau, tau, Ttotal,
              t, Coeff, P_T, P0Exp1Rau, h2_a2t2, _2h_at, a2t2_h2;
static DWORD i, j;
static char str[50];
static BOOL FlagSwitch = TRUE;
double Ot, Ou;
long int iFindPoint, jFindPoint;
unsigned long int RealTime;

// ������ ��������� ���������
int CModel2D :: CalcWaveProcess()
 {
  GetAsyncKeyState(VK_ESCAPE);
  SetParameters();

  struct time tBeg, tEnd;

  gettime(&tBeg);

  wsprintf(str, "%2d:%02d:%02d.%02d", tBeg.ti_hour, tBeg.ti_min,
									  tBeg.ti_sec,  tBeg.ti_hund);
  AnsiString AText = AnsiString(str);
  ShowCalculate->StatusBar1->Panels->Items[0]->Text = AText;

  BeginShowWave();

  asIt = Parameters.AutoSaveIter;
  a0 = Parameters.a0;
  P0 = Parameters.P0;
  h =  Parameters.h;
  tmax = Parameters.tmax;
  tetta = Parameters.w*1e-6;
  tp = Parameters.tp;
  Rau= Parameters.Rau;
  Ttotal = Parameters.Ttotal; // tau*Parameters.NumberIteration;

  if (Parameters.Model2D)
    //tau = h/(a0*sqrt(2.0));
    // tau = h/a0;
     tau = Parameters.Eps;
  else
    tau = h/a0;

  t = tau;
  h2_a2t2 = (h*h)/(a0*a0*tau*tau);
  _2h_at = 2.0+h2_a2t2;
  a2t2_h2 = (a0*a0*tau*tau)/(h*h);

  P_T;
  P0Exp1Rau = (P0*exp(1))/Rau;
  FlagSwitch = TRUE;

  iFindPoint = (Parameters.xCoord - rModel.left)/Interval;
  jFindPoint = (rModel.bottom - Parameters.yCoord)/Interval;


  gcvt(tau, 5, str);
  AText = AnsiString(str);
  ShowCalculate->StatusBar1->Panels->Items[1]->Text = AText;

  DWORD CurrIter = 0;  // ������� ��������
  DWORD CentrI = N/2, CentrJ = M/2;

  while (t < Ttotal)  {

	 Application->ProcessMessages();

     if (GetAsyncKeyState(VK_ESCAPE)) {
        EndShowWave();

		CalcWindow->cntME = CurrIter-1;
		CalcP1->cntME = CurrIter-1;
		CalcP2->cntME = CurrIter-1;
		CalcEp->cntME = CurrIter-1;
		CalcEk->cntME = CurrIter-1;
		PressOne->cntME = CurrIter-1;

		return 0;
	 }
	 // ������������� �����
	 if (Parameters.bTwoWhile) {
		/*
		for (j = 0; j<=M; j++)  {
			jN1 = j*N1;
			signed long int istep=0;
			while (0<=(istep+CentrI) && (istep+CentrI)<=N)  {
				i = istep+CentrI;
				if (Knots[jN1+i].ePhisic == IT_POINT_CENTER)
					CalcSwitch();

			if(istep==0) istep++;
				else if(istep>0) istep=istep*(-1);
				else { istep=istep*(-1); istep++; }
			}
		}
		*/

		for (j = 0; j<=M; j++) {
		   jN1 = j*N1;
		   for (i = 0; i<=N; i++)
			  if (Knots[jN1+i].ePhisic == IT_POINT_CENTER)
				 CalcSwitch();
		}

		for (j = 0; j<=M; j++) {
		   jN1 = j*N1;
		   for (i = 0; i<=N; i++)
//              if (Knots[jN1+i].eArrange != IT_NO_BORDER)
			  if (Knots[jN1+i].ePhisic != IT_POINT_CENTER &&
				  Knots[jN1+i].ePhisic != IT_UNDEFINE)
				 CalcSwitch();
		}

		// ������ ��������������� ����
		for (j = 0; j<=M; j++) {
		   jN1 = j*N1;
		   for (i = 0; i<=N; i++)
//              if (Knots[jN1+i].eArrange != IT_NO_BORDER)
			  if (Knots[jN1+i].ePhisic != IT_POINT_CENTER &&
				  Knots[jN1+i].ePhisic != IT_UNDEFINE &&
				  Knots[jN1+i].ePhisic != IT_INPUT_BORDER)
				 CalcSwitchDopSloy();
		}

		for (j = 0; j<=M; j++) {
		   jN1 = j*N1;
		   for (i = 0; i<=N; i++)
			  if (Knots[jN1+i].ePhisic == IT_POINT_CENTER ||
				  Knots[jN1+i].ePhisic == IT_INPUT_BORDER)
				 CalcSwitchDopSloy();
		}

	 }
	 // 1-� ������� ����� ����� �������
	 else if (Parameters.bLeftRight) {
		for (j = 0; j<=M; j++) {
		   jN1 = j*N1;
		   for (i = 0; i<=N; i++)
			   CalcSwitch();
		}
	 }
	 // 2-� ������� ����� ������ ������
	 else if (Parameters.bRightLeft) {
		for (j = 0; j<=M; j++) {
		   jN1 = j*N1;
		   for (i = N; i>0; i--)
			   CalcSwitch();
		}
	 }
	 // 3-� ������� ����� �� ������
	 else if (Parameters.bFromCenter) {
		for (j = 0; j<=M; j++)  {
			jN1 = j*N1;
			signed long int istep=0;
			while (0<=(istep+CentrI) && (istep+CentrI)<=N)  {
				i = istep+CentrI;

				CalcSwitch();

			if(istep==0) istep++;
				else if(istep>0) istep=istep*(-1);
				else { istep=istep*(-1); istep++; }
			}
		}
	 }
	 // 4-� ������� ����� � ������
	 else if (Parameters.bToCenter) {
		for (j = 0; j<=M; j++)  {
			jN1 = j*N1;
			CentrI = N/2 + 1;
			i=0;
			signed long int istep=0;
			while (istep != (CentrI+1))  {

				CalcSwitch();

				if (i<=CentrI) {
				   i=N-istep;
				   istep++;
				}
				else i=istep;
			}
		}
	 }
/*
	 // 2-� ������� �����
	 DWORD j;
	 signed long int jstep=0;
	 while (0<=(jstep+CentrJ) && (jstep+CentrJ)<=M)  {
	 j = jstep+CentrJ;
	 .
	 .
	 .
	 if(jstep==0) jstep++;
	 else if(jstep>0) jstep=jstep*(-1);
	 else { jstep=jstep*(-1); jstep++; }

*//*
	 // 3-� �������
	 CentrJ = M/2 + 1;
	 DWORD j=0;
	 signed long int jstep=0;
	 while (jstep!=(CentrJ+1))  {
	 .
	 .
	 .
	 if (j<=CentrJ) {
		j=M-jstep;
		jstep++;
	 }
	 else j=jstep;

*/

/*   if (t > tp && FlagSwitch) {
	  ProgonkaLibmana();
	  FlagSwitch = FALSE;
   }
*/
/*   if (t > tp) */
   CalcPressure(CurrIter);

   if (CurrIter == asIt)  {
	  asIt += Parameters.AutoSaveIter;

	   wsprintf(str, "N%d", CurrIter);
	   AText = AnsiString(str);
	   ShowCalculate->StatusBar1->Panels->Items[2]->Text = AText;

	   // gcvt(t, 5, str);
	   int ct = (int)ceil(t*1e6);
	   wsprintf(str, "%d ���", ct);
	   AText = AnsiString(str);
	   ShowCalculate->StatusBar1->Panels->Items[3]->Text = AText;

	   ShowWave(CurrIter);
	   Application->ProcessMessages();

	  /*
	  wsprintf(FileName, "U%d.imp", CurrIter);
	  ofstream fw(FileName, ios::out|ios::binary);
	  if ( fw.bad() )
		 BWCCMessageBox(Application->Handle, "���������� �������� ����.", "������ �����",
		 MB_OK | MB_ICONEXCLAMATION);
	  else {
		 Write(fw);
		 fw.close();
	  }
	  */
   }

   // ��������������� ������� ������
   for (j = 0; j<=M; j++)   {
	   DWORD jN1 = j*N1;
	   for (DWORD i = 0; i<=N; i++)   {
		  index5 = jN1+i; // ������ �� ����� "������"
		  Knots[index5].U1 = Knots[index5].U2;
          Knots[index5].D1 = Knots[index5].D2;
          Knots[index5].U2 = Knots[index5].U3;
          Knots[index5].D2 = Knots[index5].D3;
       }
    }

   t=t+tau;
   CurrIter++;

 } // while Ttotal

 EndShowWave();
 Application->ProcessMessages();

 CalcWindow->cntME = CurrIter-1;
 CalcP1->cntME = CurrIter-1;
 CalcP2->cntME = CurrIter-1;
 CalcEp->cntME = CurrIter-1;
 CalcEk->cntME = CurrIter-1;
 PressOne->cntME = CurrIter-1;


 gettime(&tEnd);

 wsprintf(str, "%2d:%02d:%02d.%02d",  tEnd.ti_hour, tEnd.ti_min,
									  tEnd.ti_sec, tEnd.ti_hund);

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

  wsprintf(str, "%2d:%02d:%02d.%02d", tBeg.ti_hour, tBeg.ti_min,
									  tBeg.ti_sec, tBeg.ti_hund);

  RealTime=(unsigned long int)((3600*tEnd.ti_hour+60*tEnd.ti_min+tEnd.ti_sec)-
							   (3600*tBeg.ti_hour+60*tBeg.ti_min+tBeg.ti_sec));
  sprintf(str,"%6.1f(%ld)",(float)RealTime/60.0, RealTime);
  AText = AnsiString(str);
  ShowCalculate->StatusBar1->Panels->Items[5]->Text = AText;

  return 1;
}


void CModel2D :: CalcSwitch()
{
 double sum, scobki, sub;
 int diametr;

 index5 = jN1+i; // ������ �� ����� "������"
 switch (Knots[index5].ePhisic)  {
    // ������ ��������� �������
    // ������ ����������� �����
    case IT_POINT_CENTER:
       index6 = jN1+(i+1);
       index4 = jN1+(i-1);
       index2 = (j-1)*N1+i;
       index8 = (j+1)*N1+i;
       /*
       if (t < tp) {
          // ����� ���������� �����
          Knots[index5].U3 = - Knots[index5].U1 - 2*Knots[index5].U2  +
                             Knots[index6].U2 + Knots[index4].U2 +
							 Knots[index2].U2 + Knots[index8].U2;
       }
       else {
          // ������� ���������� �����
          Knots[index5].U3 = (2*Knots[index5].U2 - Knots[index5].U1 +
                             Knots[index6].U3 + Knots[index4].U3 +
                             Knots[index2].U3 + Knots[index8].U3)/5;
       }
       */
	   if (Parameters.Model2D)  {
		  // ����� "����" � �������
		  // 1-� �������
          /*
          sum = Knots[index4].U2 + Knots[index6].U2 +
                Knots[index2].U2 + Knots[index8].U2;
          Knots[index5].U3 = (sum + 2*Knots[index5].U2 - 3*Knots[index5].U1)/3.0;
          */
          // 2-� �������
          /*
          sum = Knots[index4].U2 + Knots[index6].U2 +
                Knots[index2].U2 + Knots[index8].U2 - 2*Knots[index5].U1;
          Knots[index5].U3 = (sum - h2_a2t2*(Knots[index5].U1 - 2*Knots[index5].U2))/_2h_at;
          */
          // ����� ���������� �����

          sum = Knots[index6].U2 + Knots[index4].U2 +
                Knots[index2].U2 + Knots[index8].U2 - 4*Knots[index5].U2;
          Knots[index5].U3 = a2t2_h2*sum - Knots[index5].U1 + 2*Knots[index5].U2;

          // ����-"�������" ���������� �����
          /*
          sum = Knots[index6].U3 + Knots[index4].U3 +
                Knots[index2].U3 + Knots[index8].U3;
          Knots[index5].U3 = (2*Knots[index5].U2 - Knots[index5].U1 + sum)/5;
          */
          // ���������� ����� ���������������� �����
          // 1-� ������� ��� tau=h/a0
          /*
          sum = Knots[index6].U3 + Knots[index4].U3 +
                Knots[index2].U3 + Knots[index8].U3;
          Knots[index5].U3 = sum - Knots[index5].U1 - 2*Knots[index5].U2;
		  */
          // 2-� ������� ��� tau=h/a0*sqrt(2)
          /*
		  sum = Knots[index6].U3 + Knots[index4].U3 +
                Knots[index2].U3 + Knots[index8].U3 - 4*Knots[index5].U2;
          Knots[index5].U3 = a2t2_h2*sum - Knots[index5].U1 + 2*Knots[index5].U2;
          */
          /*
          sum = Knots[index4].U2 + Knots[index6].U2 +
                Knots[index2].U2 + Knots[index8].U2;
          sub = h_at*(Knots[index5].U1 - 2*Knots[index5].U2);
          Knots[index5].U3 = (sum - 2*Knots[index5].U1 - sub)/_2h_at;
          */
       }
       else {
          // ����� "����" � ��������
          sum = Knots[index4].U2 + Knots[index6].U2 +
                Knots[index2].U2 + Knots[index8].U2;
          diametr = N - 2*i;
          if (diametr==0)  {
   //          Knots[index5].U3 = (Knots[index8].U2 + Knots[index2].U2 +
   //                              Knots[index4].U2 + Knots[index6].U2)/4.0;
               Knots[index5].U3 = (sum - 2*Knots[index5].U1)/2.0;
          }
          else  {
             // scobki = 1/diametr*(Knots[index6].U2 - Knots[index5].U2);
             scobki = h/diametr*(Knots[index6].U2 - Knots[index4].U2);
             Knots[index5].U3 = (sum - 3*Knots[index5].U1  + scobki +
                                 2*Knots[index5].U2)/3.0;
          }
       }
	break;

    // ������ ������� ������
    case IT_HARD_BORDER:
       switch (Knots[index5].eArrange)  {
          // ����� �������
          case IT_LEFT_BORDER:
                 index6 = jN1+(i+1);
                 Knots[index5].U3 = Knots[index6].U3;
          break;
          // ������ �������
          case IT_RIGHT_BORDER:
                 index4 = jN1+(i-1);
                 Knots[index5].U3 = Knots[index4].U3;
          break;
          // ������� �������
		  case IT_TOP_BORDER:
                 index2 = (j-1)*N1+i;
                 Knots[index5].U3 = Knots[index2].U3;
          break;
          // ������ �������
          case IT_BOTTOM_BORDER:
                 index8 = (j+1)*N1+i;
                 Knots[index5].U3 = Knots[index8].U3;
                 //Knots[index8].U3 *= 0.96;
                 //Knots[index5].U3 = Knots[index8].U3*0.96;
          break;
      }
    break;

   // ������ ������� �����
   case IT_INPUT_BORDER:
      // ��������
      // P_T = (P0*t)/(t1*t1)*exp(-t/t1);
      // P_T = P0*(1-exp(-t/teta1))*exp(-t/teta2);
      // P_T = P0*exp(-t/teta1);

      // ������ ��������
      if (WhatCalc == 'P') {
		 if (Parameters.Model2D)  {
            P_T = P0*(t/tmax)*exp(1 - t/tmax);
            Knots[index5].U3 = (P_T*tau)/Rau;
         }
         else {
            /*
            if (t<tp)
               P_T = P0*(t/tetta)*exp(1 - t/tetta);
            else {
               // P_T = P0*(t/tmax)*exp(1 - t/tmax);
               P_T = P0*((t-tp)/tmax)*exp(1 - (t-tp)/tmax);
            }
            */
            P_T = P0*(t/tmax)*exp(1 - t/tmax);
            Knots[index5].U3 = (P_T*tau)/Rau;
         }
      }
      else { // ������ ��������
         // Knots[index5].U3 = P0Exp1Rau*(tmax-(tmax+t)*exp(-t/tmax));
		 if (Parameters.Model2D)  {
            Knots[index5].U3 = P0Exp1Rau*(tmax-(tmax+t)*exp(-t/tmax));
			/*
            if (t<tp) {
			   // Knots[index5].U3 = P0Exp1Rau*(tetta-(tetta+t)*exp(-t/tetta));
               Knots[index5].U3 = P0*tetta/Rau*(1-exp(-t/tetta));
               Ou = Knots[index5].U3;
            }
            else {
               Ot = t - tp;
               Knots[index5].U3 = P0Exp1Rau*(tmax-(tmax+Ot)*exp(-Ot/tmax));
               Knots[index5].U3 += Ou;
               // Knots[index5].U3 = P0Exp1Rau*(tmax-(tmax+t)*exp(-t/tmax));
            }
            */
         }
         else  { 
            if (t<tp) {
               // Knots[index5].U3 = P0Exp1Rau*(tetta-(tetta+t)*exp(-t/tetta));
               Knots[index5].U3 = P0*tetta/Rau*(1-exp(-t/tetta));
               Ou = Knots[index5].U3;
            }
            else {
               Ot = t - tp;
               Knots[index5].U3 = P0Exp1Rau*(tmax-(tmax+Ot)*exp(-Ot/tmax));
               Knots[index5].U3 += Ou;
               // Knots[index5].U3 = P0Exp1Rau*(tmax-(tmax+t)*exp(-t/tmax));
            }
         }
      }
    break;

    // ������ ������� ������
    case IT_OUTPUT_BORDER:
       switch (Knots[index5].eArrange)  {
		  // ����� �������
          case IT_LEFT_BORDER:
             index6 = jN1+(i+1);
             index4 = index6;
             index2 = (j-1)*N1+i;
             index8 = (j+1)*N1+i;
             Knots[index5].U3 = (Knots[index8].U3 + Knots[index2].U3 +
                                 Knots[index4].D3 + Knots[index6].U3)/4.0;
          break;
          // ������ �������
          case IT_RIGHT_BORDER:
			 index4 = jN1+(i-1);
             index6 = index4;
             index2 = (j-1)*N1+i;
             index8 = (j+1)*N1+i;
             Knots[index5].U3 = (Knots[index8].U3 + Knots[index2].U3 +
                                 Knots[index4].U3 + Knots[index6].D3)/4.0;
          break;
          // ������� �������
          case IT_TOP_BORDER:
             index2 = (j-1)*N1+i;
             index8 =  index2;
             index6 = jN1+(i+1);
             index4 = jN1+(i-1);
             Knots[index5].U3 = (Knots[index8].D3 + Knots[index2].U3 +
                                 Knots[index4].U3 + Knots[index6].U3)/4.0;
          break;
          // ������ �������
          case IT_BOTTOM_BORDER:
             index8 = (j+1)*N1+i;
             index2 = index8;
		 index6 = jN1+(i+1);
             index4 = jN1+(i-1);
             Knots[index5].U3 = (Knots[index8].U3 + Knots[index2].D3 +
                                 Knots[index4].U3 + Knots[index6].U3)/4.0;
          break;
      }
     Knots[index5].D3 = Knots[index5].U3;
        // Knots[index5].U3 = Knots[index5].U2;
    break;

    // ������ ������� ������
    case IT_MODIFY:
       switch (Knots[index5].eArrange)  {
          // ����� �������
          case IT_LEFT_BORDER:
                 index6 = jN1+(i+1);
                 Knots[index5].U3 = Knots[index6].U2;
          break;
          // ������ �������
          case IT_RIGHT_BORDER:
                 index4 = jN1+(i-1);
                 Knots[index5].U3 = Knots[index4].U2;
          break;
          // ������� �������
		  case IT_TOP_BORDER:
                 index2 = (j-1)*N1+i;
                 Knots[index5].U3 = Knots[index2].U2;
          break;
          // ������ �������
          case IT_BOTTOM_BORDER:
                 index8 = (j+1)*N1+i;
				 Knots[index5].U3 = Knots[index8].U2;
          break;
      }
    break;

    // ������� ���������
    case IT_SYMMETRIC:
       switch (Knots[index5].eArrange)  {
          // ����� �������
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
          // ������ �������
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
          // ������� �������
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
		  // ������ �������
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

      Knots[index5].U3 = (Knots[index8].U3 + Knots[index2].U3 +
                          Knots[index4].U3 + Knots[index6].U3)/4.0;
    break;
 }  // switch
}

int CModel2D :: CalcPressure(DWORD CurrIter)
 {
  // ������ ��������� V �� ���� �������
  /*
  for (j=0; j<=M; j++)   {
	  jN1 = j*N1;
      for (i = 0; i<=N; i++)   {
          index5 = jN1+i;
          switch (Knots[index5].ePhisic)  {
              case IT_POINT_CENTER:
                 double Vx = (Knots[index5+1].U3 - Knots[index5].U3)/h;
                 double Vy = (Knots[(j-1)*N1+i].U3 - Knots[index5].U3)/h;
                 Knots[index5].V = sqrt(Vx*Vx + Vy*Vy);
              break;
         }
     }
  }
  */
  // ������ �������� P1 � Ep �� ���������
  j=Parameters.NumLevel;
  jN1=j*N1;
  double P1P1;
  for (DWORD i=0; i<=N; i++)  {
     if (Knots[jN1+i].ePhisic == IT_POINT_CENTER) {
        if (WhatCalc == 'P')
             // 1-� �������
             Knots[jN1+i].P1 = Rau*(Knots[jN1+i].U3/tau);
        else // 2-� �������
	     Knots[jN1+i].P1 = Rau*fabs(Knots[jN1+i].U3-Knots[jN1+i].U1)/(2*tau);
		 PressWin->arrPress[CurrIter][i] = Knots[jN1+i].P1;

        //P1P1 = Knots[jN1+i].P1*Knots[jN1+i].P1;
        //Knots[jN1+i].Ep = P1P1/(2.0*Rau*a0*a0);
        
     }
  }


  // ������ �������� � ������ �����
  if (iFindPoint > 0 && jFindPoint > 0)  {
     DWORD index = jFindPoint*N1 + iFindPoint;
     float Press;
     if (WhatCalc == 'P')
          // 1-� �������
          Press = (Knots[index].U3/tau)*Rau;
     else // 2-� �������
	  Press = fabs(Knots[index].U3-Knots[index].U1)/(2*tau)*Rau;
	  PressOne->arrEps[CurrIter] = Press;
  }
  

  // ������ �������� P2 � Ek � ��������
  /*
  int cnt=0;
  j=atol(ChoicePlane.NumLevel);
  jN1=j*N1;
  double V2 = 0;
  for (i=0; i<=N; i++)  {
     cnt=0;
     Knots[jN1+i].P2 = 0;
     V2 = 0;
     for (j=0; j<=M; j++)  {
        index5 = j*N1+i;
        switch (Knots[index5].ePhisic)  {
           case IT_POINT_CENTER:
           case IT_INPUT_BORDER:
              // Knots[jN1+i].P2 += Knots[index5].V;
			  double Vy = fabs(Knots[(j-1)*N1+i].U3 - Knots[index5].U3)/h;
              V2 += Vy;
              cnt++;
           break;
        }
     }

     if (cnt!=0) V2 = V2 / cnt;
     // double P = Rau*(Knots[jN1+i].Psi*Knots[jN1+i].Psi);
	 Knots[jN1+i].P2 = Rau*(V2*V2);
	 winIMPULSE->AllPress->arrPress[CurrIter][i] = Knots[jN1+i].P2;
  }
  */
   
  // ���������� ���������� �� ���������
  float Max_P1 = 0.0, Max_P2 = 0.0, Max_Ep = 0.0, Max_Ek = 0.0;
  int   iMax_P1 = 0, iMax_P2 = 0, iMax_Ep = 0, iMax_Ek = 0;
  j = Parameters.NumLevel;
  jN1=j*N1;
  for (i=0; i<N; i++)  {
      if (Knots[jN1+i].ePhisic == IT_POINT_CENTER) {
		 if (Max_P1 < Knots[jN1+i].P1) {
	    Max_P1 = Knots[jN1+i].P1;
            iMax_P1 = i;
         }
         if (Max_P2 < Knots[jN1+i].P2) {
	    Max_P2 = Knots[jN1+i].P2;
            iMax_P2 = i;
         }
         if (Max_Ep < Knots[jN1+i].Ep) {
	    Max_Ep = Knots[jN1+i].Ep;
			iMax_Ep = i;
         }
         if (Max_Ek < Knots[jN1+i].Ek)  {
	    Max_Ek = Knots[jN1+i].Ek;
            iMax_Ek = i;
         }
     }
  }

  CalcP1->arrEps[CurrIter] = Max_P1;
  CalcP2->arrEps[CurrIter] = Max_P2;
  CalcEp->arrEps[CurrIter] = Max_Ep;
  CalcEk->arrEps[CurrIter] = Max_Ek;
  CalcP1->arrNum[CurrIter] =iMax_P1;
  CalcP2->arrNum[CurrIter] =iMax_P2;
  CalcEp->arrNum[CurrIter] =iMax_Ep;
  CalcEk->arrNum[CurrIter] =iMax_Ek;


  int i1 = 71, j1 = 33, i2 = 71, j2 = 0;
  double dU = Knots[j1*N1+i1].U3-Knots[j2*N1+i2].U3;
  double U_2 = dU*dU;
  double n = (j1-j2)*h;
  Max_Ek = Rau*U_2/(2*n*n);
  CalcEk->arrEps[CurrIter] = Max_Ek;
  CalcEk->arrNum[CurrIter] = 71;

  return 1;
}

int CModel2D :: ProgonkaLibmana()
 {
//  ���������, ������������ ��� ������� �������� ����������
//  const double _w_4 = Parameters.w/4;
//  const double _1_w= 1-Parameters.w;
  const double Omega = 1.9;
  const double _w_4 = Omega/4;
  const double _1_w= 1-Omega;
  DWORD index5, index4, index6, index8, index2;
  DWORD jN1;
  double unew, resid;
  double d;

  // ������������ ����� �������
  do  {
      d = 0.0; // ���������� �������� �������� �����������,
               // ���������� ��� ���������������� ���������
     // ����� �� ���� ������ �����
     for (DWORD j = 0; j<=M; j++)   {
        if (GetAsyncKeyState(VK_ESCAPE)) return 0;
        jN1 = j*N1;
        for (DWORD i = 0; i<=N; i++)   {
           index5 = jN1+i; // ������ �� ����� "������"
           if (Knots[index5].U3 != 0.0)   {
              switch (Knots[index5].ePhisic)  {
                 // ������ ����������� �����
                 case IT_POINT_CENTER:
                    index6 = jN1+(i+1);
                    index4 = jN1+(i-1);
                    index2 = (j-1)*N1+i;
                    index8 = (j+1)*N1+i;
                    unew = _w_4 * (Knots[index8].U3 + Knots[index2].U3 +
                                   Knots[index4].U3 + Knots[index6].U3)
                           + _1_w * Knots[index5].U3;
                    if (unew<0.0) resid = 0.0;
                    resid = fabs(unew - Knots[index5].U3);
                    if (resid > d) d = resid;
                    Knots[index5].U3 = unew;
                 break;
                 // ������ ������� ������
                 case IT_HARD_BORDER:
					switch (Knots[index5].eArrange)  {
                       // ����� �������
                       case IT_LEFT_BORDER:
                              index6 = jN1+(i+1);
                              Knots[index5].U3 = Knots[index6].U3;
                       break;
                       // ������ �������
					   case IT_RIGHT_BORDER:
                              index4 = jN1+(i-1);
                              Knots[index5].U3 = Knots[index4].U3;
                       break;
                       // ������� �������
                       case IT_TOP_BORDER:
                              index2 = (j-1)*N1+i;
                              Knots[index5].U3 = Knots[index2].U3;
                       break;
                       // ������ �������
                       case IT_BOTTOM_BORDER:
                              index8 = (j+1)*N1+i;
                              Knots[index5].U3 = Knots[index8].U3;
                   }
                 break;
              }  // switch
           } // if Uij != 0.0
        }  // for i
     } // for j

//   CurrIter++;
   char str[50];
   gcvt(d, 5, str);

   AnsiString AText = AnsiString(str);
   ShowCalculate->StatusBar1->Panels->Items[6]->Text = AText;
  }
  // �������� �� ����������
  while(d > Parameters.Eps);

  return 1;
 }



void CModel2D :: CalcSwitchDopSloy()
{
 double sum, scobki, sub;
 int diametr;

 index5 = jN1+i; // ������ �� ����� "������"
 switch (Knots[index5].ePhisic)  {
	// ������ ��������� �������
	// ������ ����������� �����
	case IT_POINT_CENTER:
   // ������ ������� ����� ����� ��� � ����������� �����
   case IT_INPUT_BORDER:
	   index6 = jN1+(i+1);
	   index4 = jN1+(i-1);
	   index2 = (j-1)*N1+i;
	   index8 = (j+1)*N1+i;
	   /*
	   if (t < tp) {
		  // ����� ���������� �����
		  Knots[index5].U3 = - Knots[index5].U1 - 2*Knots[index5].U2  +
							 Knots[index6].U2 + Knots[index4].U2 +
							 Knots[index2].U2 + Knots[index8].U2;
	   }
	   else {
		  // ������� ���������� �����
		  Knots[index5].U3 = (2*Knots[index5].U2 - Knots[index5].U1 +
							 Knots[index6].U3 + Knots[index4].U3 +
							 Knots[index2].U3 + Knots[index8].U3)/5;
	   }
	   */
	   if (Parameters.Model2D)  {
		  // ����� "����" � �������
		  // 1-� �������
		  /*
		  sum = Knots[index4].U2 + Knots[index6].U2 +
				Knots[index2].U2 + Knots[index8].U2;
		  Knots[index5].U3 = (sum + 2*Knots[index5].U2 - 3*Knots[index5].U1)/3.0;
		  */
		  // 2-� �������
		  /*
          sum = Knots[index4].U2 + Knots[index6].U2 +
                Knots[index2].U2 + Knots[index8].U2 - 2*Knots[index5].U1;
          Knots[index5].U3 = (sum - h2_a2t2*(Knots[index5].U1 - 2*Knots[index5].U2))/_2h_at;
          */
          // ����� ���������� �����

		  sum = Knots[index6].D2 + Knots[index4].D2 +
                Knots[index2].D2 + Knots[index8].D2 - 4*Knots[index5].D2;
          Knots[index5].D3 = a2t2_h2*sum - Knots[index5].D1 + 2*Knots[index5].D2;

          // ����-"�������" ���������� �����
          /*
          sum = Knots[index6].U3 + Knots[index4].U3 +
				Knots[index2].U3 + Knots[index8].U3;
          Knots[index5].U3 = (2*Knots[index5].U2 - Knots[index5].U1 + sum)/5;
          */
		  // ���������� ����� ���������������� �����
          // 1-� ������� ��� tau=h/a0
          /*
          sum = Knots[index6].U3 + Knots[index4].U3 +
                Knots[index2].U3 + Knots[index8].U3;
          Knots[index5].U3 = sum - Knots[index5].U1 - 2*Knots[index5].U2;
          */
          // 2-� ������� ��� tau=h/a0*sqrt(2)
          /*
          sum = Knots[index6].U3 + Knots[index4].U3 +
                Knots[index2].U3 + Knots[index8].U3 - 4*Knots[index5].U2;
          Knots[index5].U3 = a2t2_h2*sum - Knots[index5].U1 + 2*Knots[index5].U2;
          */
          /*
		  sum = Knots[index4].U2 + Knots[index6].U2 +
                Knots[index2].U2 + Knots[index8].U2;
          sub = h_at*(Knots[index5].U1 - 2*Knots[index5].U2);
          Knots[index5].U3 = (sum - 2*Knots[index5].U1 - sub)/_2h_at;
          */
       }
       else {
          // ����� "����" � ��������
          sum = Knots[index4].D2 + Knots[index6].D2 +
                Knots[index2].D2 + Knots[index8].D2;
          diametr = N - 2*i;
          if (diametr==0)  {
   //          Knots[index5].U3 = (Knots[index8].U2 + Knots[index2].U2 +
   //                              Knots[index4].U2 + Knots[index6].U2)/4.0;
               Knots[index5].D3 = (sum - 2*Knots[index5].D1)/2.0;
          }
          else  {
			 // scobki = 1/diametr*(Knots[index6].U2 - Knots[index5].U2);
             scobki = h/diametr*(Knots[index6].D2 - Knots[index4].D2);
             Knots[index5].D3 = (sum - 3*Knots[index5].D1  + scobki +
								 2*Knots[index5].D2)/3.0;
          }
       }
    break;

    // ������ ������� ������
    case IT_HARD_BORDER:
	   switch (Knots[index5].eArrange)  {
          // ����� �������
          case IT_LEFT_BORDER:
                 index6 = jN1+(i+1);
				 Knots[index5].D3 = Knots[index6].D3;
          break;
          // ������ �������
          case IT_RIGHT_BORDER:
                 index4 = jN1+(i-1);
                 Knots[index5].D3 = Knots[index4].D3;
          break;
          // ������� �������
          case IT_TOP_BORDER:
                 index2 = (j-1)*N1+i;
                 Knots[index5].D3 = Knots[index2].D3;
          break;
          // ������ �������
          case IT_BOTTOM_BORDER:
                 index8 = (j+1)*N1+i;
                 Knots[index5].D3 = Knots[index8].D3;
                 // Knots[index5].U3 = Knots[index8].U1;
		  break;
      }
    break;

    // ������ ������� ������
    case IT_OUTPUT_BORDER:
       switch (Knots[index5].eArrange)  {
          // ����� �������
          case IT_LEFT_BORDER:
             index6 = jN1+(i+1);
             index4 = index6;
             index2 = (j-1)*N1+i;
             index8 = (j+1)*N1+i;
             Knots[index5].D3 = (Knots[index8].D3 + Knots[index2].D3 +
								 Knots[index4].U3 + Knots[index6].D3)/4.0;
          break;
		  // ������ �������
          case IT_RIGHT_BORDER:
             index4 = jN1+(i-1);
             index6 = index4;
             index2 = (j-1)*N1+i;
             index8 = (j+1)*N1+i;
             Knots[index5].D3 = (Knots[index8].D3 + Knots[index2].D3 +
								 Knots[index4].D3 + Knots[index6].U3)/4.0;
          break;
          // ������� �������
          case IT_TOP_BORDER:
             index2 = (j-1)*N1+i;
             index8 =  index2;
             index6 = jN1+(i+1);
             index4 = jN1+(i-1);
			 Knots[index5].D3 = (Knots[index8].U3 + Knots[index2].D3 +
                                 Knots[index4].D3 + Knots[index6].D3)/4.0;
          break;
          // ������ �������
          case IT_BOTTOM_BORDER:
             index8 = (j+1)*N1+i;
             index2 = index8;
	     index6 = jN1+(i+1);
             index4 = jN1+(i-1);
             Knots[index5].D3 = (Knots[index8].D3 + Knots[index2].U3 +
                                 Knots[index4].D3 + Knots[index6].D3)/4.0;
          break;
      }
     Knots[index5].U3 = Knots[index5].D3;
	 // Knots[index5].U3 = Knots[index5].U2;
    break;

    // ������ ������� ������
    case IT_MODIFY:
       switch (Knots[index5].eArrange)  {
          // ����� �������
          case IT_LEFT_BORDER:
                 index6 = jN1+(i+1);
                 Knots[index5].D3 = Knots[index6].D2;
          break;
          // ������ �������
          case IT_RIGHT_BORDER:
                 index4 = jN1+(i-1);
                 Knots[index5].D3 = Knots[index4].D2;
		  break;
          // ������� �������
		  case IT_TOP_BORDER:
                 index2 = (j-1)*N1+i;
                 Knots[index5].D3 = Knots[index2].D2;
          break;
          // ������ �������
		  case IT_BOTTOM_BORDER:
                 index8 = (j+1)*N1+i;
                 Knots[index5].D3 = Knots[index8].D2;
          break;
      }
    break;

    // ������� ���������
    case IT_SYMMETRIC:
	   switch (Knots[index5].eArrange)  {
          // ����� �������
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
          // ������ �������
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
          // ������� �������
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
          // ������ �������
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

      Knots[index5].D3 = (Knots[index8].D3 + Knots[index2].D3 +
                          Knots[index4].D3 + Knots[index6].D3)/4.0;
    break;
 }  // switch
}


//---------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "TParams.h"
#include "impulse.hpp"

//---------------------------------------------------------------------
#pragma resource "*.dfm"
TParametersDlg *ParametersDlg;
//---------------------------------------------------------------------
__fastcall TParametersDlg::TParametersDlg(TComponent* AOwner)
	: TForm(AOwner)
{
}
//---------------------------------------------------------------------
void __fastcall TParametersDlg::OKBtnClick(TObject *Sender)
{
  if (MathModel != NULL) {
	  MathModel->Parameters.h = StrToFloat(sStep->Text);
	  MathModel->Interval =  MathModel->Parameters.h*1000;
	  MathModel->Parameters.Rau = StrToFloat(sDensity->Text);
	  MathModel->Parameters.a0 = StrToFloat(sSoundSpeed->Text);
	  MathModel->Parameters.P0 = StrToFloat(sBeginPressing->Text);
	  MathModel->Parameters.tmax = StrToFloat(sTimeMax->Text)*1e-6;
	//  MathModel->Parameters.tetta = StrToFloat(sTimeTetta)*1e-6;
	  MathModel->Parameters.tp = StrToFloat(sTimeSwitch->Text)*1e-6;
	//  MathModel->Parameters.Psi = 50.0;  // значение потенциала на источнике
	//  MathModel->Parameters.dPsi = 2.0; // "толщина" эквипотенциальной линии
	  MathModel->Parameters.Eps = StrToFloat(sEpsilon->Text);  // погрешность вычислений
	  MathModel->Parameters.w = StrToFloat(sOmega->Text);    // ускор€ющий коэффициент [1..2]
	  MathModel->Parameters.Ttotal = StrToFloat(sTtotal->Text)*1e-6;
	//  MathModel->Parameters.QEquLine = (int)ceil(MathModel->Parameters.Psi/MathModel->Parameters.dPsi);
	  MathModel->Parameters.QEquLine = StrToInt(sQEquLine->Text);
	  MathModel->Parameters.AutoSaveIter = StrToInt(sAutoSaveIter->Text);

	  MathModel->Parameters.bLeftRight = bLeftRight->Checked;
	  MathModel->Parameters.bRightLeft = bRightLeft->Checked;
	  MathModel->Parameters.bFromCenter = bFromCenter->Checked;
	  MathModel->Parameters.bToCenter = bToCenter->Checked;
	  MathModel->Parameters.bTwoWhile = bTwoWhile->Checked;

	  MathModel->Parameters.xCoord = StrToInt(xCoord->Text);
	  MathModel->Parameters.yCoord = StrToInt(yCoord->Text);
	  MathModel->Parameters.Ntrub = StrToInt(sNtrub->Text);
	  MathModel->Parameters.Delitel = StrToInt(sDelitel->Text);

	  MathModel->Parameters.Model2D = Model2D->Checked;
	  MathModel->Parameters.ModelFiZR = ModelFiZR->Checked;
	  MathModel->Parameters.NumLevel = StrToInt(NumLevel->Text);
  }
  Close();
}
//---------------------------------------------------------------------------

void __fastcall TParametersDlg::CancelBtnClick(TObject *Sender)
{
  Close();
}
//---------------------------------------------------------------------------

void __fastcall TParametersDlg::FormCreate(TObject *Sender)
{
/*
  MathModel->Parameters.h = 0.001;
  MathModel->Interval =  MathModel->Parameters.h*1000;
  MathModel->Parameters.Rau = 1000;
  MathModel->Parameters.a0 = 1500.0;
  MathModel->Parameters.P0 = 2000000;
  MathModel->Parameters.tmax = 100;
//  MathModel->Parameters.tetta = atof(dataParameter.sTimeTetta)*1e-6;
  MathModel->Parameters.tp = 38*1e-6;
//  MathModel->Parameters.Psi = 50.0;  // значение потенциала на источнике
//  MathModel->Parameters.dPsi = 2.0; // "толщина" эквипотенциальной линии
  MathModel->Parameters.Eps = 0.01;  // погрешность вычислений
  MathModel->Parameters.w = 1.7;    // ускор€ющий коэффициент [1..2]
  MathModel->Parameters.Ttotal = 5000*1e-6;
//  MathModel->Parameters.QEquLine = (int)ceil(MathModel->Parameters.Psi/MathModel->Parameters.dPsi);
  MathModel->Parameters.QEquLine = 20;
  MathModel->Parameters.AutoSaveIter = 5;
  */
}
//---------------------------------------------------------------------------

void __fastcall TParametersDlg::FormActivate(TObject *Sender)
{
  if (MathModel != NULL) {

	 sStep->Text = FloatToStrF (MathModel->Parameters.h, ffGeneral, 8, 5);
	 sDensity->Text = FloatToStrF (MathModel->Parameters.Rau, ffGeneral, 8, 2);
	 sSoundSpeed->Text = FloatToStrF (MathModel->Parameters.a0, ffGeneral, 8, 2);
	 sBeginPressing->Text = FloatToStrF (MathModel->Parameters.P0, ffGeneral, 8, 2);
	 sTimeMax->Text = FloatToStrF (MathModel->Parameters.tmax/1e-6, ffGeneral, 8, 2);
	 sTimeSwitch->Text = FloatToStrF (MathModel->Parameters.tp/1e-6, ffGeneral, 8, 2);
	 sEpsilon->Text = FloatToStrF (MathModel->Parameters.Eps, ffGeneral, 8, 2);
	 sOmega->Text = FloatToStrF (MathModel->Parameters.w, ffGeneral, 8, 2);
	 sTtotal->Text = FloatToStrF (MathModel->Parameters.Ttotal/1e-6, ffGeneral, 8, 2);
	 sQEquLine->Text = IntToStr(MathModel->Parameters.QEquLine);
	 sAutoSaveIter->Text = IntToStr(MathModel->Parameters.AutoSaveIter);

	 bLeftRight->Checked = MathModel->Parameters.bLeftRight;
	 bRightLeft->Checked = MathModel->Parameters.bRightLeft;
	 bFromCenter->Checked = MathModel->Parameters.bFromCenter;
	 bToCenter->Checked = MathModel->Parameters.bToCenter;
	 bTwoWhile->Checked = MathModel->Parameters.bTwoWhile;

	 xCoord->Text =	IntToStr(MathModel->Parameters.xCoord);
	 yCoord->Text =	IntToStr(MathModel->Parameters.yCoord);
	 sNtrub->Text =	IntToStr(MathModel->Parameters.Ntrub);
	 sDelitel->Text = IntToStr(MathModel->Parameters.Delitel);

	 Model2D->Checked = MathModel->Parameters.Model2D;
	 ModelFiZR->Checked = MathModel->Parameters.ModelFiZR;
	 NumLevel->Text = IntToStr(MathModel->Parameters.NumLevel);
  }
}
//---------------------------------------------------------------------------

void __fastcall TParametersDlg::SetParametersAfterLoad()
{
	TReplaceFlags Flags;
	// Flags << rfReplaceAll;

	 sStep->Text = AnsiString(dataParameter.sStep);
	 sStep->Text = StringReplace(sStep->Text, ".", ",", Flags);

	 sDensity->Text = AnsiString(dataParameter.sDensity);
	 sDensity->Text = StringReplace(sDensity->Text, ".", ",", Flags);

	 sSoundSpeed->Text = AnsiString(dataParameter.sSoundSpeed);
	 sSoundSpeed->Text = StringReplace(sSoundSpeed->Text, ".", ",", Flags);

	 sBeginPressing->Text = AnsiString(dataParameter.sBeginPressing);
	 sBeginPressing->Text = StringReplace(sBeginPressing->Text, ".", ",", Flags);

	 sTimeMax->Text = AnsiString(dataParameter.sTimeMax);
	 sTimeMax->Text = StringReplace(sTimeMax->Text, ".", ",", Flags);

	 sTimeSwitch->Text = AnsiString(dataParameter.sTimeSwitch);
	 sTimeSwitch->Text = StringReplace(sTimeSwitch->Text, ".", ",", Flags);

	 sEpsilon->Text = AnsiString(dataParameter.sEpsilon);
	 sEpsilon->Text = StringReplace(sEpsilon->Text, ".", ",", Flags);

	 sOmega->Text = AnsiString(dataParameter.sOmega);
	 sOmega->Text = StringReplace(sOmega->Text, ".", ",", Flags);

	 sTtotal->Text = AnsiString(dataParameter.sTtotal);
	 sTtotal->Text = StringReplace(sTtotal->Text, ".", ",", Flags);

	 sQEquLine->Text = AnsiString(dataParameter.sQEquLine);
	 sAutoSaveIter->Text = AnsiString(dataParameter.sAutoSaveIter);
}


void __fastcall TParametersDlg::SetParametersBeforeSave()
{
	TReplaceFlags Flags;
	// Flags << rfReplaceAll;

	// sStep->Text = StringReplace(sStep->Text, ",", ".", Flags);
	 strcpy(dataParameter.sStep, sStep->Text.c_str());
	 strcpy(dataParameter.sDensity, sDensity->Text.c_str());
	 strcpy(dataParameter.sSoundSpeed, sSoundSpeed->Text.c_str() );
	 strcpy(dataParameter.sBeginPressing, sBeginPressing->Text.c_str() );
	 strcpy(dataParameter.sTimeMax, sTimeMax->Text.c_str() );
	 strcpy(dataParameter.sTimeSwitch, sTimeSwitch->Text.c_str() );
	 strcpy(dataParameter.sEpsilon, sEpsilon->Text.c_str() );
	 strcpy(dataParameter.sOmega, sOmega->Text.c_str() );
	 strcpy(dataParameter.sTtotal, sTtotal->Text.c_str() );
	 strcpy(dataParameter.sQEquLine, sQEquLine->Text.c_str() );
	 strcpy(dataParameter.sAutoSaveIter, sAutoSaveIter->Text.c_str());
   }


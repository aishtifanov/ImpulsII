// ПРОЕКТ:     Математическая 2D-модель волновых процессов
// ВЕРСИЯ:     2.0
// ФАЙЛ:       TImpWinII.cPP
// ДАТА:       08/98
// АВТОР:      Штифанов А.И.
// СОДЕРЖАНИЕ: Описание классов и структур данных

#include <vcl\vcl.h>
#pragma hdrstop

#include "impulse.hpp"

#include "TImpWinII.h"
#include "About.h"
#include "TModConf.h"
#include "TParams.h"
#include "TShowBorder.h"
#include "TCalcWindow.h"
#include "TPressOne.h"
#include "TPressWin.h"

#pragma resource "*.dfm"

TImpulseWindow  *ImpulseWindow;
CModel2D        *MathModel = NULL;

//SState              State;       // СОСТОЯНИЕ ОСНОВНЫХ ПАРАМЕТРОВ ПРОГРАММЫ
SParameterInDlg     dataParameter;
SReport             Report;
SPeriodInDlg        Period;

static char TitleIMP[] = "IMP#1";
static char TitleIMP_II[] = "IMP#2";
BOOL OpenFailed = TRUE;
char FileName[128] = "*.imp";
extern BOOL bBlackWhite;

//---------------------------------------------------------------------------
__fastcall TImpulseWindow::TImpulseWindow(TComponent* Owner)
	: TForm(Owner)
{
  IsNewFile = TRUE;
  IsDirty = FALSE;
}
//----------------------------------------------------------------------------
void __fastcall TImpulseWindow::FormCreate(TObject *Sender)
{
 Application->OnHint = ShowHint;
}
//----------------------------------------------------------------------------
void __fastcall TImpulseWindow::ShowHint(TObject *Sender)
{
 StatusLine->SimpleText = Application->Hint;
}
//----------------------------------------------------------------------------
void __fastcall TImpulseWindow::FormCloseQuery(TObject *Sender, bool &CanClose)
{
  CanClose = TRUE;
  int  iRet = IDCANCEL;

  if ( IsDirty )  {
     iRet = Application->MessageBox("Сохранить изменения?",
                                    "Модель изменена", MB_YESNOCANCEL | MB_ICONQUESTION);
     switch ( iRet )  {
        case IDYES: IDMSaveModelClick(NULL);
                    CanClose = TRUE;
        break;
        case IDNO:  CanClose = TRUE;
        break;
        case IDCANCEL:  CanClose = FALSE;
        break;
     }
  }
  /*
  if (bRet!=IDCANCEL) {
     if (hWndServer != NULL)
        PostMessage(hWndServer, WM_DDE_TERMINATE, (WPARAM)HWindow, 0L);
  }
  */
}

//---------------------------------------------------------------------------
void __fastcall TImpulseWindow::FilePrint(TObject *Sender)
{
  if (PrintDialog->Execute())	{
		//---- Add code to print current file ----
  }
}
//----------------------------------------------------------------------------
void __fastcall TImpulseWindow::FilePrintSetup(TObject *Sender)
{
 PrintSetupDialog->Execute();
}
//----------------------------------------------------------------------------
void __fastcall TImpulseWindow::EditUndo(TObject *Sender)
{
	//---- Add code to perform Edit Undo ----
}
//----------------------------------------------------------------------------
void __fastcall TImpulseWindow::EditCut(TObject *Sender)
{
	//---- Add code to perform Edit Cut ----
}
//----------------------------------------------------------------------------
void __fastcall TImpulseWindow::EditCopy(TObject *Sender)
{
	//--- Add code to perform Edit Copy ----
}
//----------------------------------------------------------------------------
void __fastcall TImpulseWindow::EditPaste(TObject *Sender)
{
	//---- Add code to perform Edit Paste ----
}
//----------------------------------------------------------------------------
void __fastcall TImpulseWindow::WindowTile(TObject *Sender)
{
	Tile();
}
//----------------------------------------------------------------------------
void __fastcall TImpulseWindow::WindowCascade(TObject *Sender)
{
	Cascade();
}
//----------------------------------------------------------------------------
void __fastcall TImpulseWindow::WindowArrange(TObject *Sender)
{
	ArrangeIcons();
}
//----------------------------------------------------------------------------
void __fastcall TImpulseWindow::HelpContents(TObject *Sender)
{
	Application->HelpCommand(HELP_CONTENTS, 0);
}
//----------------------------------------------------------------------------
void __fastcall TImpulseWindow::HelpSearch(TObject *Sender)
{
	Application->HelpCommand(HELP_PARTIALKEY, Longint(""));
}
//----------------------------------------------------------------------------
void __fastcall TImpulseWindow::HelpHowToUse(TObject *Sender)
{
	Application->HelpCommand(HELP_HELPONHELP, 0);
}
//----------------------------------------------------------------------------
void __fastcall TImpulseWindow::HelpAbout(TObject *Sender)
{
        // AboutBox->ShowModal();
		   AboutBox->Show();
}
//----------------------------------------------------------------------------
void __fastcall TImpulseWindow :: Read(ifstream &fr)
 {
  char tGMB[10];
  // BOOL CalcDOIT; // 4 bytes
  short CalcDOIT; // 2 bytes !!!!
  fr.read(tGMB, lstrlen(TitleIMP));
  tGMB[lstrlen(TitleIMP)] = '\0';

  if (!lstrcmp(tGMB, TitleIMP)) {
	 ModelConf->SelectGeometryObject(1000, 1000);
	 ModelConf->Read(fr);
	 fr.read((char *)&(CalcDOIT), sizeof(CalcDOIT));
	 fr.read((char *)&dataParameter, sizeof(dataParameter));
	 ParametersDlg->SetParametersAfterLoad();

	 /*
	 switch(iGraphics) {
		case SAVE_SOURCEDATA:
		break;
		case SAVE_PERIODREZ: // wAllGR->Read(fr);
                             if (MathModel==NULL)  {
                                TMessage Msg;
                                IDMInitModel(Msg);
                             }
                             PressOne->Read(fr);
        break;
        case SAVE_GRPHICREZ: if (MathModel==NULL)  {
                                TMessage Msg;
                                IDMInitModel(Msg);
                             }
                             CalcP1->Read(fr);
							 AllPress->Read(fr);
        break;
        case SAVE_1STAGE:    if (MathModel==NULL)  {
                                TMessage Msg;
                                IDMInitModel(Msg);
                             }
                             MathModel->Read(fr);
                              // CalcWin->Read(fr);
        break;
     }
     */
  }
  ModelConf->RedrawButtonClick(NULL);
 }

//----------------------------------------------------------------------------
void __fastcall TImpulseWindow :: Write(ofstream &fw)
 {
   // BOOL CalcDOIT;  // 4 bytes
   short CalcDOIT = 0; // 2 bytes !!!!

   fw.write(TitleIMP, lstrlen(TitleIMP));
   ModelConf->Write(fw);
   fw.write((char *)&(CalcDOIT), sizeof(CalcDOIT));
   ParametersDlg->SetParametersBeforeSave();
   fw.write((char *)&dataParameter, sizeof(dataParameter));
   /*
   switch(iGraphics) {
	  case SAVE_SOURCEDATA:
	  break;
      case SAVE_PERIODREZ: // wAllGR->Write(fw);
                              PressOne->Write(fw);
      break;
      case SAVE_GRPHICREZ: CalcP1->Write(fw);
						   AllPress->Write(fw);
      break;
      case SAVE_1STAGE:    MathModel->Write(fw);
                           // CalcWin->Write(fw);
      break;

   }
   */
 }

void __fastcall TImpulseWindow::IDMCreateModelClick(TObject *Sender)
{

  ParametersDlg->sStep->Text = "0,001";
  ParametersDlg->sDensity->Text = "1000";
  ParametersDlg->sSoundSpeed->Text = "1500,0";
  ParametersDlg->sBeginPressing->Text = "2000000";
  ParametersDlg->sTimeMax->Text = "100";
  ParametersDlg->sTimeSwitch->Text = "38";
  ParametersDlg->sEpsilon->Text = "0.01";
  ParametersDlg->sTtotal->Text = "5000";
  ParametersDlg->sOmega->Text = "1,7";
  ParametersDlg->sQEquLine->Text = "20";
  ParametersDlg->sAutoSaveIter->Text = "5";

  ParametersDlg->bLeftRight->Checked = false;
  ParametersDlg->bRightLeft->Checked = false;
  ParametersDlg->bFromCenter->Checked = false;
  ParametersDlg->bToCenter->Checked = false;
  ParametersDlg->bTwoWhile->Checked = true;
  ParametersDlg->xCoord->Text = "10";
  ParametersDlg->yCoord->Text = "210";
  ParametersDlg->sNtrub->Text = "0";
  ParametersDlg->sDelitel->Text = "1";

  ParametersDlg->NumLevel->Text = "1";
  ParametersDlg->Model2D->Checked = true;
  ParametersDlg->ModelFiZR->Checked = false;


  IsNewFile = TRUE;
  IsDirty = FALSE;

  lstrcpy(FileName, "noname.imp");

  ModelConf->drawList.Destroy();
  ModelConf->Invalidate();

  if (MathModel != NULL) {
	 MathModel->Destroy();
	 MathModel = NULL;
	 ShowBorderArrange->Close();
	 ShowBorderPhisic->Close();
  }
}
//---------------------------------------------------------------------------
void __fastcall TImpulseWindow::IDMOpenModelClick(TObject *Sender)
{
  if (OpenDialog->Execute())  {
	 lstrcpy(FileName, OpenDialog->FileName.c_str());
	 ifstream fr(FileName, ios::in|ios::binary);
	 if ( fr.bad() ) {
		AnsiString asMsg = "Невозможно открыть файл "+OpenDialog->FileName;
		Application->MessageBox(asMsg.c_str(),
								"Ошибка файла", MB_OK | MB_ICONEXCLAMATION);
		OpenFailed = TRUE;
	 } else {
		Read(fr);

		fr.close();

		IsNewFile = IsDirty = FALSE;

		// Caption = "Impulse II - " + ExtractFileName(OpenDialog->FileName);
		Caption = "Impulse II - " + OpenDialog->FileName;
		OpenFailed = FALSE;

     /*
        if (MathModel!=NULL)  {
	    delete MathModel;
            MathModel = NULL;
        }
        if (ShowBorArr!=NULL) {
	   delete ShowBorArr;
           ShowBorArr = NULL;
        }
        if (ShowBorPh!=NULL) {
           delete ShowBorPh;
           ShowBorPh = NULL;
        }

        HCURSOR prev = SetCursor(LoadCursor(0, IDC_WAIT));
        if (iGraphics == OPEN_TEMPLATE)  {
           fr.close();
           fr.open(FileName);
           ModelConf->ReadTemplate(fr);
        }
        else

        Read(fr);

        fr.close();
		ModelConf->listGrid.Destroy();

        IsNewFile = IsDirty = FALSE;
        char fn[128];
        lstrcpy(fn, GetFileName(FileName));
        StatusWin->TextStatusOut(STATUS_FILENAME, fn, FALSE);
        SetCursor(prev);
        OpenFailed = FALSE;
      */
     }
	}
}
//---------------------------------------------------------------------------
void __fastcall TImpulseWindow::IDMSaveModelClick(TObject *Sender)
{
  if (!lstrcmp(FileName, "noname.imp")) IDMSaveModelAsClick(NULL);

  if ( IsNewFile )  IDMSaveModelAsClick(NULL);
  else  {
	 // ofstream fw(OpenDialog->FileName.c_str(), ios::out|ios::binary);
	 ofstream fw(FileName, ios::out|ios::binary);
	 if (fw.fail()) {
		 AnsiString asMsg = "Невозможно открыть файл "+OpenDialog->FileName;
		 Application->MessageBox(asMsg.c_str(),
						   "Ошибка файла", MB_OK | MB_ICONEXCLAMATION);
	 } else {
		 Write(fw);
		 fw.close();
		 IsNewFile = IsDirty = FALSE;

	 }
  }

}
//---------------------------------------------------------------------------
void __fastcall TImpulseWindow::IDMSaveModelAsClick(TObject *Sender)
{
 if (SaveDialog->Execute())	{
    lstrcpy (FileName, SaveDialog->FileName.c_str());
    ofstream fw(FileName, ios::out|ios::binary);
    if ( fw.bad() )  {
	   AnsiString asMsg = "Невозможно записать файл "+SaveDialog->FileName;
	   Application->MessageBox(asMsg.c_str(),
							  "Ошибка файла", MB_OK | MB_ICONEXCLAMATION);
	}
    else {
       Write(fw);
       fw.close();
       IsNewFile = IsDirty = FALSE;
       Caption = "Impulse II - " + SaveDialog->FileName;
    }
 }
}
//---------------------------------------------------------------------------
void __fastcall TImpulseWindow::IDMQuitClick(TObject *Sender)
{
 Close();
}
//---------------------------------------------------------------------------

void __fastcall TImpulseWindow::IDMInitModelClick(TObject *Sender)
{
 if (MathModel != NULL) delete MathModel;

 MathModel = new CModel2D(&(ModelConf->drawList));
 MathModel->Organise();
 MathModel->Set(1);

 if (ShowBorderArrange == NULL) {
   ShowBorderArrange = CreateShowBorderWindow("Геометрические признаки границ", SHOW_ARRANGE_BORDER);
 }  else {
   ShowBorderArrange->Refresh();
}
 if (ShowBorderPhisic == NULL) {
	ShowBorderPhisic = CreateShowBorderWindow( "Физические признаки границ", SHOW_PHISIC_BORDER);
 } else {
	ShowBorderPhisic->Refresh();
}

}


TShowBorder* __fastcall TImpulseWindow::CreateShowBorderWindow(const String ATitle, EWhatShow awhatShow)
{
  TShowBorder *aShowBorder = new TShowBorder(Application);

  aShowBorder->Caption = ATitle;
  aShowBorder->whatShow = awhatShow;

  return aShowBorder;
/*
   switch(awhatShow) {
	 case SHOW_ARRANGE_BORDER:
		  ShowBorderArrange = new TShowBorder(Application);
		  ShowBorderArrange->Caption = ATitle;
		  ShowBorderArrange->whatShow = awhatShow;
	 break;
	 case SHOW_PHISIC_BORDER:
		  ShowBorderPhisic = new TShowBorder(Application);
		  ShowBorderPhisic->Caption = ATitle;
		  ShowBorderPhisic->whatShow = awhatShow;
	 break;
	 case SHOW_CALCULATE:
	 case SHOW_EQULINES_PSI:
		  ShowCalculate = new TShowBorder(Application);
		  ShowCalculate->Caption = ATitle;
		  ShowCalculate->whatShow = awhatShow;
	 break;
  }
*/
}

//---------------------------------------------------------------------------


void __fastcall TImpulseWindow::IDMCalcParam(TObject *Sender)
{
 ParametersDlg->Show();
}
//---------------------------------------------------------------------------



void __fastcall TImpulseWindow::IDMCalcStaticClick(TObject *Sender)
{
  if (MathModel == NULL)	{
	  Application->MessageBox("Модель не проинициализирована.", "Модель", MB_OK | MB_ICONSTOP);
  } else {
	 // CalcWindow->SetFields("Расчет", 50);
	 // CalcWindow->Show(); // SW_SHOWMAXIMIZED
	 if (ShowCalculate  == NULL)	{
		 ShowCalculate = CreateShowBorderWindow("Расчет (стационарный режим)", SHOW_EQULINES_PSI);
	 }
	 MathModel->CalcLaplas();
 /*
	 if (ShowEquV == NULL) {
		 ShowEquV = CreateShowBorderWindow("Линии равных напряженностей", SHOW_EQULINES_V);
	 }
	 if (ShowEquU == NULL) {
		ShowEquU = CreateShowBorderWindow( "Линии равных энергий", SHOW_EQULINES_U);
	 }
*/
	 // CalcWindow->CalcDOIT = TRUE;
/*
	 CalcWin->Show(SW_MINIMIZE);
	 MathModel->SetMaxValue();
	  if (ShowEquV!=NULL) ShowEquV->MaxValue = MathModel->MaxValue_V;
	  if (ShowEquL!=NULL) ShowEquL->MaxValue = MathModel->MaxValue_Psi;
	  if (ShowEquJ!=NULL) ShowEquJ->MaxValue = MathModel->MaxValue_J;
	  if (ShowEquU!=NULL) ShowEquU->MaxValue = MathModel->MaxValue_U;
*/
   }
}
//---------------------------------------------------------------------------




void __fastcall TImpulseWindow::IDMCalcDynamicPClick(TObject *Sender)
{
 if (MathModel==NULL) {
	 Application->MessageBox("Модель не проинициализирована.", "Модель", MB_OK | MB_ICONSTOP);
 } else {
	 double tau = MathModel->GetTau();
	 int NIter = (int)ceil(MathModel->Parameters.Ttotal/tau);
	 // if (AllPress->NumIter < NIter) AllPress->Halt();
	 // if (AllPress->NumIter==0)      AllPress->Init(NIter, MathModel->N);

	  WMBeginCalcDynamic('P', "Расчет P(t)");
	 //CalcWindow->CalcDOIT = true;
	 //CalcWindow->Refresh();
  }
}
//---------------------------------------------------------------------------

void __fastcall TImpulseWindow::IDMCalcDynamicVClick(TObject *Sender)
{
  if (MathModel==NULL) {
	Application->MessageBox("Модель не проинициализирована.", "Модель", MB_OK | MB_ICONSTOP);
 } else {

	 double tau = MathModel->GetTau();
	 int NIter = (int)ceil(MathModel->Parameters.Ttotal/tau);
	 // if (AllPress->NumIter < NIter) AllPress->Halt();
	 // if (AllPress->NumIter==0)      AllPress->Init(NIter, MathModel->N);

  /*
	 if (AllPress->NumIter==0) {
		double tau = MathModel->GetTau();
		int NIter = (int)ceil(MathModel->Parameters.Ttotal/tau);
		AllPress->Init(NIter, MathModel->N);
	 }
  */

  	  WMBeginCalcDynamic('V', "Расчет V(t)");
	 //CalcWindow->CalcDOIT = true;
	 //CalcWindow->Refresh();
  }

}
//---------------------------------------------------------------------------


void __fastcall TImpulseWindow :: WMBeginCalcDynamic(const char aWhatCalc, const String ATitle)
 {
  if (MathModel==NULL) {
	  Application->MessageBox("Модель не проинициализирована.", "Модель", MB_OK | MB_ICONSTOP);
  } else {
	  if (CalcWindow == NULL)  {
		 CalcWindow = new TCalcWindow(Application);
		 CalcWindow->SetFields("Расчет ...");
		 CalcP1 = new TCalcWindow(Application);
		 CalcP1->SetFields("P1max(t)");
		 CalcP2 = new TCalcWindow(Application);
		 CalcP2->SetFields("P2max(t)");
		 CalcEp = new TCalcWindow(Application);
		 CalcEp->SetFields("Epmax(t)");
		 CalcEk = new TCalcWindow(Application);
		 CalcEk->SetFields("Ekmax(t)");

		 PressOne = new TPressOne(Application);
		 PressOne->Caption = "Давления в особой точке";

		 PressWin = new TPressWin(Application);
		 PressWin->Caption = "Спектр давлений";
		 double tau = MathModel->GetTau();
		 int NIter = (int)ceil(MathModel->Parameters.Ttotal/tau);
		 PressWin->Init(NIter, MathModel->N);
	  }
	  MathModel->WhatCalc = aWhatCalc;
	  if (ShowCalculate == NULL) {
		ShowCalculate = CreateShowBorderWindow(ATitle, SHOW_CALCULATE);
		ShowCalculate->ScaleShow = ModelConf->Scale;
        ShowCalculate->WindowState = wsMaximized;
	  }
	  MathModel->CalcWaveProcess();
	  // CalcWindow->CalcDOIT = true;
	  // CalcWin->Show(SW_MINIMIZE);
  }
 }


void __fastcall TImpulseWindow::IDMCalcSetZeroClick(TObject *Sender)
{
  //ForEach(ShowMinimize, NULL);
  if (MathModel != NULL)    MathModel->SetZero();
  if (CalcWindow != NULL)   CalcWindow->SetZero();
  if (CalcP1 != NULL) {
	 CalcP1->SetZero();
	 CalcP2->SetZero();
	 CalcEp->SetZero();
	 CalcEk->SetZero();
	 PressOne->SetZero();
	 PressWin->Halt();
  }
}
//---------------------------------------------------------------------------

void __fastcall TImpulseWindow::IDMShowEquLinesClick(TObject *Sender)
{
  if (MathModel==NULL) {
	  Application->MessageBox("Модель не проинициализирована.", "Модель", MB_OK | MB_ICONSTOP);
  } else {
	  /*
	  if (ShowEquL == NULL)	{
		ShowEquL = CreateShowBorderWindow("Эквипотенциальные линии", SHOW_EQULINES_PSI);
	  }

	  if (ShowEquJ == NULL)	{
		ShowEquJ = CreateShowBorderWindow("Линии тока", SHOW_EQULINES_J);
	  }

	  if (ShowChannel == NULL)	{
		ShowChannel = CreateShowBorderWindow("Канал пробоя", SHOW_CHANNEL);
	  }
	  */
  }
}
//---------------------------------------------------------------------------






void __fastcall TImpulseWindow::IDMShowEquSpeedClick(TObject *Sender)
{
	 if (ShowEquV == NULL) {
		 ShowEquV = CreateShowBorderWindow("Линии равных напряженностей", SHOW_EQULINES_V);
	 }

}
//---------------------------------------------------------------------------

void __fastcall TImpulseWindow::IDMShowEquLinesUClick(TObject *Sender)
{
	 if (ShowEquU == NULL) {
		ShowEquU = CreateShowBorderWindow( "Линии равных энергий", SHOW_EQULINES_U);
	 }
}
//---------------------------------------------------------------------------



void __fastcall TImpulseWindow::Init2Click(TObject *Sender)
{
if (MathModel != NULL) delete MathModel;

 MathModel = new CModel2D(&(ModelConf->drawList));
 MathModel->Organise();
 MathModel->Set(2);

 if (ShowBorderArrange == NULL) {
   ShowBorderArrange = CreateShowBorderWindow("Геометрические признаки границ", SHOW_ARRANGE_BORDER);
 }  else {
   ShowBorderArrange->Refresh();
}
 if (ShowBorderPhisic == NULL) {
	ShowBorderPhisic = CreateShowBorderWindow( "Физические признаки границ", SHOW_PHISIC_BORDER);
 } else {
	ShowBorderPhisic->Refresh();
}
}
//---------------------------------------------------------------------------

void __fastcall TImpulseWindow::Init3Click(TObject *Sender)
{
if (MathModel != NULL) delete MathModel;

 MathModel = new CModel2D(&(ModelConf->drawList));
 MathModel->Organise();
 MathModel->Set(3);

 if (ShowBorderArrange == NULL) {
   ShowBorderArrange = CreateShowBorderWindow("Геометрические признаки границ", SHOW_ARRANGE_BORDER);
 }  else {
   ShowBorderArrange->Refresh();
}
 if (ShowBorderPhisic == NULL) {
	ShowBorderPhisic = CreateShowBorderWindow( "Физические признаки границ", SHOW_PHISIC_BORDER);
 } else {
	ShowBorderPhisic->Refresh();
}
}
//---------------------------------------------------------------------------

void __fastcall TImpulseWindow::Init4Click(TObject *Sender)
{
if (MathModel != NULL) delete MathModel;

 MathModel = new CModel2D(&(ModelConf->drawList));
 MathModel->Organise();
 MathModel->Set(4);

if (ShowBorderArrange == NULL) {
   ShowBorderArrange = CreateShowBorderWindow("Геометрические признаки границ", SHOW_ARRANGE_BORDER);
 }  else {
   ShowBorderArrange->Refresh();
}
 if (ShowBorderPhisic == NULL) {
	ShowBorderPhisic = CreateShowBorderWindow( "Физические признаки границ", SHOW_PHISIC_BORDER);
 } else {
	ShowBorderPhisic->Refresh();
}
}
//---------------------------------------------------------------------------



void __fastcall TImpulseWindow::btnMoveClick(TObject *Sender)
{
	ModelConf->drawList.PrintAllPoint();
}
//---------------------------------------------------------------------------

void __fastcall TImpulseWindow::N4Click(TObject *Sender)
{
	if (N4->Checked)	{
		bBlackWhite = TRUE;
	} else {
		bBlackWhite = FALSE;
	}
}
//---------------------------------------------------------------------------


// ПРОЕКТ:     Математическая 2D-модель волновых процессов
// ВЕРСИЯ:     2.0
// ФАЙЛ:       TImpWinII.h
// ДАТА:       08/98
// АВТОР:      Штифанов А.И.
// СОДЕРЖАНИЕ: Описание классов и структур данных
//---------------------------------------------------------------------------
#ifndef TImpWinIIH
#define TImpWinIIH
//---------------------------------------------------------------------------
#include <vcl\sysutils.hpp>
#include <vcl\windows.hpp>
#include <vcl\messages.hpp>
#include <vcl\sysutils.hpp>
#include <vcl\classes.hpp>
#include <vcl\graphics.hpp>
#include <vcl\controls.hpp>
#include <vcl\forms.hpp>
#include <vcl\dialogs.hpp>
#include <vcl\stdctrls.hpp>
#include <vcl\buttons.hpp>
#include <vcl\extctrls.hpp>
#include <vcl\menus.hpp>
#include <vcl\ComCtrls.hpp>
#include <iostream.h>
#include <fstream.h>
#include <iomanip.h>
#include <Buttons.hpp>
#include <Classes.hpp>
#include <Controls.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
#include <ActnList.hpp>
#include <ImgList.hpp>

#include "TShowBorder.h"

//---------------------------------------------------------------------------
class TImpulseWindow : public TForm
{
__published:
	TStatusBar *StatusLine;
	TOpenDialog *OpenDialog;
	TSaveDialog *SaveDialog;
	TPrintDialog *PrintDialog;
	TPrinterSetupDialog *PrintSetupDialog;
	TPanel *SpeedBar;
        TSpeedButton *CreateButton;
        TSpeedButton *OpenButton;
        TSpeedButton *SaveButton;  // &Arrange All
	TSpeedButton *SpeedButton11;  // &Contents
        TMainMenu *ConfMenu;
        TMenuItem *menuModel;
        TMenuItem *IDMQuit;
        TMenuItem *N5;
        TMenuItem *IDMInitModel;
        TMenuItem *N6;
        TMenuItem *IDMParameters;
        TMenuItem *N8;
        TMenuItem *IDMListBorders;
        TMenuItem *N10;
        TMenuItem *IDMSaveModelAs;
        TMenuItem *N12;
        TMenuItem *N13;
        TMenuItem *N14;
        TMenuItem *N3772;
        TMenuItem *N15;
        TMenuItem *IDMSaveModel;
        TMenuItem *N16;
        TMenuItem *N17;
        TMenuItem *N18;
        TMenuItem *N19;
        TMenuItem *N3773;
        TMenuItem *N20;
        TMenuItem *IDMOpenModel;
        TMenuItem *IDMCreateModel;
        TMenuItem *menuCalc;
        TMenuItem *IDMCalcSetZero;
        TMenuItem *N34;
        TMenuItem *IDMCalcDynamicV;
        TMenuItem *IDMCalcDynamicP;
        TMenuItem *N36;
        TMenuItem *IDMCalcStatic;
        TMenuItem *menuView;
        TMenuItem *N41;
        TMenuItem *N42;
        TMenuItem *N43;
	TMenuItem *IDMShowEquLinesU;
	TMenuItem *IDMShowEquSpeed;
	TMenuItem *IDMShowEquLines;
        TMenuItem *N47;
        TMenuItem *N3777;
        TMenuItem *menuHelp;
        TMenuItem *N52;
        TMenuItem *N53;
        TMenuItem *N3778;
        TMenuItem *tF11;
        TMenuItem *menuWindow;
        TMenuItem *IDMCascade;
        TMenuItem *IDMTile;
        TMenuItem *N1;
        TSpeedButton *ParamButton;
        TSpeedButton *InitButton;
        TSpeedButton *SaveAsButton;
        TSpeedButton *CalcStButton;
        TSpeedButton *SpeedButton1;
        TSpeedButton *SpeedButton2;
	TActionList *ActionList1;
	TAction *ActionCreateModel;
	TImageList *ImageList1;
	TAction *ActionOpenModel;
	TAction *ActionSaveModel;
	TAction *ActionSaveAsModel;
	TAction *ActionParameters;
	TAction *ActionInitModel;
	TAction *ActionCalcStatic;
	TAction *ActionCalcDynamicP;
	TAction *ActionCalcDynamicV;
	TAction *ActionCalcSetZero;
	TSpeedButton *SpeedButton3;
	TMenuItem *N2;
	TSpeedButton *Init2;
	TSpeedButton *Init3;
	TSpeedButton *Init4;
	TSpeedButton *btnMove;
	TMenuItem *N3;
	TMenuItem *N4;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall ShowHint(TObject *Sender);
	void __fastcall FilePrint(TObject *Sender);
	void __fastcall FilePrintSetup(TObject *Sender);
	void __fastcall EditUndo(TObject *Sender);
	void __fastcall EditCut(TObject *Sender);
	void __fastcall EditCopy(TObject *Sender);
	void __fastcall EditPaste(TObject *Sender);
	void __fastcall WindowTile(TObject *Sender);
	void __fastcall WindowCascade(TObject *Sender);
	void __fastcall WindowArrange(TObject *Sender);
	void __fastcall HelpContents(TObject *Sender);
	void __fastcall HelpSearch(TObject *Sender);
	void __fastcall HelpHowToUse(TObject *Sender);
	void __fastcall HelpAbout(TObject *Sender);
	void __fastcall IDMCreateModelClick(TObject *Sender);
	void __fastcall IDMOpenModelClick(TObject *Sender);
	void __fastcall IDMQuitClick(TObject *Sender);
	void __fastcall IDMSaveModelClick(TObject *Sender);
	void __fastcall IDMSaveModelAsClick(TObject *Sender);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
	void __fastcall IDMInitModelClick(TObject *Sender);
	void __fastcall IDMCalcParam(TObject *Sender);
	void __fastcall IDMCalcStaticClick(TObject *Sender);
	void __fastcall IDMCalcDynamicPClick(TObject *Sender);
	void __fastcall IDMCalcDynamicVClick(TObject *Sender);
	void __fastcall IDMCalcSetZeroClick(TObject *Sender);
	void __fastcall IDMShowEquLinesClick(TObject *Sender);
	void __fastcall IDMShowEquSpeedClick(TObject *Sender);
	void __fastcall IDMShowEquLinesUClick(TObject *Sender);
	void __fastcall Init2Click(TObject *Sender);
	void __fastcall Init3Click(TObject *Sender);
	void __fastcall Init4Click(TObject *Sender);
	void __fastcall btnMoveClick(TObject *Sender);
	void __fastcall N4Click(TObject *Sender);
private:        // private user declarations
public:         // public user declarations
	BOOL IsNewFile, IsDirty;
	virtual __fastcall TImpulseWindow(TComponent* Owner);
	TShowBorder* __fastcall CreateShowBorderWindow(const String ATitle, EWhatShow awhatShow);
	void __fastcall WMBeginCalcDynamic(const char aWhatCalc, const String ATitle);
	void __fastcall Read(ifstream &fr);
	void __fastcall Write(ofstream &fw);
};
//---------------------------------------------------------------------------
extern TImpulseWindow *ImpulseWindow;
//---------------------------------------------------------------------------
#endif

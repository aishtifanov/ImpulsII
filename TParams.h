//----------------------------------------------------------------------------
#ifndef TParamsH
#define TParamsH
//----------------------------------------------------------------------------
#include <vcl\ExtCtrls.hpp>
#include <vcl\ComCtrls.hpp>
#include <vcl\Buttons.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Controls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\Graphics.hpp>
#include <vcl\Classes.hpp>
#include <vcl\SysUtils.hpp>
#include <vcl\Windows.hpp>
#include <vcl\System.hpp>
//----------------------------------------------------------------------------
class TParametersDlg : public TForm
{
__published:
	TPanel *Panel1;
        TPanel *Panel2;
        TButton *OKBtn;
        TButton *CancelBtn;
        TButton *HelpBtn;
        TGroupBox *GroupBox4;
        TLabel *Label17;
	TEdit *NumLevel;
        TLabel *Label18;
	TEdit *sAutoSaveIter;
        TLabel *Label19;
        TGroupBox *GroupBox5;
        TLabel *Label20;
        TLabel *Label21;
	TEdit *xCoord;
        TLabel *Label22;
	TEdit *yCoord;
        TLabel *Label23;
	TEdit *sNtrub;
        TLabel *Label24;
	TEdit *sDelitel;
	TGroupBox *gbSChoicePlane;
	TRadioButton *Model2D;
	TRadioButton *ModelFiZR;
	TPanel *Panel3;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	TLabel *Label5;
	TLabel *Label6;
	TLabel *Label7;
	TLabel *Label8;
	TEdit *sDensity;
	TEdit *sSoundSpeed;
	TEdit *sBeginPressing;
	TEdit *sTimeMax;
	TPanel *Panel4;
	TLabel *Label9;
	TLabel *Label10;
	TEdit *sStep;
	TGroupBox *GroupBox2;
	TLabel *Label16;
	TEdit *sOmega;
	TGroupBox *GroupBox1;
	TLabel *Label11;
	TLabel *Label12;
	TLabel *Label13;
	TLabel *Label14;
	TLabel *Label15;
	TEdit *sTimeSwitch;
	TEdit *sEpsilon;
	TEdit *sTtotal;
	TLabel *Label25;
	TEdit *sQEquLine;
	TGroupBox *gbSParamCalc;
	TRadioButton *bLeftRight;
	TRadioButton *bRightLeft;
	TRadioButton *bFromCenter;
	TRadioButton *bToCenter;
	TRadioButton *bTwoWhile;
	void __fastcall OKBtnClick(TObject *Sender);
	void __fastcall CancelBtnClick(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormActivate(TObject *Sender);
        
        
        
private:
public:
	virtual __fastcall TParametersDlg(TComponent* AOwner);
	void __fastcall 	SetParametersAfterLoad();
	void __fastcall 	SetParametersBeforeSave();
};
//----------------------------------------------------------------------------
extern TParametersDlg *ParametersDlg;
//----------------------------------------------------------------------------
#endif

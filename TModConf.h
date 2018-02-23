// œ–Œ≈ “:     Ã‡ÚÂÏ‡ÚË˜ÂÒÍ‡ˇ 2D-ÏÓ‰ÂÎ¸ ‚ÓÎÌÓ‚˚ı ÔÓˆÂÒÒÓ‚
// ¬≈–—»ﬂ:     2.0
// ‘¿…À:       Graphwin.H
// ƒ¿“¿:       07/98
// ¿¬“Œ–:      ÿÚËÙ‡ÌÓ‚ ¿.».
// —Œƒ≈–∆¿Õ»≈: ŒÔËÒ‡ÌËÂ ÍÎ‡ÒÒÓ‚ Ë ÒÚÛÍÚÛ ‰‡ÌÌ˚ı

//---------------------------------------------------------------------------
#ifndef graphwinH
#define graphwinH
//---------------------------------------------------------------------------
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Controls.hpp>
#include <Classes.hpp>
#include <Menus.hpp>
#include <Dialogs.hpp>
#include <ComCtrls.hpp>
#include <Buttons.hpp>
#include <StdCtrls.hpp>

#include "impulse.hpp"
#include <vcl\Mask.hpp>
//---------------------------------------------------------------------------

class TModelConf : public TForm
{
__published:
    TPanel *Panel1;
    TScrollBox *ScrollBox1;
    TImage *Image;
    TStatusBar *StatusBar1;
    TSpeedButton *PieceButton;
    TSpeedButton *CircleButton;
    TSpeedButton *NotchButton;
    TSpeedButton *SelectButton;
    TSpeedButton *EraseButton;
    TBevel *Bevel1;
    TSpeedButton *CopyButton;

        TBevel *Bevel2;
        TSpeedButton *ZoomInButton;
        TLabel *ScaleLabel;
        TSpeedButton *ZoomOutButton;
        TBevel *Bevel3;
        TSpeedButton *GridButton;
        TSpeedButton *SnapButton;
        TBevel *Bevel4;
        TSpeedButton *RedrawButton;
        TPanel *Panel2;
        TSpeedButton *BlueButton;
        TSpeedButton *GreenButton;
        TSpeedButton *RedButton;
        TSpeedButton *CyanButton;
        TSpeedButton *BlackButton;
        TPanel *Panel3;
        TLabel *LabelX1;
        TLabel *LabelY1;
        TMaskEdit *MaskEditX1;
        TMaskEdit *MaskEditY1;
        TLabel *LabelX2;
        TMaskEdit *MaskEditX2;
        TLabel *LabelY2;
        TMaskEdit *MaskEditY2;
        TLabel *Label6;
        TComboBox *ePhisicBox;
        TLabel *Label8;
        TEdit *ValuePsiEdit;
        TComboBox *SelectBox;
        TLabel *LabelLength;
        TComboBox *eArrangeBox;
        TButton *CreateGOButton;
        TMaskEdit *MaskEditR;
    void __fastcall SelectButtonClick(TObject *Sender);
    void __fastcall NotchButtonClick(TObject *Sender);
    void __fastcall CircleButtonClick(TObject *Sender);
    void __fastcall PieceButtonClick(TObject *Sender);

    void __fastcall FormMouseDown(TObject *Sender, TMouseButton Button,
                                  TShiftState Shift, int X, int Y);
    void __fastcall FormMouseMove(TObject *Sender, TShiftState Shift,
                                  int X, int Y);




        void __fastcall FormPaint(TObject *Sender);
        void __fastcall EraseButtonClick(TObject *Sender);
        void __fastcall RedrawButtonClick(TObject *Sender);
        void __fastcall CopyButtonClick(TObject *Sender);
        void __fastcall ZoomInButtonClick(TObject *Sender);
        void __fastcall ZoomOutButtonClick(TObject *Sender);
        void __fastcall GridButtonClick(TObject *Sender);
        
        void __fastcall BlueButtonClick(TObject *Sender);
        void __fastcall GreenButtonClick(TObject *Sender);
        void __fastcall RedButtonClick(TObject *Sender);
        void __fastcall CyanButtonClick(TObject *Sender);
        void __fastcall BlackButtonClick(TObject *Sender);
        
        

        void __fastcall MaskEditX1Change(TObject *Sender);
        void __fastcall MaskEditY1Change(TObject *Sender);
        void __fastcall MaskEditX2Change(TObject *Sender);
        void __fastcall MaskEditY2Change(TObject *Sender);
        void __fastcall MaskEditRChange(TObject *Sender);
        void __fastcall ValuePsiEditChange(TObject *Sender);
        void __fastcall ePhisicBoxChange(TObject *Sender);
        void __fastcall eArrangeBoxChange(TObject *Sender);
        void __fastcall SelectBoxChange(TObject *Sender);
        void __fastcall CreateGOButtonClick(TObject *Sender);
private:
public:
        bool Drawing; // œ–»«Õ¿  Õ¿◊¿À¿ ¬€◊≈–◊»¬¿Õ»ﬂ Œ¡⁄≈ “Œ¬
        bool Semaphor;
        TPoint Origin, MovePt;
        EWhatIt DrawingTool;


         // œ–»«Õ¿  ◊≈–“≈∆ÕŒ√Œ »Õ—“–”Ã≈Õ“¿
        int AllClick, NumClick;
        int X1, Y1, X2, Y2, X3, Y3, R;

        // struct TState {
           // TDrawTool  *DrawTool;
           // HBITMAP    BitMap;
           int        PenSize;
           COLORREF   PenColor;
           // int        RPoint;
           CDrawList  drawList;
           //TCanvas    *currCanvas;
           HFONT      hFont;
           int        Scale;
           BOOL       OSnapPoint; // œ–»«Õ¿  œ–»¬ﬂ« »   “Œ◊ ≈
        // };
        CDrawElement *selectDE;

        void __fastcall DrawShape(TPoint TopLeft, TPoint BottomRight, TPenMode AMode);
        CDrawElement* __fastcall AddToList(void);
        void __fastcall ClearPicture(void);
        void __fastcall SelectGeometryObject(int X, int Y);
        virtual __fastcall TModelConf(TComponent* Owner);

        void __fastcall Read(ifstream &fr);
        void __fastcall Write(ofstream &fw);

};
//---------------------------------------------------------------------------
extern TModelConf *ModelConf;
//---------------------------------------------------------------------------
#endif


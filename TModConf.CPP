// ПРОЕКТ:     Математическая 2D-модель волновых процессов
// ВЕРСИЯ:     2.0
// ФАЙЛ:       graphwin.cPP
// ДАТА:       07/98
// АВТОР:      Штифанов А.И.
// СОДЕРЖАНИЕ: Описание классов и структур данных

#include <vcl.h>
#pragma hdrstop


#include <math.h>
#include "TModConf.h"

// МАССИВ ДЛЯ ГРАДИЕНТНЫХ ЦВЕТОВ
COLORREF  BGIColor2[1000];


// МАССИВ 16 БАЗОВЫХ ЦВЕТОВ
COLORREF  BGIColor[16]= {
		 RGB(0,0,0), //BLACK
		 RGB(0,0,127), //BLUE
		 RGB(0,127,0),   //GREEN
		 RGB(0,127,127), //CYAN
		 RGB(127,0,0), //RED
		 RGB(127,0,127), //MAGENTA
		 RGB(127,127,0), //BROWN
		 RGB(192,192,192), //LIGHTGRAY
		 RGB(127,127,127), //DARKGRAY
		 RGB(0,0,255), //LIGHTBLUE
		 RGB(0,255,0), // LIGHTGREEN
		 RGB(0,255,255), //LIGHTCYAN
		 RGB(255,0,0),//LIGHTRED
		 RGB(255,0,255),  //LIGHTMAGENTA,
		 RGB(255,255,0), //YELLOW,
		 RGB(255,255,255) //WHITE
};

// МАССИВ ЦВЕТОВ, ИСПОЛЬЗУЕМЫХ ПРИ РИСОВАНИИ
COLORREF  GmtryColor[3]= {
		  RGB(0,0,255), //LIGHTBLUE
		  RGB(0,127,0),   //GREEN
		  RGB(255,0,0)  //LIGHTRED
};


bool PressCopy;
int  deltaZoom = 1;
bool InitMaskEdit = false;
COLORREF oldPenColor;

//---------------------------------------------------------------------------
#pragma resource "*.dfm"
TModelConf* ModelConf;

//---------------------------------------------------------------------------
__fastcall TModelConf::TModelConf(TComponent* Owner) : TForm(Owner)
{

/*
 Graphics::TBitmap *Bitmap;
  Bitmap = new Graphics::TBitmap();
 Bitmap->Width  = 1000;
 Bitmap->Height = 1000;
 Image->Picture->Graphic = Bitmap;

 Graphics::TMetafile *Metafile;
  Metafile = new Graphics::TMetafile();
 Metafile->Width  = 1000;
 Metafile->Height = 1000;
 Image->Picture->Graphic = Metafile;
 */

 Image->Canvas->MoveTo(0,0);
 Image->Canvas->Pen->Style = psSolid;
 Image->Canvas->Brush->Style = bsClear;
 Image->Cursor = crDefault;
 Image->Canvas->Pen->Color = GmtryColor[0];
 AllClick = 1;
 NumClick = 0;
 PenColor = GmtryColor[0];
 Scale = 1;
}

//---------------------------------------------------------------------------
void __fastcall TModelConf::SelectButtonClick(TObject *Sender)
{
  DrawingTool = IT_SELECT;
  Image->Cursor = crDefault;
  AllClick = 1;
  NumClick = 0;
}
//---------------------------------------------------------------------------
void __fastcall TModelConf::PieceButtonClick(TObject *Sender)
{
  DrawingTool = IT_PIECE;
  Image->Cursor = crCross;
  AllClick = 2;
  NumClick = 0;
}
//---------------------------------------------------------------------
void __fastcall TModelConf::CircleButtonClick(TObject *Sender)
{
  DrawingTool = IT_CIRCLE;
  Image->Cursor = crCross;
  AllClick = 2;
  NumClick = 0;
}
//---------------------------------------------------------------------
void __fastcall TModelConf::NotchButtonClick(TObject *Sender)
{
  DrawingTool = IT_NOTCH;
  Image->Cursor = crCross;
  AllClick = 3;
  NumClick = 0;
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------
void __fastcall TModelConf::FormMouseDown(TObject *Sender, TMouseButton Button,
      TShiftState Shift, int X, int Y)
{
  int oldX = X, oldY = Y;
  if (SnapButton->Down)  {
     int xb = X/Scale, yb = Y/Scale;
     drawList.FindPoint(xb, yb, NULL);
     X = xb*Scale; Y = yb*Scale;
  }

  Drawing = True;
  Image->Canvas->MoveTo(X, Y);
  Origin = Point(X, Y);
  MovePt = Origin;
  TVarRec tempvar[2] = {X/Scale, Y/Scale};

  switch (AllClick) {
     case 1: Drawing=FALSE;
             SelectGeometryObject(oldX, oldY);
     break;
     case 2: NumClick++;
             switch(NumClick)  {
                case 1:
                   StatusBar1->Panels->Items[0]->Text = Format("%d,%d", tempvar, 2);
                   X1 = X;
                   Y1 = Y;
                break;
                case 2:
                /*
                  if (SnapButton->Down)  {
                     int xb = X/Scale, yb = Y/Scale;
                     drawList.FindPoint(xb, yb, NULL);
                     if (X1 != xb && Y1 != yb)
                        X = xb*Scale; Y = yb*Scale;
                  }
                */
                   if (SnapButton->Down)  {
                       Origin = Point(X1, Y1);
                       DrawShape(Origin, Point(oldX, oldY), pmNotXor);
                   }
                   DrawShape(Origin, Point(X, Y), pmCopy);
                   Drawing=FALSE;
                   NumClick = 0;
                   StatusBar1->Panels->Items[1]->Text = Format("%d,%d", tempvar, 2);
                   AddToList();
                break;
             }
     break;
     case 3: NumClick++;
             switch(NumClick)  {
                case 1:
                   Semaphor = true;
                   StatusBar1->Panels->Items[0]->Text = Format("%d,%d", tempvar, 2);
                   X1 = X;
                   Y1 = Y;
                break;
                case 2:
                   Semaphor = false;
                break;
                case 3:
                   if (SnapButton->Down)  {
                       Origin = Point(X1, Y1);
                       DrawShape(Origin, Point(oldX, oldY), pmNotXor);
                   }
                   DrawShape(Origin, Point(X, Y), pmCopy);
                   Semaphor = true;
                   Drawing=FALSE;
                   NumClick = 0;
                   StatusBar1->Panels->Items[1]->Text = Format("%d,%d", tempvar, 2);
                   AddToList();
                break;
             }
     break;
  }
}
//---------------------------------------------------------------------
void __fastcall TModelConf::FormMouseMove(TObject *Sender, TShiftState Shift,
      int X, int Y)
{
  TVarRec tempvar[2] = {X/Scale, Y/Scale};

  if (Drawing)   {
    DrawShape(Origin, MovePt, pmNotXor);
    MovePt = Point(X, Y);
    DrawShape(Origin, MovePt, pmNotXor);
  }

  int sbItem = NumClick;
  if (NumClick == 2) sbItem = 1;
  StatusBar1->Panels->Items[sbItem]->Text = Format("%d,%d", tempvar, 2);
}

//---------------------------------------------------------------------
void __fastcall TModelConf::DrawShape(TPoint TopLeft, TPoint BottomRight, TPenMode AMode)
{

  Image->Canvas->Pen->Mode = AMode;


  switch (DrawingTool){

     case IT_PIECE : {
        X2 = BottomRight.x;
        Y2 = BottomRight.y;
        DWORD tmp1 = (DWORD)(X2 - X1)*(DWORD)(X2 - X1);
        DWORD tmp2 = (DWORD)(Y2 - Y1)*(DWORD)(Y2 - Y1);
        DWORD d = tmp1 + tmp2;
        R =  (int)sqrt((double)d);
        TVarRec tempvar[1] = {R};
        StatusBar1->Panels->Items[2]->Text = Format("%d", tempvar, 1);

        Image->Canvas->MoveTo(TopLeft.x, TopLeft.y);
        Image->Canvas->LineTo(BottomRight.x, BottomRight.y);
     break; }

     case IT_CIRCLE: {
        X2 = BottomRight.x;
        Y2 = BottomRight.y;
        DWORD tmp1 = (DWORD)(X2 - X1)*(DWORD)(X2 - X1);
        DWORD tmp2 = (DWORD)(Y2 - Y1)*(DWORD)(Y2 - Y1);
        DWORD d = tmp1 + tmp2;
        R =  (int)sqrt((double)d);
        TVarRec tempvar[1] = {R};
        StatusBar1->Panels->Items[2]->Text = Format("%d", tempvar, 1);

        Image->Canvas->Ellipse(X1-R, Y1-R, X1+R, Y1+R);
     break; }

     case IT_NOTCH : {

        if (NumClick == 1)  {
           X2 = BottomRight.x;
           Y2 = BottomRight.y;
           int xLeft = X1-R;
           int yTop  = Y1-R;
           int xRight= X1+R;
           int yBot  = Y1+R;
           DWORD tmp1 = (DWORD)(X2 - X1)*(DWORD)(X2 - X1);
           DWORD tmp2 = (DWORD)(Y2 - Y1)*(DWORD)(Y2 - Y1);
           DWORD d = tmp1 + tmp2;
           R =  (int)sqrt((double)d);
           TVarRec tempvar[1] = {R};
           StatusBar1->Panels->Items[2]->Text = Format("%d", tempvar, 1);
           Image->Canvas->MoveTo(X1, Y1);
           Image->Canvas->LineTo(X2, Y2);
 //          Image->Canvas->Ellipse(xLeft, yTop, xRight, yBot);
           X3 = X2;
           Y3 = Y2;
        }
        else  {
           X3 = BottomRight.x;
           Y3 = BottomRight.y;

           DWORD tmp1 = (DWORD)(X3 - X1)*(DWORD)(X3 - X1);
           DWORD tmp2 = (DWORD)(Y3 - Y1)*(DWORD)(Y3 - Y1);
           DWORD d = tmp1 + tmp2;
           R =  (int)sqrt((double)d);
           int xLeft = X1-R;
           int yTop  = Y1-R;
           int xRight= X1+R;
           int yBot  = Y1+R;
           TVarRec tempvar[1] = {R};
           StatusBar1->Panels->Items[2]->Text = Format("%d", tempvar, 1);

           if (Semaphor == FALSE)  {
              Semaphor = TRUE;
              Image->Canvas->MoveTo(X1, Y1);
              Image->Canvas->LineTo(X3, Y3);
              // Image->Canvas->Ellipse(xLeft, yTop, xRight, yBot);
           }
           else
              Image->Canvas->Arc(xLeft, yTop, xRight, yBot, X2, Y2, X3, Y3);
       }
     break; }
  }
}


CDrawElement* __fastcall TModelConf::AddToList(void)
{
  CDrawElement* _DE;
  switch (DrawingTool)  {
     case IT_PIECE :  {
        CPiece *Piece = new CPiece(X1/Scale, Y1/Scale, X2/Scale, Y2/Scale, "", "", PenColor);
        drawList.Add(Piece);
        _DE = Piece;
     break; }

     case IT_CIRCLE: {
        CCircle *Circle = new CCircle(X1/Scale, Y1/Scale, R/Scale, "", PenColor);
        drawList.Add(Circle);
        _DE = Circle;
     break; }

     case IT_NOTCH : {
        CNotch *Notch = new CNotch(X1/Scale, Y1/Scale, X2/Scale, Y2/Scale, X3/Scale, Y3/Scale, R/Scale, "", PenColor);
        drawList.Add(Notch);
        _DE = Notch;
     break; }
  }
  return _DE;
}


void __fastcall TModelConf::FormPaint(TObject *Sender)
{
// Image->Picture->Clear();
 RECT r;
 drawList.GetRectPicture(&r);

 TRect tr(r);
 Image->Canvas->FillRect(tr);
 drawList.DrawAllList(Image->Canvas->Handle, Scale);
}
//---------------------------------------------------------------------------
void __fastcall TModelConf::EraseButtonClick(TObject *Sender)
{
 if (selectDE != NULL)  {
    int ret = Application->MessageBox("Удалить границу?",
                                      "Операция удаления", MB_YESNO|MB_ICONQUESTION);
    if (ret != IDYES) return;

    // Image->Canvas->Pen->Color = BGIColor[WHITE];
    selectDE->PenColor = BGIColor[WHITE];
    selectDE->Draw(Image->Canvas->Handle, Scale);
    Image->Invalidate();
    drawList.Subtract(selectDE);
    delete selectDE;
    selectDE = NULL;
 }
}

void __fastcall TModelConf::ClearPicture(void)
{
  RECT r;
  drawList.GetRectPicture(&r);

  TRect tr(r);
  tr.Left *= Scale + deltaZoom;
  tr.Top *= Scale + deltaZoom;
  tr.Right *= Scale + deltaZoom;
  tr.Bottom *= Scale + deltaZoom;
  tr.Left -= 5;
  tr.Top -= 5;
  tr.Right += 5;
  tr.Bottom += 5;
  Image->Canvas->Brush->Style = bsSolid;
  Image->Canvas->FillRect(tr);
  Image->Canvas->Brush->Style = bsClear;
  drawList.DrawAllList(Image->Canvas->Handle, Scale);
  Image->Invalidate();

}

//---------------------------------------------------------------------------
void __fastcall TModelConf::RedrawButtonClick(TObject *Sender)
{
  TRect tr;
  tr.Left = Image->Left;
  tr.Top = Image->Top;
  tr.Right = Image->Width;
  tr.Bottom = Image->Height;
  Image->Canvas->Brush->Style = bsSolid;
  Image->Canvas->FillRect(tr);
  Image->Canvas->Brush->Style = bsClear;
  if (GridButton->Down) GridButtonClick(Sender);
  else {
     drawList.DrawAllList(Image->Canvas->Handle, Scale);
     Image->Invalidate();
  }
}
//---------------------------------------------------------------------------
void __fastcall TModelConf::CopyButtonClick(TObject *Sender)
{
 PressCopy = true;
}
//---------------------------------------------------------------------------
void __fastcall TModelConf::ZoomInButtonClick(TObject *Sender)
{
  deltaZoom = -1;
  if (Scale < 5) Scale++;
  Image->Canvas->Pen->Width = Scale;
  char str[5];
  wsprintf(str, "%1d:1", Scale);
  ScaleLabel->Caption = str;
  ClearPicture();
  if (GridButton->Down) GridButtonClick(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TModelConf::ZoomOutButtonClick(TObject *Sender)
{
  deltaZoom = 1;
  if (Scale > 1) Scale--;
  Image->Canvas->Pen->Width = Scale;
  char str[6];
  wsprintf(str, "%1d:1", Scale);
  ScaleLabel->Caption = str;
  ClearPicture();
  if (GridButton->Down) GridButtonClick(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TModelConf::GridButtonClick(TObject *Sender)
{
  if (GridButton->Down) {
     drawList.DrawAllList(Image->Canvas->Handle, Scale);
     
     RECT r;
     drawList.GetRectPicture(&r);

     TRect tr(r);
     tr.Left *= Scale;
     tr.Top *= Scale;
     tr.Right *= Scale;
     tr.Bottom *= Scale;

     Image->Canvas->Pen->Color = BGIColor[LIGHTGRAY];
     Image->Canvas->Pen->Width = 1;
     for (int i=tr.Left; i<=tr.Right; i+=Scale)   {
         Image->Canvas->MoveTo(i, tr.Top);
         Image->Canvas->LineTo(i, tr.Bottom);
     }
     for (int i=tr.Top; i<=tr.Bottom; i+=Scale)   {
         Image->Canvas->MoveTo(tr.Left, i);
         Image->Canvas->LineTo(tr.Right, i);
     }
     Image->Canvas->Pen->Width = Scale;
     Image->Canvas->Pen->Color = PenColor;

     Image->Invalidate();
  }
  else RedrawButtonClick(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TModelConf::BlueButtonClick(TObject *Sender)
{
 Image->Canvas->Pen->Color = GmtryColor[0];
 PenColor = GmtryColor[0];
 if (selectDE != NULL)
     oldPenColor = PenColor;
}
//---------------------------------------------------------------------------
void __fastcall TModelConf::GreenButtonClick(TObject *Sender)
{
 Image->Canvas->Pen->Color = GmtryColor[1];
 PenColor = GmtryColor[1];
 if (selectDE != NULL)
     oldPenColor = PenColor;
}
//---------------------------------------------------------------------------
void __fastcall TModelConf::RedButtonClick(TObject *Sender)
{
 Image->Canvas->Pen->Color = GmtryColor[2];
 PenColor = GmtryColor[2];
 if (selectDE != NULL)
     oldPenColor = PenColor;
}
//---------------------------------------------------------------------------
void __fastcall TModelConf::CyanButtonClick(TObject *Sender)
{
 Image->Canvas->Pen->Color = BGIColor[LIGHTCYAN];
 PenColor = BGIColor[LIGHTCYAN];
 if (selectDE != NULL)
     oldPenColor = PenColor;
}
//---------------------------------------------------------------------------
void __fastcall TModelConf::BlackButtonClick(TObject *Sender)
{
 Image->Canvas->Pen->Color = BGIColor[LIGHTMAGENTA];
 PenColor = BGIColor[LIGHTMAGENTA];
 if (selectDE != NULL)
     oldPenColor = PenColor;
}
//---------------------------------------------------------------------------
int EPhisicToIndex(EBorderPhisic ePhisic)
 {
  int ret;
  switch (ePhisic)  {
     case IT_HARD_BORDER: ret = 0;
     break;
     case IT_FREE_BORDER: ret = 1;
     break;
     case IT_INPUT_BORDER: ret = 2;
     break;
     case IT_OUTPUT_BORDER: ret = 3;
     break;
     case IT_POINT_CENTER: ret = 4;
     break;
     case IT_SYMMETRIC: ret = 5;
     break;
     case IT_MODIFY:  ret = 6;
     break;
     case IT_UNDEFINE: ret = 7;
     break;
  }
  return ret;
}

int EArrangeToIndex(EBorderArrange eArrange)
 {
  int ret;
  switch (eArrange)   {
     case IT_LEFT_BORDER: ret = 0;
     break;
     case IT_RIGHT_BORDER: ret = 1;
     break;
     case IT_TOP_BORDER: ret = 2;
     break;
     case IT_BOTTOM_BORDER: ret = 3;
     break;
     case IT_NO_BORDER: ret = 4;
     break;
  }
  return ret;
}

int IndexToEPhisic(int Index)
 {
  EBorderPhisic ret;
  switch (Index)  {
     case 0: ret = IT_HARD_BORDER;
     break;
     case 1: ret = IT_FREE_BORDER;
     break;
     case 2: ret = IT_INPUT_BORDER;
     break;
     case 3: ret = IT_OUTPUT_BORDER;
     break;
     case 4: ret = IT_POINT_CENTER;
     break;
     case 5: ret = IT_SYMMETRIC;
     break;
     case 6: ret = IT_MODIFY;
     break;
     case 7: ret = IT_UNDEFINE;
     break;
  }
  return ret;
}

int IndexToEArrange(int Index)
 {
  EBorderArrange ret;

  switch (Index)   {
     case 0: ret = IT_LEFT_BORDER;
     break;
     case 1: ret = IT_RIGHT_BORDER;
     break;
     case 2: ret = IT_TOP_BORDER;
     break;
     case 3: ret = IT_BOTTOM_BORDER;
     break;
     case 4: ret = IT_NO_BORDER;
     break;
  }

  return ret;
}


void __fastcall TModelConf::SelectGeometryObject(int X, int Y)
 {
  char str[10];

  if (selectDE != NULL)  {
     selectDE->PenColor = oldPenColor;
     Image->Canvas->Pen->Mode = pmCopy;
     selectDE->Draw(Image->Canvas->Handle, Scale);
     Image->Invalidate();
  }

  int Xfind = X/Scale, Yfind = Y/Scale;
  selectDE = drawList.FindGmtryObject(Xfind, Yfind);
  if (selectDE != NULL)  {
     oldPenColor = selectDE->PenColor;
     selectDE->PenColor = BGIColor[BLACK];
     selectDE->Draw(Image->Canvas->Handle, Scale);
     Image->Invalidate();
     CreateGOButton->Enabled = false;
     InitMaskEdit = true;
     switch(selectDE->whatIt)  {

        case IT_PIECE:  {
             SelectBox->ItemIndex = 1;

             CPiece *Piece = (CPiece *)selectDE;

             LabelX1->Caption = "X1:";
             wsprintf(str, "%3d", selectDE->X1);
             MaskEditX1->Text = str;

             LabelY1->Caption = "Y1:";
             wsprintf(str, "%3d", selectDE->Y1);
             MaskEditY1->Text = str;

             LabelX2->Visible = true;
             MaskEditX2->Visible = true;
             LabelY2->Visible = true;
             MaskEditY2->Visible = true;

             LabelX2->Caption = "X2:";
             wsprintf(str, "%3d", Piece->X2);
             MaskEditX2->Text = str;

             LabelY2->Caption = "Y2:";
             wsprintf(str, "%3d", Piece->Y2);
             MaskEditY2->Text = str;

             sprintf(str, "%.7f", selectDE->BegPsi);
             ValuePsiEdit->Text = str;

             double x12 = (double)abs(Piece->X2-Piece->X1);
             double y12 = (double)abs(Piece->Y2-Piece->Y1);
             double len = sqrt(x12*x12+y12*y12);
             wsprintf(str, "%d", (int)len);
             LabelLength->Caption = "L=";
             MaskEditR->Text = str;
             MaskEditR->Enabled = false;

             ePhisicBox->ItemIndex  = EPhisicToIndex(selectDE->ePhisic);
             eArrangeBox->ItemIndex = EArrangeToIndex(selectDE->eArrange);

             StatusBar1->Panels->Items[3]->Text = "Piece";
        }
        break;
        case IT_CIRCLE:   {
             SelectBox->ItemIndex = 2;

             CCircle *Circle = (CCircle *)selectDE;

             LabelX1->Caption = "Xc:";
             wsprintf(str, "%3d", selectDE->X1);
             MaskEditX1->Text = str;

             LabelY1->Caption = "Yc:";
             wsprintf(str, "%3d", selectDE->Y1);
             MaskEditY1->Text = str;

             LabelX2->Visible = false;
             MaskEditX2->Visible = false;
             LabelY2->Visible = false;
             MaskEditY2->Visible = false;
             MaskEditR->Enabled = true;

             sprintf(str, "%.7f", selectDE->BegPsi);
             ValuePsiEdit->Text = str;

             wsprintf(str, "%d", Circle->R);
             LabelLength->Caption = "R=";
             MaskEditR->Text = str;

             ePhisicBox->ItemIndex  = EPhisicToIndex(selectDE->ePhisic);
             eArrangeBox->ItemIndex = 5;//EArrangeToIndex(selectDE->eArrange);

             StatusBar1->Panels->Items[3]->Text = "Circle";
        }
        break;
        case IT_NOTCH:  {
             SelectBox->ItemIndex = 3;

             CNotch *Notch = (CNotch *)selectDE;

             LabelX1->Caption = "Xc:";
             wsprintf(str, "%3d", selectDE->X1);
             MaskEditX1->Text = str;

             LabelY1->Caption = "Yc:";
             wsprintf(str, "%3d", selectDE->Y1);
             MaskEditY1->Text = str;

             LabelX2->Visible = true;
             MaskEditX2->Visible = true;
             LabelY2->Visible = true;
             MaskEditY2->Visible = true;
             MaskEditR->Enabled = true;             

             LabelX2->Caption = "Xe:";
             wsprintf(str, "%3d", Notch->X3);
             MaskEditX2->Text = str;

             LabelY2->Caption = "Ye:";
             wsprintf(str, "%3d", Notch->Y3);
             MaskEditY2->Text = str;

             sprintf(str, "%.7f", selectDE->BegPsi);
             ValuePsiEdit->Text = str;

             wsprintf(str, "%d", (int)Notch->R);
             LabelLength->Caption = "R=";
             MaskEditR->Text = str;

             ePhisicBox->ItemIndex  = EPhisicToIndex(selectDE->ePhisic);
             eArrangeBox->ItemIndex = 5; // EArrangeToIndex(selectDE->eArrange);

             StatusBar1->Panels->Items[3]->Text = "Notch";
        }
        break;
        default: StatusBar1->Panels->Items[3]->Text = "Unknown";
     }
     InitMaskEdit = false;
  }
  else {
     CreateGOButton->Enabled = true;
     SelectBox->ItemIndex = 0;
     MaskEditX1->Text = "0";
     MaskEditY1->Text = "0";
     MaskEditX2->Text = "0";
     MaskEditY2->Text = "0";
     ValuePsiEdit->Text = "0.0";
     LabelLength->Caption = "?=";
     MaskEditR->Text = "0";
     ePhisicBox->ItemIndex  = 7;
     eArrangeBox->ItemIndex = 4;
     StatusBar1->Panels->Items[3]->Text = "No select";
  }
}



void __fastcall TModelConf::MaskEditX1Change(TObject *Sender)
{
  if (selectDE != NULL && !InitMaskEdit)  {
     COLORREF oldcolor = selectDE->PenColor;
     selectDE->PenColor = BGIColor[WHITE];
     selectDE->Draw(Image->Canvas->Handle, Scale);

     selectDE->X1 = atoi(MaskEditX1->EditText.c_str());

     // selectDE->PenColor = BGIColor[BROWN];
     selectDE->PenColor = oldcolor;
     selectDE->Draw(Image->Canvas->Handle, Scale);
     Image->Invalidate();
  }
}
//---------------------------------------------------------------------------
void __fastcall TModelConf::MaskEditY1Change(TObject *Sender)
{
  if (selectDE != NULL && !InitMaskEdit)  {
     COLORREF oldcolor = selectDE->PenColor;
     selectDE->PenColor = BGIColor[WHITE];
     selectDE->Draw(Image->Canvas->Handle, Scale);

     selectDE->Y1 = atoi(MaskEditY1->EditText.c_str());

     selectDE->PenColor = oldcolor;
     selectDE->Draw(Image->Canvas->Handle, Scale);
     Image->Invalidate();
  }

}
//---------------------------------------------------------------------------
void __fastcall TModelConf::MaskEditX2Change(TObject *Sender)
{
  if (selectDE != NULL && !InitMaskEdit)  {
     COLORREF oldcolor = selectDE->PenColor;
     selectDE->PenColor = BGIColor[WHITE];
     selectDE->Draw(Image->Canvas->Handle, Scale);

     switch(selectDE->whatIt)  {

        case IT_PIECE:  {
           CPiece *Piece = (CPiece *)selectDE;
           Piece->X2 = atoi(MaskEditX2->EditText.c_str());
        }
        break;
        case IT_CIRCLE:  {
        }
        break;
        case IT_NOTCH:  {
           CNotch *Notch = (CNotch *)selectDE;
           Notch->X3 = atoi(MaskEditX2->EditText.c_str());
        }
        break;
     }
     selectDE->PenColor = oldcolor;
     selectDE->Draw(Image->Canvas->Handle, Scale);
     Image->Invalidate();
  }

}
//---------------------------------------------------------------------------
void __fastcall TModelConf::MaskEditY2Change(TObject *Sender)
{
  if (selectDE != NULL && !InitMaskEdit)  {
     COLORREF oldcolor = selectDE->PenColor;
     selectDE->PenColor = BGIColor[WHITE];
     selectDE->Draw(Image->Canvas->Handle, Scale);

     switch(selectDE->whatIt)  {

        case IT_PIECE:  {
           CPiece *Piece = (CPiece *)selectDE;
           Piece->Y2 = atoi(MaskEditY2->EditText.c_str());
        }
        break;
        case IT_CIRCLE:  {
        }
        break;
        case IT_NOTCH:  {
           CNotch *Notch = (CNotch *)selectDE;
           Notch->Y3 = atoi(MaskEditY2->EditText.c_str());
        }
        break;
     }
     selectDE->PenColor = oldcolor;
     selectDE->Draw(Image->Canvas->Handle, Scale);
     Image->Invalidate();
  }
}
//---------------------------------------------------------------------------
void __fastcall TModelConf::MaskEditRChange(TObject *Sender)
{
  if (selectDE != NULL && !InitMaskEdit)  {
     COLORREF oldcolor = selectDE->PenColor;
     selectDE->PenColor = BGIColor[WHITE];
     selectDE->Draw(Image->Canvas->Handle, Scale);

     switch(selectDE->whatIt)  {

        case IT_PIECE:  {
        }
        break;
        case IT_CIRCLE:  {
           CCircle *Circle = (CCircle *)selectDE;
           Circle->R = atoi(MaskEditR->EditText.c_str());
        }
        break;
        case IT_NOTCH:  {
           CNotch *Notch = (CNotch *)selectDE;
           Notch->R = atoi(MaskEditR->EditText.c_str());
        }
        break;
     }
     selectDE->PenColor = oldcolor;
     selectDE->Draw(Image->Canvas->Handle, Scale);
     Image->Invalidate();
  }

}
//---------------------------------------------------------------------------
void __fastcall TModelConf::ValuePsiEditChange(TObject *Sender)
{
  if (selectDE != NULL && !InitMaskEdit)  {
     COLORREF oldcolor = selectDE->PenColor;
     selectDE->PenColor = BGIColor[WHITE];
     selectDE->Draw(Image->Canvas->Handle, Scale);

     selectDE->BegPsi = atof(ValuePsiEdit->Text.c_str());

     // selectDE->PenColor = BGIColor[BROWN];
     selectDE->PenColor = oldcolor;
     selectDE->Draw(Image->Canvas->Handle, Scale);
     Image->Invalidate();
  }

}
//---------------------------------------------------------------------------
void __fastcall TModelConf::ePhisicBoxChange(TObject *Sender)
{
  if (selectDE != NULL && !InitMaskEdit)
     selectDE->ePhisic = IndexToEPhisic(ePhisicBox->ItemIndex);
}
//---------------------------------------------------------------------------
void __fastcall TModelConf::eArrangeBoxChange(TObject *Sender)
{
  if (selectDE != NULL && !InitMaskEdit)
     selectDE->eArrange = IndexToEArrange(eArrangeBox->ItemIndex);
}
//---------------------------------------------------------------------------
void __fastcall TModelConf::SelectBoxChange(TObject *Sender)
{
  if (selectDE != NULL && !InitMaskEdit)  {
     switch(selectDE->whatIt)  {
        case IT_PIECE:  SelectBox->ItemIndex = 1;
        break;
        case IT_CIRCLE: SelectBox->ItemIndex = 2;
        break;
        case IT_NOTCH:  SelectBox->ItemIndex = 3;
        break;
     }
  }
  else {
     switch(SelectBox->ItemIndex)  {
     
        case 1:  {
             LabelX2->Visible = true;
             MaskEditX2->Visible = true;
             LabelY2->Visible = true;
             MaskEditY2->Visible = true;
             LabelX1->Caption = "X1:";
             LabelY1->Caption = "Y1:";
             LabelX2->Caption = "X2:";
             LabelY2->Caption = "Y2:";
             LabelLength->Caption = "L=";
             MaskEditR->Enabled = false;
        }
        break;
        case 2:   {
             LabelX2->Visible = false;
             MaskEditX2->Visible = false;
             LabelY2->Visible = false;
             MaskEditY2->Visible = false;
             MaskEditR->Enabled = true;

             LabelX1->Caption = "Xc:";
             LabelY1->Caption = "Yc:";
             LabelLength->Caption = "R=";
        }
        break;
        case 3:  {
             LabelX2->Visible = true;
             MaskEditX2->Visible = true;
             LabelY2->Visible = true;
             MaskEditY2->Visible = true;
             MaskEditR->Enabled = true;

             LabelX1->Caption = "Xc:";
             LabelY1->Caption = "Yc:";
             LabelX2->Caption = "Xe:";
             LabelY2->Caption = "Ye:";
             LabelLength->Caption = "R=";
        }
        break;
     }
  }
}
//---------------------------------------------------------------------------
void __fastcall TModelConf::CreateGOButtonClick(TObject *Sender)
{
  if (selectDE == NULL && SelectBox->ItemIndex>0)  {
     int oldScale = Scale;
     EWhatIt oldDrawingTool = DrawingTool;
     Scale = 1;
     X1 = atoi(MaskEditX1->EditText.c_str());
     Y1 = atoi(MaskEditY1->EditText.c_str());
     switch(SelectBox->ItemIndex)  {
        case 1:  {
            X2 = atoi(MaskEditX2->EditText.c_str());
            Y2 = atoi(MaskEditY2->EditText.c_str());
            DrawingTool = IT_PIECE;
        }
        break;
        case 2:   {
            R = atoi(MaskEditR->EditText.c_str());
            DrawingTool = IT_CIRCLE;
        }
        break;
        case 3:  {
            X3 = atoi(MaskEditX2->EditText.c_str());
            Y3 = atoi(MaskEditY2->EditText.c_str());
            R = atoi(MaskEditR->EditText.c_str());
            DrawingTool = IT_NOTCH;
        }
        break;
        default: return;
    }
    CDrawElement* _DE = AddToList();
    Scale = oldScale;
    DrawingTool = oldDrawingTool;
    _DE->Draw(Image->Canvas->Handle, Scale);
    Image->Invalidate();
  }
}
//---------------------------------------------------------------------------

void __fastcall TModelConf::Read(ifstream &fr)
 {
  SMALL_RECT R;
  char NamePoint[4];

  fr.read((char *)&R, sizeof(R));
  fr.read(NamePoint, sizeof(BYTE)*4);

  drawList.Read(fr);
 }


void __fastcall TModelConf::Write(ofstream &fw)
 {
  SMALL_RECT R;
  char NamePoint[4]="   ";

  // ::GetClientRect(Handle, &R);
  fw.write((char *)&R, sizeof(R));
  fw.write(NamePoint, sizeof(BYTE)*4);

  drawList.Write(fw);
 }



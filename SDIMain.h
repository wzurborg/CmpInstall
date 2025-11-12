//----------------------------------------------------------------------------
#ifndef SDIMainH
#define SDIMainH
//----------------------------------------------------------------------------
#include <vcl\ComCtrls.hpp>
#include <vcl\ExtCtrls.hpp>
#include <vcl\Buttons.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Dialogs.hpp>
#include <vcl\Menus.hpp>
#include <vcl\Controls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\Graphics.hpp>
#include <vcl\Classes.hpp>
#include <vcl\Windows.hpp>
#include <vcl\System.hpp>
#include <ActnList.hpp>
#include <ImgList.hpp>
#include <StdActns.hpp>
#include <ToolWin.hpp>
//----------------------------------------------------------------------------
#include "campaign.h"

class TSDIAppForm : public TForm
{
__published:
    TOpenDialog *OpenDialog;
    TSaveDialog *SaveDialog;
    TToolBar *ToolBar1;
    TToolButton *ToolButton1;
    TActionList *ActionList1;
    TAction *FileNew1;
    TAction *FileOpen1;
    TAction *FileSave1;
    TAction *FileSaveAs1;
    TAction *FileExit1;
    TEditCut *EditCut1;
    TEditCopy *EditCopy1;
    TEditPaste *EditPaste1;
    TAction *HelpAbout1;
    TStatusBar *StatusBar;
    TImageList *ImageList1;
    TMainMenu *MainMenu1;
    TMenuItem *File1;
    TMenuItem *FileOpenItem;
    TMenuItem *N1;
    TMenuItem *FileExitItem;
    TMenuItem *Help1;
    TMenuItem *HelpAboutItem;
    TEdit *CampName;
    TLabel *Label1;
    TLabel *Label2;
    TEdit *Szen1;
    TLabel *Label3;
    TEdit *Szen2;
    TLabel *Label4;
    TEdit *Szen3;
    TLabel *Label5;
    TEdit *Szen4;
    TLabel *Label6;
    TEdit *Szen5;
    TLabel *Label7;
    TButton *installButton;
    TButton *Button1;
    TMenuItem *Anleitung1;
    TAction *Action1;
    TToolButton *ToolButton2;
    TToolButton *ToolButton3;
    TStaticText *StaticText1;
    TToolButton *ToolButton4;
    TAction *OpenCmpView;void __fastcall FileNew1Execute(TObject *Sender);
        void __fastcall FileOpen1Execute(TObject *Sender);
        void __fastcall FileSave1Execute(TObject *Sender);
        void __fastcall FileExit1Execute(TObject *Sender);
        void __fastcall HelpAbout1Execute(TObject *Sender);
    void __fastcall installButtonClick(TObject *Sender);
    void __fastcall Button1Click(TObject *Sender);
    void __fastcall Action1Execute(TObject *Sender);
    void __fastcall OpenCmpViewExecute(TObject *Sender);
private:
    TEdit* szens[5];
    Campaign* campaign;

public:
    virtual __fastcall TSDIAppForm(TComponent *AOwner);
};
//----------------------------------------------------------------------------
extern TSDIAppForm *SDIAppForm;
//----------------------------------------------------------------------------
#endif

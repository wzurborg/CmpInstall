//---------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "SDIMain.h"
#include "About.h"

#include <FileCtrl.hpp>
#include <Dialogs.hpp>

#include "scenario.h"
#include "config.h"

#include "Unit1.h"
#include "CmpViewer.h"

//---------------------------------------------------------------------
#pragma resource "*.dfm"
TSDIAppForm *SDIAppForm;
//---------------------------------------------------------------------
__fastcall TSDIAppForm::TSDIAppForm(TComponent *AOwner)
	: TForm(AOwner)
{
    szens[0] = Szen1;
    szens[1] = Szen2;
    szens[2] = Szen3;
    szens[3] = Szen4;
    szens[4] = Szen5;

    campaign = 0;
}
//---------------------------------------------------------------------

void __fastcall TSDIAppForm::FileNew1Execute(TObject *Sender)
{
  // Do nothing        
}
//---------------------------------------------------------------------------

void __fastcall TSDIAppForm::FileOpen1Execute(TObject *Sender)
{
    OpenDialog->Filter = "Kampagnenbeschreibung (*.cmp)|*.CMP";
    if( OpenDialog->Execute() )
    {
        installButton->Enabled = false;
        delete campaign;
        campaign = new Campaign( OpenDialog->FileName );
        if( campaign->open() < 0 )
            return;

        //AnsiString dir = ExtractFileDir(OpenDialog->FileName);
        AnsiString cname = campaign->getName();
        TStrings* scenNames = campaign->getSzenNames();
        CampName->Text = cname;
        bool allesKlar = true;
        int i;
        for( i=0; i < 5; i++ )
        {
            if( i < scenNames->Count )
            {
                szens[i]->Text = scenNames->Strings[i];
                if( !campaign->scen(i)->fileExists() )
                    allesKlar = false;
            }
            else
                szens[i]->Clear();
        }

        if( allesKlar )
            installButton->Enabled = true;

    }
}
//---------------------------------------------------------------------------

void __fastcall TSDIAppForm::FileSave1Execute(TObject *Sender)
{
  SaveDialog->Execute();        
}
//---------------------------------------------------------------------------


void __fastcall TSDIAppForm::FileExit1Execute(TObject *Sender)
{
  Close();
}
//---------------------------------------------------------------------------

void __fastcall TSDIAppForm::HelpAbout1Execute(TObject *Sender)
{
  AboutBox->ShowModal();
}
//---------------------------------------------------------------------------




void __fastcall TSDIAppForm::installButtonClick(TObject *Sender)
{
    // Warnung
    AnsiString msg = "WARNUNG:\n";
//    msg += "Diese Aktion kann nicht rückgängig gemacht werden!";
//    int rsp = MessageDlg( msg, mtWarning,
//        (System::Set<TMsgDlgBtn, mbYes, mbHelp> () << mbOK << mbCancel ), 0 );
//    if( rsp == mrCancel )
//        return;

    Config cnf;
    if( !cnf.open() )
        return;

    int cmpNum = cnf.storeCampaign( campaign->getSzenNames() );
    if( cmpNum < 0 )
        return;

    AnsiString scenDir = Config::getInstallDir() + "\\" + "SZENES";
    if( !DirectoryExists( scenDir ) )
    {
        msg = "Das Verzeichnis ";
        msg += scenDir;
        msg += " existiert nicht!";
        ShowMessage( msg );
        return;
    }
    int r = campaign->copyScens( scenDir, cmpNum );
    if( r == 0 )
    {
        msg = "Die Kampagne \"";
        msg += campaign->getName();
        msg += "\" wurde erfolgreich installiert!";
        ShowMessage( msg );
    }
}
//---------------------------------------------------------------------------

void __fastcall TSDIAppForm::Button1Click(TObject *Sender)
{
    Close();
}
//---------------------------------------------------------------------------




void __fastcall TSDIAppForm::Action1Execute(TObject *Sender)
{
    Form1->Show();
}
//---------------------------------------------------------------------------




void __fastcall TSDIAppForm::OpenCmpViewExecute(TObject *Sender)
{
    CmpForm->Show();    
}
//---------------------------------------------------------------------------


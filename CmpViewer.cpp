//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "CmpViewer.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TCmpForm *CmpForm;
//---------------------------------------------------------------------------
__fastcall TCmpForm::TCmpForm(TComponent* Owner)
    : TForm(Owner)
{
    if(config.open())
    {
        TStrings* cmps = config.getCampaigns();
        cmpBox->Items = cmps;
        delete cmps;
    }
}
//---------------------------------------------------------------------------

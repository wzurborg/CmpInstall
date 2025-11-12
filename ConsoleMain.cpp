//---------------------------------------------------------------------------

#include <vcl.h>
#include <stdio.h>
#pragma hdrstop

#include "config.h"
#include "campaign.h"

//---------------------------------------------------------------------------

#pragma argsused
int main(int argc, char* argv[])
{
    if(argc < 2)
        return 1;

    Config cnf;
    if( !cnf.open() )
        return 1;

    Campaign campaign(argv[1]);
    if(campaign.open() != 0)
        return 1;

    int cmpNum = cnf.storeCampaign( campaign.getSzenNames() );
    if( cmpNum < 0 )
        return 1;

    AnsiString scenDir = Config::getInstallDir() + "\\" + "SZENES";
    if( !DirectoryExists( scenDir ) )
    {
        AnsiString msg = "Das Verzeichnis ";
        msg += scenDir;
        msg += " existiert nicht!";
        ShowMessage(msg);
        return 1;
    }
    int r = campaign.copyScens( scenDir, cmpNum );
    if( r == 0 )
    {
        AnsiString msg = "Die Kampagne \"";
        msg += campaign.getName();
        msg += "\" wurde erfolgreich installiert!";
        ShowMessage(msg);
        return 1;
    }

    return 0;
}
//---------------------------------------------------------------------------
 
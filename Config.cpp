#include <Registry.hpp>
#include <FileCtrl.hpp>
#include "config.h"
#include "scenario.h"

AnsiString Config::_installDir;

Config::Config()
 : _fh(-1), strl(0), cmpStartIndex(-1), cmpEndIndex(-1)
{
}

bool Config::open()
{
    if( _fh > 0 )
        return false;

    // find Anno base dir
    if( !getBasedir() )
        return false;

    AnsiString saveDir = GetCurrentDir();
    SetCurrentDir( _installDir );

    _fh = FileOpen( "TEXT.COD", fmOpenReadWrite|fmShareExclusive );
    if( _fh < 0 )
    {
        ShowMessage( "Kann Datei TEXT.COD nicht öffnen" );
        return false;
    }

    int bufsize = FileSeek( _fh, 0, 2);
    FileSeek( _fh, 0, 0 );
    char* buffer = new char[bufsize+1];
    int iBytesRead = FileRead( _fh, buffer, bufsize);
    if( iBytesRead != bufsize )
    {
        ShowMessage( "Kann Datei TEXT.COD nicht lesen" );
        close();
        return false;
    }

    convertBuffer( buffer, bufsize );
    if( strl == 0 )
        strl = new TStringList;
    strl->SetText( buffer );
    delete [] buffer;

    szenList = new TStringList;

    int i = 0;
    while( strl->Strings[i] != "[KAMPAGNE]" )
        i++;
    i++;
    cmpStartIndex = i;

    while( strl->Strings[i] != "[END]" )
    {
        szenList->Add( strl->Strings[i] );
        i++;
    }
    cmpEndIndex = i;

    SetCurrentDir( saveDir );
    return true;
}

int Config::storeCampaign( TStrings* clist )
{
    if( _fh < 0 )
        open();

    int clen = clist->Count;
    if( clen > 5 )
    {
        ShowMessage( "Falsche Anzahl Szenarien" );
        return -1;
    }

    int cmpNumber;

    // check if campaign already exists
    AnsiString firstSzen = clist->Strings[0];
    int first = strl->IndexOf( firstSzen );
    if( first != -1 )
    {
        AnsiString msg = "Die Kampagne existiert bereits!\n";
        msg += "Überschreiben?";
        int rsp = MessageDlg( msg, mtWarning,
            (System::Set<TMsgDlgBtn, mbYes, mbHelp> () << mbYes << mbNo ), 0 );
        if( rsp == mrYes )
        {
            // Overwrite Kampagne
            int i;
            for( i=0; i<clen; i++ )
                strl->Strings[first+i] = clist->Strings[i];
            for( ; i<5; i++ )
                strl->Strings[first+i] = AnsiString();

            cmpNumber = (first - cmpStartIndex) / 5;
        }
        else
            return -1;
    }
    else
    {
        int i;
        for( i=4; i >= clen; i-- )
            strl->Insert( cmpEndIndex, AnsiString() );
        for( ; i >= 0; i-- )
            strl->Insert( cmpEndIndex, clist->Strings[i] );

        cmpNumber = (cmpEndIndex - cmpStartIndex) / 5;
    }
    // rewrite Buffer
    char* cbuf = strl->GetText();
    int bufsize = strlen(cbuf);
    convertBuffer( cbuf, bufsize );

    // write buffer to file
    FileSeek( _fh, 0, 0 );
    int iBytesWritten = FileWrite( _fh, cbuf, bufsize );
    if( iBytesWritten != bufsize )
    {
        ShowMessage( "Kann Datei TEXT.COD nicht schreiben" );
        close();
        return -1;
    }

    StrDispose( cbuf );
    close();

    return cmpNumber;
}

void Config::close()
{
    if( _fh > 0 )
        FileClose( _fh );
    _fh = -1;
}

Config::~Config()
{
    close();
}

bool Config::getBasedir()
{
    // Get Anno directory from registry
    TRegistry* Registry = new TRegistry;
    Registry->RootKey = HKEY_CURRENT_USER;

    Registry->RootKey = HKEY_LOCAL_MACHINE;
    AnsiString basekey
    ( "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\App Paths\\" );
    if( Registry->OpenKeyReadOnly( basekey + "1602.EXE" )
        || Registry->OpenKeyReadOnly( basekey + "ANNO.EXE" ) )
    {
        _installDir = Registry->ReadString( "Path" );
    }

    delete Registry;

    if( _installDir.Length() > 0 && DirectoryExists( _installDir ) )
        return true;     // found!

    bool input = SelectDirectory
        ( "Bitte das Anno 1602 Installationsverzeichnis angeben:",
          "", _installDir );

    if( input && DirectoryExists( _installDir ) )
        return true;

    ShowMessage( "Kann Anno 1602 Installationsverzeichnis nicht finden" );
    _installDir = AnsiString();
    return false;
}

void Config::convertBuffer( char* buffer, int bufsize )
{
    int i;
    unsigned char* buf = (unsigned char*)buffer;
    for( i=0; i<bufsize; i++ )
        // _buffer[i] ^= 0xFE;
        buf[i] = 256 - buf[i];
}

TStrings* Config::getCampaigns()
{
    TStrings* cmps = new TStringList;
    // Scan all files in szenes directory for files ending in digit 0
    String szenesPath = IncludeTrailingPathDelimiter(_installDir) + "szenes\\*.szs";
    TSearchRec tsr;
    int stat = FindFirst(szenesPath, 0, tsr);
    while(stat == 0)
    {
        String fname = ChangeFileExt(tsr.Name, "");
        if(fname[fname.Length()] == '0')
        {
            int cmpNr = getCmpNr(IncludeTrailingPathDelimiter(_installDir)
                + "szenes\\" + tsr.Name);
            if(cmpNr > 0)
            {
                fname = fname.SubString(0, fname.Length()-1);
                cmps->Add(fname + "=" + cmpNr);
            }
        }
        stat = FindNext(tsr);
    }
    FindClose(tsr);
    return cmps;
}

int Config::getCmpNr( String szenfile )
{
    Scenario* szen = new Scenario(szenfile);
    szen->init();
    int n = szen->campno();
    delete szen;
    return n;
}

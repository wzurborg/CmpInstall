#include "SDIMain.h"
#include "scenario.h"

Scenario::Scenario( const AnsiString& filename )
 : _filename(filename), _campno(-1), _fh(-1)
{
    init();
}

__fastcall Scenario::~Scenario()
{
    close();
}

void Scenario::init()
{
    open();

    // read properties
    unsigned char buffer[21];
    int n = FileRead( _fh, buffer, 24 );
    if( n != 24 )
    {
        AnsiString msg = "Kann Datei nicht lesen: "
            + _filename;
        Application->MessageBoxA( msg.c_str(), "Error", MB_OK );
        return;
    }

    // check for campaign
    if( CompareMem( buffer, "SZENE_KAMPAGNE", 14 ) )
    {
        _campno = *(short*)&buffer[20];
    }
}

void Scenario::open( int openMode )
{
    if( _fh > 0 )
        return;

    // open file
    _fh = FileOpen( _filename, openMode );
    if( _fh < 0 )
    {
        AnsiString msg = "Kann Datei nicht öffnen: "
            + _filename;
        ShowMessage( msg );
    }
}

bool Scenario::fileExists()
{
    open();
    return ( _fh > 0 );
}

void Scenario::close()
{
    // close file
    if( _fh > 0 )
        FileClose( _fh );
    _fh = -1;
}

int Scenario::copyTo(const AnsiString& dir, int cmpNum)
{
    open();
    int filesize = FileSeek( _fh, 0, 2 );
    FileSeek( _fh, 0, 0 );
    char* buffer = new char[filesize + 1];
    int n = FileRead( _fh, buffer, filesize );
    close();
    if( n != filesize )
    {
        ShowMessage( "Kann Szenariodatei nicht lesen!" );
        return -1;
    }

    // Dirname + Filename
    AnsiString outfile = ExtractFileName( _filename );
    outfile = dir + "\\" + outfile;
    int fh;
    if( FileExists( outfile ) )
    {
        fh = FileOpen( outfile, fmOpenWrite | fmShareExclusive );
    }
    else
    {
        fh = FileCreate( outfile );
    }
    if( fh < 0 )
    {
        AnsiString msg = "Kann Datei nicht öffnen: "
            + outfile;
        ShowMessage( msg );
        delete [] buffer;
        return -1;
    }

    // Setzen der Kampagnennummer
    short number = (short)cmpNum;
    if( CompareMem( buffer, "SZENE_KAMPAGNE", 14 ) )
    {
        *((short*)&buffer[20]) = number;
    }
    else
    {
        // Mach Szen zu Kampagne
        FileWrite( fh, "SZENE_KAMPAGNE\0\0\4\0\0\0", 20 );
        FileWrite( fh, &number, 2 );
        FileWrite( fh, "\0\0", 2 );
    }

    n = FileWrite( fh, buffer, filesize );
    delete [] buffer;
    if( n != filesize )
    {
        AnsiString msg = "Kann Datei nicht schreiben: "
            + outfile;
        ShowMessage( msg );
        return -1;
    }
    FileClose(fh);
    return 0;
}

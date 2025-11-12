#include "savegame.h"

Savegame::Savegame( const AnsiString& filename )
: buffer(0),bufSize(0)
{
    int fd = FileOpen( filename, fmOpenRead );
    if( fd > 0 )
    {
        bufSize = FileSeek( fd, 0, 2 );
        buffer = new char[bufSize];
        FileSeek( fd, 0, 0 );
        FileRead( fd, buffer, bufSize );
        FileClose( fd );
    }
}

void Savegame::draw( TCanvas* canvas )
{
    if( buffer == 0 )
        return;

    canvas->TextOut( 10, 10, AnsiString( bufSize ) );
}

Savegame::~Savegame()
{
    delete [] buffer;
}
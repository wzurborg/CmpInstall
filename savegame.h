#ifndef __savegame__h__
#define __savegame__h__

#include <vcl/graphics.hpp>

class Savegame
{
public:
    Savegame( const AnsiString& );
    void draw( TCanvas* );

    ~Savegame();

private:
    char* buffer;
    int bufSize;

};

#endif

#ifndef _scenario_h_
#define _scenario_h_

#include <system.hpp>

class Scenario : public TObject
{
public:
    Scenario( const AnsiString& filename );
    virtual __fastcall ~Scenario();
    void init();
    void open( int openMode = fmOpenRead);
    void close();
    short inline campno();
    bool fileExists();
    int copyTo(const AnsiString& dir, int cmpNum);
private:
    short _campno;    // campaign number
    AnsiString _filename;
    AnsiString _descr;  // description
    int _fh;    // file handle
};

short inline Scenario::campno()
{
    return _campno;
}

#endif



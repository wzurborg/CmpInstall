#ifndef _config_h_
#define _config_h_

#include <vcl.h>

class Config
{
public:
    Config();
    bool open();
    void close();
    TStrings* getCampaigns();
    int storeCampaign( TStrings* clist );
    inline static AnsiString getInstallDir();
    ~Config();
private:
    void convertBuffer( char* buffer, int bufsize );
    bool getBasedir();
    int getCmpNr(String szenfile);

    int _fh;
    static AnsiString _installDir;
    TStrings* strl;     // Gesamte Datei
    TStrings* szenList; // Liste der Szenarien
    int cmpStartIndex;
    int cmpEndIndex;
};

inline AnsiString Config::getInstallDir()
{
    return _installDir;
}


#endif

 
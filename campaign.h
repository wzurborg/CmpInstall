#ifndef _campaign_h_
#define _campaign_h_

#include <vcl.h>
#include "scenario.h"

class Campaign
{
public:
    Campaign( const AnsiString& filename );
    ~Campaign();
    int open();
    const AnsiString& getName() const;
    TStrings* getSzenNames() const;
    Scenario* scen(int i);
    int copyScens( const AnsiString& dir, int cmpNum );

private:
    AnsiString _filename;
    AnsiString _basename;
    TStrings* _list;
};

#endif

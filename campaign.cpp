#include "campaign.h"

Campaign::Campaign( const AnsiString& filename )
 : _filename(filename)
{
    _list = new TStringList;
}

Campaign::~Campaign()
{
    int i;
    for( i=0; i<_list->Count; i++ )
        delete (Scenario*)_list->Objects[i];
    delete _list;
}

int Campaign::open()
{
    _list->LoadFromFile( _filename );

    // remove empty lines
    int i;
    for( i=_list->Count-1; i >= 0; i-- )
    {
        if( _list->Strings[i].Trim() == AnsiString() )
            _list->Delete( i );
    }

    if( _list->Count < 1 || _list->Count > 5 )
    {
        ShowMessage( "Fehlerhafte Beschreibungsdatei" );
        return -1;
    }

    _basename = ExtractFileName( _filename );
    _basename = _basename.SubString( 1, _basename.Length()-4 );

    for( i=0; i < 5; i++ )
    {
        if( i < _list->Count )
        {
            AnsiString szname = _basename + i + ".szs";
            Scenario* sz = new Scenario( szname );
            //if( sz->isCampaign() )
                _list->Objects[i] = sz;
        }
    }

    return 0;
}


const AnsiString& Campaign::getName() const
{
    return _basename;
}

TStrings* Campaign::getSzenNames() const
{
    return _list;
}

Scenario* Campaign::scen(int i)
{
    return (Scenario*)_list->Objects[i];
}

int Campaign::copyScens( const AnsiString& dir, int cmpNum )
{
    int res = 0;
    int i;
    for( i=0; i < _list->Count; i++ )
    {
        Scenario* sz = (Scenario*)_list->Objects[i];
        int r = sz->copyTo( dir, cmpNum );
        if( r != 0 ) res = r;
    }
    return res;
}

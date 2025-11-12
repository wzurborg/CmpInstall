//---------------------------------------------------------------------------

#ifndef CmpViewerH
#define CmpViewerH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>

#include "Config.h"
//---------------------------------------------------------------------------

class TCmpForm : public TForm
{
__published:	// IDE-managed Components
    TListBox *cmpBox;
    TLabeledEdit *editSzen1;
    TLabeledEdit *editSzen2;
    TLabeledEdit *editSzen3;
    TLabeledEdit *editSzen4;
    TLabeledEdit *editSzen5;
    TButton *btnOk;

private:	// User declarations
    Config config;

public:		// User declarations
    __fastcall TCmpForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TCmpForm *CmpForm;
//---------------------------------------------------------------------------
#endif

//---------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------
USEFORM("SDIMain.cpp", SDIAppForm);
USEFORM("About.cpp", AboutBox);
USERES("AnnoSGE.res");
USEUNIT("Scenario.cpp");
USEUNIT("campaign.cpp");
USEUNIT("Config.cpp");
USEFORM("Unit1.cpp", Form1);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	Application->Initialize();
	Application->Title = "Sir Henry's Anno 1602 Kampagnen-Installer";
         Application->CreateForm(__classid(TSDIAppForm), &SDIAppForm);
         Application->CreateForm(__classid(TAboutBox), &AboutBox);
         Application->CreateForm(__classid(TForm1), &Form1);
         Application->Run();

	return 0;
}
//---------------------------------------------------------------------

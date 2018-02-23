//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("TImpWinII.cpp", ImpulseWindow);
USEFORM("TModConf.CPP", ModelConf);
USEFORM("TParams.cpp", ParametersDlg);
USEFORM("TShowBorder.cpp", ShowBorder);
USEFORM("TCalcWindow.cpp", CalcWindow);
USEFORM("TPressOne.cpp", PressOne);
USEFORM("TPressWin.cpp", PressWin);
USEFORM("About.cpp", AboutBox);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	try
	{
		Application->Initialize();
		Application->CreateForm(__classid(TImpulseWindow), &ImpulseWindow);
		Application->CreateForm(__classid(TModelConf), &ModelConf);
		Application->CreateForm(__classid(TParametersDlg), &ParametersDlg);
		Application->CreateForm(__classid(TAboutBox), &AboutBox);
		Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	catch (...)
	{
		try
		{
			throw Exception("");
		}
		catch (Exception &exception)
		{
			Application->ShowException(&exception);
		}
	}
	return 0;
}
//---------------------------------------------------------------------------

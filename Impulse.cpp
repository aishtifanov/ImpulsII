//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
//---------------------------------------------------------------------------
USEFORM("About.cpp", AboutBox);
USEFORM("TCalcWindow.cpp", CalcWindow);
USEFORM("TImpWinII.cpp", ImpulseWindow);
USEFORM("TModConf.CPP", ModelConf);
USEFORM("TParams.cpp", ParametersDlg);
USEFORM("TPressOne.cpp", PressOne);
USEFORM("TPressWin.cpp", PressWin);
USEFORM("TShowBorder.cpp", ShowBorder);
//---------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	try
	{
		Application->Initialize();
		Application->MainFormOnTaskBar = true;
		Application->CreateForm(__classid(TImpulseWindow), &ImpulseWindow);
		Application->CreateForm(__classid(TAboutBox), &AboutBox);
		Application->CreateForm(__classid(TCalcWindow), &CalcWindow);
		Application->CreateForm(__classid(TModelConf), &ModelConf);
		Application->CreateForm(__classid(TParametersDlg), &ParametersDlg);
		Application->CreateForm(__classid(TPressOne), &PressOne);
		Application->CreateForm(__classid(TPressWin), &PressWin);
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

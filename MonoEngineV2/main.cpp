#include "pch.h"
#include "Application.h"

#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

int APIENTRY WinMain(_In_ HINSTANCE hInst, _In_opt_ HINSTANCE hPrevInst, _In_ LPSTR lpCmdLine, _In_ int nCmdLine)
{
	Application* app = nullptr;
	
	try
	{
		app = new Application();
		app->Run();
		SafeDel(app);
		return 0;
	}
	catch (const std::exception& ex)
	{
		MessageBoxA(nullptr, ex.what(), "Exception!", MB_OK | MB_ICONERROR | MB_TOPMOST);
		SafeDel(app);
		return -1;
	}
}
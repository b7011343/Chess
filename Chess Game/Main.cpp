#include "EasyGraphics.h"
#include "StartWindow.h"
#include <Windows.h>
#include <string>

using namespace std;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	#ifdef _DEBUG   // Only include this section of code in the DEBUG build
		_CrtSetBreakAlloc(65);  // Useful line of code to help find memory leaks
		_onexit(_CrtDumpMemoryLeaks); // Check for memory leaks when the program exits
	#endif

	StartWindow* startWindow = new StartWindow(hInstance);
	startWindow->waitForClose();
	delete startWindow;

	return 0;
}
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "Application.h"

int main( void )
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);

	Application &app = Application::GetInstance();
	app.Init();
	app.Run();
	app.Exit();

	//_CrtDumpMemoryLeaks();
}
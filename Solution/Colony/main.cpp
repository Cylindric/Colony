#include "main.h"
#include "Engine.h"


INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
{
	Colony::Engine e;
	if(!e.Initialise())
	{
		return 1;
	}
	e.Run();
	return 0;
}
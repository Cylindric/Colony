////////////////////////////////////////////////////////////////////////////////
// Filename: main.cpp
////////////////////////////////////////////////////////////////////////////////


//////////////
// INCLUDES //
//////////////
#include <fstream>
#include <iostream>
#include <Windows.h>

///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include <CoreManager.h>


HWND hWnd;
int windowWidth = 800;	
int windowHeight = 600;
Core::CoreManager* renderer;


/*******************************************************************
* Main Window Procedure - handles application events
*******************************************************************/
LRESULT CALLBACK wndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) 
	{
		// Allow the user to press the escape key to end the application
        case WM_KEYDOWN	:	switch(wParam)
							{
								// Check if the user hit the escape key
								case VK_ESCAPE : PostQuitMessage(0);
								break;
							}
		
        break;		
	
		// The user hit the close button, close the application
		case WM_DESTROY	:	PostQuitMessage(0);
		break;
	}
	
	return DefWindowProc(hWnd, message, wParam, lParam);
}


/*******************************************************************
* Initialize Main Window
********************************************************************/
bool initWindow(HWND &hWnd, HINSTANCE hInstance, int width, int height)
{
	WNDCLASSEX wcex;

	wcex.cbSize			= sizeof(WNDCLASSEX);
	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= (WNDPROC)wndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= 0;
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName	= TEXT("Colony");
	wcex.hIconSm		= 0;
	RegisterClassEx(&wcex);

	//Resize the window
	RECT rect = { 0, 0, width, height };
    AdjustWindowRect(&rect, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, FALSE);

	//create the window from the class above
	hWnd = CreateWindow( "Colony", 
						 "Colony - Tile Test", 
						 WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
						 CW_USEDEFAULT, 
						 CW_USEDEFAULT, 
						 rect.right - rect.left, 
						 rect.bottom - rect.top, 
						 NULL, 
						 NULL, 
						 hInstance, 
						 NULL);
   
	//window handle not created
	if (!hWnd) return false;
	
	//if window creation was successful
	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);
	return true;
}


/*******************************************************************
* WinMain
*******************************************************************/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow)
{
	// redirect std output to files
	std::ofstream coutfile;
	coutfile.open("cout.log");
	std::streambuf* coutbuf = std::cout.rdbuf();
	std::cout.rdbuf(coutfile.rdbuf());

	std::ofstream cerrfile;
	cerrfile.open("cerr.log");
	std::streambuf* cerrbuff = std::cerr.rdbuf();
	std::cerr.rdbuf(cerrfile.rdbuf());

	// Set up the application window
	if ( !initWindow(hWnd, hInstance, windowWidth, windowHeight)) return 0;
	
	//set up the renderer
	renderer = new Core::CoreManager("dx10");
	if(!renderer->Initialise(&hWnd))
	{
		std::cerr << "Failed to initialise a renderer" << std::endl;
		return 0;
	}
	
	// Main message loop
    MSG msg = {0};
    while (WM_QUIT != msg.message)
    {
        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) == TRUE)
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);			
		}	

		if(!renderer->Render())
		{
			msg.message = WM_QUIT;
		}
    }

	renderer->Release();
	delete renderer;
	renderer = 0;

	return (int) msg.wParam;
}
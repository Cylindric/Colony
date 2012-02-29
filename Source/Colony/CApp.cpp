#include "CApp.h"

CApp::CApp() {
	Surf_Display = NULL;
	Default_Tileset = NULL;

	Running = true;
}

int CApp::OnExecute() {
	if(OnInit() == false) {
		return -1;
	}

	SDL_Event Event;

	while(Running) {
		while(SDL_PollEvent(&Event)) {
			OnEvent(&Event);
		}

		OnLoop();
		OnRender();
		SDL_Delay(1);
	}

	OnCleanup();

	return 0;
}

int main(int argc, char* args[])
{
	CApp theApp;
	return theApp.OnExecute();
}
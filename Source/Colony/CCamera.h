#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include "CCamera.h"
#include "CCursor.h"
#include "Define.h"
#include "CFont.h"
#include "CArea.h"
#include "CFPS.h"

enum {
    TARGET_MODE_NORMAL = 0,
    TARGET_MODE_CENTER
};
 
class CCamera {

    public:
        static CCamera CameraControl;
 
    private:
		SDL_Surface* Surf_Display;
        int X;
        int Y;
		int Width;
		int Height;
 
        int* TargetX;
        int* TargetY;
		SDL_Surface *text;
		SDL_Color text_color;
		char DebugTextBuffer[50];

    public:
        int TargetMode;
 
    public:
        CCamera();
 
    public:
		SDL_Surface* OnInit();
        void OnMove(int MoveX, int MoveY);
 		void OnRender(SDL_Surface* Surf_Display);

    public:
        int GetX();
        int GetY();
		int GetWidth();
		int GetHeight();

    public:
        void SetPos(int X, int Y);
        void SetTarget(int* X, int* Y);
		bool SetSize(int Width, int Height);
};

#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include "Define.h"

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
 	    TTF_Font *font;
		SDL_Surface *text;
		SDL_Color text_color;

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

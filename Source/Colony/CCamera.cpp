#include "CCamera.h"

#include <SDL.h>
#include <SDL_ttf.h>
#include "Define.h"
#include "CCamera.h"
#include "CCursor.h"
#include "CFont.h"
#include "CFPS.h"
#include "CMap.h"

CCamera CCamera::CameraControl;
 
CCamera::CCamera() {
    X = 0;
	Y = 0;
	Width = 640;
	Height = 480;
    TargetX = NULL;
	TargetY = NULL;
    TargetMode = TARGET_MODE_NORMAL;
}
 
SDL_Surface* CCamera::OnInit() {
	this->SetSize(this->Width, this->Height);
	return this->Surf_Display;
}

void CCamera::OnMove(int MoveX, int MoveY) {
    X += MoveX;
    Y += MoveY;

	// limit
	if(X > 0) {
		X = 0;
	}
	if(Y > 0) {
		Y = 0;
	}

	int MaxX = ((CMap::MapControl.getWidth() * CMap::MapControl.getTileSize()) - (this->Width));
	if(X < -MaxX) {
		X = -MaxX;
	}
 
	int MaxY = ((CMap::MapControl.getHeight() * CMap::MapControl.getTileSize()) - (this->Height));
	if(Y < -MaxY) {
		Y = -MaxY;
	}
}
 
int CCamera::GetX() {
    if(TargetX != NULL) {
        if(TargetMode == TARGET_MODE_CENTER) {
            return *TargetX - (this->Width / 2);
        }
 
        return *TargetX;
    }
 
    return X;
}
 
int CCamera::GetY() {
    if(TargetY != NULL) {
        if(TargetMode == TARGET_MODE_CENTER) {
            return *TargetY - (this->Height / 2);
        }
 
        return *TargetY;
    }
 
    return Y;
}

int CCamera::GetWidth() {
	return this->Width;
}

int CCamera::GetHeight() {
	return this->Height;
}

bool CCamera::SetSize(int Width, int Height) {
	this->Width = Width;
	this->Height = Height;
	if((Surf_Display = SDL_SetVideoMode(this->Width, this->Height, 32, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_RESIZABLE)) == NULL) {
		return false;
	}
	return true;
}

void CCamera::SetPos(int X, int Y) {
    this->X = X;
    this->Y = Y;
}
 
void CCamera::SetTarget(int* X, int* Y) {
    TargetX = X;
    TargetY = Y;
}

void CCamera::OnRender(SDL_Surface* Surf_Display) {
}
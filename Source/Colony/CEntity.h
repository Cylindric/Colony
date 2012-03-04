#pragma once
#include <SDL.h> 
#include <vector>
#include "Define.h"
#include "CAnimation.h"
#include "CSurface.h"
#include "CCamera.h"

class CEntity {
public:
	static std::vector<CEntity*> EntityList;

protected:
	CAnimation Anim_Control;
	SDL_Surface* EntityTileset;

public:
	int X;
	int Y;
	int SpriteWidth;
	int SpriteHeight;
	int AnimState;
	char Label[1];

public:
	CEntity();
	virtual ~CEntity();

public:
	virtual bool OnLoad(SDL_Surface* EntityTileset);
	virtual void OnLoop();
	virtual void OnRender(SDL_Surface* Surf_Display);
	virtual void OnCleanup();
};

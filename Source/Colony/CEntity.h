#ifndef _CENTITY_H_
#define _CENTITY_H_

#include <vector>
#include <SDL.h>
#include "Define.h"
#include "CAnimation.h"
#include "CCoord.h"
#include "CCamera.h"
#include "CSurface.h"

class CEntity {
public:
	static std::vector<CEntity*> EntityList;

protected:
	CAnimation Anim_Control;
	SDL_Surface* EntityTileset;

public:
	CCoord Coord;
	int SpriteWidth;
	int SpriteHeight;
	int AnimState;
	char Label[1];

public:
	CEntity();
	virtual ~CEntity();

public:
	virtual bool OnLoad();
	virtual void OnLoop();
	virtual void OnRender(SDL_Surface* Surf_Display);
	virtual void OnCleanup();
};

#endif
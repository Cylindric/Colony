#ifndef _CENTITY_H_
#define _CENTITY_H_

#include <list>
#include <set>
#include <vector>
#include <SDL.h>
#include "Define.h"
#include "CAnimation.h"
#include "CCoord.h"

// Forward declarations
class ATile;
class CTile;

// The class
class CEntity {

public:
	static std::vector<CEntity*> EntityList;
	CCoord Coord;
	int SpriteWidth;
	int SpriteHeight;
	int AnimState;
	char Label[1];
	CEntity();
	virtual ~CEntity();
	virtual bool OnLoad();
	virtual void OnLoop();
	virtual void OnRender(SDL_Surface* Surf_Display);
	virtual void OnCleanup();
	CCoord Destination;

protected: // properties
	CAnimation Anim_Control;
	SDL_Surface* EntityTileset;

	// A* objects
	bool isValidPath_;
	std::vector<CTile*> pathToDestination_;
	unsigned long lastMoveTime_;
	//std::list<ATile*> openList_;
	//std::list<ATile*> closedList_;
	std::set<ATile*> openList_;
	std::set<ATile*> closedList_;

protected: //methods
	int CostToDestination();
	void CalcRoute(CTile* StartNode, CTile* EndNode);
	void decorateClosedList();
	void decorateFinalPath();

private: //methods
	int GetHeuristic(CCoord A, CCoord B);
	ATile* GetLowestF(std::set<ATile*> List);
	ATile* FindTileOnList(std::set<ATile*> List, CTile* Tile);
};

#endif
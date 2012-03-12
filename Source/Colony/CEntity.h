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
	enum SearchState {
		SEARCH_STATE_NOT_INITIALISED = 0,
		SEARCH_STATE_SEARCHING,
		SEARCH_STATE_SUCCEEDED,
		SEARCH_STATE_FAILED,
		SEARCH_STATE_INVALID
	};

	static std::vector<CEntity*> EntityList;
	CCoord Coord;
	int SpriteWidth;
	int SpriteHeight;
	int AnimState;
	char Label[1];
	unsigned int currentState;
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

protected: // methods
	int CostToDestination();
	unsigned int setSearchStates(CTile* start, CTile* goal);
	unsigned int searchStep();
	void decorateClosedList();
	void decorateFinalPath();
	CTile* getSolutionStart();
	CTile* getSolutionNext();

private: // methods
	int GetHeuristic(CCoord A, CCoord B);
	void AddSuccessors(ATile* tile);
	void FreeAllNodes();
	void FreeNode(ATile* n);
	void FreeUnusedNodes();
	void dumpClosedList();

private: // properties
	unsigned int stepCount_;
	ATile* startTile_;
	ATile* goalTile_;
	std::vector<ATile*> openList_;
	std::vector<ATile*> closedList_;
	std::vector<ATile*> successorList_;
	ATile* currentSolutionNode_;
};

#endif
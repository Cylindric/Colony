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

public: //methods
	CEntity();
	virtual ~CEntity();
	virtual bool OnLoad();
	virtual void OnLoop();
	virtual void OnRender(SDL_Surface* Surf_Display);
	virtual void OnCleanup();

public: // properties
	static std::vector<CEntity*> EntityList;
	CCoord Position;
	int SpriteWidth;
	int SpriteHeight;
	int AnimState;
	char Label[1];
	unsigned int currentState;
	CCoord Destination;

protected: // properties
	CAnimation Anim_Control;
	SDL_Surface* tileset_;

	// A* objects
	unsigned long lastMoveTime_;
	unsigned int currentPathStep_;

protected: // methods
	unsigned int setSearchStates(CTile* start, CTile* goal);
	unsigned int doSearchStep();
	void decorateClosedList();
	void decorateFinalPath();
	CTile* getSolutionStart();
	CTile* getSolutionNext();

private: // methods
	int getHeuristic(CCoord A, CCoord B);
	void addSuccessors(ATile* tile);
	void freeAllNodes();
	void freeNode(ATile* n);
	void freeUnusedNodes();
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
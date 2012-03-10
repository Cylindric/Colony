#ifndef _CENTITY_BUGGY_H_
#define _CENTITY_BUGGY_H_

// Included dependencies
#include "CEntity.h"

// Forward declarations
class CEntity_TargetCursor;

// The class
class CEntity_Buggy : public CEntity {

public:
	CEntity_Buggy();
	void OnLoop();
	bool OnLoad();
	void OnRender(SDL_Surface* Surf_Display);

private:
	CEntity_TargetCursor* DestinationCursor;
};

#endif
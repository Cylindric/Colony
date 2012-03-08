#ifndef _CENTITY_TARGETCURSOR_H_
#define _CENTITY_TARGETCURSOR_H_

// Forward declared dependencies

// Included dependencies
#include <SDL.h>
#include "CEntity.h"

// The class
class CEntity_TargetCursor : public CEntity {

public:
	CEntity_TargetCursor();
	void OnLoop();
	bool OnLoad();
};

#endif
#pragma once

#include <SDL.h>
#include "CSurface.h"
#include "CEntity.h"
#include "CFPS.h"

class CEntity_Buggy : public CEntity {

public:
	CEntity_Buggy();
	bool OnLoad();
	void OnLoop();

private:
	float SpeedX;
	float SpeedY;
	float AccelerationX;
	float AccelerationY;
	float MaxSpeed;
};


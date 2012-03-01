#include "CEntity_Buggy.h"


CEntity_Buggy::CEntity_Buggy() {
	this->SpeedX = 0;
	this->SpeedY = 0;
	this->MaxSpeed = 2;
	this->AccelerationX = 1;
	this->AccelerationY = 1;
}

bool CEntity_Buggy::OnLoad() {
	CEntity::OnLoad("./gfx/buggy.png", 20, 20, 4);
	return true;
}

void CEntity_Buggy::OnLoop() {
	// hack in a random walk type thing
	int r = (rand() % 500);
	if(r < 10) {
		this->AccelerationX = -this->AccelerationX;
	} else if(r < 20) {
		this->AccelerationY = -this->AccelerationY;
	}
	this->SpeedX += this->AccelerationX * CFPS::FPSControl.GetSpeedFactor();
	this->SpeedY += this->AccelerationY * CFPS::FPSControl.GetSpeedFactor();

	if(this->SpeedX > this->MaxSpeed) this->SpeedX = this->MaxSpeed;
	if(this->SpeedY > this->MaxSpeed) this->SpeedY = this->MaxSpeed;
	if(this->SpeedX < -this->MaxSpeed) this->SpeedX = -this->MaxSpeed;
	if(this->SpeedY < -this->MaxSpeed) this->SpeedY = -this->MaxSpeed;

	Anim_Control.OnAnimate();

	this->X += this->SpeedX * CFPS::FPSControl.GetSpeedFactor();
	this->Y += this->SpeedY * CFPS::FPSControl.GetSpeedFactor();
}

#include "CEntity_Buggy.h"


CEntity_Buggy::CEntity_Buggy() {
	this->SpeedX = 0;
	this->SpeedY = 0;
	this->MaxSpeed = 2;
	this->AccelerationX = 1;
	this->AccelerationY = 1;
	this->DestinationX = -1;
	this->DestinationY = -1;
}

bool CEntity_Buggy::OnLoad() {
	CEntity::OnLoad("./gfx/buggy.png", 20, 20, 4);
	return true;
}

void CEntity_Buggy::OnLoop() {
	// if no destination set, pick a random place to go to
	if(this->DestinationX < 0 && this->DestinationY < 0) {
		this->DestinationX = this->X - 200 + (rand() % 400);
		this->DestinationY = this->Y - 200 + (rand() % 400);
		if(this->DestinationX < 0) this->DestinationX = 0;
		if(this->DestinationY < 0) this->DestinationY = 0;
	}

	// head towards destination
	float distance = sqrt(pow((this->X - this->DestinationX), 2) + pow((this->Y - this->DestinationY), 2));

	if(distance < 1) {
		// arrived
	} else {
		this->AccelerationX = (this->X - this->DestinationX);
		this->AccelerationY = (this->Y - this->DestinationY);
		float vMax = abs(this->AccelerationX);
		if(this->AccelerationY > this->AccelerationX) vMax = abs(this->AccelerationY);
		this->AccelerationX = this->AccelerationX / vMax;
		this->AccelerationY = this->AccelerationY/ vMax;
	}

	// hack in a random walk type thing
	//int r = (rand() % 500);
	//if(r < 10) {
	//	this->AccelerationX = -this->AccelerationX;
	//} else if(r < 20) {
	//	this->AccelerationY = -this->AccelerationY;
	//}

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

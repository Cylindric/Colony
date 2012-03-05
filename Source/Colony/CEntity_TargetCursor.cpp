#include "CEntity_TargetCursor.h"


CEntity_TargetCursor::CEntity_TargetCursor() {
}


bool CEntity_TargetCursor::OnLoad() {
	bool rv = CEntity::OnLoad();
	Anim_Control.SetLoop(40, 41);
	Anim_Control.SetFrameRate(200);
	return rv;
}


void CEntity_TargetCursor::OnLoop() {
	Anim_Control.OnAnimate();
}

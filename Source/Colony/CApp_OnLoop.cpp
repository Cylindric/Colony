#include "CApp.h"
#include "CFPS.h"
#include "CEntity.h"

void CApp::OnLoop() {
	CFPS::FPSControl.OnLoop();

	for(unsigned int i = 0; i < CEntity::EntityList.size(); i++) {
		if(!CEntity::EntityList[i]) continue;
		CEntity::EntityList[i]->OnLoop();
	}
}
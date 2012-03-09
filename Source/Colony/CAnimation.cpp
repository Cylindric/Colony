#include "CAnimation.h"
#include <SDL.h>

CAnimation::CAnimation() {
	this->StartFrame = 0;
	this->EndFrame = 0;
	this->CurrentFrame = 0;

	FrameInc = 1;
	FrameRate = 100; //ms
	OldTime = 0;
	Oscillate = false;
}

void CAnimation::SetLoop(int StartFrame, int EndFrame) {
	this->StartFrame = StartFrame;
	this->EndFrame = EndFrame;
	this->CurrentFrame = StartFrame;
}

void CAnimation::OnAnimate() {
	if(OldTime + FrameRate > SDL_GetTicks()) {
		return;
	}

	OldTime = SDL_GetTicks();
	CurrentFrame += FrameInc;

	if(Oscillate) {
		if(FrameInc > 0) {
			if(CurrentFrame >= EndFrame) {
				FrameInc = -FrameInc;
			}
		} else {
			if(CurrentFrame <= StartFrame) {
				FrameInc = -FrameInc;
			}
		}
	} else {
		if(CurrentFrame > EndFrame) {
			CurrentFrame = StartFrame;
		}
	}
}

void CAnimation::SetFrameRate(int Rate) {
	FrameRate = Rate;
}

void CAnimation::SetCurrentFrame(int Frame) {
	if(Frame < StartFrame || Frame >= EndFrame) return;

	CurrentFrame = Frame;
}

int CAnimation::GetCurrentFrame() {
	return CurrentFrame;
}
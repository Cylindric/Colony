#pragma once
#include <SDL.h>

class CAnimation {

private:
	int CurrentFrame;
	int StartFrame;
	int EndFrame;
	int FrameInc;
	int FrameRate;
	unsigned long OldTime;

public:
	bool Oscillate;

public:
	CAnimation();
	void SetLoop(int StartFrame, int EndFrame);
	void OnAnimate();
	void SetFrameRate(int Rate);
	void SetCurrentFrame(int Frame);
	int GetCurrentFrame();
};


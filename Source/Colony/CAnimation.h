#pragma once
#include <SDL.h>

class CAnimation {

private:
	int CurrentFrame;
	int FrameInc;
	int FrameRate;
	unsigned long OldTime;

public:
	int MaxFrames;
	bool Oscillate;

public:
	CAnimation();
	void OnAnimate();
	void SetFrameRate(int Rate);
	void SetCurrentFrame(int Frame);
	int GetCurrentFrame();
};


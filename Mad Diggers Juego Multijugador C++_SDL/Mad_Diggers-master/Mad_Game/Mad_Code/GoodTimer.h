#pragma once
#include "SDLGame.h"

class GoodTimer
{
public:
	GoodTimer();
	~GoodTimer();
	bool checkRunning();
	bool checkCountdown(Uint32 time);
	void startCountdown(Uint32 time, Uint32 timer);
	void stopCountdown();
private:
	bool running_ = false;
	Uint32 time_;
};


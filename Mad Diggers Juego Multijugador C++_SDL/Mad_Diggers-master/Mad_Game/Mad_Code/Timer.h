#pragma once
#include "SDLGame.h"

class Timer
{
public:
	Timer();
	~Timer();

	void start();
	void startCountDown(float duration);
	void stop();
	void pause();
	void unpause();

	//Gets the timer's time
	int get_ticks();
	int get_countDown_ticks();
	//bool checkRunning();
	bool checkCountdown(Uint32 time);
	//void startCountdown(Uint32 time, Uint32 timer);*/
private:
	//The clock time when the timer started
	int startTicks;
	bool started;
	float timeToFinish_;
	float countDownDuration_;


	//bool running_ = false;
	Uint32 time_;
};


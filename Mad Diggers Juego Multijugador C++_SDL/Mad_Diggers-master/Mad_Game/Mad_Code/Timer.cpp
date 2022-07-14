#include "Timer.h"



Timer::Timer(){
	startTicks = 0;
	timeToFinish_ = 0;
	started = false;
}


Timer::~Timer(){

}

void Timer::start()
{
	started = true;
	startTicks = SDL_GetTicks();
}

void Timer::startCountDown(float duration)
{
	started = true;
	timeToFinish_ = SDL_GetTicks();
	countDownDuration_ = duration;
}

int Timer::get_ticks()
{
	if(started) return SDL_GetTicks() - startTicks;
	else return 0;
}

int Timer::get_countDown_ticks()
{
	int cdTime = timeToFinish_ + countDownDuration_ - SDL_GetTicks();
	if (started && cdTime >= 0) return cdTime;
	else return 0;
}

//bool Timer::checkRunning() {
//	return running_;
//}
//
bool Timer::checkCountdown(Uint32 time) {
	if(timeToFinish_ + countDownDuration_ >= time){
		//running_ = false;
		return true;
	}
	else
		return false;
}

//void Timer::startCountdown(Uint32 time, Uint32 timer) {
//	running_ = true;
//	time_ = time + timer;
//}

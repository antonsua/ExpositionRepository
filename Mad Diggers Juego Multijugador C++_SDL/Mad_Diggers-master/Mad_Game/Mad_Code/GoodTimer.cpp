#include "GoodTimer.h"



GoodTimer::GoodTimer(){

}


GoodTimer::~GoodTimer(){

}

bool GoodTimer::checkRunning() {
	return running_;
}

bool GoodTimer::checkCountdown(Uint32 time) {
	if(time >= time_){
		running_ = false;
		return true;
	}
	else
		return false;
}

void GoodTimer::startCountdown(Uint32 time, Uint32 timer) {
	running_ = true;
	time_ = time + timer;
}

void GoodTimer::stopCountdown()
{
	running_ = false;
	time_ = 0;
}

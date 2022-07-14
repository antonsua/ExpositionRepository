#include "weirdTimer.h"

weirdTimer::weirdTimer() {

}

weirdTimer::weirdTimer(double time) : time_(time) {

}

weirdTimer::~weirdTimer() {}

// Starts the timer 
void weirdTimer::startTimer()
{
	active = true;
	timeLeft = time_;
}

// Starts the timer with given duration
void weirdTimer::startTimer(double time)
{
	active = true;
	timeLeft = time_ = time;
}

// Sets duration to given value
void weirdTimer::setTime(double time)
{
	time_ = time;
}

void weirdTimer::stopTimer() {
	active = false;
}

bool weirdTimer::update(double t) {
	if (active)
		timeLeft -= t;

	return checkEnd();
}
 // Checks if the timer has ended
bool weirdTimer::checkEnd()
{
	if (timeLeft <= 0 && active)
		return true;

	return false;
}

bool weirdTimer::isActive()
{
	return active;
}

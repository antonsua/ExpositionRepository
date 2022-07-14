#pragma once

// Timer class to control time passed events

class weirdTimer {

public:
	weirdTimer();
	weirdTimer(double time); 

	~weirdTimer();

	void startTimer();
	void startTimer(double time);
	void setTime(double time);
	void stopTimer();

	bool update(double t);
	bool checkEnd();
	bool isActive();

private:
	double time_ = 0, timeLeft = 0;
	bool active = false;
};
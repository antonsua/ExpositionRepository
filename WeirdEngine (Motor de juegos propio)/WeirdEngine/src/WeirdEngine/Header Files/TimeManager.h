#pragma once

/*
	This class allows to check the time passed
*/


class TimeManager {
public:

	void StartTime();
	double GetTime();

private:

	long long int countStart = 0;
	long long int countLast = 0;
};


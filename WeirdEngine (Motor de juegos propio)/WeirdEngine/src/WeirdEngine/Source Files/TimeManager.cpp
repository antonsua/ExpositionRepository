#include "TimeManager.h"
#include <Windows.h>


void TimeManager::StartTime()
{
	LARGE_INTEGER aux;

	if (!QueryPerformanceFrequency(&aux))
		return;

	QueryPerformanceCounter(&aux);
	countStart = aux.QuadPart;
	countLast = countStart;
}

double TimeManager::GetTime()
{
	LARGE_INTEGER aux;

	QueryPerformanceCounter(&aux);

	double t = double(aux.QuadPart - countLast);
	countLast = aux.QuadPart;

	return t;
}

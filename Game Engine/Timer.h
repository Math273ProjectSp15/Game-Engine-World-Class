#pragma once
#include <windows.h>
#pragma comment(lib, "winmm.lib")

class Timer
{
protected:
	LARGE_INTEGER frequency_;
	LARGE_INTEGER referenceTime_;
public:
	Timer();
	double check() const;
	void reset();
	void sleep(DWORD sleepTime) const;
};
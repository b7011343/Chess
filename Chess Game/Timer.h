#pragma once

#include <string>

class Timer
{
public:
	Timer();
	~Timer();
	std::string TimeStr();

	Timer& operator=(const bool enabled);
	Timer& operator=(const int time);
	const Timer& operator+=(const int timeToAdd);

private:
	int seconds;
	bool enabled;
};
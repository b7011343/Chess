#include "Timer.h"

Timer::Timer() : enabled(false), seconds(0)
{}

Timer::~Timer()
{}

std::string Timer::TimeStr()
{
	int mins = seconds / 60;
	int secs = seconds % 60;
	int hours = mins / 60;
	mins = mins % 60;
	   
	std::string timeStr = std::to_string(hours * 0.000001).substr(6) + ":" + std::to_string(mins * 0.000001).substr(6) + ":" + std::to_string(secs * 0.000001).substr(6);

	return timeStr;
}

Timer& Timer::operator=(const int time)
{
	this->seconds = time;
	return *this;
}

Timer& Timer::operator=(const bool enabled)
{
	this->enabled = enabled;
	return *this;
}

const Timer& Timer::operator+=(const int timeToAdd)
{
	if (enabled)
		this->seconds += timeToAdd;
	return *this;
}


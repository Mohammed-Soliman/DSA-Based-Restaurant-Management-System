#pragma once
#include "TimeManager.h"


TimeManager::TimeManager()
{
	currentTime = 0;
}

void TimeManager::tick()
{
	currentTime++;
}

int TimeManager::now() const
{
	return currentTime;
}

void TimeManager::reset()
{
	currentTime = 1;
}

void TimeManager::reset(const int& ts)
{
	currentTime = ts;
}


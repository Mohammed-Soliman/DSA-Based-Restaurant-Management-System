#pragma once
#include<iostream>
#include <thread>
#include <chrono>
#include <conio.h>
using namespace std;

class TimeManager
{
private:
    int currentTime;

public:
    TimeManager();
    void tick();
    int now() const;
    void reset();
    void reset(const int& ts);
};

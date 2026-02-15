#pragma once
#include "Event.h"
class Restaurant;

class PromoteEvent : public Event {
private:
    double extraMoney;
public:
    PromoteEvent(Restaurant* RS,int time, int id, double exMoney,int event_TYPi);

    bool Execute() override;       
};

#pragma once
#include "PromoteEvent.h"
#include "Restaurant.h"
using namespace std;
#include <iostream>
PromoteEvent::PromoteEvent(Restaurant* RS, int ts, int id, double exMoney, int event_TYPi) : Event(RS,ts, id, event_TYPi), extraMoney(exMoney)
{
}
bool PromoteEvent::Execute() {
    if (RS->getCurrentTime() == event_time) {
        RS->promoteOrder(order_ID, extraMoney);

        return true;
    }
    return false;
}

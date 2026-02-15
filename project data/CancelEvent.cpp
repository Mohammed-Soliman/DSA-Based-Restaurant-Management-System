#pragma once
#include "CancelEvent.h"
#include "Restaurant.h"
using namespace std;
#include <iostream>
CancelEvent::CancelEvent(Restaurant* R,int cancellationTime, int id, int event_TYPi):Event(R, cancellationTime,id, event_TYPi){

}
bool CancelEvent::Execute() {
    if (RS->getCurrentTime() == event_time) {
        RS->cancelOrder(order_ID);
        return true;
    }
    return false;
}

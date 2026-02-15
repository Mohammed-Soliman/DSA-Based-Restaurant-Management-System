 #pragma once
#include "ArrivalEvent.h"
#include "Order.h"
#include "Restaurant.h"
#include "Event.h"
using namespace std;
#include <iostream>

ArrivalEvent::ArrivalEvent(Restaurant* R, int time, int id, orderTYP type, int size, double price, int event_TYPi):Event(R,time,id, event_TYPi){
    order_typ = type;
    order_size=size;
    order_price = price;
}
bool ArrivalEvent::Execute() {
    if (RS->getCurrentTime() == event_time) {
        Order* OR = new Order(order_size, order_typ, order_ID, event_time, order_price);
        RS->addOrder(OR);
        return true;
    }
    return false;
}

#pragma once
#include "Order.h"
class Restaurant;
class Event{
protected:
	int event_time;
	int order_ID;
	Restaurant* RS;
	int event_TYP;
public:
	Event(Restaurant* re, int ts, int id, int event_TYPi);
	virtual bool Execute() = 0;
	friend ostream& operator<<(ostream& COUT, const Event* EV);
};

#pragma once
#include "Event.h"
#include"Restaurant.h"
Event::Event(Restaurant* re, int ts, int id, int event_TYPi){
	RS = re;
	event_time = ts;
	order_ID = id;
	event_TYP = event_TYPi;
}

ostream& operator<<(ostream& COUT, const Event* EV)
{
	string typ;
	switch (EV->event_TYP) {
	case 1:typ = "R"; break;
	case 2:typ = "X"; break;
	case 3:typ = "P"; break;
	}
	COUT << "[" << typ << ", " << EV->event_time << ", " << EV->order_ID << "] ";
	return COUT;
}
#pragma once
#include "Event.h"
class Restaurant;
class CancelEvent : public Event {
public:
	CancelEvent(Restaurant* R,int time, int id, int event_TYPi);
	bool Execute() override;
};
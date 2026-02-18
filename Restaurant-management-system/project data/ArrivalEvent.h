#pragma once
#include "Event.h"


class Restaurant;
class ArrivalEvent :public Event{
private:
	orderTYP order_typ;
	int order_size;
	double order_price;
public:
	ArrivalEvent(Restaurant* R,int time, int id, orderTYP type, int size, double price,int event_TYPi);
	bool Execute() override;
};


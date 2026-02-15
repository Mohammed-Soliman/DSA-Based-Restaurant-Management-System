#pragma once
#include <iostream>
#include <string>
#include "TimeManager.h"
#include"LinkedQueue.h"
#include"ArrayStack.h"
#include "priQueue.h"
#include "Normal_orders_queue.h"
using namespace std;
class Restaurant;
class Event;
class UI {
private:
	string inputFileName;
	Restaurant* RS;
	bool isInteractive;
public:
	UI(Restaurant* RSi);
	~UI();
	void printWelcomeMessage();
	void tick_print(Normal_orders_queue& waiting_normal_orders,
	priQueue<Order*>& waiting_VIP_orders,
	priQueue<Order*>& In_service_orders,
	LinkedQueue<Order*>& waiting_vegan_orders,
	ArrayStack<Order*>& Delivered_orders,
	LinkedQueue<Chef*>& ready_normal_chiefs,
	LinkedQueue<Chef*>& ready_VIP_chiefs,
	LinkedQueue<Chef*>& ready_vegan_chiefs,
	priQueue<Chef*>& In_break_chefs, priQueue<Chef*>& unhealthy_chefs,
		LinkedQueue<Event*>& events) const;
	
};

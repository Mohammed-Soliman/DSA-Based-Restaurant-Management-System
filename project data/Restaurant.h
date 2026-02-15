#pragma once
using namespace std;
#include "TimeManager.h"
#include"LinkedQueue.h"
#include"ArrayStack.h"
#include "priQueue.h"
#include "Event.h"
#include "ArrivalEvent.h"
#include "CancelEvent.h"
#include "PromoteEvent.h"
#include "InService_orders_queue.h"
#include "Chef.h"
#include "Order.h"
#include "UI.h"
#include <string>
#include <fstream>
#include <iostream>


class Restaurant{
private:
	LinkedQueue<Event*> events;
	Normal_orders_queue waiting_normal_orders;
	priQueue<Order*> waiting_VIP_orders;
	InServiceOrdersQueue In_service_orders;
	LinkedQueue<Order*> waiting_vegan_orders;
	LinkedQueue<Order*> waiting_dessert_orders;
	ArrayStack<Order*> Delivered_orders;
	LinkedQueue<Chef*> ready_normal_chiefs;
	LinkedQueue<Chef*> ready_VIP_chiefs;
	LinkedQueue<Chef*> ready_vegan_chiefs;
	LinkedQueue<Chef*> ready_joker_chiefs;
	priQueue<Chef*> In_break_chefs;
	priQueue<Chef*> unhealthy_chefs;
	int total_orders_count;
	int total_chiefs_count;
	int total_normal_chiefs_count;
	int total_vegan_chiefs_count;
	int total_VIP_chiefs_count;
	int total_vegan_orders_count;
	int total_VIP_orders_count;
	int total_normal_orders_count;
	int max_orders;
	int AutoPromotionLimit;
	int promoted;
	TimeManager* TM;
	UI* UI_in;

public:
	Restaurant();
	void addOrder(Order* &O);
	void cancelOrder(int id);
	void promoteOrder(int id, double extra_mony);
	void loadFromFile(const string& filename);
	void makeOutFile();
	void checkBreaks();
	void return_chef(Chef* CH);
	void acceptOrder(Order* O);
	int in_service_priority(Order* OR);
	void processEvents();
	void cookingProcess();
	void checkChefHealth();
	int getCurrentTime()const;
	void assignOrdersToChef();
	void print();
	void AutoPromote();
	void run();
	void return_unhealthyChef_Order(Order* OR);
	void assignChefHealth();
	void assignJokerChef();
	~Restaurant();
};
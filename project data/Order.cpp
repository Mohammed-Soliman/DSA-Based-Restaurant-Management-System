#pragma once
#include "Order.h"
#include <ostream>
#include <string>
#include "Restaurant.h"
#include "Config.h"
Order::Order(int size, orderTYP type, int ID, int time, double price){
		if (size > 0) { Order_size = size; }
		if (time > 0) { Request_time = time; }
		if (price > 0) { Order_price = price; }
		Order_type = type;
		order_id = ID;
		served = false;
}
void Order::set_time(int time) {
	if (time > 0) {
		Request_time = time;
	}
}
void Order::set_price(double price) {
	if (price > 0) {
		Order_price = price;
	}
}
void Order::set_type(orderTYP type) {
	Order_type = type;
}
int Order::get_time() const {
	return Request_time;
}
double Order::get_price()const {
	return Order_price;
}
void Order::set_size(int size) {
	if (size > 0) {
		Order_size = size;
	}
}
int Order::get_size() const {
	return Order_size;
}

void Order::set_assignment_time(int time){
	if (time > 0) {
		assignment_time = time;
	}
}

double Order::calculate_VIP_priority()
{
	return (Config.weight_time * (double(1) / (Request_time + 1)) + Config.weight_money * Order_price + Config.weight_size * Order_size);
}

int Order::get_duration()const
{
	return (Order_size/pC->getSpeed());
}

bool Order::isServed() const
{
	return served;
}

void Order::setSRV(const bool& st, const int& currentTime)
{
	served = st;
	finish_time = currentTime;
}

void Order::checkOut(Chef* &CH)
{
	if (pC) 
	{
		pC->finish();
		CH = pC;
	}
}

int Order::getFT() const
{
	return finish_time;
}

void Order::setFT(int ft)
{
	finish_time = ft; 
}

int Order::getWaitTime() const
{
	return assignment_time - Request_time;
}

void Order::set_cheif(Chef* npC)
{
	pC = npC;
}

Chef* Order::getChef() const
{
	return pC;
}

int Order::getID()const
{
	return order_id;
}

orderTYP Order::get_type()const
{
    return Order_type;
}

ostream& operator<<(ostream& COUT, const Order *order)
{
	if (order->getChef() && !order->isServed()) {
		COUT << order->getID() << "(" << order->get_size() << ") -> " << order->getChef()->getID() << "(" << order->getChef()->getSpeed() << ") ";
	}
	else {
		COUT << order->getID() << " ";
	}
	return COUT;
}
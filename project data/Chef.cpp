#pragma once
#include "Chef.h"
#include <ostream>
#include <string>
#include "Config.h"
#include "Restaurant.h"
Chef::Chef(Restaurant* RSI,const chefTYP& TYP, const int& ID, const int& duration, const int& speedi, int max_orders)
	: ID(ID), break_duration(duration), speed(speedi) {
	cooked_orders = 0;
	this->chef_type = TYP;
	cooking = false;
	health = true;
	RS = RSI;
	this->max_orders = max_orders;
}

Chef::~Chef()
{
	//delete RS;
}


chefTYP Chef::getTYP() const
{
	return chef_type;
}

ostream& operator<<(ostream& COUT, const Chef* chef) {
	COUT << chef->getID()<<" ";
	return COUT;
}

int Chef::getSpeed() const
{
	return speed;
}

int Chef::getCookedOrders() const
{
	return cooked_orders;
}

int Chef::getBreakDuration() const {
	return break_duration;
}

int Chef::getID() const {
	return ID;
}

void Chef::finish() {
	cooked_orders++;
}

void Chef::start_cooking() {
	cooking = true;

}

bool Chef::needBreak()
{
		if (cooked_orders == this->max_orders) 
		{
			cooked_orders = 0;
			return true;
		}
		else
			return false;
}

void Chef::setHealth(const bool& h)
{
	health = h;
}

bool Chef::getHealth() const
{
	return health;
}

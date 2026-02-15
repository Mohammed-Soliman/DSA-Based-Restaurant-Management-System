#pragma once
#include<iostream>
#include "Config.h"
using namespace std;
enum chefTYP { cVIP, cVEGAN, cNORMAL, cJOKER };
class Order;
class Restaurant;
class Chef
{
private:
	chefTYP chef_type;
	int speed;
	int break_duration;
	int cooked_orders;
	const int ID;
	bool cooking, health;
	int max_orders;
	Restaurant* RS;
public:
	int getSpeed() const;
	int getCookedOrders()const;
	int getBreakDuration() const;
	int getID() const;
	void finish();
	void start_cooking();
	bool needBreak();
	void setHealth(const bool& h);
	bool getHealth() const;
	Chef(Restaurant* RSI,const chefTYP& TYP, const int& ID, const int& duration, const int& speedi, int max_orders);
	~Chef();
	chefTYP getTYP() const;

	friend ostream& operator<<(ostream& os, const Chef* chef);
};
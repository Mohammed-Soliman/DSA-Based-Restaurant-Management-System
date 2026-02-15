#pragma once
#include<iostream>
#include"Chef.h"
class Restaurant;
enum orderTYP{ oNORMAL, oVIP, oVEGAN, oDESSERT};
using namespace std;
class Order
{
private:
	int Request_time , assignment_time , finish_time;
	orderTYP Order_type;
	int Order_size; //in dishes
	double Order_price;
	int order_id;
	bool served;
	Chef* pC;
public:
	Order(int size, orderTYP type, int ID, int time, double price);
	int getID()const;
	//void set_id(int id);
	void set_time(int time);
	int get_time()const;
	void set_price(double price);
	double get_price()const;
	void set_type(orderTYP type);
	orderTYP get_type()const;
	void set_size(int size);
	int get_size()const;
	void set_assignment_time(int time);
	double calculate_VIP_priority();
	int get_duration()const;
	//bool check_Chef();
	bool isServed()const;
	void setSRV(const bool& st, const int& currentTime);
	void checkOut(Chef* &CH);
	int getFT() const;
	void setFT(int ft);
	int getWaitTime() const;
	void set_cheif(Chef* npC);
	Chef* getChef() const;
};

ostream& operator<<(ostream& COUT, const Order *order);
#pragma once
#include "LinkedQueue.h"
#include "Order.h"
#include "Config.h"
class Restaurant;
class Normal_orders_queue:public LinkedQueue<Order*>{
private:
	Restaurant* RS;
public:
	Order* getOrderID(const int& ID)
	{
		Order* ptr=nullptr;
		LinkedQueue<Order*> tempQ;
		while (!this->isEmpty())
		{
			Order* temp;
			this->dequeue(temp);
			if (temp->getID() == ID) {
				ptr = temp;
			}
			tempQ.enqueue(temp);
		}
		while (!tempQ.isEmpty()) {
			Order* temp;
			tempQ.dequeue(temp);
			this->enqueue(temp);
		}
		return ptr;
	}

	void cancelOrder(const int& ID) {
		Order* ptr;
		LinkedQueue<Order*> tempQ;
		while (!this->isEmpty())
		{
			Order* temp;
			this->dequeue(temp);
			if (temp->getID() == ID) {
				ptr = temp;
				continue;
			}
			tempQ.enqueue(temp);
		}
		while (!tempQ.isEmpty()) {
			Order* temp;
			tempQ.dequeue(temp);
			this->enqueue(temp);
		}
	}
	bool check_promotion(const int TS, Order* &ORD,const int promotionlimit) {
		if (!frontPtr) { return false; }
		Node<Order*>* OR = frontPtr;
		int wait_time = TS - OR->getItem()->get_time();
		while (OR) {
			if (promotionlimit >= wait_time) {
				ORD = OR->getItem();
				return true;
			}
			OR = OR->getNext();
		}
	}
};


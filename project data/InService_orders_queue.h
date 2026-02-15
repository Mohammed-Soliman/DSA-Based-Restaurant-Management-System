#pragma once
#include "priQueue.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Order.h"

class Order;

class InServiceOrdersQueue : public priQueue<Order*>
{
private:


    bool generate15Percent() {
       return (rand() % 100) < 15; // 15% chance
    }

    bool generate10Percent() {
        return (rand() % 100) < 10; // 10% chance
    }

    bool generate5Percent() {
        return (rand() % 100) < 5; // 5% chance
    }

    public:
	void ChefHealth()
	{
        if(this->isEmpty())
			return;

        srand(time(0));
        priNode<Order*>* current = head;

        while(current)
        {
            int pr;
            Chef* CH = current->getItem(pr)->getChef();

            if (CH->getTYP() == cNORMAL)
                generate15Percent() ? CH->setHealth(false) : CH->setHealth(true);
            
            else if (CH->getTYP() == cVEGAN) 
                generate10Percent() ? CH->setHealth(false) : CH->setHealth(true);
            
            else 
                generate5Percent() ? CH->setHealth(false) : CH->setHealth(true);

			current = current->getNext();
        }
	}

    bool isChefInjured() {
        if (isEmpty()) return false;

        priNode<Order*>* current = head;
        while (current) {
			int pr;
            Chef* CH = current->getItem(pr)->getChef();
            if (!CH->getHealth()) 
            {
                return true; 
            }
            current = current->getNext();
        }
        return false;
	}

    void getUnhealthyChefOrder(Order*& OR) {
        if (this->isEmpty()) return;
        priNode<Order*>* current = head;
        while (current) {
            int pr;
            Chef* CH = current->getItem(pr)->getChef();
            if (!CH->getHealth()) {
                OR = current->getItem(pr);
                return;
            }
            current = current->getNext();
        }
        OR = nullptr;
    }

    void cancelOrder(int id) 
    {
        Order* ptr = nullptr;
        priQueue<Order*> tempQ;
        Order* temp = nullptr;
        int pr = 0;
        bool removed = false;

        while (!this->isEmpty()) {
            this->dequeue(temp, pr);
            if (temp->getID() == id && !removed) {
                // found the order to remove
                ptr = temp;
                removed = true;
                continue;
            }
            //preserving the priority
            tempQ.enqueue(temp, pr);
        }

        // restore remaining orders back into this queue preserving priorities
        while (!tempQ.isEmpty()) {
            tempQ.dequeue(temp, pr);
            this->enqueue(temp, pr);
        }
	}
};

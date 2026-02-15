#include "UI.h"
#include <iostream>
#include <string>
#include <conio.h>
#include "Config.h"
#include"Restaurant.h"
using namespace std;
UI::UI(Restaurant* RSi) {
	RS = RSi;
	this->printWelcomeMessage();
    
    char mode;
    cout << "Select mode (I for Interactive, S for Silent): ";
    cin >> mode;
    cin.ignore();
    isInteractive = (mode == 'I' || mode == 'i'); 
    if (!isInteractive && mode != 'S' && mode != 's') {
        cout << "Invalid mode, defaulting to Interactive.\n";
        isInteractive = true;
    }

    if (!isInteractive) {
        cout << "Simulation Starts in Silent mode ...\n";
    }

	cout << "Please, enter the name of the input file: ";
	getline(cin, inputFileName);
	RS->loadFromFile(inputFileName);
	cout << endl;
}

UI::~UI() {
    RS->makeOutFile();
    if (!isInteractive) {
        cout << "Simulation ends, Output file created\n"; 
    }
}

void UI::printWelcomeMessage()
{
	cout << "Welcome to the Restaurant Simulation!\n";
	cout << "This program simulates a restaurant's order processing system.\n";
}

void UI::tick_print(Normal_orders_queue& waiting_normal_orders, priQueue<Order*>& waiting_VIP_orders, priQueue<Order*>& In_service_orders, LinkedQueue<Order*>& waiting_vegan_orders, ArrayStack<Order*>& Delivered_orders, LinkedQueue<Chef*>& ready_normal_chiefs, LinkedQueue<Chef*>& ready_VIP_chiefs, LinkedQueue<Chef*>& ready_vegan_chiefs, priQueue<Chef*>& In_break_chefs, priQueue<Chef*>& unhealthy_chefs, LinkedQueue<Event*>& events) const
{
    if (!isInteractive) {
        return; 
    }
    cout << "\n\nCurrent timestep\t" << RS->getCurrentTime() << "\n============Events List============\n";
    cout << events.getSize()<< " event remaining\n";
    events.print(10);
    cout << "\n---------------- Waiting Orders IDs ----------------\n" << waiting_normal_orders.getSize() << " NRM orders: "; 
    waiting_normal_orders.print(-1);
    cout << "\n" << waiting_vegan_orders.getSize() << " VEG orders: ";
    waiting_vegan_orders.print(-1);
    cout << "\n" << waiting_VIP_orders.getSize() << " VIP orders: ";
    waiting_VIP_orders.print();
    cout << "\n---------------- In service Orders IDs ----------------\n";
    In_service_orders.print();
    cout << "\n---------------- In break chefs IDs ----------------\n";
    cout << In_break_chefs.getSize() << " In break: ";
    In_break_chefs.print();
    cout << "\n---------------- Available chef IDs ----------------\n";
    cout << ready_normal_chiefs.getSize() << " NRM Chefs: ";
    ready_normal_chiefs.print(-1);
    cout << "\n" << ready_vegan_chiefs.getSize() << " VEG Chefs: ";
    ready_vegan_chiefs.print(-1);
    cout << "\n" << ready_VIP_chiefs.getSize() << " VIP chefs: ";
    ready_VIP_chiefs.print(-1);
    // Print injured (unhealthy) chefs
    /*cout << "\n---------------- Injured chefs IDs ----------------\n";
    cout << unhealthy_chefs.getSize() << " Injured: ";
    unhealthy_chefs.print();*/
    cout << "\n---------------- done IDs ----------------\n";
    cout << "\n" << Delivered_orders.getSize() << "  done until now\n";
    if (!Delivered_orders.isEmpty())
        cout << "IDs:";
    Delivered_orders.print();
    _getch();
}
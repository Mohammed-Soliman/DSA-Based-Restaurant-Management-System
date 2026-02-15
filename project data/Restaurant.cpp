#include "Restaurant.h"
#include <iostream>
#include"Chef.h"
#include "Node.h"
#include <fstream>
#include <string>
#include "Config.h"
#include <random>
#include "TimeManager.h"
#include"LinkedQueue.h"
#include"ArrayStack.h"
#include "priQueue.h"
#include "Event.h"
#include "ArrivalEvent.h"
#include "CancelEvent.h"
#include "PromoteEvent.h"
#include "InService_orders_queue.h"
#include "Order.h"
#include "UI.h"
using namespace std;

void Restaurant::return_chef(Chef* CH)
{
    if (CH)
    {
        chefTYP get_type = CH->getTYP();

        switch (get_type)
        {
        case cNORMAL: ready_normal_chiefs.enqueue(CH); break;
        case cVEGAN: ready_vegan_chiefs.enqueue(CH); break;
        case cVIP: ready_VIP_chiefs.enqueue(CH); break;
        }
    }
}

void Restaurant::checkBreaks()
{
    if (!In_break_chefs.isEmpty())
    {
        Chef* pC;
        int pr;

        while (In_break_chefs.peek(pC, pr) && -pr == TM->now()) {
            In_break_chefs.dequeue(pC, pr);
            return_chef(pC);
        }
    }
}


void Restaurant::loadFromFile(const string& filename) 
{
    ifstream infile(filename);
    int NormChiefSpeed = 0, VeganChiefSpeed = 0, VipChiefSpeed = 0;
    int total_chiefs_count = 0;
    int total_normal_chiefs_count = 0;
    int total_vegan_chiefs_count = 0;
    int total_VIP_chiefs_count = 0;
    int speed_VIP = 0;
    int speed_vegan = 0;
    int num_events = 0;
    int speed_normal = 0;
    int breakD_nrm = 0;
    int breakD_VIP = 0;
    int breakD_veg = 0;

    infile >> total_normal_chiefs_count >> total_vegan_chiefs_count >> total_VIP_chiefs_count;

    total_chiefs_count = total_VIP_chiefs_count + total_vegan_chiefs_count + total_normal_chiefs_count;

    infile >> NormChiefSpeed >> VeganChiefSpeed >> VipChiefSpeed;
    infile >> max_orders >> breakD_nrm >> breakD_veg >> breakD_VIP;


    infile >> AutoPromotionLimit;

    infile >> num_events;
    // Normal chefs
    for (int i = 0; i < total_normal_chiefs_count; i++) {
        Chef* chef = new Chef(this, cNORMAL, i + 1, breakD_nrm, NormChiefSpeed, max_orders);
        ready_normal_chiefs.enqueue(chef);
    }

    // Vegan chefs
    for (int i = 0; i < total_vegan_chiefs_count; i++) {
        Chef* chef = new Chef(this, cVEGAN, total_normal_chiefs_count + i + 1, breakD_veg, VeganChiefSpeed, max_orders);
        ready_vegan_chiefs.enqueue(chef);
    }

    // VIP chefs
    for (int i = 0; i < total_VIP_chiefs_count; i++) {
        Chef* chef = new Chef(this, cVIP, total_vegan_chiefs_count + total_normal_chiefs_count + i + 1, breakD_VIP, VipChiefSpeed, max_orders);
        ready_VIP_chiefs.enqueue(chef);
    }

    for (int i = 0; i < num_events; i++) {
        string event_type;
        infile >> event_type;
        if (event_type == "R") {
            string order_type_char;
            int time, id, size;
            double price;
            infile >> order_type_char >> time >> id >> size >> price;
            orderTYP order_type_enum = oNORMAL;
            if (order_type_char == "N") { order_type_enum = oNORMAL; total_normal_orders_count++; }
            else if (order_type_char == "V") { order_type_enum = oVIP; total_VIP_orders_count++; }
            else if (order_type_char == "G") {
                order_type_enum = oVEGAN; total_vegan_orders_count++;
            }
            events.enqueue(new ArrivalEvent(this, time, id, order_type_enum, size, price, 1));
            total_orders_count++;
        }
        else if (event_type == "X") {
            int time, id;
            infile >> time >> id;
            events.enqueue(new CancelEvent(this, time, id, 2));
        }
        else if (event_type == "P") {
            int time, id, money;
            infile >> time >> id >> money;
            events.enqueue(new PromoteEvent(this, time, id, money, 3));
        }
    }
    infile.close();
}

void Restaurant::acceptOrder(Order* OR) {
    OR->set_assignment_time(TM->now());
}

int Restaurant::in_service_priority(Order* OR)
{
    return -(TM->now() + OR->get_duration());
}

Restaurant::Restaurant() {
    TM = new TimeManager;
    UI_in = new UI(this);
}

void Restaurant::addOrder(Order*& OR)
{
    if (OR)
    {
        orderTYP type = OR->get_type();

        switch (type)
        {
        case oNORMAL:waiting_normal_orders.enqueue(OR); break;
        case oVIP:waiting_VIP_orders.enqueue(OR, OR->calculate_VIP_priority()); break;
        case oVEGAN:waiting_vegan_orders.enqueue(OR); break;
        }
    }
}

void Restaurant::cancelOrder(int id) {
    waiting_normal_orders.cancelOrder(id);
}

void Restaurant::promoteOrder(int id,double extra_mony) {
    Order* OR = waiting_normal_orders.getOrderID(id);
    if (OR) {
        waiting_normal_orders.cancelOrder(id);
        OR->set_price(OR->get_price() + extra_mony);
        waiting_VIP_orders.enqueue(OR, OR->calculate_VIP_priority());
    }
}

void Restaurant::makeOutFile() {
    ofstream outfile("output.txt", ios::out);
    Order* OR;
    double avg_serv = 0;
    double avg_wait = 0;
    double promotedPercent = 0;
    outfile << "FT\tID\tRT\tWT\tST\n";
    while (!Delivered_orders.isEmpty()) {
        Delivered_orders.pop(OR);
        outfile << OR->getFT() << "\t" << OR->getID() << "\t" << OR->get_time() << "\t" << OR->getWaitTime() << "\t" << -in_service_priority(OR);
        outfile << "\n";
        avg_serv += OR->get_duration();
        avg_wait += OR->getWaitTime();
    }
    
    if (total_orders_count > 0) {
        avg_wait /= total_orders_count;
        avg_serv /= total_orders_count;
        promotedPercent = (double(promoted) / total_orders_count) * 100;
    }
    else {
        avg_wait = avg_serv = promotedPercent = 0.0;
    }

    outfile << "=============================================\n";
    outfile << "Orders: " << total_orders_count
        << " [ Norm:" << total_normal_orders_count
        << ", VIP: " << total_VIP_orders_count
        << ", Vegan: " << total_vegan_orders_count << " ]\n";
    outfile << "Chefs: " << total_chiefs_count
        << " [ Norm:" << total_normal_chiefs_count
        << ", VIP: " << total_VIP_chiefs_count
        << ", Vegan: " << total_vegan_chiefs_count << " ]\n";
    outfile << "Avg Wait = " << avg_wait << ", Avg Srv = " << avg_serv << ", Auto Promoted = " << promotedPercent << "%\n";
    outfile.close();
}


void Restaurant::processEvents() {
    if (!events.isEmpty()) {
        Event* event = nullptr;
        events.peek(event);
        while (events.peek(event) && event->Execute()) {
            events.dequeue(event);
            delete event;
        }
    }
}

void Restaurant::cookingProcess()
{
    if (!In_service_orders.isEmpty())
    {
        Order* OR;
        int pr;

        while (In_service_orders.peek(OR, pr) && -pr == TM->now())
        {
            Chef* CH;

            In_service_orders.dequeue(OR, pr);
            OR->setSRV(true, TM->now());
            Delivered_orders.push(OR);
            OR->checkOut(CH);

            if (CH->needBreak())
                In_break_chefs.enqueue(CH, -(TM->now() + CH->getBreakDuration()));
            else
                return_chef(CH);

            OR = nullptr;
            CH = nullptr;
        }

        OR = nullptr;
    }
}

void Restaurant::checkChefHealth()
{
    if (unhealthy_chefs.isEmpty())
        return;

    Chef* CH = nullptr;
    int pr = 0;
    while (unhealthy_chefs.peek(CH, pr) && -pr == TM->now())
    {
        unhealthy_chefs.dequeue(CH, pr);
        CH->setHealth(true); // Heal the chef
        return_chef(CH); // Return the chef to the ready queue
        CH = nullptr;
    }

    CH = nullptr;
}

void Restaurant::return_unhealthyChef_Order(Order* OR)
{
    OR->set_type(oVIP);
    waiting_VIP_orders.enqueue(OR, OR->calculate_VIP_priority());
}

void Restaurant::assignChefHealth()
{
    if (In_service_orders.isEmpty())
        return;

    In_service_orders.ChefHealth();

    while (In_service_orders.isChefInjured())
    {

        Order* OR = nullptr;
        In_service_orders.getUnhealthyChefOrder(OR);
        if (OR != nullptr)
        {
            Chef* CH = OR->getChef();

            if (CH != nullptr)
            {
                In_service_orders.cancelOrder(OR->getID());
                return_unhealthyChef_Order(OR);
                unhealthy_chefs.enqueue(CH, -(TM->now() + CH->getBreakDuration())); // the healling time is equal to the break duration
            }
        }
    }
}

void Restaurant::assignJokerChef()
{
    if (!ready_joker_chiefs.isEmpty())
    {
        while (!(waiting_VIP_orders.isEmpty() && waiting_vegan_orders.isEmpty() && waiting_normal_orders.isEmpty() && waiting_dessert_orders.isEmpty()))
        {
            Chef* CH;
            if (!ready_joker_chiefs.peek(CH))
                break;

            ready_joker_chiefs.dequeue(CH);

            Order* OR;
            int pr;
            // Assign the joker chef to the any available order
            if (waiting_VIP_orders.peek(OR, pr))
            {
                OR->set_cheif(CH);
                OR->set_assignment_time(TM->now());
                CH->start_cooking();
                waiting_VIP_orders.dequeue(OR, pr);
                In_service_orders.enqueue(OR, in_service_priority(OR));
            }
            else if (waiting_vegan_orders.peek(OR))
            {
                OR->set_cheif(CH);
                OR->set_assignment_time(TM->now());
                CH->start_cooking();
                waiting_vegan_orders.dequeue(OR);
                In_service_orders.enqueue(OR, in_service_priority(OR));
            }
            else if (waiting_normal_orders.peek(OR))
            {
                OR->set_cheif(CH);
                OR->set_assignment_time(TM->now());
                CH->start_cooking();
                In_service_orders.enqueue(OR, in_service_priority(OR));
                waiting_normal_orders.dequeue(OR);
            }
            else if (waiting_dessert_orders.peek(OR))
            {
                OR->set_cheif(CH);
                OR->set_assignment_time(TM->now());
                CH->start_cooking();
                In_service_orders.enqueue(OR, in_service_priority(OR));
                waiting_dessert_orders.dequeue(OR);
            }
        }
    }
}

int Restaurant::getCurrentTime() const
{
    return TM->now();
}

void Restaurant::assignOrdersToChef()
{
    Order* OR = nullptr;
    Chef* CH = nullptr;
    int pr = 0;

    // 1) Assign VIP Orders 
    while (!waiting_VIP_orders.isEmpty())
    {
        if (!waiting_VIP_orders.peek(OR, pr))
            break;

        CH = nullptr;

        if (!ready_VIP_chiefs.isEmpty())
            ready_VIP_chiefs.dequeue(CH);
        else if (!ready_normal_chiefs.isEmpty())
            ready_normal_chiefs.dequeue(CH);
        else if (!ready_vegan_chiefs.isEmpty())
            ready_vegan_chiefs.dequeue(CH);

        if (CH != nullptr)
        {
            OR->set_cheif(CH);
            OR->set_assignment_time(TM->now());
            CH->start_cooking();

            In_service_orders.enqueue(OR, in_service_priority(OR));


            if (!waiting_VIP_orders.dequeue(OR, pr))
                break;
        }
        else
        {
            break;
        }
    }

    // 2) Assign Vegan Orders (only to vegan chefs)
    while (!waiting_vegan_orders.isEmpty() && !ready_vegan_chiefs.isEmpty())
    {
        if (!waiting_vegan_orders.peek(OR))
            break;

        ready_vegan_chiefs.dequeue(CH);

        if (CH != nullptr && OR != nullptr)
        {
            OR->set_cheif(CH);
            OR->set_assignment_time(TM->now());
            CH->start_cooking();

            In_service_orders.enqueue(OR, in_service_priority(OR));

            waiting_vegan_orders.dequeue(OR);
        }
    }

    // 3) Assign Normal Orders (Normal orders to VIP chefs, but not vegan)
    while (!waiting_normal_orders.isEmpty())
    {
        if (!waiting_normal_orders.peek(OR))
            break;

        CH = nullptr;

        if (!ready_normal_chiefs.isEmpty())
            ready_normal_chiefs.dequeue(CH);
        else if (!ready_VIP_chiefs.isEmpty())
            ready_VIP_chiefs.dequeue(CH);

        if (CH != nullptr)
        {
            OR->set_cheif(CH);
            OR->set_assignment_time(TM->now());
            CH->start_cooking();

            In_service_orders.enqueue(OR, in_service_priority(OR));

            waiting_normal_orders.dequeue(OR);
        }
        else
        {
            break;
        }
    }
}

void Restaurant::print()
{
    UI_in->tick_print(waiting_normal_orders,
        waiting_VIP_orders,
        In_service_orders,
        waiting_vegan_orders,
        Delivered_orders,
        ready_normal_chiefs,
        ready_VIP_chiefs,
        ready_vegan_chiefs,
        In_break_chefs, unhealthy_chefs, events);
}

void Restaurant::AutoPromote() {
    Order* OR;
    while (waiting_normal_orders.check_promotion(getCurrentTime(), OR, AutoPromotionLimit)) {
        waiting_normal_orders.cancelOrder(OR->getID());
        waiting_VIP_orders.enqueue(OR, OR->calculate_VIP_priority());
        promoted++;
    }
}

void Restaurant::run() {
    do {
        AutoPromote();
        processEvents();
        assignOrdersToChef();
        cookingProcess();
        checkBreaks();
        //assignChefHealth();
        //checkChefHealth();
        print();
        TM->tick();
    } while (!events.isEmpty() || Delivered_orders.getSize() < total_orders_count);
}

Restaurant::~Restaurant()
{
    delete UI_in;
    delete TM;
    UI_in = nullptr;
    TM = nullptr;
}
# DSA-Based-Restaurant-Management-System

This project implements a Restaurant Management System using specific data structures and algothim analysis techniques. The system simulates order handling, chef assignment, cooking, delivery, and break management.

Course: CIE 205 – Data Structures and Algorithm Analysis  
Institution: Zewail City of Science and Technology  
Semester: Summer 2025  

---

## 🚀 Project Overview

The system models a restaurant workflow using queues, priority queues, and stacks while following strict implementation rules:

- Handling Orders based on priority  
- Calculating average wait time for the system  
- Interactive and Silent Simulations  

---

## 📂 Input/Output File Management

The system reads all simulation data from an input file that contains:

- Restaurant configuration parameters  
- Number and types of chefs  
- Order details (type, arrival time, size, etc.)  
- Events such as cancellations and promotions  

Events are processed in chronological order to simulate real-time restaurant operation.  
The output file is given at the end of the simulation containing the statistics of the simulation.  

---

## 🧾 Orders Management

The system manages three main types of orders:

- **VIP Orders**
  - Served based on priority.
  - Can be promoted from Normal orders.

- **Vegan Orders**
  - Served in arrival order.

- **Normal Orders**
  - Served in arrival order.
  - Can be canceled or promoted.

Orders move through the following stages:

1. Waiting
2. In-service (being prepared)
3. Delivered
4. Some extra DSs [Bonus]  

Each order is assigned to a chef and tracked until completion.

---

## 👨‍🍳 Chefs Management

Chefs are categorized into:

- VIP Chefs  
- Vegan Chefs  
- Normal Chefs  
- Some extra Chef classes [Bonus]  

Chef workflow:

1. Ready → Assigned to order  
2. In-Service → Preparing order  
3. Break → After completing a set number of orders  
4. Return → Available again after break  

Chef assignment follows availability rules to ensure efficient order handling.

---

## 👨‍💻 Author(s)
- Mohammed Soliman  
- Abdelrahman Mohsen  
- Mahmoud Tamer  

---

## 📚 References
- Mark Allen Weiss, **Data Structures and Algorithm Analysis in C++**, 4th Edition, Pearson Education, 2014.  
- CIE 205 Lab Materials.
---

## 📌 Key Takeaway

This project demonstrates practical application of core Data Structures concepts including:

- Queue (FCFS scheduling)
- Priority Queue (time-based scheduling)
- Stack (reverse-order output)
- Inheritance (extending queue functionality)

The system efficiently simulates real restaurant operations using proper data structure selection.

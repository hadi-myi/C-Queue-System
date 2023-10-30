#include <iomanip>
#include <iostream>

#include "customer.h"

// Static number to generate automatic customer names if needed.
int Customer::customer_number = 0;

// Static variables for generating random Customers. Please don't touch.
std::random_device Customer::rd;
// Swap the following two lines of code as desired for testing purposes.
//std::mt19937 Customer::generator(rd);     // This line of code generates truly random customers.
std::mt19937 Customer::generator(1);        // This line of code generates the same customers each time.
std::uniform_int_distribution<> Customer::distrib(1, 30);
std::uniform_int_distribution<> Customer::short_dis(1, 10);
std::uniform_int_distribution<> Customer::med_dis(11, 20);
std::uniform_int_distribution<> Customer::long_dis(21, 30);

// Create a Customer with the given name and a task/order/whatever that takes the specified number of minutes.
Customer::Customer(std::string name, int time_needed) {
  Customer::name_ = name;
  Customer::timer_ = time_needed;
}

// Create a Customer with a generic and a task/order/whatever that takes the specified number of minutes.
Customer::Customer(int time_needed) {
  Customer::name_ = "Customer #" + std::to_string(++Customer::customer_number);
  Customer::timer_ = time_needed;
}


Customer::~Customer() {
}

// Get the customer's name.
std::string Customer::GetName() {
  return Customer::name_;
}

// Get how much time is remaining for the customer's task/order/whatever.
int Customer::GetTimeRemaining() {
  return Customer::timer_;
}

// Service the customer for a minute.
void Customer::ServiceTime() {
  if (Customer::timer_ > 0) {
    Customer::timer_--;
  }
}

// Check whether the customer's task is complete.
bool Customer::GetDone() {
  return Customer::timer_ == 0;
}

// Assign a new random task to this Customer. Should only be used when the Customer
// is finished one task and needs to be served again.
void Customer::GiveNewTask() {
  Customer::timer_ = Customer::distrib(Customer::generator);
}

// Assign a new short task to this Customer. Should only be used when the Customer
// is finished one task and needs to be served again.
void Customer::GiveShortTask() {
  Customer::timer_ = Customer::short_dis(Customer::generator);
}

// Assign a new medium task to this Customer. Should only be used when the Customer
// is finished one task and needs to be served again.
void Customer::GiveMediumTask() {
  Customer::timer_ = Customer::med_dis(Customer::generator);
}

// Assign a new long task to this Customer. Should only be used when the Customer
// is finished one task and needs to be served again.
void Customer::GiveLongTask() {
  Customer::timer_ = Customer::long_dis(Customer::generator);
}

// Generate the specified number of Customers, with automated names and random task times.
std::vector<Customer*> GenerateRandomCustomers(int num_customers) {
  std::vector<Customer*> customers(num_customers);

  for (int i=0; i<num_customers; i++) {
    customers[i] = new Customer(Customer::distrib(Customer::generator));
  }
      
  return customers;
}

// A test function for customers.
void Customer_main() {
  // Create 3 customers, with different names and tasks.
  Customer brian = Customer("Brian", 10);
  Customer mark = Customer("Mark", 15);
  Customer andrew = Customer("Andrew", 3);

  // Serve each of the customers concurrently until their tasks are complete.
  for (int i=0; i<15; i++) {
    std::cout << "Time is: 12:" << std::setw(2) << std::setfill('0') << i << std::endl;
    if (!andrew.GetDone()) {
      andrew.ServiceTime();
      std::cout << andrew.GetName() << " was served. " << andrew.GetTimeRemaining() << " more minute(s) needed." << std::endl;
      if (andrew.GetDone()) {
        std::cout << "Andrew has left the line!" << std::endl;
      }
    }
    
    if (!brian.GetDone()) {
      brian.ServiceTime();
      std::cout << brian.GetName() << " was served. " << brian.GetTimeRemaining() << " more minute(s) needed." << std::endl;
      if (brian.GetDone()) {
       std::cout << "Brian has left the line!" << std::endl;
      }
    }
    
    if (!mark.GetDone()) {
      mark.ServiceTime();
      std::cout << mark.GetName() << " was served. " << mark.GetTimeRemaining() << " more minute(s) needed." << std::endl;
      if (mark.GetDone()) {
       std::cout << "Mark has left the line!" << std::endl;
      }
    }
    
    std::cout << std::endl;
  }
}
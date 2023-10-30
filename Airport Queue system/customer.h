#ifndef CUSTOMER_H_
#define CUSTOMER_H_

#include <string>
#include <vector>
#include <random>

// A customer in our system.
class Customer {
  public:
    Customer(std::string name, int time_needed);
    Customer(int time_needed);
    ~Customer();

    std::string GetName();
    int GetTimeRemaining();
    void ServiceTime();
    bool GetDone();

    void GiveNewTask();
    void GiveShortTask();
    void GiveMediumTask();
    void GiveLongTask();

    // Static variables for generating random Customers. Please don't touch.
    static std::random_device rd;
    static std::mt19937 generator;
    static std::uniform_int_distribution<> distrib;
    static std::uniform_int_distribution<> short_dis;
    static std::uniform_int_distribution<> med_dis;
    static std::uniform_int_distribution<> long_dis;
 
  private:
    std::string name_;
    int timer_;
    static int customer_number;
};

std::vector<Customer*> GenerateRandomCustomers(int num_customers);

void Customer_main();

#endif
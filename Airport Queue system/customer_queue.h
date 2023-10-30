#ifndef CUSTOMER_QUEUE_H_
#define CUSTOMER_QUEUE_H_

#include <list>
#include "customer.h"

class CustomerQueue {
  public:
    CustomerQueue();
    CustomerQueue(int capacity);
    ~CustomerQueue();

    virtual void Enqueue(Customer* new_customer);
    virtual Customer* Dequeue();
    virtual Customer* Peek();
    int NumCustomers();
    bool IsEmpty();
    int EstimatedTime();

    void Print();
  
  protected:
    std::list<Customer*> queue_;
    int capacity_;
};

void CustomerQueue_main();

#endif

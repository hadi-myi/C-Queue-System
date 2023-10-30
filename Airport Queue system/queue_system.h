#ifndef QUEUE_SYSTEM_H_
#define QUEUE_SYSTEM_H_

#include <vector>
#include <iostream>
#include "customer.h"
#include "customer_queue.h"
#include "service_counter.h"
//#include "priority_queue.h"

/* The QueueSystem is an abstract class that's meant for you to override with more complex systems.
   Extending subclasses need to override Enqueue(...) and AdvanceTime(), but should call these in their
   overrides so as to properly maintain the time and customer counters.
*/
class QueueSystem {
  public:
    QueueSystem();
    ~QueueSystem();

    // These pure virtual methods must be overridden in your subclasses.
    virtual void Enqueue(Customer* new_customer) = 0;
    virtual void AdvanceTime() = 0;
    int NumCustomers();
    bool IsEmpty();
    

    std::string ReportTimes();
  
  protected:
    int time_elapsed_;
		int num_customers_;
    std::vector<int> customer_wait_times_;
};

#endif
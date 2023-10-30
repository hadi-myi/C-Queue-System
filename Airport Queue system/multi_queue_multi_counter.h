#ifndef MULTI_QUEUE_MULTI_COUNTER_H_
#define MULTI_QUEUE_MULTI_COUNTER_H_

#include "queue_system.h"


class MultiQueueMultiCounter : public QueueSystem {
  public:
    MultiQueueMultiCounter(int num_counters);
    ~MultiQueueMultiCounter();

    // methods that need to be overriden
    void Enqueue(Customer* new_customer);
    void AdvanceTime();

  private:
    // std::vector of service counter to keep track how many service counters 
    std::vector<ServiceCounter> service_counter_multi_;
    std::vector<CustomerQueue> customer_queue_multi_;
    int num_counters_;
};




void MultiQueueMultiCounter_main();


#endif
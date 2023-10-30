#ifndef SINGLE_QUEUE_MULTI_COUNTER_H_
#define SINGLE_QUEUE_MULTI_COUNTER_H_

#include "queue_system.h"


class SingleQueueMultiCounter : public QueueSystem {
  public:
    SingleQueueMultiCounter(int num_counters);
    ~SingleQueueMultiCounter();

    // methods that need to be overriden
    void Enqueue(Customer* new_customer);
    void AdvanceTime();

  private:
    // std::vector of service counter to keep track how many service counters 
    std::vector<ServiceCounter> service_counter_multi_;
    CustomerQueue customer_queue_;
    int num_counters_;
};



void SingleQueueMultiCounter_main();


#endif
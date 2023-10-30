 #ifndef SIMPLE_SYSTEM_H_
#define SIMPLE_SYSTEM_H_

#include "queue_system.h"

class SimpleSystem : public QueueSystem {
  public:
    SimpleSystem();
    ~SimpleSystem();

    // methods that need to be overriden
    void Enqueue(Customer* new_customer);
    void AdvanceTime();

  private:
    // methods to use 
    ServiceCounter service_counter_;
    CustomerQueue  customer_queue_;
    
};

void SimpleSystem_main();

#endif
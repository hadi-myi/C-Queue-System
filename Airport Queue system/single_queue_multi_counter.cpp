#include <iostream>
#include "single_queue_multi_counter.h"


// constructor forSingleQueueMultiCounter that initializes all attributes 
// and a customer queue and service counter with unlimited capacity
// and num_counters num_counters_
SingleQueueMultiCounter::SingleQueueMultiCounter(int num_counters): QueueSystem() {

  SingleQueueMultiCounter::customer_queue_ = CustomerQueue();
  SingleQueueMultiCounter::service_counter_multi_ = {};

  for(int i = 0; i < num_counters; i++) {
    SingleQueueMultiCounter::service_counter_multi_.push_back(ServiceCounter());
  }
}

// destructor for SingleQueueMultiCounter
SingleQueueMultiCounter::~SingleQueueMultiCounter(){
  
}

// this method adds a new customer to the queue or counter as needed and increments customer count
void SingleQueueMultiCounter::Enqueue(Customer* new_customer){

  // bool variable to check if counter is available
  bool counter_available = true;

  // enqueue the new customer
  QueueSystem::Enqueue(new_customer);

  //loop over all the counters, and add a customer from the counter if no one is there
  for (int i = 0; i< SingleQueueMultiCounter::service_counter_multi_.size() && counter_available; i++){
    if (service_counter_multi_[i].IsEmpty()) {
      SingleQueueMultiCounter::service_counter_multi_[i].Enqueue(new_customer);
      counter_available = false;
    }
  }
  // if counter is available, enqueue customer
  if (counter_available) {
    SingleQueueMultiCounter::customer_queue_.Enqueue(new_customer);
  }
  
}


// this method simulates 1 minute passing
void SingleQueueMultiCounter::AdvanceTime(){

  //advance time to increment time by 1 
  QueueSystem::AdvanceTime();
  std::cout << "test" << QueueSystem::time_elapsed_ << std::endl;

  // loop over every counter and check where a customer is ready to be served
  for (int i = 0; i<(SingleQueueMultiCounter::service_counter_multi_.size()); i++){
    // if there someone one at the service counter, serve
    if (SingleQueueMultiCounter::service_counter_multi_[i].NumCustomers() != 0){
      SingleQueueMultiCounter::service_counter_multi_[i].Serve();
  
      // variable to check if customer is dequeud 
      Customer* served_customer_ = service_counter_multi_[i].Dequeue();
      // if there is someone in the queue, attempt to dequeue
      if (served_customer_ !=0){
          
  
        // subtract 1 from num_customers_ because they have been served
        SingleQueueMultiCounter::num_customers_--;
  
        // add customer wait time to the std::vector customer_wait_times_
        SingleQueueMultiCounter::customer_wait_times_.push_back(SingleQueueMultiCounter::time_elapsed_);
  
        // while simple customer queue is not empty, dequeue from customer_queue 
        // and add to service counter
        if (!(SingleQueueMultiCounter::customer_queue_.IsEmpty())){
          Customer* temp = SingleQueueMultiCounter::customer_queue_.Dequeue();
          SingleQueueMultiCounter::service_counter_multi_[i].Enqueue(temp);
        }
    }
  }
  }
}



// This is a test function provided for you to check whether your SingleQueueMultiCounter class
// is implemented properly.
// This is a test function provided for you to check whether your SingleQueueMultiCounter class
// is implemented properly.
void SingleQueueMultiCounter_main() {
  
  SingleQueueMultiCounter test_system1 = SingleQueueMultiCounter(4);
  Customer* brian = new Customer("Brian", 10);
  Customer* mark = new Customer("Mark", 15);
  Customer* andrew = new Customer("Andrew", 3);
  test_system1.Enqueue(brian);
  test_system1.Enqueue(mark);
  test_system1.Enqueue(andrew);

  while (!test_system1.IsEmpty()) {
    test_system1.AdvanceTime();
  }
  std::cout << "First Scenario: " << std::endl;
  std::cout << test_system1.ReportTimes() << std::endl;

  // Expected scenario output
  // Customer wait times: 3, 10, 15
  // Average: 9.33, Median: 10.00, Max: 15

  // Clean up heap after first scenario
  delete brian;
  delete mark;
  delete andrew;
  brian = 0;
  mark = 0;
  andrew = 0;

  std::cout << std::endl << "--------------------------------------------------------" << std::endl << std::endl;

  SingleQueueMultiCounter test_system2 = SingleQueueMultiCounter(4);
  std::vector<Customer*> customers = GenerateRandomCustomers(20);
  for (Customer* customer: customers) {
    std::cout << customer->GetTimeRemaining() << std::endl;
    test_system2.Enqueue(customer);
  }

  while (!test_system2.IsEmpty()) {
    test_system2.AdvanceTime();
  }
  std::cout << "Second Scenario: " << std::endl;
  std::cout << test_system2.ReportTimes() << std::endl;

  // Expected scenario output
  // Customer wait times: 13, 14, 18, 22, 28, 28, 30, 33, 33, 36, 39, 45, 48, 50, 52, 60, 66, 69, 79, 86
  // Average: 42.45, Median: 37.50, Max: 86

  // Clean up heap after second scenario.
  for (Customer* c: customers) {
    delete c;
  }
  
}
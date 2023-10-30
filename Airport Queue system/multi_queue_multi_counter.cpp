#include <iostream>
#include "multi_queue_multi_counter.h"


// constructor forSingleQueueMultiCounter that initializes all attributes 
// and num_counters  service counters and customer queues
MultiQueueMultiCounter::MultiQueueMultiCounter(int num_counters): QueueSystem() {

  MultiQueueMultiCounter::customer_queue_multi_ = {};
  MultiQueueMultiCounter::service_counter_multi_ = {};

  // loop over the std::vectors service_counter_multi
  // and customer_queue_multi and add a service counter or a customer queue to it
  for(int i = 0; i < num_counters; i++) {
    MultiQueueMultiCounter::service_counter_multi_.push_back(ServiceCounter());
    MultiQueueMultiCounter::customer_queue_multi_.push_back(CustomerQueue());
  }
}

// destructor for SingleQueueMultiCounter
MultiQueueMultiCounter::~MultiQueueMultiCounter(){
  
}

// this method adds a new customer to the service counter and increments customer count
// if there is no one at the service counter, otherwise it "sends" the cust to the 
// shortest queue
void MultiQueueMultiCounter::Enqueue(Customer* new_customer){

  // variables to use in loops
  // shortest is for finding the shortest queue and counter available checks the 
  // availability of the counter
  int shortest = 0;
  bool counter_available = true;

  // enqueue new customer
  QueueSystem::Enqueue(new_customer);
  
  // loop that goes over every counter and checks if it is available
  for (int i = 0; i< MultiQueueMultiCounter::service_counter_multi_.size() && counter_available; i++){
    // if it is empty, enqueue the new customer directly in to the service counter
    if (service_counter_multi_[i].IsEmpty()) {
      MultiQueueMultiCounter::service_counter_multi_[i].Enqueue(new_customer);
      counter_available = false;
    }
  }

  // check to see all counters occupied or not
  if (!counter_available){
   return; 
  }

  // loop over all the queues to find the shortest one
  for (int i = 1; i < MultiQueueMultiCounter::customer_queue_multi_.size(); i++){
     if (MultiQueueMultiCounter::customer_queue_multi_[i].NumCustomers() < MultiQueueMultiCounter::customer_queue_multi_[shortest].NumCustomers()){
       shortest = i;
     }
       
  }

  // enquque the new customer to the shortest queue
  MultiQueueMultiCounter::customer_queue_multi_[shortest].Enqueue(new_customer);

}


// this method simulates 1 minute passing 
void MultiQueueMultiCounter::AdvanceTime(){

  //advance time of the queue
  QueueSystem::AdvanceTime();

  //go over every counter
  for (int i = 0; i<(MultiQueueMultiCounter::service_counter_multi_.size()); i++){
    // if there someone one at the service counter, serve
    if (MultiQueueMultiCounter::service_counter_multi_[i].NumCustomers() != 0){
      MultiQueueMultiCounter::service_counter_multi_[i].Serve();
      //served customer variable to check if they are ready to be dequeued
      Customer* served_customer_ = service_counter_multi_[i].Dequeue();
      // if there is someone in the queue, attempt to dequeue
      if (served_customer_ !=0){
          
  
        // subtract 1 from num_customers_ because they have been served
        MultiQueueMultiCounter::num_customers_--;
  
        // add customer wait time to the std::vector customer_wait_times_
          
        MultiQueueMultiCounter::customer_wait_times_.push_back(MultiQueueMultiCounter::time_elapsed_);
        std::cout<< customer_wait_times_[i] <<std::endl;
        // while simple customer queue is not empty, dequeue from customer_queue 
        // and add to service counter
        if (!(MultiQueueMultiCounter::customer_queue_multi_[i].IsEmpty())){
          Customer* temp = MultiQueueMultiCounter::customer_queue_multi_[i].Dequeue();
          MultiQueueMultiCounter::service_counter_multi_[i].Enqueue(temp);
        }
      }
    }
  }
}


void MultiQueueMultiCounter_main() {
  
  MultiQueueMultiCounter test_system1 = MultiQueueMultiCounter(4);
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

  MultiQueueMultiCounter test_system2 = MultiQueueMultiCounter(4);
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
  // Customer wait times: 13, 14, 19, 22, 25, 28, 30, 32, 34, 35, 37, 42, 46, 54, 58, 63, 70, 83, 91, 117
  // Average: 45.65, Median: 36.00, Max: 117

  // Your output may vary slightly depending on the order in which you broke ties. Here's what my
  // version looked like at the start:
  
  // SC0: Customer #1, 13
  // SC1: Customer #2, 30
  // SC2: Customer #3, 22
  // SC3: Customer #4, 28
  // Q0: Customer #5: 1, Customer #9: 5, Customer #13: 6, Customer #17: 12
  // Q1: Customer #6: 4, Customer #10: 8, Customer #14: 12, Customer #18: 29
  // Q2: Customer #7: 10, Customer #11: 3, Customer #15: 11, Customer #19: 17
  // Q3: Customer #8: 30, Customer #12: 12, Customer #16: 21, Customer #20: 26
  

  // Clean up heap after second scenario.
  for (Customer* c: customers) {
    delete c;
  }
}
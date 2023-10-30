#include <iostream>
#include "simple_system.h"

// constructor for SImple System that initializes all attributes 
// and a customer queue and service counter with unlimited capacity
SimpleSystem::SimpleSystem(){

  // intializing all attributes
  SimpleSystem::time_elapsed_ = 0;
	SimpleSystem::num_customers_ = 0;
  SimpleSystem::customer_wait_times_ = {};
  SimpleSystem::service_counter_ = ServiceCounter();
  SimpleSystem::customer_queue_ = CustomerQueue();
}

// destructor for Simple System
SimpleSystem::~SimpleSystem(){
  
}

// this method adds a new customer to the queue and increments customer count
void SimpleSystem::Enqueue(Customer* new_customer){
  
  // if the service counter is empty, add a new customer to the service counter and add one to num_customers
  if (SimpleSystem::service_counter_.IsEmpty()){
    SimpleSystem::service_counter_.Enqueue(new_customer);
    SimpleSystem::num_customers_++;
  }

  // else enqueue the new customer and increment num_customers
  else{
    SimpleSystem::customer_queue_.Enqueue(new_customer);
    SimpleSystem::num_customers_++;
    
  }
}

// this method simulates 1 minute passing for SimpleSystem
void SimpleSystem::AdvanceTime(){
  
  // add one to time elapsed when Advancetime is called
  QueueSystem::AdvanceTime();

  // if there someone one at the service counter, serve
  if (SimpleSystem::service_counter_.NumCustomers() != 0){
    SimpleSystem::service_counter_.Serve();

    //new temp variable to find if customer has been served or not
    Customer* served_customer_ = service_counter_.Dequeue();
    // if there is someone in the queue, attempt to dequeue
    if (served_customer_ !=0){
        

      // subtract 1 from num_customers_ because they have been served
      SimpleSystem::num_customers_--;

      // add customer wait time to the std::vector customer_wait_times_
      SimpleSystem::customer_wait_times_.push_back(SimpleSystem::time_elapsed_);

    // while simple customer queue is not empty, dequeue from customer_queue 
    // and add to service counter
    if (!(SimpleSystem::customer_queue_.IsEmpty())){
      Customer* temp = SimpleSystem::customer_queue_.Dequeue();
       SimpleSystem::service_counter_.Enqueue(temp);
    }
  }

}
  
}

// This is test code for you to test whether your SimpleSystem was implemented properly.
void SimpleSystem_main() {
  
  SimpleSystem test_system1 = SimpleSystem();
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

  // This test code should output:
  // Customer wait times: 10, 25, 28
  // Average: 21.00, Median: 25.00, Max: 28

  // Clean up heap after first scenario
  delete brian;
  delete mark;
  delete andrew;
  brian = 0;
  mark = 0;
  andrew = 0;

  std::cout << std::endl << "--------------------------------------------------------" << std::endl << std::endl;

  SimpleSystem test_system2 = SimpleSystem();
  std::vector<Customer*> customers = GenerateRandomCustomers(20);
  for (Customer* customer: customers) {
    test_system2.Enqueue(customer);
  }
  while (!test_system2.IsEmpty()) {
    test_system2.AdvanceTime();
  }
  std::cout << "Second Scenario: " << std::endl;
  std::cout << test_system2.ReportTimes() << std::endl;

  // This test code should output:
  // Customer wait times: 13, 43, 65, 93, 94, 98, 108, 138, 143, 151, 154, 166, 172, 184, 195, 216, 228, 257, 274, 300
  // Average: 154.60, Median: 152.50, Max: 300

  // Clean up heap after second scenario.
  for (Customer* c: customers) {
    delete c;
  }
  //*/
}
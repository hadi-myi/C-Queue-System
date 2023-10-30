#include <iostream>

#include "service_counter.h"

// initialize service counter queue with capacity of 1
ServiceCounter::ServiceCounter() {

  // empty queue 
  ServiceCounter::queue_ = {};

  // capacity of 1
  ServiceCounter::capacity_ = 1;
}

ServiceCounter::~ServiceCounter() {
  
}

// serve function that simulates serving a customer for 1 minute
void ServiceCounter::Serve() {

  // use peek to get to the first customer and call ServiceTime
  ServiceCounter::queue_.front()->ServiceTime();
  
}

// Dequeue the cust while the queue is not empty and Cust has been served
Customer* ServiceCounter::Dequeue() {

  // if statement to see if size is 1 and time remaining is 0
  if ((ServiceCounter::queue_.size() == 1) && ServiceCounter::queue_.front()->GetTimeRemaining() == 0){

    // temp variable to return from later
    Customer* return_this = CustomerQueue::queue_.front();

    // erase the last name
    CustomerQueue::queue_.erase(CustomerQueue::queue_.begin());

    // return the last name
    return return_this;
  } 
  // else return 0
  else {
    return 0;
  }
}

void ServiceCounter_main() {
	ServiceCounter counter1 = ServiceCounter();
  
  // Create 1 customer and put them in this service counter.
  counter1.Enqueue(new Customer("Brian", 5));

	// We expect Brian to be at this counter.
	std::cout << counter1.Peek()->GetName() << " is at this service counter with processing time " << counter1.EstimatedTime() << "." << std::endl;


	for (int i=0; i<5; i++) {
		counter1.Serve();

		Customer* first_customer = counter1.Dequeue();


		if (first_customer != 0) {
			std::cout << first_customer->GetName() << " is finished." << std::endl;
		}
		if (!counter1.IsEmpty()) {
			std::cout << counter1.Peek()->GetName() << " is at this service counter with processing time " << counter1.EstimatedTime() << "." << std::endl;
		}
	}
  
	/** Expected output:

	Brian is at this service counter with processing time 5.
	Brian is at this service counter with processing time 4.
	Brian is at this service counter with processing time 3.
	Brian is at this service counter with processing time 2.
	Brian is at this service counter with processing time 1.
	Brian is finished.
	*/
}
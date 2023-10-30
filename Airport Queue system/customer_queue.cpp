#include <iostream>

#include "customer_queue.h"

// Initialization of Customer queue object with infinite capacity and no customers
CustomerQueue::CustomerQueue() {
  CustomerQueue::queue_ = {};
  CustomerQueue::capacity_ = -1;
}

// Initialization of Customer queue object with capacity specified and no customers
CustomerQueue::CustomerQueue(int capacity) {
  CustomerQueue::queue_ = {};
  CustomerQueue::capacity_ = capacity;
}


CustomerQueue::~CustomerQueue() {
  
}

// enqueue new_customer into the queue 
void CustomerQueue::Enqueue(Customer* new_customer) {

  // if statement in case capacity is max
  if (CustomerQueue::NumCustomers() != CustomerQueue::capacity_){
    // use pushback to enter a new customer at the back of the queue 
    CustomerQueue::queue_.push_back(new_customer);
  }
  else{
    throw std::runtime_error ("Max Capacity");
  }
}

// dequeue the first customer and return their name, or return 0 if no customers 
Customer* CustomerQueue::Dequeue() {

  // check to see if the queue is empty or not, if empty return 0
  if (CustomerQueue::IsEmpty()){
    return 0;
  }
  
  // temporary variable that stores the first name to return after deleting
	Customer* return_this = CustomerQueue::queue_.front();

  // use erase at the begining of the queue to remove first customer
  CustomerQueue::queue_.erase(CustomerQueue::queue_.begin());

  // return return_this
  return return_this;
}

// returns a pointer to the first Customer in this CustomerQueue or returns zero if no customers
Customer* CustomerQueue::Peek() {
  
  // check to see if the queue is empty or not, if empty return 0
  if (CustomerQueue::IsEmpty()){
    return 0;
  }
  
  // temporary variable that stores the first name to return
  Customer* return_this = CustomerQueue::queue_.front();

  // return the value
  return return_this;
}

// returns the number of customers in the queue
int CustomerQueue::NumCustomers() {

  // use .size() to get the size of queue and return
 return CustomerQueue::queue_.size();
}

// check to see if the queue is empty or not
bool CustomerQueue::IsEmpty() {

  // use .empty() to check 
  return CustomerQueue::queue_.empty();
}

// calculates the estimated time it would take for serving all customers
int CustomerQueue::EstimatedTime() {

  // int variable to store time 
   int time_ = 0;

  // iterator that iterates over the whole list and 
  // adds the time remaining to time_
	std::list<Customer*>::iterator it;
    for (it = queue_.begin(); it != queue_.end(); ++it){
      time_ = time_ + (*it)->GetTimeRemaining();
    }

  // return the total time
  return time_;
}


// Print method provided for your convenience.
void CustomerQueue::Print() {
  std::list<Customer*>::iterator it = CustomerQueue::queue_.begin();
  while (it != CustomerQueue::queue_.end()) {
    std::cout << (*it)->GetName() << ": " << (*it)->GetTimeRemaining() << ", ";
    it++;
  }
  std::cout << std::endl;
}

// A test function for basic customer queues.
void CustomerQueue_main() {
  CustomerQueue test_queue1 = CustomerQueue();
  
  // Create 3 customers and put them in this queue.
  test_queue1.Enqueue(new Customer("Brian", 10));
  test_queue1.Enqueue(new Customer("Mark", 15));
  test_queue1.Enqueue(new Customer("Andrew", 3));

  // Should say 3 customers are in the queue.
	std::cout << test_queue1.NumCustomers() << " customers are in queue." << std::endl;

  // Should say the queue will take 28 minutes.
	std::cout << "Estimated queue time: " << test_queue1.EstimatedTime() << std::endl;

  // Should say the first person needs 10 minutes to help.
  std::cout << test_queue1.Peek()->GetTimeRemaining() << std::endl;
  test_queue1.Peek()->ServiceTime();

  // Should say the first person needs 9 minutes to help.
  std::cout << test_queue1.Peek()->GetTimeRemaining() << std::endl;

  // Should say the queue will take 27 minutes.
  std::cout << "Estimated queue time is now: " << test_queue1.EstimatedTime() << std::endl;

  Customer* first_customer = test_queue1.Dequeue();

  // Should say 2 customers are in the queue.
	std::cout << test_queue1.NumCustomers() << " customers are still in queue." << std::endl;

  // Should say the queue will take 18 minutes.
  std::cout << "Estimated queue time is now: " << test_queue1.EstimatedTime() << std::endl;

  // Prevent memory leak at end of test function.
  delete first_customer;
  while (!test_queue1.IsEmpty()) {
    first_customer = test_queue1.Dequeue();
    delete first_customer;
  }

}
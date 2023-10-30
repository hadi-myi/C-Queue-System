#include <algorithm>
#include <iomanip>
#include <sstream>
#include "queue_system.h"

// Set up an empty queue system.
QueueSystem::QueueSystem() {
  QueueSystem::time_elapsed_ = 0;
  QueueSystem::num_customers_ = 0;
  QueueSystem::customer_wait_times_ = {};
}

QueueSystem::~QueueSystem() {

}

// Add a customer to this queue system. Must be overwritten in your extending subclasses.
void QueueSystem::Enqueue(Customer* new_customer) {
  QueueSystem::num_customers_++;
}

// Add a customer to this queue system. Must be overwritten in your extending subclasses.
void QueueSystem::AdvanceTime() {
  QueueSystem::time_elapsed_++;
}

// Get the number of customers currently in line in this system, counting all queues and service
// counters in the system.
int QueueSystem::NumCustomers() {
  return QueueSystem::num_customers_;
}


// Check if the queue system is empty.
bool QueueSystem::IsEmpty() {
  return QueueSystem::num_customers_ == 0;
}


// Generate some string output that reports the processing times of each customer,
// plus the mean, median, and maximum wait times.
std::string QueueSystem::ReportTimes() {
  std::string return_this = "Customer wait times: ";
  int sum = 0;
  for (int wait_time: QueueSystem::customer_wait_times_) {
    return_this += std::to_string(wait_time) + ", ";
    sum += wait_time;
  }
  return_this.erase(return_this.size() - 2);
  return_this += '\n';

    
  double mean = (double)sum / QueueSystem::customer_wait_times_.size();
  int max = *std::max_element(QueueSystem::customer_wait_times_.begin(), QueueSystem::customer_wait_times_.end());
  std::vector<int> wait_time_copy = {QueueSystem::customer_wait_times_};
  std::sort(wait_time_copy.begin(), wait_time_copy.end());
  double median = wait_time_copy[wait_time_copy.size() / 2];
  if (wait_time_copy.size() % 2 == 0) {
    median = 0.5 * (wait_time_copy[wait_time_copy.size() / 2 - 1] + median);
  }

  // Don't mind this nonsense here. This is just formatting floats so they only print out with 2 decimal places.
  std::stringstream stream;
  stream << std::fixed << std::setprecision(2) << mean;
  std::string mean_string = stream.str();
  stream.str("");
  stream << std::fixed << std::setprecision(2) << median;
  std::string median_string = stream.str();

  
  return_this += "Average: " + mean_string + ", Median: " + median_string + ", Max: " + std::to_string(max);

  return return_this;
}


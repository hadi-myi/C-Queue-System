#ifndef SERVICE_COUNTER_H_
#define SERVICE_COUNTER_H_

#include "customer.h"
#include "customer_queue.h"

class ServiceCounter : public CustomerQueue {
public:
	ServiceCounter();
	~ServiceCounter();

	void Serve();
	virtual Customer *Dequeue();

  

};

void ServiceCounter_main();

#endif

#ifndef LISTENER_H_
#define LISTENER_H_

#include "Messages.h"

class Listener
{
public:
	Listener();
	virtual ~Listener();

	virtual void receive(Message* msg) = 0;
};

#endif /* LISTENER_H_ */

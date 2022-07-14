#ifndef EMITTER_H_
#define EMITTER_H_

#include "Listener.h"
#include "messages.h"
#include <vector>

class Emitter {

public:
	Emitter();
	virtual ~Emitter();

	virtual void send(Message* msg);
	void send(Message * msg, Listener * l);

	virtual void registerListener(Listener* l);
	virtual void removeListener(Listener* l);

private:
	std::vector<Listener*> listeners_;
};

#endif /* EMITTER_H_ */

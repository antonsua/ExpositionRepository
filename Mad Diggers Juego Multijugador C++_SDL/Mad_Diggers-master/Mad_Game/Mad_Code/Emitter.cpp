#include "Emitter.h"

Emitter::Emitter() : listeners_()
{
}

Emitter::~Emitter()
{
}

//////////////////////////////////////////////////////////////////////////////

void Emitter::send(Message* msg)
{
	for (Listener* o : listeners_) {
		o->receive(msg);
	}
}

void Emitter::send(Message * msg, Listener* l)
{
	l->receive(msg);
}

void Emitter::registerListener(Listener* l)
{
	listeners_.push_back(l);
}

void Emitter::removeListener(Listener* l)
{
	std::vector<Listener*>::iterator position = std::find(
		listeners_.begin(), listeners_.end(), l);

	if (position != listeners_.end())
		listeners_.erase(position);
}

#include "Activable.h"

Activable::Activable() : active_(true)
{
}

Activable::~Activable()
{
}

///////////////////////////////////////////////////////////////////////////////

bool Activable::isActive() const
{
	return active_;
}
void Activable::setActive(bool active)
{
	active_ = active;
}

bool Activable::toggleActive()
{
	active_ = !active_;
	return active_;
}
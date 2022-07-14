#include "PatrolPhysics.h"



PatrolPhysics::PatrolPhysics(Vector2D velocity, Uint32 turnTime): turnTime_(turnTime), velocity_(velocity)
{
}


PatrolPhysics::~PatrolPhysics()
{
}

void PatrolPhysics::update(Entity * o, Uint32 time)
{
	if (firstU) {
		firstU = false;
		iniPosition_ = o->getPosition();
	}
	if (timer_.checkRunning()) {
		if (timer_.checkCountdown(time)) {
			velocity_ = Vector2D(-velocity_.getX(), -velocity_.getY());
			if (back)
				o->setPosition(iniPosition_);
			back = !back;
		}
	}
	else {
		o->setVelocity(velocity_);
		timer_.startCountdown(time, turnTime_);
	}
}

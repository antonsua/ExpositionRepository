#include "PaddlePhysicsComponent.h"



PaddlePhysicsComponent::PaddlePhysicsComponent(bool typeMv, float offsetX, float offsetY, double standardVel) :
	typeMv_(typeMv), offsetX_(offsetX), offsetY_(offsetY), standardVel_(standardVel)
{
	vel.set(0, 0);
}


PaddlePhysicsComponent::~PaddlePhysicsComponent()
{
}

void PaddlePhysicsComponent::update(Entity * o, Uint32 time)
{
	pos = o->getPosition();
	pos = pos + vel;

	if (typeMv_) {
		if (pos.getY() <= offsetY_)
			pos.setY(offsetY_);
		else if (pos.getY() + o->getHeight() >= o->getGame()->getWindowHeight() - offsetY_)
			pos.setY(o->getGame()->getWindowHeight() - offsetY_ - o->getHeight());
	}
	else {
		if (pos.getX() <= offsetX_)
			pos.setX(offsetX_);
		else if (pos.getX() + o->getWidth() >= o->getGame()->getWindowWidth() - offsetX_)
			pos.setX(o->getGame()->getWindowWidth() - offsetX_ - o->getWidth());
	}

	o->setVelocity(vel);
	o->setPosition(pos);
}

void PaddlePhysicsComponent::receive(Message* message) {
	if (message->id_ == MOVE_1) {
		if (!typeMv_)
			vel.set(-standardVel_, 0);
		else
			vel.set(0, -standardVel_);
	}
	else if (message->id_ == MOVE_2) {
		if (!typeMv_)
		vel.set(standardVel_, 0);
		else
		vel.set(0, standardVel_);
	}
	else if (message->id_ == NO_MOVE) {
		vel.set(0, 0);
	}

}
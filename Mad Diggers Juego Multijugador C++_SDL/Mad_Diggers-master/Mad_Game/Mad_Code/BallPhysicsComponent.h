#pragma once

#include "EntityUpdateComponent.h"
#include "Paddle.h"
#include "Listener.h"


class BallPhysicsComponent : public EntityUpdateComponent, public Listener
{
public:
	BallPhysicsComponent(float offsetX, float offsetY);
	~BallPhysicsComponent();
	virtual void receive(Message* msg);
	virtual void update(Entity* o, Uint32 time);

protected:
	bool checkInBorderX(Entity* o);
	bool checkInBorderY(Entity* o);

private:
	Paddle* paddle;
	bool exitX, exitY, collide, pCollide;
	float winWidth_, winHeight_, offsetX_, offsetY_;
};
#pragma once
#include "EntityUpdateComponent.h"
#include "Listener.h"

class PaddlePhysicsComponent : public EntityUpdateComponent, public Listener
{
public:
	//typeMv variable refers to the type of smoothMovement: vertical(false) and horizontal(true)
	PaddlePhysicsComponent(bool typeMv, float offsetX, float offsetY, double standardVel);
	~PaddlePhysicsComponent();

	virtual void update(Entity* o, Uint32 time);
	virtual void receive(Message* message);

private:
	float offsetX_, offsetY_, offsetAxisDependant_;
	bool typeMv_;
	double axisPos_, axisVel_, oDimension_, winDimension_;
	double standardVel_;
	Vector2D pos, vel;
};


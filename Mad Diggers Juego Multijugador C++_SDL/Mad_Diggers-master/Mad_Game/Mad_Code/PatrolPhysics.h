#pragma once
#include "EntityUpdateComponent.h"
#include "GoodTimer.h"

class PatrolPhysics :
	public EntityUpdateComponent
{
public:
	PatrolPhysics(Vector2D velocity, Uint32 turnTime);
	~PatrolPhysics();
	void virtual update(Entity* o, Uint32 time);
protected:
	bool firstU = true;
	bool back = false;
	GoodTimer timer_;
	Vector2D velocity_, iniPosition_;
	Uint32 turnTime_;
};


#pragma once
#include "EntityUpdateComponent.h"
#include "Entity.h"
#include "Emitter.h"

const int FLOOR_POS = 150;
const int MIN_VEL = 2;
const int MAX_VEL = 7;

class ApplesManager;
class AppleController : public EntityUpdateComponent,public Emitter
{
public:
	AppleController() {};
	AppleController(Game* game, Entity* o ,ApplesManager* applMG, int colorID);
	~AppleController();

	void update(Entity* o, Uint32 time);
private:

	void setRandVel(Entity* o) const;

	Game * game_;

	double velocity_;
	int colorID_;

};


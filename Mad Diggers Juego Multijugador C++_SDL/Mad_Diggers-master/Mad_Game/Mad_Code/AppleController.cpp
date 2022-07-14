#include "AppleController.h"
#include "ApplesManager.h"


AppleController::AppleController(Game* game,Entity* o ,ApplesManager* applMG,int colorID): 
	game_(game),colorID_(colorID)
{
	setRandVel(o);
	registerListener(applMG);
}

AppleController::~AppleController()
{
}

void AppleController::update(Entity * o, Uint32 time)
{
	o->setPosition(o->getPosition() + o->getVelocity());

	if (o->getPosition().getY() > game_->getWindowWidth()-FLOOR_POS) {
		send(&AppleDown(colorID_));
		o->setActive(false);
	}


}

void AppleController::setRandVel(Entity* o) const
{
	o->setVelocity(Vector2D(0, rand() % MAX_VEL + MIN_VEL));
}

#include "DemoActor.h"

DemoActor::DemoActor(Game* game) : DemoActor(game, vector<EntityComponent*>()) {}

DemoActor::DemoActor(Game* game, vector<EntityComponent*> components) : Entity(game, components)
{
	init();
}

DemoActor::~DemoActor()
{
	//only delete components if you created them here
}

void DemoActor::init()
{
	setWidth(50);
	setHeight(50);

	//random position
	setPosition(Vector2D(
		game_->getRnd(game_->getWindowWidth() - width_),
		game_->getRnd(game_->getWindowHeight() - height_)));

	setVelocity(Vector2D(0, 0));
}
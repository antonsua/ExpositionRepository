#include "Apple.h"



Apple::Apple(Game* game, Resources::ColorId appleColor) : Entity(game),
renderComp_(game,Resources::s_hive,appleColor)
{
	
	addComponent(&renderComp_);
	setWidth(APPLE_WIDHT);
	setHeight(APPLE_HEIGHT);
	c.x = getWidth() / 2;
	c.y = getHeight() / 2;
	c.r = getWidth() / 2;
	
}


Apple::~Apple()
{
}

void Apple::setIdentifier(const int n)
{
	colorIdentifier_ = n;
}

void Apple::update(Uint32 time)
{
	Entity::update(time);
	updateCircle();
}

void Apple::updateCircle()
{
	c.x = getPosition().getX();
	c.y = getPosition().getY();
}


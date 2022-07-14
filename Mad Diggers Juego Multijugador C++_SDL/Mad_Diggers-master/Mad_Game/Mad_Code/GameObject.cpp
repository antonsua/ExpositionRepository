#include "GameObject.h"

GameObject::GameObject(Game* game) :
	Activable(), game_(game), killed_(false)
{
}

GameObject::~GameObject()
{
}

Game* GameObject::getGame() const {
	return game_;
}

///////////////////////////////////////////////////////////////////////////////

bool GameObject::isKilled() const
{
	return killed_;
}

void GameObject::kill()
{
	setActive(false);
	killed_ = true;
}

#include "ButtonInputComponent.h"


ButtonInputComponent::ButtonInputComponent(int x)
{
	isAbove = false;
	this->setActive(true);
	butId_ = x;
}

ButtonInputComponent::~ButtonInputComponent()
{
}

void ButtonInputComponent::handleEvents(Entity* o, Uint32 time, const SDL_Event& event) {
	if (event.type == SDL_MOUSEBUTTONDOWN && isAbove) {
		std::cout << "You thought it was a button, but it was me, Dio!" << endl;
		switch (butId_)
		{
		case 0:
			send(new Message(STATE_BOARD));
			break;
		case 1:
			send(new Message(STATE_CREDITS));
			break;
		case 2:
			send(new Message(STATE_CREDITS_EXT));
			break;
		default:
			break;
		}
	}
}
void ButtonInputComponent::update(Entity* o, Uint32 time) {
	if (isInRect(o))
		isAbove = true;
	else
		isAbove = false;
}
bool ButtonInputComponent::isInRect(Entity* o) {
	bool itIs = false;
	SDL_Point p;
	SDL_GetMouseState(&p.x, &p.y);
	if (p.x > o->getPosition().getX() && p.x < o->getPosition().getX() + o->getWidth() && p.y> o->getPosition().getY() && p.y < o->getPosition().getY() + o->getHeight())
		itIs = true;
	return itIs;
}
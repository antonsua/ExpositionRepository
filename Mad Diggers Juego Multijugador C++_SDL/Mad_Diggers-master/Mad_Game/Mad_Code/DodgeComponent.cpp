#include "DodgeComponent.h"



DodgeComponent::DodgeComponent(SDL_Keycode left, SDL_Keycode right, SDL_Keycode up, SDL_Keycode down, double speed, double maxVelocity, int id)
	:left_(left), right_(right), up_(up), down_(down), speed_(speed), maxVelocity_(maxVelocity), id_(id) {
}

DodgeComponent::DodgeComponent()
{
}


DodgeComponent::~DodgeComponent()
{
}

void DodgeComponent::update(Entity * o, Uint32 time)
{
	Vector2D v = o->getVelocity();
	//Controlamos las posibles direcciones
	if (keysHeld[0])
			v = (v + Vector2D(-speed_, 0));
	if (keysHeld[1])
			v = (v + Vector2D(speed_, 0));
	if (keysHeld[2])
		v = (v + Vector2D(0, -speed_));
	if ((keysHeld[3]))
		v = (v + Vector2D(0, speed_));

	if (!(v.getX() == 0) && !(keysHeld[0] || keysHeld[1])) {
			if (v.getX() < 0)
				v.setX(v.getX() + maxVelocity_ / 12);
			else
				v.setX(v.getX() - maxVelocity_ / 12);
	}
	if (!(v.getY() == 0) && !(keysHeld[2] || keysHeld[3])) {
		if (v.getY() < 0)
			v.setY(v.getY() + maxVelocity_ / 12);
		else
			v.setY(v.getY() - maxVelocity_ / 12);
	}

	//Si la velocidad supera la maxVelocity_, entonces la nueva velocidad es maxvelocity
	if (v.getX() > maxVelocity_)
		v = Vector2D(maxVelocity_, v.getY());
	else if (v.getX() < -maxVelocity_)
		v = Vector2D(-maxVelocity_, v.getY());
	if (v.getY() > maxVelocity_)
		v = Vector2D(v.getX(), maxVelocity_);
	else if (v.getY() < -maxVelocity_)
		v = Vector2D(v.getX(),  - maxVelocity_);
	if (v.getX() < maxVelocity_ / 25 && v.getX() > -maxVelocity_ / 25)
		v.setX(0);
	if (v.getY() < maxVelocity_ / 25 && v.getY() > -maxVelocity_ / 25)
		v.setY(0);

	o->setVelocity(v);
}

void DodgeComponent::handleEvents(Entity* o, Uint32 time, const SDL_Event& event)
{
	if (event.type) {

		if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == left_)keysHeld[0] = true;
			if (event.key.keysym.sym == right_)keysHeld[1] = true;
			if (event.key.keysym.sym == up_)keysHeld[2] = true;
			if (event.key.keysym.sym == down_)keysHeld[3] = true;
		}
		if (event.type == SDL_KEYUP)
		{
			if (event.key.keysym.sym == left_)keysHeld[0] = false;
			if (event.key.keysym.sym == right_)keysHeld[1] = false;
			if (event.key.keysym.sym == up_)keysHeld[2] = false;
			if (event.key.keysym.sym == down_)keysHeld[3] = false;
		}
	}


}


void DodgeComponent::receive(Message * msg)
{
	switch (msg->id_)
	{
	case PLATFORM_COLLISION: {
		Message_PlayerCollision* m = static_cast<Message_PlayerCollision*>(msg);
		break;
	}
	case TRAP_COLLISION: {
		Message_DeadlyCollision* m = static_cast<Message_DeadlyCollision*>(msg);
		break;
	}
	case DPAD_LEFT: {
		keysHeld[0] = true;
		break;
	}
	case DPAD_RIGHT: {
		keysHeld[1] = true;
		break;
	}
	case DPAD_UP: {
		keysHeld[2] = true;
		break;
	}
	case DPAD_DOWN: {
		keysHeld[3] = true;
		break;
	}
	case uA: {
		keysHeld[2] = false;
		break;
	}
	case uDPAD_LEFT: {
		keysHeld[0] = false;
		break;
	}
	case uDPAD_RIGHT: {
		keysHeld[1] = false;
		break;
	}
	case uDPAD_UP: {
		keysHeld[2] = false;
		break;
	}
	case uDPAD_DOWN: {
		keysHeld[3] = false;
		break;
	}
	default:
		break;
	}


}

#include "PlatformGameComponent.h"



PlatformGameComponent::PlatformGameComponent(SDL_Keycode left, SDL_Keycode right, SDL_Keycode up, SDL_Keycode down, double speed, double maxVelocity, double jumpVelocity, int id)
	:left_(left), right_(right), up_(up), down_(down), speed_(speed), maxVelocity_(maxVelocity), jumpVelocity_(jumpVelocity), id_(id){
}

PlatformGameComponent::PlatformGameComponent()
{
}


PlatformGameComponent::~PlatformGameComponent()
{
}

void PlatformGameComponent::setIniPosition(Vector2D pos)
{
	iniPosition_ = pos;
}

void PlatformGameComponent::update(Entity * o, Uint32 time)
{
	if (goIni) {
		o->setPosition(iniPosition_);
		o->setVelocity({ 0,0 });
		goIni = false;
	}

	if (!air_) {
		if (!timer.checkRunning())
			timer.startCountdown(time, 80);
		else if (timer.checkCountdown(time))
			canJump_ = true;
	}
	else if (timer.checkRunning())
		timer.stopCountdown();

	Vector2D v = o->getVelocity();
	//Controlamos las posibles direcciones
	if (keysHeld[0]) {
		if (air_)
			v = (v + Vector2D(-speed_/2, 0));
		else
			v = (v + Vector2D(-speed_, 0));
		}
	if (keysHeld[1]) {
		if (air_)
			v = (v + Vector2D(speed_/2, 0));
		else 
			v = (v + Vector2D(speed_, 0));
	}
	if (keysHeld[2]) {
		if (canJump_) {
			v = Vector2D(v.getX(), -jumpVelocity_);
			o->setPosition(o->getPosition() + Vector2D(0, -jumpVelocity_));
			o->getGame()->sendToSM(&Message(JUMP));
		}
	}
	if ((keysHeld[3]) && v.getY() >= -1)
		v = (v + Vector2D(0, speed_));

	if (!(v.getX() == 0) && !(keysHeld[0] || keysHeld[1])) {
		if (air_) {
			if (v.getX() < 0)
				v.setX(v.getX() + maxVelocity_ / 28);
			else
				v.setX(v.getX() - maxVelocity_ / 28);
		}
		else {
			if (v.getX() < 0)
				v.setX(v.getX() + maxVelocity_ / 12);
			else
				v.setX(v.getX() - maxVelocity_ / 12);
		}
	}
	if (air_) {
		if(v.getY() < 0)
			if(keysHeld[2])
				v = v - Vector2D(0, 0.07);
			v = v + Vector2D(0, 0.20);
	}



	//Si la velocidad supera la maxVelocity_, entonces la nueva velocidad es maxvelocity
	if (v.getX() > maxVelocity_)
		v = Vector2D(maxVelocity_, v.getY());
	else if (v.getX() < -maxVelocity_)
		v = Vector2D(-maxVelocity_, v.getY());
	else if (v.getX() < maxVelocity_ / 25 && v.getX() > -maxVelocity_ / 25)
		v.setX(0);
	if (v.getY() > 10)
		v = Vector2D(v.getX(), 10);

	o->setVelocity(v);
}

void PlatformGameComponent::handleEvents(Entity* o, Uint32 time, const SDL_Event& event)
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


void PlatformGameComponent::receive(Message * msg)
{
	switch (msg->id_)
	{
	case PLATFORM_COLLISION: {
		Message_PlatformCollision* m = static_cast<Message_PlatformCollision*>(msg);
		if (m->player_ == id_) {
			if (m->collision_) {
				air_ = m->collision_;
				canJump_ = false;
			}
			else 
				air_ = false;
		}
		break;
	}
	case TRAP_COLLISION: {
		Message_TrapCollision* m = static_cast<Message_TrapCollision*>(msg);
		if (m->player_ == id_) {
			air_ = true;
			canJump_ = keysHeld[0] = keysHeld[1] = keysHeld[2] = keysHeld[3] = false;
			goIni = true; 
		}
		break;
	}
	case A: {
		keysHeld[2] = true;
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

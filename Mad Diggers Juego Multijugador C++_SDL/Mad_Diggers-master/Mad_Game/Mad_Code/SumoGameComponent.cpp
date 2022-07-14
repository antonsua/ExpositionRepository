#include "SumoGameComponent.h"



SumoGameComponent::SumoGameComponent(SDL_Keycode left, SDL_Keycode right, SDL_Keycode up, SDL_Keycode down, double Thurst, double maxVelocity)
	:left_(left), right_(right), up_(up), down_(down), thurst_(Thurst), maxVelocity_(maxVelocity)
{
}

SumoGameComponent::SumoGameComponent()
{
}


SumoGameComponent::~SumoGameComponent()
{
}

void SumoGameComponent::update(Entity * o, Uint32 time)
{
	Vector2D v = o->getVelocity();
	//Controlamos las posibles direcciones
	if (keysHeld[0])
		v = (v + Vector2D(-thurst_, 0));
	if (keysHeld[1])
		v = (v + Vector2D(thurst_, 0));
	if (keysHeld[2])
		v = (v + Vector2D(0, -thurst_));
	if ((keysHeld[3]))
		v = (v + Vector2D(0, thurst_));

	if (!(v.getX() == 0) && !(keysHeld[0] || keysHeld[1])) {
		if (v.getX() < 0)
			v.setX(v.getX() + maxVelocity_ / 60);
		else
			v.setX(v.getX() - maxVelocity_ / 60);
	}
	if (!(v.getY() == 0) && !(keysHeld[2] || keysHeld[3])) {
		if (v.getY() < 0)
			v.setY(v.getY() + maxVelocity_ / 60);
		else
			v.setY(v.getY() - maxVelocity_ / 60);
	}

	//Si la velocidad supera la maxVelocity_, entonces la nueva velocidad es maxvelocity
	if (v.getX() > maxVelocity_)
		v = Vector2D(maxVelocity_, v.getY());
	else if (v.getX() < -maxVelocity_)
		v = Vector2D(-maxVelocity_, v.getY());
	if (v.getY() > maxVelocity_)
		v = Vector2D(v.getX(), maxVelocity_);
	else if (v.getY() < -maxVelocity_)
		v = Vector2D(v.getX(), -maxVelocity_);
	if (v.getX() < maxVelocity_ / 25 && v.getX() > -maxVelocity_ / 25)
		v.setX(0);
	if (v.getY() < maxVelocity_ / 25 && v.getY() > -maxVelocity_ / 25)
		v.setY(0);

	o->setVelocity(v);
}

void SumoGameComponent::handleEvents(Entity* o, Uint32 time, const SDL_Event& event)
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


void SumoGameComponent::receive(Message * msg)
{
	switch (msg->id_)
	{
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

//	if (event.type) {
//
//		if (event.type == SDL_KEYDOWN)
//		{
//			if (event.key.keysym.sym == left_)keysHeld[0] = true;
//			if (event.key.keysym.sym == right_)keysHeld[1] = true;
//			if (event.key.keysym.sym == up_)keysHeld[2] = true;
//			if (event.key.keysym.sym == down_)keysHeld[3] = true;
//		}
//		if (event.type == SDL_KEYUP)
//		{
//			if (event.key.keysym.sym == left_)keysHeld[0] = false;
//			if (event.key.keysym.sym == right_)keysHeld[1] = false;
//			if (event.key.keysym.sym == up_)keysHeld[2] = false;
//			if (event.key.keysym.sym == down_)keysHeld[3] = false;
//		}
//	}
//
//	//Controlamos las posibles direcciones
//	if (keysHeld[0] || keysHeld[1] || keysHeld[2] || keysHeld[3])
//
//	{
//		if (keysHeld[0])o->setDirection(direccionControl(o->getDirection() + Vector2D(-1, 0)));
//		if (keysHeld[1]) o->setDirection(direccionControl(o->getDirection() + Vector2D(1, 0)));
//		if (keysHeld[2]) o->setDirection(direccionControl(o->getDirection() + Vector2D(0, -1)));
//		if (keysHeld[3]) o->setDirection(direccionControl(o->getDirection() + Vector2D(0, 1)));
//		o->setVelocity(o->getVelocity() + o->getDirection()*thurst_);
//	}
//	 if(gamepadActive){
//		o->setDirection(direccionControl(o->getDirection() + auxDir_));
//		o->setVelocity(o->getVelocity() + o->getDirection()*thurst_);
//	}
//
//	
//
//	//else  o->setDirection(Vector2D(0, 0));
//
//	//Si la velocidad supera la maxVelocity_, entonces la nueva velocidad es maxvelocity
//	if (o->getVelocity().magnitude() > maxVelocity_)
//	{
//		Vector2D aux = o->getVelocity();
//		aux.normalize();
//		aux = aux * maxVelocity_;
//		o->setVelocity(aux);
//	}
//
//	//Establecemos la velocidad
//
//}
//
//
//Vector2D SumoGameComponent::direccionControl(Vector2D direccion)
//{
//	int x = direccion.getX();
//	int y = direccion.getY();
//
//	if (x < -1) x = -1;
//	if (x > 1) x = 1;
//	if (y < -1)y = -1;
//	if (y > 1)y = 1;
//
//
//	return Vector2D(x, y);
//}
//
//void SumoGameComponent::receive(Message * msg)
//{
//	if (msg->id_ == DPAD_LEFT)
//	{
//		auxDir_ = { -1, 0 };
//		gamepadActive = true;
//	}
//	if (msg->id_ == DPAD_RIGHT) {
//		auxDir_ = { 1, 0 };
//		gamepadActive = true;
//	}
//	if (msg->id_ == DPAD_UP) {
//		auxDir_ = {0,-1 };
//		gamepadActive = true;
//	}
//	if (msg->id_ == DPAD_DOWN) {
//		auxDir_ = { 0, 1 };
//		gamepadActive = true;
//	}
//	
//	
//}

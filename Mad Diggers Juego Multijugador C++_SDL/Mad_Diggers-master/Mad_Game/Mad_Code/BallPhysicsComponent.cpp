#include "BallPhysicsComponent.h"

BallPhysicsComponent::BallPhysicsComponent(float offsetX, float offsetY) :offsetX_(offsetX), offsetY_(offsetY)
{
	collide = pCollide = false;
}

BallPhysicsComponent::~BallPhysicsComponent()
{
}

void BallPhysicsComponent::update(Entity * o, Uint32 time)
{
	Vector2D v = o->getVelocity();
	Vector2D v2;

	if (collide) {
		if (exitX || exitY) {
		if (exitX) {
			v.setY(-v.getY());
			v2 = v;
			v2.normalize();
			//while (checkCollision(o))
			o->setPosition(o->getPosition() + Vector2D(v2.getX(), 0));
		}

		if (exitY) {
			v.setX(-v.getX());
			v2 = v;
			v2.normalize();
			//while (checkCollision(o))
			o->setPosition(o->getPosition() + Vector2D(0, v2.getY()));
		}
	}
		else { //logica de rebote con las palas

			if (checkInBorderX(o)) {
				v.setX(-v.getX());
				if (pCollide) {
					v2 = v;
					v2.normalize();
					double distance = paddle->getPosition().getY() - (o->getPosition().getY() + o->getHeight() / 2);
					if (distance > -paddle->getHeight() / 3) {
						if (v.getY() < 0) {
							v2.setY(v2.getY() * 1.3);
							v2.normalize();
							v = v2 * v.magnitude();
						}
						else {
							v.setX(v.getX() * 1.3);
							v2.normalize();
							v = v2 * v.magnitude();
						}
					}
					else if (distance < -2 * paddle->getHeight() / 3) {
						if (v.getY() < 0) {
							v2.setX(v2.getX() * 1.3);
							v2.normalize();
							v = v2 * v.magnitude();
						}
						else {
							v.setY(v.getY() * 1.3);
							v2.normalize();
							v = v2 * v.magnitude();
						}
					}
					pCollide = false;
					
				}
			}
			if (checkInBorderY(o)) {
				v.setY(-v.getY());
				if (pCollide) {
					v2 = v;
					v2.normalize();
					double distance = paddle->getPosition().getX() - (o->getPosition().getX() + o->getWidth() / 2);
					if (distance > -paddle->getWidth() / 3) {
						if (v.getX() < 0) {
							v2.setY(v2.getY() * 1.3);
							v2.normalize();
							v = v2 * v.magnitude();
						}
						else {
							v.setX(v.getX() * 1.3);
							v2.normalize();
							v = v2 * v.magnitude();
						}
					}
					else if (distance < -2 * paddle->getWidth() / 3) {
						if (v.getX() < 0) {
							v2.setX(v2.getX() * 1.3);
							v2.normalize();
							v = v2 * v.magnitude();
						}
						else {
							v.setY(v.getY() * 1.3);
							v2.normalize();
							v = v2 * v.magnitude();
						}
					}
					pCollide = false;
				}
			}
		}
		//v = v * 1.03;
		if(v.getY() < 0)
			v.setY(v.getY() - 0.08);
		else
			v.setY(v.getY() + 0.08);

		if (v.getX() < 0)
			v.setX(v.getX() - 0.08);
		else
			v.setX(v.getX() + 0.08);
		o->setVelocity(v);
		collide = false;
	}
	else {
		exitX = checkInBorderX(o);
		exitY = checkInBorderY(o);
	}

	o->setPosition(o->getPosition() + o->getVelocity());

}

bool BallPhysicsComponent::checkInBorderX(Entity* o)
{
	if (o->getPosition().getX() + o->getWidth() > o->getGame()->getWindowWidth() - offsetX_
		|| offsetX_ > o->getPosition().getX())
		return true;

	else
		return false;
}

bool BallPhysicsComponent::checkInBorderY(Entity * o)
{
	if (o->getPosition().getY() + o->getHeight() > o->getGame()->getWindowHeight() - offsetY_
		|| offsetY_ > o->getPosition().getY())
		return true;

	else
		return false;
}

void BallPhysicsComponent::receive(Message* msg) {
	switch (msg->id_)
	{
	case BALL_BLOCK_COLLISION:{
		collide = true;
		break;
		}
	case BALL_PADDLE_COLLISION: {
		PongMessage_BallPaddleCollision* m = static_cast<PongMessage_BallPaddleCollision*>(msg);
		paddle = m->paddle_;
		collide = true;
		pCollide = true;
		break;
	}
	}
}

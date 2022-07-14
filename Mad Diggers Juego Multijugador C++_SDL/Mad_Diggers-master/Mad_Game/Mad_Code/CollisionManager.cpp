#include "CollisionManager.h"

bool CollisionManager::checkCollision(Physical * o1, Physical * o2) {
	Vector2D o1Pos = o1->getPosition();
	double o1Width = o1->getWidth();
	double o1Height = o1->getHeight();

	Vector2D o2Pos = o2->getPosition();
	double o2Width = o2->getWidth();
	double o2Height = o2->getHeight();

	bool collideX, collideY;

	collideX = collideY = false;


	collideX = !(o1Pos.getX() + o1Width < o2Pos.getX()
		|| o2Pos.getX() + o2Width < o1Pos.getX());

	collideY = !(o1Pos.getY() + o1Height < o2Pos.getY()
		|| o2Pos.getY() + o2Height < o1Pos.getY());

	return (collideX && collideY);
}

CollisionManager::CollisionManager()
{
}

CollisionManager::~CollisionManager()
{
}

bool CollisionManager::checkCollision(Vector2D pointPos, double width, Physical * o)
{
	Vector2D oPos = o->getPosition();
	double oWidth = o->getWidth();
	double oHeight = o->getHeight();
	bool collideX, collideY;

	collideX = collideY = false;


	collideX = !(pointPos.getX() + width < oPos.getX() + 1
		|| oPos.getX() + oWidth < pointPos.getX());

	collideY = !(pointPos.getY() < oPos.getY()
		|| oPos.getY() + oHeight < pointPos.getY());

	return (collideX && collideY);
}

bool CollisionManager::checkCollisionTop(Physical * o1, Physical * o2)
{
	Vector2D o1Pos = o1->getPosition();
	double o1Width = o1->getWidth();
	double o1Height = o1->getHeight();
	Vector2D o2Pos = o2->getPosition();
	double o2Width = o2->getWidth();
	double o2Height = o2->getHeight();

	bool collideX, collideY;
	collideX = collideY = false;

	collideX = !(o1Pos.getX() + o1Width <= o2Pos.getX()
		|| o2Pos.getX() + o2Width <= o1Pos.getX());

	collideY = !(o1Pos.getY() + o1Height / 2 < o2Pos.getY() + o2Height || o2Pos.getY() > o1Pos.getY()
		|| o2Pos.getY() + o2Height < o1Pos.getY());

	return (collideX && collideY);
}

bool CollisionManager::checkCollisionBot(Physical * o1, Physical * o2)
{
	Vector2D o1Pos = o1->getPosition();
	double o1Width = o1->getWidth();
	double o1Height = o1->getHeight();
	Vector2D o2Pos = o2->getPosition();
	double o2Width = o2->getWidth();
	double o2Height = o2->getHeight();

	bool collideX, collideY;
	collideX = collideY = false;

	collideX = !(o1Pos.getX() + o1Width <= o2Pos.getX()
		|| o2Pos.getX() + o2Width <= o1Pos.getX());

	collideY = !(o1Pos.getY() + o1Height < o2Pos.getY() || o1Pos.getY() + o1Height > o2Pos.getY() + o2Height
		|| o2Pos.getY() < o1Pos.getY() + o1Height / 2);

	return (collideX && collideY);

}

bool CollisionManager::checkCollisionLeft(Physical * o1, Physical * o2)
{
	Vector2D o1Pos = o1->getPosition();
	double o1Width = o1->getWidth();
	double o1Height = o1->getHeight();
	Vector2D o2Pos = o2->getPosition();
	double o2Width = o2->getWidth();
	double o2Height = o2->getHeight();

	bool collideX, collideY;
	collideX = collideY = false;

	collideX = !(o1Pos.getX() + o1Width / 4 < o2Pos.getX() + o2Width || o2Pos.getX() > o1Pos.getX()
		|| o2Pos.getX() + o2Width < o1Pos.getX());

	collideY = !(o1Pos.getY() + o1Height <= o2Pos.getY()
		|| o2Pos.getY() + o2Height <= o1Pos.getY());

	return (collideX && collideY);
}

bool CollisionManager::checkCollisionRight(Physical * o1, Physical * o2)
{
	Vector2D o1Pos = o1->getPosition();
	double o1Width = o1->getWidth();
	double o1Height = o1->getHeight();
	Vector2D o2Pos = o2->getPosition();
	double o2Width = o2->getWidth();
	double o2Height = o2->getHeight();

	bool collideX, collideY;
	collideX = collideY = false;

	collideX = !(o1Pos.getX() + o1Width < o2Pos.getX() || o1Pos.getX() + o1Width > o2Pos.getX() + o2Width
		|| o2Pos.getX() < o1Pos.getX() - o1Width / 4);

	collideY = !(o1Pos.getY() + o1Height <= o2Pos.getY()
		|| o2Pos.getY() + o2Height <= o1Pos.getY());

	return (collideX && collideY);
}
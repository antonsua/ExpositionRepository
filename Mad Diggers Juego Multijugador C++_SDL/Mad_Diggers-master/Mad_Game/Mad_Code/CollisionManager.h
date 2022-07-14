#pragma once
#include "Physical.h"

class CollisionManager {
	public:
		CollisionManager();
		~CollisionManager();

	protected:
		bool virtual checkCollision(Vector2D pointPos, double width, Physical* o);
		bool virtual checkCollisionTop(Physical* o1, Physical* o2);
		bool virtual checkCollisionBot(Physical* o1, Physical* o2);
		bool virtual checkCollisionLeft(Physical* o1, Physical* o2);
		bool virtual checkCollisionRight(Physical* o1, Physical* o2);
		bool virtual checkCollision(Physical * o1, Physical * o2);
};
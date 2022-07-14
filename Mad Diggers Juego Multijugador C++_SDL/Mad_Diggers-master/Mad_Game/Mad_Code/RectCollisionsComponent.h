#pragma once

#include "Vector2D.h"
#include "EntityUpdateComponent.h"

typedef struct
{
	const Vector2D* pos;
	double width, heigth;
}Rect;


class RectCollisionsComponent : public EntityUpdateComponent
{
public:
	RectCollisionsComponent(vector<Rect>* gOVec);
	~RectCollisionsComponent() {};

protected:
	bool checkCollision(Physical* o1);
	bool checkCollisionTop(Physical* o1);
	bool checkCollisionBot(Physical* o1);
	bool checkCollisionLeft(Physical* o1);
	bool checkCollisionRight(Physical* o1);

private:
	std::vector<Rect>* gOVec_;
};
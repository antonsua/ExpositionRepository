#include "RectCollisionsComponent.h"

RectCollisionsComponent::RectCollisionsComponent(vector<Rect> *gOVec) : gOVec_(gOVec){
	// TODO Auto-generated constructor stub

}

//RectCollisionsComponent::~RectCollisionsComponent() {
//	// TODO Auto-generated destructor stub
//}

bool RectCollisionsComponent::checkCollision(Physical* o1) {

	Vector2D o1Pos = o1->getPosition();
	double o1Width = o1->getWidth();
	double o1Height = o1->getHeight();
	bool collideX, collideY;

	for (Rect a : *gOVec_) {
		Vector2D o2Pos = *a.pos;
		collideX = collideY = false;


			collideX = !(o1Pos.getX() + o1Width < o2Pos.getX()
				|| o2Pos.getX() + a.width < o1Pos.getX());

			collideY = !(o1Pos.getY() + o1Height < o2Pos.getY()
				|| o2Pos.getY() + a.heigth < o1Pos.getY());

		if (collideX && collideY)
			return true;
	}

	return false;
}

bool RectCollisionsComponent::checkCollisionTop (Physical* o1){

	Vector2D o1Pos = o1->getPosition();
	double o1Width = o1->getWidth();
	double o1Height = o1->getHeight();
	bool collideX, collideY;

	for (Rect a : *gOVec_) {
		Vector2D o2Pos = *a.pos;
		collideX = collideY = false;


		collideX = !(o1Pos.getX() + (9/10) * o1Width < o2Pos.getX()
			|| o2Pos.getX() + a.width < o1Pos.getX() + o1Width/10);

		collideY = !(o1Pos.getY() + o1Height/2 < o2Pos.getY()
			|| o2Pos.getY() + a.heigth < o1Pos.getY());

		if (collideX && collideY)
			return true;
	}

	return false;

}

bool RectCollisionsComponent::checkCollisionBot(Physical* o1) {

	Vector2D o1Pos = o1->getPosition();
	double o1Width = o1->getWidth();
	double o1Height = o1->getHeight();
	bool collideX, collideY;

	for (Rect a : *gOVec_) {
		Vector2D o2Pos = *a.pos;
		collideX = collideY = false;


		collideX = !(o1Pos.getX() + (9 / 10) * o1Width < o2Pos.getX()
			|| o2Pos.getX() + a.width < o1Pos.getX() + o1Width / 10);


		collideY = !(o1Pos.getY() + o1Height < o2Pos.getY()
			|| o2Pos.getY() + a.heigth < o1Pos.getY() + o1Height/2);

		if (collideX && collideY)
			return true;
	}

	return false;
}

bool RectCollisionsComponent::checkCollisionLeft(Physical* o1) {

	Vector2D o1Pos = o1->getPosition();
	double o1Width = o1->getWidth();
	double o1Height = o1->getHeight();
	bool collideX, collideY;

	for (Rect a : *gOVec_) {
		Vector2D o2Pos = *a.pos;
		collideX = collideY = false;


		collideX = !(o1Pos.getX() + o1Width/2 < o2Pos.getX()
				|| o2Pos.getX() + a.width < o1Pos.getX());


		collideY = !(o1Pos.getY() + (9/10) * o1Height < o2Pos.getY()
			|| o2Pos.getY() + a.heigth < o1Pos.getY() + o1Height /10);

		if (collideX && collideY)
			return true;
	}

	return false;
}

bool RectCollisionsComponent::checkCollisionRight(Physical* o1) {

	Vector2D o1Pos = o1->getPosition();
	double o1Width = o1->getWidth();
	double o1Height = o1->getHeight();
	bool collideX, collideY;

	for (Rect a : *gOVec_) {
		Vector2D o2Pos = *a.pos;
		collideX = collideY = false;


		collideX = !(o1Pos.getX() + o1Width < o2Pos.getX()
			|| o2Pos.getX() + a.width < o1Pos.getX() + o1Width / 2);

		collideY = !(o1Pos.getY() + (9 / 10) * o1Height < o2Pos.getY()
			|| o2Pos.getY() + a.heigth < o1Pos.getY() + o1Height / 10);

		if (collideX && collideY)
			return true;
	}

	return false;
}

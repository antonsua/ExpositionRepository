#include "BasicMotionPhysics.h"

BasicMotionPhysics::BasicMotionPhysics() {

}

BasicMotionPhysics::~BasicMotionPhysics() {
}

void BasicMotionPhysics::update(Entity* o, Uint32 time) {
	//moveToSomePoint( Vector2D(650,370),o);
	o->setPosition(o->getPosition() + o->getVelocity());
}
//
//void BasicMotionPhysics::moveToSomePoint(Vector2D v,GameObject* o) {//For some given point
//																	//Moves the G.O to that point
//	Vector2D v2 = v - o->getPosition();								//Maybe needed to change this method emplacement
//	v2.normalize();
//	o->setVelocity(v2);
//	cout << v2 << endl;
//}
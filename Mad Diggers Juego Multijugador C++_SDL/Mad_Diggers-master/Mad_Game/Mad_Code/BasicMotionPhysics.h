#ifndef BASICMOTIONPHYSICS_H_
#define BASICMOTIONPHYSICS_H_

#include "EntityUpdateComponent.h"

class BasicMotionPhysics: public EntityUpdateComponent
{
public:
	BasicMotionPhysics();
	virtual ~BasicMotionPhysics();

	virtual void update(Entity* o, Uint32 time);
};

#endif /* BASICMOTIONPHYSICS_H_ */

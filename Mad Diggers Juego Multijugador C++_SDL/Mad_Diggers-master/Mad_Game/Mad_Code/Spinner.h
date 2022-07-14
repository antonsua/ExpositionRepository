//Mad_Diggers
#pragma once

#include "Entity.h"
#include "Emitter.h"

class Spinner : public Entity, public Emitter
{
public:
	Spinner(Game* game);
	~Spinner();

	virtual void endMovement(bool timeOut);
	virtual void endResizing();
};

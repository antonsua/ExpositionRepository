#pragma once

#include "Entity.h"
#include "jsonReader.h"



class ballPong : public Entity, public jsonReader
{
public:
	ballPong(Game* game, Vector2D offset);
	virtual ~ballPong();
	virtual void update(Uint32 time);
private:
	const double _BALL_SIZE_;
};


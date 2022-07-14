#pragma once
#include "GameObject.h"
#include "Emitter.h"
#include "Listener.h"
#include "ballPong.h"
#include "BlockPong.h"
#include "Paddle.h"
#include "BallPhysicsComponent.h"

class PongManager :
	public GameObject, public Emitter, public Listener
{
public:

	PongManager(Game* game, vector<BlockPong*>* blocks, vector<Paddle*> paddles, ballPong* ball, Vector2D offset);
	~PongManager();
	void virtual update(Uint32 time);
	void virtual render(Uint32 time);
	void virtual handleEvents(Uint32 time, const SDL_Event& event);
	void virtual receive(Message* msg);
private:
	bool checkCollision(Physical* o1, Physical* o2);
	void checkBallLimits();
	vector<BlockPong*>* blocks_;
	vector<Paddle*> paddles_;
	ballPong* ball_;
	BallPhysicsComponent* ballPhysics;
};


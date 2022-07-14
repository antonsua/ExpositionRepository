//Mad_Diggers

#pragma once
//#include "SDLError.h"

#include <list>
#include "GameObject.h"

#include "Emitter.h"
#include "jsonReader.h"

class GameState : public Emitter, public virtual jsonReader
{
public:
	GameState(Game* game);
	GameState(Game* game, string stateID);
	virtual ~GameState();

	virtual void handleEvents(Uint32 time, const SDL_Event event);
	virtual void update(Uint32 time);
	virtual void render(Uint32 time);

	string getStateID() { return stateID_; };
	void sendToGSM(Message* msg);

protected:
	virtual void initState() = 0;
	virtual void closeState() = 0;

	void killDeadObjects ();

	Game* game_;
	list<GameObject*> gameObjects_;

	string stateID_;
};
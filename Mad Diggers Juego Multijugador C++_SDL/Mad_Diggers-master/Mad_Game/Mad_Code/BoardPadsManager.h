#pragma once
#include "Entity.h"
#include "Emitter.h"
#include "GamePadComponent.h"

class BoardPadsManager :
	public Entity, public Emitter, public Listener
{
public:
	BoardPadsManager(Game* game, int numPlayers);
	virtual ~BoardPadsManager();
	virtual void handleEvents(Uint32 time, const SDL_Event& event);
	virtual void receive(Message* msg);
protected:
	vector<GamePadComponent> gamePads_;
	int numPlayers_;
	int playerNum_;
};


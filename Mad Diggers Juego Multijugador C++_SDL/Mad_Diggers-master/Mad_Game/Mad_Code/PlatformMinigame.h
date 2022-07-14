#pragma once
#include "MiniGameState.h"
#include "EntityComponent.h"

#include "PlatformManager.h"

class PlatformMinigame :
	public MiniGameState
{
public:
	PlatformMinigame(Game* game, stack<int> *p_playersTurnsOrder, int numPlayers);
	virtual ~PlatformMinigame();
	virtual void update(Uint32 time);
	virtual void handleEvents(Uint32 time, SDL_Event event);
	virtual void render(Uint32 time);

private:
	static const string idName_;
	bool starting = true;

protected:
	//from GameState
	virtual void initState();
	virtual void closeState();
	virtual void endMiniGame();

	PlatformManager platformManager;
	
};


#pragma once
#include "MiniGameState.h"
#include "EntityComponent.h"

#include "PlatformManager.h"
#include "ImageRenderer.h"
#include "SpriteSheetRenderer.h"
#include "SkeletonRenderer.h"

class RaceMinigame :
	public MiniGameState
{
public:
	RaceMinigame(Game* game, stack<int> *p_playersTurnsOrder, int numPlayers);
	virtual ~RaceMinigame();
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


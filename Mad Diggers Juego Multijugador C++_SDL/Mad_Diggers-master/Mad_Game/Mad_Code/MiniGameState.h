#pragma once
#include "gamestate.h"

#include <queue>

class MiniGameState : public GameState
{
public:

	MiniGameState(Game* game, stack<int> *p_playersTurnsOrder, string nameId,int numPlayers);
	virtual ~MiniGameState();

	virtual void handleEvents(Uint32 time, const SDL_Event event);
	virtual void update(Uint32 time);
	virtual void render(Uint32 time);

protected:
	//not instanciable because no initState, closeState
	virtual void initMinigame();
	virtual void closeMinigame();

	virtual void endMiniGame();

	///////////////////////////////////////////////////////////////////

	stack<int> *p_playersTurnsOrder_; //pointer to the queue
	int numOfPlayers_;
};
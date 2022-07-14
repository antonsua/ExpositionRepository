#include "PlatformMinigame.h"

const string PlatformMinigame::idName_ = "PlatformMinigame";

PlatformMinigame::PlatformMinigame(Game* game, stack<int> *p_playersTurnsOrder, int numPlayers) :
	MiniGameState(game, p_playersTurnsOrder, idName_, numPlayers), platformManager(game, p_playersTurnsOrder,1)
{
	initState();
}

PlatformMinigame::~PlatformMinigame()
{
	closeState();
}

void PlatformMinigame::update(Uint32 time)
{
	if (starting) {
		starting = false;
		sendToGSM(&Message(STATE_PLAT_CHALLENGE));
	}
	MiniGameState::update(time);
	if (platformManager.checkEnd())
		endMiniGame();
}

void PlatformMinigame::initState()
{
	gameObjects_.push_back(&platformManager);
}

void PlatformMinigame::closeState()
{
	
}

///////////////////////////////////////////////////////////////////////////////

//propagates the event and then if no one handles it, tries ti handle
void PlatformMinigame::handleEvents(Uint32 time, SDL_Event event)
{
	bool handled = false;

	if (event.type == SDL_KEYDOWN) {
		switch (event.key.keysym.sym) {

		case SDLK_SPACE: //close minigame
			handled = true;
			endMiniGame(); //atm comes from minigameState
			break;
		}
	}

	//prior propagation
	if (!handled) MiniGameState::handleEvents(time, event);
}

void PlatformMinigame::render(Uint32 time)
{
	if(!starting)
	GameState::render(time);
}

///////////////////////////////////////////////////////////////////////////////

void PlatformMinigame::endMiniGame()
{
	if (MiniGameState::p_playersTurnsOrder_->size() == 4)
		sendToGSM(&StateMessage_Minigame(STATE_PODIUM, p_playersTurnsOrder_));
	else
		MiniGameState::endMiniGame(); //default rnd behabior
}

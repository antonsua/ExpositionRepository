#include "RaceMinigame.h"

const string RaceMinigame::idName_ = "RaceMinigame";

RaceMinigame::RaceMinigame(Game* game, stack<int> *p_playersTurnsOrder, int numPlayers) :
	MiniGameState(game, p_playersTurnsOrder, idName_, numPlayers), platformManager(game, p_playersTurnsOrder, 0)
{
	initState();
}

RaceMinigame::~RaceMinigame()
{
	closeState();
}

void RaceMinigame::update(Uint32 time)
{
	if (starting) {
		starting = false;
		sendToGSM(&Message(STATE_CONTROLS_PLATFORM));
	}
	MiniGameState::update(time);
	if (platformManager.checkEnd())
		endMiniGame();
}

void RaceMinigame::initState()
{
	gameObjects_.push_back(&platformManager);
}

void RaceMinigame::closeState()
{

}

///////////////////////////////////////////////////////////////////////////////

//propagates the event and then if no one handles it, tries ti handle
void RaceMinigame::handleEvents(Uint32 time, SDL_Event event)
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

void RaceMinigame::render(Uint32 time)
{
	if (!starting) GameState::render(time);
}

///////////////////////////////////////////////////////////////////////////////

void RaceMinigame::endMiniGame()
{
	if (MiniGameState::p_playersTurnsOrder_->size() == 4)
		sendToGSM(&StateMessage_Minigame(STATE_PODIUM, p_playersTurnsOrder_));
	else
		MiniGameState::endMiniGame(); //default rnd behabior
}

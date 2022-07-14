#include "DodgeMinigame.h"

const string DodgeMinigame::idName_ = "DodgeMinigame";

DodgeMinigame::DodgeMinigame(Game* game, stack<int> *p_playersTurnsOrder, int numPlayers) :
	MiniGameState(game, p_playersTurnsOrder, idName_, numPlayers), dodgeManager(game, p_playersTurnsOrder)
{
	initState();
}

DodgeMinigame::~DodgeMinigame()
{
	closeState();
}

void DodgeMinigame::update(Uint32 time)
{
	if (starting) {
		starting = false;
		sendToGSM(&Message(STATE_BULLET_CONTROLS));
	}

	MiniGameState::update(time);
	if (dodgeManager.checkEnd())
		endMiniGame();
}

void DodgeMinigame::initState()
{
	gameObjects_.push_back(&dodgeManager);
}

void DodgeMinigame::closeState()
{

}

///////////////////////////////////////////////////////////////////////////////

//propagates the event and then if no one handles it, tries ti handle
void DodgeMinigame::handleEvents(Uint32 time, SDL_Event event)
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

void DodgeMinigame::render(Uint32 time)
{
	if (!starting)
		GameState::render(time);
}

///////////////////////////////////////////////////////////////////////////////

void DodgeMinigame::endMiniGame()
{
	if (MiniGameState::p_playersTurnsOrder_->size() == 4)
		sendToGSM(&StateMessage_Minigame(STATE_PODIUM, p_playersTurnsOrder_));
	else
		MiniGameState::endMiniGame(); //default rnd behabior
}

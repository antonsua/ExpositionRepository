#include "MiniGameState.h"

MiniGameState::MiniGameState(Game* game, stack<int> *p_playersTurnsOrder, string nameId,int numPlayers)
	: GameState(game, nameId), p_playersTurnsOrder_(p_playersTurnsOrder)
{
	numOfPlayers_ = numPlayers;
}

MiniGameState::~MiniGameState()
{
}

void MiniGameState::initMinigame()
{
	// Initialize common minigames things
}

void MiniGameState::closeMinigame()
{
	// destroy common minigames things
}


//propagates the event and then if no one handles it, tries ti handle
void MiniGameState::handleEvents(Uint32 time, const SDL_Event event)
{
	//Controll some common minigaeme inputs

	bool handled = false;

	//if (event.type == SDL_KEYDOWN) {
	//	switch (event.key.keysym.sym) {

	//	case SDLK_SPACE: //close minigame
	//		handled = true;
	//		endMiniGame();
	//		break;
	//	}
	//}

	//prior propagation
	  if (!handled) GameState::handleEvents(time, event);
}

//controls logic and calls all gameobjects' update
void MiniGameState::update(Uint32 time)
{
	//control common? if everything is specific then we can just remove this

	GameState::update(time);
}

void MiniGameState::render(Uint32 time)
{
	//any common hud? etc

	GameState::render(time);
}

///////////////////////////////////////////////////////////////////

//should be specific for each minigame, but now allows testing rnd
void MiniGameState::endMiniGame() {

	//pushes the players ordered randomly into the queue

	vector<int> playerNumbers = { 0, 1, 2, 3 };
	int numPlayers = playerNumbers.size();

	cout << "Minigame RND reversed finish positions: ";

	for (size_t i = 0; i < numPlayers; i++)
	{
		int rndPos = game_->getRnd(playerNumbers.size()-1);
		p_playersTurnsOrder_->push(playerNumbers[rndPos]);
		cout << playerNumbers[rndPos];
		playerNumbers.erase(playerNumbers.begin() + rndPos);
	}

	cout << endl;
	sendToGSM(&Message(STATE_POP_MINIGAME));
}
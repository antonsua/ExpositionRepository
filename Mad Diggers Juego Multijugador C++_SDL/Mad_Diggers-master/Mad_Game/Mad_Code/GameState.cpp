#include "GameState.h"

///////////////////////////////////////////////////////////////////

GameState::GameState(Game * game, string stateID) :
	game_(game), stateID_(stateID)
{
}

GameState::GameState(Game * game) : GameState(game, "undefinedID") {}

GameState::~GameState()
{
}

///////////////////////////////////////////////////////////////////////////////

#include "GameStateMachine.h" //avoid fowarded rewriting
//so states do not need this include and is cleaner

void GameState::sendToGSM(Message * msg)
{
	send(msg, game_->getGSM());
}

///////////////////////////////////////////////////////////////////////////////

//sends the event too all the entities
//no controlled propagation, cause it had limitations
void GameState::handleEvents(Uint32 time, const SDL_Event event)
{
	for (GameObject* o : gameObjects_) {
		if (o->isActive())o->handleEvents(time, event);
	}
}

//iterates all the gameObjects and calls their updates
void GameState::update(Uint32 time)
{
	for (GameObject* o : gameObjects_) {
		if (o->isActive())o->update(time);
	}
	killDeadObjects();
}

//requires sencond iteration to delete killed objects
void GameState::killDeadObjects()
{
	auto it = gameObjects_.begin();
	while (it != gameObjects_.end())
	{
		if ((*it)->isKilled())
		{
			delete (*it);
			if (it == gameObjects_.begin()) //in case of fisrt one, we fckd up
			{
				gameObjects_.erase(it);
				it = gameObjects_.begin(); //we fix
			}
			else gameObjects_.erase(it);
		}
		else ++it;
	}
}

//normal render, we may create other to decide better what renders first/last?
void GameState::render(Uint32 time)
{
	for (GameObject* o : gameObjects_) {
		if (o->isActive())o->render(time);
	}
}
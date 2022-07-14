//#include "PauseState.h"
//#include "Game.h"
//
//PauseState::PauseState(Game* game)
//: GameState(game)
//{
//	this->stateID = nameID;
//
//	vector <Texture*> tex = game->getTextures();
//	//directly creates all buttons and sprites
//	GameState::createHudElements(tex, sprites_data, buttons_data, numbers_data, numbers_pointers);
//}
//
//PauseState::~PauseState()
//{
//
//}
//
//void PauseState::update()
//{
//	GameState::update();
//}
//
//void PauseState::render()
//{
//	GameState::render();
//}
//
//bool PauseState::handleEvent(SDL_Event event)
//{
//	//filters the events to just buttons
//	if (event.type == SDL_MOUSEBUTTONUP || event.type == SDL_MOUSEBUTTONDOWN)
//		return GameState::handleEvent(event);
//
//	else return false;
//}

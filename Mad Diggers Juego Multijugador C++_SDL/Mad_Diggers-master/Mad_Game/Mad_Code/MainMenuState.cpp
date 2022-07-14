//#include "MainMenuState.h"
//#include "Game.h"
//
//MainMenuState::MainMenuState(Game* game)
//: GameState(game)
//{
//	this->stateID = nameID;
//
//	vector <Texture*> tex = game->getTextures();
//	GameState::createHudElements(tex, sprites_data, buttons_data, numbers_data, numbers_pointers); //directly
//}
//
//MainMenuState::~MainMenuState()
//{
//	//nothing special?
//}
//
//void MainMenuState::update()
//{
//	GameState::update();
//}
//
//void MainMenuState::render()
//{
//	GameState::render();
//}
//
//bool MainMenuState::handleEvent(SDL_Event event)
//{
//	//filters events for the buttons
//	if (event.type == SDL_MOUSEBUTTONUP || event.type == SDL_MOUSEBUTTONDOWN)
//		return GameState::handleEvent(event);
//
//	else return false;
//}

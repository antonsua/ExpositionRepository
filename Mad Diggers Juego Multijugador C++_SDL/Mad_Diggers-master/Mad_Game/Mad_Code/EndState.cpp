//#include "EndState.h"
//#include "Game.h"
//
//EndState::EndState(Game* game, bool win)
//: GameState(game)
//{
//	this->stateID = nameID;
//	points = game->getPoints(); //to draw the final points
//
//	vector <Texture*> tex = game->getTextures();
//
//	//the background changes if the player wins or not
//	if (win) GameState::createHudElements(tex, sprites_data_win, buttons_data, numbers_data, numbers_pointers);
//	else GameState::createHudElements(tex, sprites_data_lose, buttons_data, numbers_data, numbers_pointers);
//}
//
//EndState::~EndState()
//{
//
//}
//
//void EndState::update()
//{
//	GameState::update();
//}
//
//void EndState::render()
//{
//	GameState::render();
//}
//
//bool EndState::handleEvent(SDL_Event event)
//{
//	if (event.type == SDL_MOUSEBUTTONUP || event.type == SDL_MOUSEBUTTONDOWN)
//		return GameState::handleEvent(event);
//
//	else return false;
//}

////Diego Mateos Arlanzón
////Jorge García García
//
//#pragma once
//#include "GameState.h"
//
//
//class MainMenuState : public GameState
//{
//
//private:
//
//	const string nameID = "menu";
//
//	//size, positions, and TexNames of the buttons and sprites
//	vector<Hud_Data> sprites_data = {
//		{ 4, 5, 0, 0, main_Menu_Full },
//	};
//
//	vector<Hud_Data> buttons_data = {
//		{ 1, 1, 0.25, 3, mM_Play },
//		{ 1, 1, 1.75, 3, mM_Load },
//		{ 0.5, 0.5, 4.25, 3.5, mM_Exit },
//	};
//
//	vector<Hud_Data> numbers_data = { };
//	vector<uint*> numbers_pointers = { };
//
//public:
//
//	MainMenuState(Game* game);
//	virtual ~MainMenuState();
//
//	virtual void update();
//	virtual void render();
//
//	virtual bool handleEvent(SDL_Event event);
//
//	virtual string getStateID() { return GameState::getStateID(); };
//};
//

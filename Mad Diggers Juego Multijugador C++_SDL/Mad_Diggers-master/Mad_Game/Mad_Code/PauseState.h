////Diego Mateos Arlanzón
////Jorge García García
//
//#pragma once
//#include "GameState.h"
//
//
//class PauseState : public GameState
//{
//
//private:
//
//	const string nameID = "menu"; //not used at the end
//
//	//size, positions, and TexNames of the buttons and sprites
//	vector<Hud_Data> sprites_data = {
//		{ 4, 5, 0, 0, main_Menu_Full },
//	};
//
//	vector<Hud_Data> buttons_data = {
//		{ 1.4, 1, 0.15, 3.1, m_Continue },
//		{ 0.75, 0.75, 2.10, 3.2, m_Save },
//		{ 0.5, 0.5, 4.25, 3.5, m_Menu },
//	};
//
//	vector<Hud_Data> numbers_data = {};
//	vector<uint*> numbers_pointers = {};
//
//public:
//
//	PauseState(Game* game);
//	virtual ~PauseState();
//
//	virtual void update();
//	virtual void render();
//
//	virtual bool handleEvent(SDL_Event event);
//
//	virtual string getStateID() { return GameState::getStateID(); };
//};
//

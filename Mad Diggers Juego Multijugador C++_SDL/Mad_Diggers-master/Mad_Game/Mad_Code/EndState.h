////Diego Mateos Arlanzón
////Jorge García García
//
//#pragma once
//#include "GameState.h"
//
//
//class EndState : public GameState
//{
//
//private:
//
//	const string nameID = "end";
//	uint points;
//
//	//size, positions, and TexNames of the buttons and sprites
//	vector<Hud_Data> sprites_data_win = {
//		{ 4, 5, 0, 0, winner },
//		{ 1, 0.66, 1, 2.9, text_Your_Points },
//	};
//	vector<Hud_Data> sprites_data_lose = {
//		{ 4, 5, 0, 0, loser },
//		{ 1, 0.66, 1, 2.9, text_Your_Points },
//	};
//	vector<Hud_Data> buttons_data = {
//		{ 0.5, 0.5, 4.25, 3, m_Menu },
//		{ 0.5, 0.5, 4.25, 3.5, mM_Exit },
//	};
//
//	vector<Hud_Data> numbers_data = {
//		{ 0.16, 0.66, 2.2, 2.9, Numbers },
//	};
//
//	vector<uint*> numbers_pointers = {&points };
//
//public:
//
//	EndState(Game* game, bool win);
//	virtual ~EndState();
//
//	virtual void update();
//	virtual void render();
//
//	virtual bool handleEvent(SDL_Event event);
//
//	virtual string getStateID() { return GameState::getStateID(); };
//};
//

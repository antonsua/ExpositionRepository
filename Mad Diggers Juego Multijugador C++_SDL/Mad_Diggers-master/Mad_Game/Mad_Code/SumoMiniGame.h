#pragma once

#include "MiniGameState.h"
#include "Entity.h"
#include <stack>
#include "Listener.h"
#include "jsonReader.h"
#include "ControlsState.h"

#include "SumoManager.h"

class SumoMinigame : public MiniGameState, public Listener
{
public:
	SumoMinigame(Game* game, stack<int> *p_playersTurnsOrder, int numPlayers);
	virtual ~SumoMinigame();

	virtual void handleEvents(Uint32 time, const SDL_Event event);
	virtual void update(Uint32 time);
	virtual void render(Uint32 time);

	void receive(Message* msg);
	bool isPlacingCircles() const { return placedCircles_ < sumos_.size(); };

private:
	static const string idName_;

protected:
	//from GameState
	virtual void initState();
	virtual void closeState();

	virtual void endMiniGame();

private:
	 Vector2D p1Position_;
	 Vector2D p2Position_;
	 Vector2D p3Position_;
	 Vector2D p4Position_;

	stack<int> eliminationOrder_;
	std::list<SumoPlayer*> sumos_;
	std::vector<Vector2D> initialPositions_;

	AnimationRenderer renderAnim_;

	SumoManager* sumoManager_;
	ControlsState* controlState_;
	Entity countEntity_;

	bool starting_ = true;
	bool ready = false;
	size_t placedCircles_ = 0;

	Vector2D getInitialPos();
	void placeCircles();
	void moveCirclesToInitial();

	spriteSheetData animData_ = {
		Vector2D(1.0, 1.0), //go to spriteSheetData definition to see value names etc
		Vector2D(0.0, 0.0),
		false,

		0, 0, //0,0 is auto min / max
		0, 0,

		10,
		false,
		false,
	};
};



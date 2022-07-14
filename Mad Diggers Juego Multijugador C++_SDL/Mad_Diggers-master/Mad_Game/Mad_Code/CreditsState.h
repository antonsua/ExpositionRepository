#pragma once
#include"GameState.h"

#include "ImageRenderer.h"
#include "GamePadComponent.h"


class CreditsState : public GameState, public Listener
{
public:
	CreditsState(Game* game);
	~CreditsState();
	virtual void handleEvents(Uint32 time, const SDL_Event event);
	virtual void update(Uint32 time);

	virtual void receive(Message* msg);

private:
	const int creditsOffset = 50;
	const int creditsWidth = 687;
	const int creditsHeight = 3025;
	const int xOffset = 60;
	const int creditsEnd = -3100;

	double moveVelocity = 2;

	void initState();
	void closeState();

	ImageRenderer background_;
	ImageRenderer moveImg_;
	Entity backObject_;
	Entity peopleObject_;

	int objectY;

	///////////////////////////////////////////////////////////////////////////

	ImageRenderer instRC_;
	GamePadComponent padIC_;

	Entity* padEntity_;

	const int fadeIntTime_ = 1000;
	const Vector2D INST_OFFSET = { 200, 65 };
};


#pragma once
#include"GameState.h"
#include "ImageRenderer.h"
#include "GamePadComponent.h"


class MenuState :public GameState, public Listener
{
public:
	MenuState(Game* game);
	~MenuState();
	virtual void handleEvents(Uint32 time, const SDL_Event event);
	virtual void receive(Message* msg);


private:
	void moveSelector();
	void activateButton();
	void initState();
	void closeState();
	Entity* addEntity(const int height, const int width, const Vector2D pos, const Resources::ImageId image, bool fade = true);

	void launchBoard();

	///////////////////////////////////////////////////////////////////////////

	const int fadeIntTime_ = 1000;
	const int fadeBoardTime_ = 2000;

	const int NUM_BUTTONS = 2;
	const int distanceBTWButtons = 90;
	const int buttonXDistance = 440;
	const int firstButtonY = 250;
	const int buttonHeight = 68;

	const Vector2D INST_OFFSET = { 381, 65 };
	const Vector2D selectorIniPos = { 249, 250 };

	///////////////////////////////////////////////////////////////////////////

	int currentButton = 0;

	ImageRenderer instRC_;
	vector<ImageRenderer*> images_;
	GamePadComponent padIC_;

	Entity* selectorObject_;
	Entity* padEntity_;
};


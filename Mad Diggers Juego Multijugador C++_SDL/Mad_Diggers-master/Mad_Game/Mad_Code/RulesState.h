#pragma once
#include "GameState.h"
#include "ImageRenderer.h"
#include "GamePadComponent.h"
#include "Listener.h"

const Vector2D MENU_BUTTON_SIZE(199, 57);
const Vector2D BACKTO_MENU(173, 51);



class RulesState : public GameState, public Listener
{

public:
	RulesState(Game* game);
	~RulesState();
	void receive(Message* msg);
private:
	void initState();
	void closeState();

	ImageRenderer rules1RC_;
	ImageRenderer rules2RC_;
	ImageRenderer nextRC_;
	ImageRenderer backMenuRC_;

	Entity back1_;
	Entity back2_;
	Entity button_;

	GamePadComponent gpad_;

	bool changed = false;
};


#pragma once
#include "EntityInputComponent.h"
#include "Listener.h"
#include "GoodTimer.h"

class PlatformGameComponent :public EntityInputComponent, public Listener
{
public:
	PlatformGameComponent(SDL_Keycode left, SDL_Keycode right, SDL_Keycode up, SDL_Keycode down, double speed,
		double maxVelocity, double jumpVelocity, int id);
	PlatformGameComponent();
	~PlatformGameComponent();
	void setIniPosition(Vector2D pos);
	void update(Entity* o, Uint32 time);
	void handleEvents(Entity* o, Uint32 time, const SDL_Event& event);

protected:
	GoodTimer timer;
	int id_;
	SDL_Keycode left_;
	SDL_Keycode right_;
	SDL_Keycode up_;
	SDL_Keycode down_;
	double maxVelocity_;
	double speed_;
	double jumpVelocity_;
	bool canJump_ = false;
	bool air_ = false;
	bool goIni = false;
	bool keysHeld[4] = { false };
	void receive(Message* msg);
	Vector2D  iniPosition_;
	bool gamepadActive = false;
};


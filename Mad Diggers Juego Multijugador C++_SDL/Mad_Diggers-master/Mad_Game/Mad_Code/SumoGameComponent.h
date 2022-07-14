#pragma once
#include "EntityInputComponent.h"
#include "GamePadComponent.h"
#include "Listener.h"


class SumoGameComponent: public EntityInputComponent, public Listener
{
public:
	SumoGameComponent(SDL_Keycode left, SDL_Keycode right, SDL_Keycode up, SDL_Keycode down, double thurst,
		double maxVelocity);
	SumoGameComponent();
	~SumoGameComponent();
	void virtual handleEvents(Entity* o, Uint32 time, const SDL_Event& event);
	void virtual update(Entity* o, Uint32 time);
private:
	
	SDL_Keycode left_;
	SDL_Keycode right_;
	SDL_Keycode up_;
	SDL_Keycode down_;
	double maxVelocity_;
	double thurst_;
	bool keysHeld[4] = { false };
	void receive(Message* msg);
	Vector2D auxDir_;
	bool gamepadActive = false;
};

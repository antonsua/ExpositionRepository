#pragma once
#include "EntityInputComponent.h"
#include "Listener.h"
#include "GoodTimer.h"

struct Message_PlayerCollision : Message {
	Message_PlayerCollision(int player) :
		Message(PLATFORM_COLLISION), player_(player) {
	}
	int player_;
};

struct Message_DeadlyCollision : Message {
	Message_DeadlyCollision(int player) :
		Message(TRAP_COLLISION), player_(player) {
	}
	int player_;
};



class DodgeComponent :public EntityInputComponent, public Listener
{
public:
	DodgeComponent(SDL_Keycode left, SDL_Keycode right, SDL_Keycode up, SDL_Keycode down, double speed,
		double maxVelocity, int id);
	DodgeComponent();
	~DodgeComponent();
	void update(Entity* o, Uint32 time);
	void handleEvents(Entity* o, Uint32 time, const SDL_Event& event);

protected:
	int id_;
	SDL_Keycode left_;
	SDL_Keycode right_;
	SDL_Keycode up_;
	SDL_Keycode down_;
	double maxVelocity_;
	double speed_;

	bool keysHeld[4] = { false };
	void receive(Message* msg);
	bool gamepadActive = false;
};


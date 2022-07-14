#pragma once
#include "EntityInputComponent.h"
#include "AppleTree.h"
#include "Emitter.h"
#include "ShapeRenderer.h"


const int PLAYER_VEL = 5;

class ApplePlayer;
class ApplePlayerController : public EntityInputComponent,public Emitter,public Listener
{
public:
	ApplePlayerController(SDL_Keycode left, SDL_Keycode right, SDL_Keycode shake, SDL_Keycode exploit,
		ApplePlayer* player, AppleTree* tree);
	~ApplePlayerController();
	ApplePlayerController() {};

	void handleEvents(Entity* o, Uint32 time, const SDL_Event& event);
	void receive(Message* msg);
private:
	SDL_Keycode left_;
	SDL_Keycode right_;
	SDL_Keycode shake_;
	SDL_Keycode exploit_;

	AppleTree* tree_;

	ShapeRenderer* playerSRC_;

	bool keysHeld[2] = { false };

	bool gamePadActive = false;

	float padVelocity;

	
};


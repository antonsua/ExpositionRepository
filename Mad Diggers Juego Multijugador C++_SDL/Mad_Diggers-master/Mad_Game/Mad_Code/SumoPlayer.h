#pragma once
#include "Entity.h"
#include "SumoManager.h"
#include "jsonReader.h"
#include "GamePadComponent.h"
#include "SumoGameComponent.h"

#include "Emitter.h"

class SumoMinigame;

class SumoPlayer : public Entity, public jsonReader, public Emitter
{
public:
	SumoPlayer(Game * game, Json::Value keys, Resources::ImageId ballColor, SumoMinigame* sumoGame,int gamepadNum);
	~SumoPlayer();
	void setCircleCoordinates(int x, int y);
	void update(Uint32 time);
	GamePadComponent* getGamepad() { return &gamePad_; };

protected:
	virtual void endMovement(bool timeOut);

private:
	SDL_Keycode left_;
	SDL_Keycode up_;
	SDL_Keycode right_;
	SDL_Keycode down_;

	SumoGameComponent sumoGameComp_;
	GamePadComponent gamePad_;
	SumoMinigame* sumoGame_;
};


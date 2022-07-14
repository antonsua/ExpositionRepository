#pragma once
#include "jsonReader.h"
#include "Spinner.h"
#include "Emitter.h"

#include "ImageRenderer.h"

class SpinnerManager :public Emitter, public Listener, public GameObject
{
public:
	SpinnerManager(Game* game, jsonReader* jr);
	~SpinnerManager();

	void handleEvents(Uint32 time, const SDL_Event & event);
	void update(Uint32 time);
	void render(Uint32 time);

	void receive(Message* msg);

private:
	void initSpinner();
	void initBackGround();
	void initForeGround();

	void spinOnce();
	void spinLast();
	void pickMinigame();

	///////////////////////////////////////////////////////////////////////////

	static vector<MessageId> minigameIds;
	static vector<Resources::ImageId> minigameImagesIds;

	Message* idCarrier;

	///////////////////////////////////////////////////////////////////////////
	///constants

	const double baseTime, speedReductionFactor;
	const int repetitionsMin, repetitionsMax;

	const double spinY, spinH, spinW, bgWtimesSpin, bgHtimesSpin;

	///////////////////////////////////////////////////////////////////////////

	double bgW, bgH;
	Vector2D bgPos_, startPos, endPos;
	int reps, lastRep; //counter

	vector<GameObject*> objects_;

	Spinner* spinner_;
	ImageRenderer interrogation_RC;
	ImageRenderer minigame_RC;
	spriteData imageData_ = { Vector2D(1, 1), Vector2D(0, 0), false, false };

	Entity* backGround_;
	ImageRenderer bgImage_;
	Entity* foreGround_;
	ImageRenderer fgImage_;
};

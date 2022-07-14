#pragma once
#include "Entity.h"
#include "jsonReader.h"
#include "Listener.h"

#include "ImageRenderer.h"


class BackgroundObject : public Entity,public jsonReader,public Listener
{
public:
	BackgroundObject(Game* game_,Resources::ImageId backgroundImage);
	~BackgroundObject();
	void update(Uint32 time);
	void receive(Message* msg);

private:
	ImageRenderer renderer_;
	spriteData renderData_;

	double REDUCTION_FACTOR;
	double MINIMUM_SIZE;
	bool startReduction_ = false;
};


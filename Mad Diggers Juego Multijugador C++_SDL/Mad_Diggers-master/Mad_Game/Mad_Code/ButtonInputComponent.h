#include "EntityComponent.h"
#include "Emitter.h"
#pragma once
class ButtonInputComponent :public EntityComponent, public Emitter
{
public:
	ButtonInputComponent(int x);
	~ButtonInputComponent();

	virtual void handleEvents(Entity* o, Uint32 time, const SDL_Event& event);
	virtual void update(Entity* o, Uint32 time);
	virtual void render(Entity* o, Uint32 time) {};

	bool isInRect(Entity*o);

private:
	bool isAbove;
	int butId_;
};


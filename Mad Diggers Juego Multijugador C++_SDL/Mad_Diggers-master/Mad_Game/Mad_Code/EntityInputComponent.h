//Mad_Diggers

#ifndef ENTITYINPUTCOMPONENT_H_
#define ENTITYINPUTCOMPONENT_H_

#include "EntityComponent.h"

class EntityInputComponent : public EntityComponent
{
public:
	EntityInputComponent();
	virtual ~EntityInputComponent();

	virtual void handleEvents(Entity* o, Uint32 time, const SDL_Event& event) = 0;
	virtual void update(Entity* o, Uint32 time) {};
	virtual void render(Entity* o, Uint32 time) {};
};

#endif /* ENTITYINPUTCOMPONENT_H_ */

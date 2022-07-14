//Mad_Diggers

#ifndef ENTITYUPDATECOMPONENT_H_
#define ENTITYUPDATECOMPONENT_H_

#include "EntityComponent.h"

class EntityUpdateComponent : public EntityComponent
{
public:
	EntityUpdateComponent();
	virtual ~EntityUpdateComponent();

	virtual void handleEvents(Entity* o, Uint32 time, const SDL_Event& event) {};
	virtual void update(Entity* o, Uint32 time) = 0;
	virtual void render(Entity* o, Uint32 time) {};
};

#endif /* ENTITYUPDATECOMPONENT_H_ */

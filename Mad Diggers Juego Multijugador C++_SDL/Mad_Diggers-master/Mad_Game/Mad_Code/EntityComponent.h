//Mad_Diggers

#ifndef ENTITYCOMPONENT_H_
#define ENTITYCOMPONENT_H_

#include "Entity.h"
#include "Activable.h" //be activable

class EntityComponent : public Activable
{
public:
	EntityComponent();
	virtual ~EntityComponent();

	// abstract methods to be implemented in sub-classes
	virtual void handleEvents(Entity* o, Uint32 time, const SDL_Event& event) = 0;
	virtual void update(Entity* o, Uint32 time) = 0;
	virtual void render(Entity* o, Uint32 time) = 0;
};

#endif /* ENTITYCOMPONENT_H_ */

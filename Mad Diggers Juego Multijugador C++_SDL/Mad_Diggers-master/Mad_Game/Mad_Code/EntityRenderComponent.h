#ifndef ENTITYRENDERCOMPONENT_H_
#define ENTITYRENDERCOMPONENT_H_

#include "EntityComponent.h"

struct spriteData
{
	Vector2D scale_, offset_; //on top of object
	bool rotation_; //check direction and rotate render accordingly
	bool drawRealPosition_;
};

class EntityRenderComponent : public EntityComponent
{
public:
	EntityRenderComponent();
	virtual ~EntityRenderComponent();

	virtual void handleEvents(Entity* o, Uint32 time, const SDL_Event& event) {};
	virtual void update(Entity* o, Uint32 time) {};
	virtual void render(Entity* o, Uint32 time) = 0;
};

#endif /* ENTITYRENDERCOMPONENT_H_ */
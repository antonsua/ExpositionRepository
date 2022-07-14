//Mad_Diggers

#ifndef SPRITESHEETRENDERER_H_
#define SPRITESHEETRENDERER_H_

#include "EntityRenderComponent.h"

class SpriteSheetRenderer : public EntityRenderComponent {

public:

	SpriteSheetRenderer(Texture* spriteSheet);
	virtual ~SpriteSheetRenderer();

	virtual void render(Entity* o, Uint32 time);

private:

	Texture* spriteSheet_;
};


#endif /* SPRITESHEETRENDERER_H_ */

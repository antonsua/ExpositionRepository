//Mad_Diggers

#ifndef FILLRECTRENDERER_H_
#define FILLRECTRENDERER_H_

#include "EntityRenderComponent.h"

class FillRectRenderer : public EntityRenderComponent {

public:
	FillRectRenderer();
	FillRectRenderer(SDL_Color** color);
	virtual ~FillRectRenderer();

	virtual void render(Entity* o, Uint32 time);

private:
	SDL_Color **color_;
	SDL_Color *tmpColor_ = nullptr; //used to hold the default color pointer

	static const Resources::ColorId _DEFAULT_COLOR_;
};

#endif /* FILLRECTRENDERER_H_ */

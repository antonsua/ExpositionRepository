#ifndef SHAPERENDERER_H_
#define SHAPERENDERER_H_

#include "ImageRenderer.h"

class ShapeRenderer : public ImageRenderer
{
public:
	ShapeRenderer();
	ShapeRenderer(Game* game, Resources::ShapeId shape, Resources::ColorId color);
	ShapeRenderer(Game* game, Resources::ShapeId shape, Resources::ColorId color, spriteData* data);

	virtual ~ShapeRenderer();

	void setShape(Resources::ShapeId shape);
	void setColor(Resources::ColorId color);

	virtual void render(Entity* o, Uint32 time);

protected:
	virtual void fadeEnd() { ImageRenderer::fadeEnd(); if (alpha_ == 0) toggleActive(); };

private:
	Game* game_; //used to load resources
	SDL_Color *color_;
};

#endif /* SHAPERENDERER_H_ */

#include "ShapeRenderer.h"

ShapeRenderer::ShapeRenderer()
{
}

ShapeRenderer::ShapeRenderer(Game* game, Resources::ShapeId shape, Resources::ColorId color)
	: game_(game), ImageRenderer(game->getResources()->getShapeTexture(shape)),
	color_(Resources::getSDLColor(color))
{
}

ShapeRenderer::ShapeRenderer(Game * game, Resources::ShapeId shape, Resources::ColorId color, spriteData* data)
	: game_(game), ImageRenderer(game->getResources()->getShapeTexture(shape), data),
	color_(Resources::getSDLColor(color))
{
}

ShapeRenderer::~ShapeRenderer()
{
}

///////////////////////////////////////////////////////////////////

void ShapeRenderer::setShape(Resources::ShapeId shape)
{
	image_ = game_->getResources()->getShapeTexture(shape);
}

void ShapeRenderer::setColor(Resources::ColorId color)
{
	color_ = Resources::getSDLColor(color);
}

///////////////////////////////////////////////////////////////////

void ShapeRenderer::render(Entity* o, Uint32 time)
{
	//mudulate color before render
	image_->modulateColor(*color_);

	ImageRenderer::render(o, time);
}
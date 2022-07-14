#include "FillRectRenderer.h"

const Resources::ColorId FillRectRenderer::_DEFAULT_COLOR_ = Resources::c_Green_olive;

FillRectRenderer::FillRectRenderer()
{
	tmpColor_ = Resources::getSDLColor(_DEFAULT_COLOR_);
	color_ = &tmpColor_;
}

FillRectRenderer::FillRectRenderer(SDL_Color **color)
{
	color_ = color;
}

FillRectRenderer::~FillRectRenderer()
{
}

void FillRectRenderer::render(Entity* o, Uint32 time) {
	SDL_Rect rect
	RECT(o->getPosition().getX(), o->getPosition().getY(),
			o->getWidth(), o->getHeight());

	SDL_SetRenderDrawColor(o->getGame()->getRenderer(), COLOREXP_PP(color_));
	SDL_RenderFillRect(o->getGame()->getRenderer(), &rect);
}


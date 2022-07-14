#include "SpriteSheetRenderer.h"

SpriteSheetRenderer::SpriteSheetRenderer(Texture* spriteSheet) : spriteSheet_(spriteSheet) {
}

SpriteSheetRenderer::~SpriteSheetRenderer() {
}

void SpriteSheetRenderer::render(Entity* o, Uint32 time) {
	SDL_Rect rect RECT(
		o->getPosition().getX(), o->getPosition().getY(),
		o->getWidth(), o->getHeight());

	double angle = o->getDirection().angle();
	//cout << angle << endl;

	spriteSheet_->renderFrame(2, 0, o->getGame()->getRenderer(), rect, angle);
}

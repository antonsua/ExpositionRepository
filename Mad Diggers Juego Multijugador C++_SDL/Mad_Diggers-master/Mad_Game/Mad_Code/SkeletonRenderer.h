#ifndef SKELETONTENDERER_H_
#define SKELETONTENDERER_H_

#include "EntityRenderComponent.h"

class SkeletonRenderer : public EntityRenderComponent
{
public:
	SkeletonRenderer();
	SkeletonRenderer(SDL_Color* hitboxC);
	SkeletonRenderer(SDL_Color* hitboxC, SDL_Color* directionC, SDL_Color* velocityC);
	virtual ~SkeletonRenderer();

	static void init();

	void render(Entity *o, Uint32 time);

private:
	SDL_Color *hitboxColor_, *directionColor_, *velocityColor_;
	static SDL_Color *G_hitboxColor_, *G_directionColor_, *G_velocityColor_;

	static const Resources::ColorId _HITBOX_DEFAULT_COLOR_ID_;
	static const Resources::ColorId _DIRECTION_DEFAULT_COLOR_ID_;
	static const Resources::ColorId _VELOCITY_DEFAULT_COLOR_ID_;
};

#endif /* SKELETONTENDERER_H_ */

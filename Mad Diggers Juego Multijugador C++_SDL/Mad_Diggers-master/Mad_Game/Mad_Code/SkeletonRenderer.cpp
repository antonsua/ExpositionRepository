#include "SkeletonRenderer.h"
#include <algorithm>

const Resources::ColorId SkeletonRenderer::_HITBOX_DEFAULT_COLOR_ID_ = { Resources::c_White};
const Resources::ColorId SkeletonRenderer::_DIRECTION_DEFAULT_COLOR_ID_ = { Resources::c_Blue_light };
const Resources::ColorId SkeletonRenderer::_VELOCITY_DEFAULT_COLOR_ID_ = { Resources::c_Green_light };

//inited by enity
SDL_Color* SkeletonRenderer::G_hitboxColor_ = NULL;
SDL_Color* SkeletonRenderer::G_directionColor_ = NULL;
SDL_Color* SkeletonRenderer::G_velocityColor_ = NULL;
void SkeletonRenderer::init()
{
	G_hitboxColor_ = Resources::getSDLColor(_HITBOX_DEFAULT_COLOR_ID_);
	G_directionColor_ = Resources::getSDLColor(_DIRECTION_DEFAULT_COLOR_ID_);
	G_velocityColor_ = Resources::getSDLColor(_VELOCITY_DEFAULT_COLOR_ID_);
}

///////////////////////////////////////////////////////////////////

SkeletonRenderer::SkeletonRenderer() :
	hitboxColor_(G_hitboxColor_),
	directionColor_(G_directionColor_),
	velocityColor_(G_velocityColor_)
{
	toggleActive(); //init deactivated
}

SkeletonRenderer::SkeletonRenderer(SDL_Color* hitboxColor) :
	hitboxColor_(hitboxColor),
	directionColor_(G_directionColor_),
	velocityColor_(G_velocityColor_)
{
	toggleActive();
}

SkeletonRenderer::SkeletonRenderer(SDL_Color* hitboxColor,
	SDL_Color* directionColor, SDL_Color* velocityColor) :
	hitboxColor_(hitboxColor),
	directionColor_(directionColor),
	velocityColor_(velocityColor)
{
	toggleActive();
}

SkeletonRenderer::~SkeletonRenderer()
{
}

///////////////////////////////////////////////////////////////////

void SkeletonRenderer::render(Entity *o, Uint32 time) {

	SDL_Renderer* renderer = o->getGame()->getRenderer();

	double angle = o->getDirection().angle(Vector2D::getDefaultZeroAngle());

	Vector2D lu(-o->getWidth() / 2, -o->getHeight() / 2);
	Vector2D ru(o->getWidth() / 2, -o->getHeight() / 2);
	Vector2D rb(o->getWidth() / 2, o->getHeight() / 2);
	Vector2D lb(-o->getWidth() / 2, o->getHeight() / 2);

	double x = o->getPosition().getX() + o->getWidth() / 2;
	double y = o->getPosition().getY() + o->getHeight() / 2;

	lu.rotate(angle);
	ru.rotate(angle);
	rb.rotate(angle);
	lb.rotate(angle);

	SDL_SetRenderDrawColor(renderer, COLOREXP_P(hitboxColor_));
	SDL_RenderDrawLine(renderer, lu.getX() + x, lu.getY() + y,
		ru.getX() + x, ru.getY() + y);
	SDL_RenderDrawLine(renderer, ru.getX() + x, ru.getY() + y,
		rb.getX() + x, rb.getY() + y);
	SDL_RenderDrawLine(renderer, rb.getX() + x, rb.getY() + y,
		lb.getX() + x, lb.getY() + y);
	SDL_RenderDrawLine(renderer, lb.getX() + x, lb.getY() + y,
		lu.getX() + x, lu.getY() + y);

	SDL_SetRenderDrawColor(renderer, COLOREXP_P(directionColor_));

	Vector2D dir = (o->getDirection()) * (o->getHeight() / 2);
	SDL_RenderDrawLine(renderer, x, y, dir.getX() + x, dir.getY() + y);

	SDL_SetRenderDrawColor(renderer, COLOREXP_P(velocityColor_));

	Vector2D vel = o->getVelocity();
	vel.normalize();
	vel = vel * (std::min(o->getHeight(), o->getWidth()) / 2)
		* (o->getVelocity().magnitude() / 5);
	SDL_RenderDrawLine(renderer, x, y, vel.getX() + x, vel.getY() + y);
}

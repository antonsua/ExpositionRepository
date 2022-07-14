#include "ballPong.h"
#include "ImageRenderer.h"


ballPong::ballPong(Game* game, Vector2D offset) :
	Entity(game), jsonReader(game->getResources()->getJsonFile(Resources::j_PongMinigame)),
	_BALL_SIZE_(jsonData["_BALL_SIZE_"].asDouble())
{
	setHeight(_BALL_SIZE_);
	setWidth(_BALL_SIZE_);

	addComponent(new ImageRenderer(game->getResources()->getImageTexture(Resources::i_yellowCircle)));
}


ballPong::~ballPong()
{
}

void ballPong::update(Uint32 time) {	
	Entity::update(time);
}
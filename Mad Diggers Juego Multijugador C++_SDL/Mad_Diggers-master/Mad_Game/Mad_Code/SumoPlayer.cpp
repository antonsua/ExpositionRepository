#include "SumoPlayer.h"
#include "ImageRenderer.h"
#include "BasicMotionPhysics.h"
#include "BasicKBCtrlComponent.h"
#include "SumoMiniGame.h"
#include "SumoManager.h"

/*SumoPlayer::SumoPlayer(Game * game, SDL_Keycode left, SDL_Keycode right, SDL_Keycode up,
	SDL_Keycode down, Resources::ImageId ballColor) : Entity(game)*/



SumoPlayer::SumoPlayer(Game * game, Json::Value keys, Resources::ImageId ballColor, SumoMinigame* sumoGame, int gamepadNum) :
Entity(game),gamePad_(gamepadNum),sumoGame_(sumoGame)

{
	readFromJson(game->getResources()->getJsonFile(Resources::j_SumoPlayer));
	left_ = (SDL_Keycode)keys[0].asUInt();
	right_ = (SDL_Keycode)keys[1].asUInt();
	up_ = (SDL_Keycode)keys[2].asUInt();
	down_ = (SDL_Keycode)keys[3].asUInt();
	sumoGameComp_ = SumoGameComponent (left_, right_, up_, down_, jsonData["thurst"].asUInt(), jsonData["maxVelocity"].asUInt());

	this->setActive(true);
	setWidth(jsonData["width"].asUInt());
	setHeight(jsonData["height"].asUInt());

	//random position
	setPosition(Vector2D(0,0));


	setVelocity(Vector2D(0, 0));

	this->c.x = getPosition().getX() / 2;
	this->c.y = getPosition().getY() / 2;
	this->c.r = getWidth() / 2;


	addComponent(new ImageRenderer(game_->getResources()->getImageTexture(ballColor)));
	addComponent(&sumoGameComp_);
	addComponent(&gamePad_);
	gamePad_.registerListener(&sumoGameComp_);

}

SumoPlayer::~SumoPlayer()
{
}

void SumoPlayer::setCircleCoordinates(int x, int y)
{
	c.x = x;
	c.y = y;

}

void SumoPlayer::update(Uint32 time)
{
	Entity::update(time);
	if (!sumoGame_->isPlacingCircles()) {
		setPosition(getPosition() + getVelocity());
		setCircleCoordinates(getPosition().getX(), getPosition().getY());
	}
}

void SumoPlayer::endMovement(bool timeOut)
{
	send(&Message(SUMOGAME_PLACE_REACHED), sumoGame_);
}




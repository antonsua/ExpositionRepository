#include "ApplePlayer.h"
#include "AppleMiniGame.h"


ApplePlayer::ApplePlayer(Game* game, AppleTree* tree, int colorIdentifier, SDL_Keycode left, SDL_Keycode right,
	SDL_Keycode shake, SDL_Keycode exploit, ApplesManager* applesManager, Resources::ColorId color, int padNum, int numPlayers)
	: Entity(game), score_(0), gamepad_(padNum), numPlayers_(numPlayers),
	colorIdentifier_(colorIdentifier), myTree_(tree), shapeRC_(game, Resources::s_BeeKeeperNet, color),
	playerController_(left, right, shake, exploit, this, tree)
{
	setWidth(APPLE_PLAYER_WIDTH);
	setHeight(APPLE_PLAYER_HEIGHT);
	setPos();
	setCollisionBox();
	phRect_.w = getWidth();
	phRect_.h = getHeight();

	shapeRC_.activateFlip();
	nameData_ = { Vector2D(0.35,0.35), Vector2D(-10,-65), false, false, };
	valueRC_ = Value_RC(MAX_SCORE_DIGITS, Resources::f_ARIAL_64, color, &nameData_);


	addComponent(&playerController_);
	addComponent(&shapeRC_);
	addComponent(&valueRC_);
	addComponent(&gamepad_);

	registerListener(applesManager);
	gamepad_.registerListener(&playerController_);


}



ApplePlayer::~ApplePlayer()
{
}

ApplePlayer::ApplePlayer()
{
}

void ApplePlayer::addScore(int s)
{

	score_ += s;
	if (score_ < 0) {
		score_ = 0;
	}
}

bool ApplePlayer::isOverlapping(const Point l1, const Point r1, const Point l2, const Point r2) const
{
	// If one rectangle is on left side of other
	return (!(l1.x > r2.x || l2.x > r1.x));
}

void ApplePlayer::setCollisionBox()
{
	l1.x = getPosition().getX();
	l1.y = getPosition().getY();
	r1.x = l1.x + getWidth();
	r1.y = l1.y + getHeight();
}

void ApplePlayer::update(Uint32 time)
{
	Entity::update(time);
	setCollisionBox();
	boundToLimits();
	setPosition(getPosition() + getVelocity());
	updateRectangle();


}

void ApplePlayer::updateRectangle()
{
	phRect_.A.x = getPosition().getX();
	phRect_.A.y = getPosition().getY();
	phRect_.B.x = getPosition().getX() + getWidth();
	phRect_.B.y = getPosition().getY();
	phRect_.C.x = getPosition().getX();
	phRect_.C.y = getPosition().getY() + getHeight();
	phRect_.D.x = getPosition().getX() + getWidth();
	phRect_.D.y = getPosition().getY() + getHeight();
}


void ApplePlayer::receive(Message * msg)
{
	int auxApples;
	switch (msg->id_)
	{
	case SHAKING_TREE:
	{
		if (isOverlapping(l1, r1, myTree_->getl2(), myTree_->getr2())) {
			myTree_->addTicks(1);
		}
		break;
	}
	case DETONATE_TREE:
		if (isOverlapping(l1, r1, myTree_->getl2(), myTree_->getr2())) {
			auxApples = myTree_->getTicks();
			myTree_->setTicks(0);
			send(&SpawnApplesMG(colorIdentifier_, auxApples));
		}
		break;
	}
	game_->sendToSM(msg);
}

void ApplePlayer::boundToLimits()
{
	if (getVelocity().getX() < 0) {
		if (getPosition().getX() + getVelocity().getX() <= 0) {
			setPosition(Vector2D(0, game_->getWindowHeight() - getHeight()));
		}
	}
	else if (getVelocity().getX() > 0) {
		if (getPosition().getX() + getVelocity().getX() + getWidth() >= game_->getWindowWidth()) {
			setPosition(Vector2D(game_->getWindowWidth() - getWidth(), game_->getWindowHeight() - getHeight()));
		}
	}
}

void ApplePlayer::setPos()
{
	switch (colorIdentifier_-1)
	{
	case 0:
		setPosition(Vector2D(T1_INI_POS.getX(), game_->getWindowHeight() - getHeight()));
		break;
	case 1:
		if (numPlayers_ == 2) {
			setPosition(Vector2D(T2_INI_POS_2P.getX(), game_->getWindowHeight() - getHeight()));
		}
		else setPosition(Vector2D(T2_INI_POS_4P.getX(), game_->getWindowHeight() - getHeight()));
		break;
	case 2:
		setPosition(Vector2D(T3_INI_POS.getX(), game_->getWindowHeight() - getHeight()));
		break;
	case 3:
		setPosition(Vector2D(T4_INI_POS.getX(), game_->getWindowHeight() - getHeight()));
		break;

	}
}




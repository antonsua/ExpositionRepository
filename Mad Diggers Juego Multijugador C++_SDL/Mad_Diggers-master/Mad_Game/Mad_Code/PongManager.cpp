#include "PongManager.h"

PongManager::PongManager(Game* game, vector<BlockPong*>* blocks, vector<Paddle*> paddles, ballPong* ball, Vector2D offset): GameObject(game),
	blocks_(blocks), paddles_(paddles), ball_(ball)
{
	ballPhysics = new BallPhysicsComponent(offset.getX(), offset.getY());
	registerListener(ballPhysics);
	ball->addComponent(ballPhysics);
}


PongManager::~PongManager()
{
	delete ballPhysics;
}

void PongManager::render(Uint32 time){

}

void PongManager::handleEvents(Uint32 time, const SDL_Event& event){

}

void  PongManager::update(Uint32 time) {
	bool collision = false;

	int i = 0;
	while (i < paddles_.size() && !collision)
	{
		if (checkCollision(ball_, paddles_[i]) && paddles_[i]->isActive()) {
			i += 0;
			send(&PongMessage_BallPaddleCollision(paddles_[i]));
			game_->sendToSM(& Message(BALL_PADDLE_COLLISION));
			collision = true;
		}
		i++;
	}
	
	i = 0;
	while (i < blocks_->size() && !collision)
	{
		if (checkCollision(ball_, (*blocks_)[i]) && (*blocks_)[i]->isActive()) {
			i += 0;
			send(&Message(BALL_BLOCK_COLLISION));
			game_->sendToSM(& Message(BALL_BLOCK_COLLISION));
			collision = true;
		}
		i++;
	}

	checkBallLimits();
}

void PongManager::checkBallLimits() {
	Vector2D bPos = ball_->getPosition();
	int tmp = 4;

	if (bPos.getX() > game_->getWindowWidth())
		tmp = 1;
	else if (bPos.getX() < 0)
		tmp = 0;
	else if (bPos.getY() > game_->getWindowHeight())
		tmp = 3;
	else if (bPos.getY() < 0)
		tmp = 2;
	if (tmp != 4) {
		send(new Message_BallLimits(tmp));
		//paddles_[tmp]->setActive(false);
		ball_->setPosition(Vector2D( game_->getWindowWidth() / 2, game_->getWindowHeight() / 2 ));
		ball_->setVelocity({ 0, 0 });
	}
}

void PongManager::receive(Message* msg) {
	switch (msg->id_) {
	case MINIGAME_ROUND_START: {
		int dx = 1 - 2 * game_->getRnd(1); // 1 or -1
		int dy = 1 - 2 * game_->getRnd(1); // 1 or -1
		int rnd = game_->getRnd(2, 6);
		if (game_->getRnd(1) == 1)
			rnd = -rnd;
		Vector2D v(dx + rnd, dy);
		v.normalize();
		ball_->setVelocity(v * 2);
		break;
	}
	}
}

bool PongManager::checkCollision(Physical* o1, Physical* o2) {

	Vector2D o1Pos = o1->getPosition();
	double o1Width = o1->getWidth();
	double o1Height = o1->getHeight();

	Vector2D o2Pos = o2->getPosition();
	double o2Width = o2->getWidth();
	double o2Height = o2->getHeight();

	bool collideX, collideY;
	collideX = collideY = false;


	collideX = !(o1Pos.getX() + o1Width < o2Pos.getX()
		|| o2Pos.getX() + o2Width < o1Pos.getX());

	collideY = !(o1Pos.getY() + o1Height < o2Pos.getY()
		|| o2Pos.getY() + o2Height < o1Pos.getY());

	if (collideX && collideY)
		return true;

	return false;
}
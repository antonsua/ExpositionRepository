#include "AppleMiniGame.h"

const float gameDuration = 60000.0f;

const string AppleMiniGame::idName_ = "AppleMiniGame";

AppleMiniGame::AppleMiniGame(Game * game, stack<int>* p_playersTurnsOrder, int numPlayers) :
	MiniGameState(game, p_playersTurnsOrder, idName_, numPlayers), timer_(game), timerSquare_(game),
	timerRC_(game->getResources()->getImageTexture(Resources::i_timer))
{
	numOfPlayers_ = numPlayers;
	initMinigame();
	applesManager_ = ApplesManager(game, this);
	gameObjects_.push_back(&timerSquare_);
	gameObjects_.push_back(&timer_);

	timerSquare_.addComponent(&timerRC_);
	timerSquare_.setHeight(82);
	timerSquare_.setWidth(350);
	timerSquare_.setPosition(Vector2D(400 - 175, 0));
	timer_.startCountDown(gameDuration);


}

AppleMiniGame::~AppleMiniGame()
{
}

void AppleMiniGame::handleEvents(Uint32 time, const SDL_Event event) {

	if (event.type == SDL_KEYDOWN) {
		switch (event.key.keysym.sym) {

		case SDLK_SPACE: //close minigame
			MiniGameState::endMiniGame();
			break;
		}
	}
}

void AppleMiniGame::update(Uint32 time)
{
	if (starting)
	{
		starting = false;
		sendToGSM(&AppleControlsPop(this));

	}

	GameState::update(time);
	if (timer_.get_countDown_ticks() <= 0) {
		endMiniGame();
		sendToGSM(&StateMessage_Minigame(STATE_PODIUM, p_playersTurnsOrder_));
	}
}

void AppleMiniGame::render(Uint32 time)
{
	if (!starting) {
		GameState::render(time);
	}
}
void AppleMiniGame::initState()
{
}

void AppleMiniGame::closeState()
{
}

void AppleMiniGame::endMiniGame()
{
	vector<ApplePlayer*>::iterator it;
	ApplePlayer* auxPla = new ApplePlayer();
	size_t i = 0;
	while (i < numOfPlayers_) {
		int minScore = 1000000;
		for (it = applePlayers_.begin(); it != applePlayers_.end(); it++)
		{
			if ((*it)->isActive()) {
				int aux = (*it)->getScore();
				if (aux < minScore) {
					minScore = aux;
					auxPla = (*it);
				}
			}
		}

		p_playersTurnsOrder_->push(auxPla->getID() - 1);
		(auxPla)->setActive(false);
		i++;
	}
}

void AppleMiniGame::initMinigame()
{
	AppleTree* t1 = nullptr;
	AppleTree* t2 = nullptr;
	AppleTree* t3 = nullptr;
	AppleTree* t4 = nullptr;

	ApplePlayer* p1 = nullptr;
	ApplePlayer* p2 = nullptr;
	ApplePlayer* p3 = nullptr;
	ApplePlayer* p4 = nullptr;

	if (numOfPlayers_ >= 2) {
		t1 = new AppleTree(game_, 1, numOfPlayers_);

		t2 = new AppleTree(game_, 2, numOfPlayers_);

		p1 = new ApplePlayer(game_, t1, 1, SDLK_a, SDLK_d, SDLK_w, SDLK_s, &applesManager_,
			Resources::_DEFAULT_PLAYERS_COLORS_ID_[0], 0, numOfPlayers_);
		p2 = new ApplePlayer(game_, t2, 2, SDLK_j, SDLK_l, SDLK_i, SDLK_k, &applesManager_,
			Resources::_DEFAULT_PLAYERS_COLORS_ID_[1], 1, numOfPlayers_);

		applePlayers_.push_back(p1);
		applePlayers_.push_back(p2);
	}
	if (numOfPlayers_ == 4) {
		t3 = new AppleTree(game_, 3, numOfPlayers_);

		t4 = new AppleTree(game_, 4, numOfPlayers_);

		p3 = new ApplePlayer(game_, t3, 3, SDLK_LEFT, SDLK_RIGHT, SDLK_UP, SDLK_DOWN, &applesManager_,
			Resources::_DEFAULT_PLAYERS_COLORS_ID_[2], 2, numOfPlayers_);
		p4 = new ApplePlayer(game_, t4, 4, SDLK_f, SDLK_h, SDLK_t, SDLK_g, &applesManager_,
			Resources::_DEFAULT_PLAYERS_COLORS_ID_[3], 3, numOfPlayers_);
		applePlayers_.push_back(p3);
		applePlayers_.push_back(p4);

	}

	if (t1 != nullptr)gameObjects_.push_back(t1);
	if (t2 != nullptr)gameObjects_.push_back(t2);
	if (t3 != nullptr)gameObjects_.push_back(t3);
	if (t4 != nullptr)gameObjects_.push_back(t4);

	if (p1 != nullptr)gameObjects_.push_back(p1);
	if (p2 != nullptr)gameObjects_.push_back(p2);
	if (p3 != nullptr)gameObjects_.push_back(p3);
	if (p4 != nullptr)gameObjects_.push_back(p4);

	gameObjects_.push_back(&applesManager_);
}

void AppleMiniGame::receive(Message * msg)
{
	switch (msg->id_)
	{
	case APPLE_TOUCHED_FLOOR:
		applePlayers_[static_cast<AppleDown*>(msg)->colorIdentifier_ - 1]->addScore(-60);
		//send updategui
		game_->sendToSM(msg);
		break;
	case PLAYER_CAUGTH_APPLE:
		addScoreToPlayer(static_cast<PlayerGotApple*>(msg)->colorIdentifier_);
		game_->sendToSM(msg);
		break;
	case STATE_CONTROLS_POP:
		timer_.startCountDown(gameDuration);
		break;
	}


}

bool AppleMiniGame::pointInRectangle(Point p, ApplePlayer* player)
{
	RectanglePhysics r = player->getRectangle();

	//Area of ABCD
	float A = area(r.A, r.B, r.C) + area(r.A, r.C, r.D);
	//Area of PAB
	float A1 = area(p, r.A, r.B);
	//Area of PBC
	float A2 = area(p, r.B, r.C);
	//Area of PCD
	float A3 = area(p, r.C, r.D);
	//Area of PAD
	float A4 = area(p, r.A, r.D);

	/*If P lies inside the triangle, then A1 + A2 + A3 + A4 must be equal to A.*/
	return (A == A1 + A2 + A3 + A4);
}

float AppleMiniGame::area(Point a, Point b, Point c)
{
	return abs((a.x * (b.y - c.x) + b.x * (c.y - a.y) +
		c.x * (a.y - b.y)) / 2.0);
}

bool AppleMiniGame::RectCircleCollision(Circle c, RectanglePhysics r)
{
	float distX = abs(c.x - r.A.x - r.w / 2);
	float distY = abs(c.y - r.A.y - r.h / 2);

	if (distX > (r.w / 2 + c.r)) { return false; }
	if (distY > (r.h / 2 + c.r)) { return false; }

	if (distX <= (r.w / 2)) { return true; }
	if (distY <= (r.h / 2)) { return true; }

	float dx = distX - r.w / 2;
	float dy = distY - r.h / 2;
	return (dx*dx + dy * dy <= (c.r*c.r));
}

void AppleMiniGame::addScoreToPlayer(int playerID)
{
	applePlayers_[playerID - 1]->addScore(30);

}



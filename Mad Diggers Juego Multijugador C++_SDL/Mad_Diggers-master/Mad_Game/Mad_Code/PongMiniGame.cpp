#include "PongMiniGame.h"

const string PongMiniGame::idName_ = "PongMinigame";


PongMiniGame::PongMiniGame(Game* game, stack<int> *p_playersTurnsOrder, int numPlayers)
	: MiniGameState(game, p_playersTurnsOrder, idName_, numPlayers), jsonReader(game->getResources()->getJsonFile(Resources::j_PongMinigame)),
	_BORDER_(Vector2D(jsonData["_BORDER_"][0].asUInt(), jsonData["_BORDER_"][1].asUInt())), _MAX_SCORE_(jsonData["_MAX_SCORE_"].asInt()), 
	renderAnim(game_->getResources()->getSpriteSheetTexture(Resources::ss_SumoCD), &animData_, false)
{
	initState();
	//Entity::toggleDebugGlobal();
}

PongMiniGame::~PongMiniGame()
{
	closeState();
	//Entity::toggleDebugGlobal();
}

void PongMiniGame::initState()
{
	exit_ = false;

	renderAnim.registerListener(this);
	countEntity = new Entity(game_);
	countEntity->setWidth(320);
	countEntity->setHeight(240);
	countEntity->setPosition(Vector2D(game_->getWindowWidth() / 2 - 160, game_->getWindowHeight() / 2 - 120));
	countEntity->addComponent(&renderAnim);
	countEntity->setActive(false);
	//Creation of the corner blocks

	for (int i = 0; i < BlockPositions.size(); i++)
	{
		//TODO borrar los objetos pls ty
		BlockPong* Block = new BlockPong(game_, Resources::ShapeId::s_pongBlock, _BORDER_);
		Block->setPosition(BlockPositions[i]);
		blocks.push_back(Block);
		gameObjects_.push_back(Block);
	}

	//Creation of the ball

	ballPong* ball = new ballPong(game_, _BORDER_);
	ball->setPosition(Vector2D(game_->getWindowWidth() / 2, game_->getWindowHeight() / 2));
	gameObjects_.push_back(ball);

	//Creation of 2 paddles
	Paddle* Paddle0 =
		new Paddle(game_,0, Resources::i_paddle0, DPAD_UP, DPAD_DOWN, uDPAD_UP, uDPAD_DOWN, _BORDER_, false, 0, SDLK_q, SDLK_w);
	Paddle0->setPosition(Vector2D(_BORDER_.getX() - Paddle0->getWidth(), (game_->getWindowHeight() - Paddle0->getHeight()) / 2));
	paddles.push_back(Paddle0);
	gameObjects_.push_back(Paddle0);

	Paddle* Paddle1 =
	new Paddle(game_, 1, Resources::i_paddle1, DPAD_UP, DPAD_DOWN, uDPAD_UP, uDPAD_DOWN, _BORDER_, false, 1, SDLK_c, SDLK_v);
	Paddle1->setPosition(Vector2D(game_->getWindowWidth() - _BORDER_.getX(), (game_->getWindowHeight() - Paddle1->getHeight()) / 2));
	paddles.push_back(Paddle1);
	gameObjects_.push_back(Paddle1);

	// depending of the number of players this creates more walls or more paddles
	if (numOfPlayers_ == 2) {
		addWall(Vector2D(0.0, 0.0), true);
		addWall(Vector2D(0.0, game_->getWindowHeight() - _BORDER_.getY()), true);
	}
	else
	{
		Paddle* Paddle2 =
		new Paddle(game_,2, Resources::i_paddle2, DPAD_LEFT, DPAD_RIGHT, uDPAD_LEFT, uDPAD_RIGHT, _BORDER_, true, 2, SDLK_t, SDLK_y);
		Paddle2->setPosition(Vector2D((game_->getWindowWidth() - Paddle2->getWidth()) / 2, _BORDER_.getY() - Paddle2->getHeight()));
		paddles.push_back(Paddle2);
		gameObjects_.push_back(Paddle2);

		Paddle* Paddle3 =
		new Paddle(game_,3, Resources::i_paddle3, DPAD_LEFT, DPAD_RIGHT, uDPAD_LEFT, uDPAD_RIGHT, _BORDER_, true, 3, SDLK_j, SDLK_k);
		Paddle3->setPosition(Vector2D((game_->getWindowWidth() - Paddle3->getWidth()) / 2, game_->getWindowHeight() - _BORDER_.getY()));
		paddles.push_back(Paddle3);
		gameObjects_.push_back(Paddle3);
	}

	manager = new PongManager(game_, &blocks, paddles, ball, _BORDER_);
	manager->registerListener(this);
	registerListener(manager);
	gameObjects_.push_back(manager);
}

//orientation indicates if it's a vertical(false) or horizontal(true) wall
void PongMiniGame::addWall(Vector2D pos, bool orientation) {
	BlockPong* NBlock;
	if (orientation) {
		if (pos.getY() == 0) {
			NBlock = new BlockPong(game_, Resources::ImageId::i_honeyPongU, _BORDER_, orientation);
			NBlock->setPosition(pos - Vector2D(0, _BORDER_.getY()));
		}
		else {
			NBlock = new BlockPong(game_, Resources::ImageId::i_honeyPongD, _BORDER_, orientation);
			NBlock->setPosition(pos + Vector2D(0, _BORDER_.getY()));
		}
		NBlock->setHeight(_BORDER_.getY());
		NBlock->setWidth(game_->getWindowWidth());
		NBlock->setFinalPos(pos);
		NBlock->moveToPoint(pos, 1000);

	}
	else {
		if (pos.getX() == 0) {
			NBlock = new BlockPong(game_, Resources::ImageId::i_honeyPongL, _BORDER_, orientation);
			NBlock->setPosition(pos - Vector2D(_BORDER_.getX(), 0));
		}
		else {
			NBlock = new BlockPong(game_, Resources::ImageId::i_honeyPongR, _BORDER_, orientation);
			NBlock->setPosition(pos + Vector2D(_BORDER_.getX(), 0));
		}
		NBlock->setHeight(game_->getWindowHeight());
		NBlock->setWidth(_BORDER_.getX());
		NBlock->setFinalPos(pos);
		NBlock->moveToPoint(pos, 1000);

	}

	blocks.push_back(NBlock);
	gameObjects_.push_back(NBlock);
}



void PongMiniGame::createPlayer(int numPlayer) {

}

void PongMiniGame::closeState()
{
	for each (Entity* var in gameObjects_)
	{
		delete var;
	}
	delete manager;
	delete countEntity;
}

//propagates the event and then if no one handles it, tries ti handle
void PongMiniGame::handleEvents(Uint32 time, SDL_Event event)
{
	bool handled = false;

	if(!count)
	if (event.type == SDL_KEYDOWN || event.type == SDL_CONTROLLERBUTTONDOWN) {
		// if any key pressed while not running, we choose a random velocity of the ball
		if (!running_ && !blockMoving) {
			handled = true;
			running_ = true;
			send(&Message(MINIGAME_ROUND_START));

		}
		switch (event.key.keysym.sym) {

		case SDLK_SPACE: //close minigame
			handled = true;
			MiniGameState::endMiniGame();
			break;

		}
	}

	//prior propagation
	if (!handled) MiniGameState::handleEvents(time, event);
}

//controls logic and calls all gameobjects' update
void PongMiniGame::update(Uint32 time)
{
	if (starting_)
	{
		starting_ = false;
		sendToGSM(&Message(STATE_PONG_CONTROLS));
	}
	else {
		if (count && !countEntity->isActive()) {
			countEntity->setActive(true);
			renderAnim.start();
		}
	}
	if (countEntity->isActive())
		countEntity->update(time);
	if (count) return;
	MiniGameState::update(time);

	if (blocks.size() > 4) {
		if (!blocks.back()->isMoving()) {
			blocks.back()->setPosition(blocks.back()->getFinalPos());
			blockMoving = false;
		}
		else
			blockMoving = true;
	}
	if (paddleAux != -1) {
		if (!paddles[paddleAux]->isMoving()) {
			removePlayer(paddleAux);
			paddleAux = -1;
		}
	}
}

void PongMiniGame::receive(Message* message) {
	Vector2D v;
	switch (message->id_)
	{
	case MINIGAME_ROUND_OVER: 
	{
		Message_BallLimits* m = static_cast<Message_BallLimits*>(message);
		running_ = false;
		paddleAux = m->player_;
		rightScore_++;
		if (numOfPlayers_ == 4) {
			paddles[paddleAux]->getAxisInpComp()->send(&Message(NO_MOVE));
			paddles[paddleAux]->delComponent(paddles[paddleAux]->getAxisInpComp());
		}
		if (m->player_ == 0) {
			if (numOfPlayers_ == 4) {
				addWall(Vector2D(0.0, 0.0), false);
				paddles[0]->moveToPoint(Vector2D(0, paddles[0]->getPosition().getY()), 1000);
			}
		}
		else if (m->player_ == 1) {
			if (numOfPlayers_ == 2) {
				leftScore_++;
				rightScore_--;
			}
			else {
				addWall(Vector2D(game_->getWindowWidth() - _BORDER_.getX(), 0.0), false);
				paddles[1]->moveToPoint(Vector2D(game_->getWindowWidth(), paddles[1]->getPosition().getY()), 1000);
			}
		}
		else if (m->player_ == 2) {
			paddles[2]->moveToPoint(Vector2D(paddles[2]->getPosition().getX(), 0), 1000);
			addWall(Vector2D(0.0, 0.0), true);
		}
		else if (m->player_ == 3) {
			paddles[3]->moveToPoint(Vector2D(paddles[3]->getPosition().getX(), game_->getWindowHeight()), 1000);
			addWall(Vector2D(0.0, game_->getWindowHeight() - _BORDER_.getY()), true);
		}
	}
		break;
	case ANIMATION_ENDED: {
			count = false;
			countEntity->setActive(false);
		}
		break;
	default:
			break;
	}
}

void PongMiniGame::removePlayer(int playerNum)
{
	paddles[playerNum]->setActive(false);
	p_playersTurnsOrder_->push(playerNum);
	playerNum_.remove(playerNum);
	if (numOfPlayers_ == 2) {
		if (leftScore_ == _MAX_SCORE_ || rightScore_ == _MAX_SCORE_) {
			endMiniGame();
		}
	}
	else {
		if (playerNum_.size() == 1)
			endMiniGame();
	}
}


void PongMiniGame::render(Uint32 time)
{
	if (starting_) return;
	MiniGameState::render(time);
	if(countEntity->isActive())
		countEntity->render(time);
}

void PongMiniGame::endMiniGame()
{
	if (numOfPlayers_ == 2) {
		if (rightScore_ > leftScore_) {
			p_playersTurnsOrder_->push(0);
			p_playersTurnsOrder_->push(1);
		}
		else {
			p_playersTurnsOrder_->push(1);
			p_playersTurnsOrder_->push(0);
		}
		p_playersTurnsOrder_->push(2);
		p_playersTurnsOrder_->push(3);

		sendToGSM(&StateMessage_Minigame(STATE_PODIUM, p_playersTurnsOrder_));
	}
	else {
		if (playerNum_.size() == 1) {
			p_playersTurnsOrder_->push(playerNum_.front());
			cout << playerNum_.front();
			sendToGSM(&StateMessage_Minigame(STATE_PODIUM, p_playersTurnsOrder_));
		}
		else {
			MiniGameState::endMiniGame();
		}
	}
}

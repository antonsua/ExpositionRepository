#include "PodiumState.h"



PodiumState::PodiumState(Game* game, std::stack<int>* playersinOrder, bool ending)
	:GameState(game), ending_(ending), numPlayers_(4),
	jsonReader(game->getResources()->getJsonFile(Resources::j_Board)), padIC_(0),
	nextRC_(game->getResources()->getImageTexture(Resources::i_menuNext_)),

#define json jsonData["Spinner"] //Macro to short

	miniPlayersOffset_(Vector2D(json["miniPlayersOffset_"]["x"].asDouble(),
		json["miniPlayersOffset_"]["y"].asDouble())),
	miniPlayerW_(json["miniPlayerW_"].asDouble()),
	miniPlayerH_(json["miniPlayerH_"].asDouble()),
	miniplayersScaleTime_(json["miniplayersScaleTime_"].asDouble()),
	playersMove{ 305, 365, 420, 505 }
{
	playersinOrder_ = *playersinOrder;
	podiumRender_ = ImageRenderer(game_->getResources()->getImageTexture(Resources::i_Podium));

	initState();
	initMiniPlayers();
}

PodiumState::~PodiumState() {
	closeState();
}

void PodiumState::initMiniPlayers() {
	//mini players animations
	for (size_t i = 0; i < numPlayers_; i++) {
		AnimationRenderer mini(game_->getResources()->getSpriteSheetTexture(Resources::ss_PlayerHandsMoving), &miniAnimData_, true);
		mini.setColor(Resources::getSDLColor(Resources::_DEFAULT_PLAYERS_COLORS_ID_[playersinOrder_.top()]));
		playersinOrder_.pop();
		mini_player_Animation_.push_back(mini);
	}

	//mini players entities
	double //centered
		wOffset = miniPlayersOffset_.getX() - miniPlayerW_,
		wTotal = (miniPlayerW_ + wOffset) * numPlayers_ - wOffset,
		xTotal = game_->getWindowWidth() / 2 - wTotal / 2;

	Vector2D topLeft(xTotal, -200);

	for (size_t i = 0; i < numPlayers_; i++) {
		Entity* miniPlayer_ = new Entity(game_);

		int d;
		switch (i)
		{
		case 0:
			d = 2;
			break;
		case 1:
			d = 1;
			break;
		case 2:
			d = 3;
			break;
		case 3:
			d = 0;
			break;
		}
		miniPlayer_->setPosition(topLeft + (miniPlayersOffset_ * d));
		miniPlayer_->setWidth(miniPlayerW_);
		miniPlayer_->setHeight(miniPlayerH_);

		miniPlayer_->addComponent(&mini_player_Animation_[i]);
		miniPlayer_->moveToPoint(miniPlayer_->getPosition() + Vector2D(0, playersMove[i]), (i+1)*1000);

		mini_players_.push_back(miniPlayer_);
		gameObjects_.push_back(miniPlayer_);
	}
}

void PodiumState::initState() {
	podium_ = new Entity(game_);
	gameObjects_.push_back(podium_);

	podium_->setWidth(718);
	podium_->setHeight(320);
	podium_->setPosition(Vector2D(41, 600));
	podium_->moveToPoint(Vector2D(41, 200), 600);
	podium_->addComponent(&podiumRender_);
	padEntity_ = new Entity(game_);
	padIC_.registerListener(this);
	padEntity_->addComponent(&padIC_);
	gameObjects_.push_back(padEntity_);
	next_ = new Entity(game_);
	next_->addComponent(&nextRC_);
	next_->setHeight(NEXT_BUTTON_SIZE.getY());
	next_->setWidth(NEXT_BUTTON_SIZE.getX());
	next_->setPosition(Vector2D(game_->getWindowWidth() - next_->getWidth(),
		game_->getWindowHeight() - next_->getHeight()));
	gameObjects_.push_back(next_);

	nextRC_.waveAlpha(0, 1, 1000);
}

void PodiumState::closeState() {
	for (auto mini : mini_players_) {
		if (mini != nullptr) {
		delete mini;
		}
	}
	if (podium_ != nullptr) {
		delete podium_;
	}
	if (padEntity_ != nullptr) {
		delete padEntity_;
	}
	if (next_ != nullptr) {
		delete next_;
	}
}

void PodiumState::handleEvents(Uint32 time, const SDL_Event event) {
	if(!pause)
	 padEntity_->handleEvents(time, event);
	if (event.type && !pause) {
		if (event.type == SDL_KEYDOWN) {
			sendToGSM(&Message(STATE_POP));
			sendToGSM(&Message(STATE_POP));
			if (ending_) {
				sendToGSM(&Message(STATE_CREDITS));
			}
			else game_->sendToSM(&Message(STATE_POP_MINIGAME));
		}
	}
}

void PodiumState::update(Uint32 time)
{
	if (start) {
		start = false;
		timer.startCountdown(time, 3000);
	}
	else if (timer.checkRunning() && timer.checkCountdown(time))
		pause = false;
	GameState::update(time);
}

void PodiumState::receive(Message * msg) {
	if (msg->id_ == A && !pause)
	{
		sendToGSM(&Message(STATE_POP));
		sendToGSM(&Message(STATE_POP));
		if (ending_) {
			sendToGSM(&Message(STATE_CREDITS));
		}
		else game_->sendToSM(&Message(STATE_POP_MINIGAME));
	}
}

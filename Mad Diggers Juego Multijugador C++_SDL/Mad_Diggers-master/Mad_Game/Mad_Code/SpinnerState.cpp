#include "SpinnerState.h"

SpinnerState::SpinnerState(Game* game, MessageId* nextMinigame, int numPlayers)
	: GameState(game), nextMinigame_(nextMinigame), numPlayers_(numPlayers),
	jsonReader(game->getResources()->getJsonFile(Resources::j_Board)),

	//read const from json
#define json jsonData["Spinner"] //Macro to short

	outWorldVel_(Vector2D(json["endSpeed_"]["x"].asDouble(),
		json["endSpeed_"]["y"].asDouble())),

	miniPlayersOffset_(Vector2D(json["miniPlayersOffset_"]["x"].asDouble(),
		json["miniPlayersOffset_"]["y"].asDouble())),
	miniplayersScaleEnd_(Vector2D(json["miniplayersScaleEnd_"]["x"].asDouble(),
		json["miniplayersScaleEnd_"]["y"].asDouble())),
	miniPlayerY_(json["miniPlayerY_"].asDouble()),
	miniPlayerW_(json["miniPlayerW_"].asDouble()),
	miniPlayerH_(json["miniPlayerH_"].asDouble()),
	miniplayersScaleTime_(json["miniplayersScaleTime_"].asDouble()),

	msgY_(json["msgY_"].asDouble()),
	msgWaveMin_(json["msgWaveMin_"].asDouble()),
	msgWaveMax_(json["msgWaveMax_"].asDouble()),
	msgWaveTime_(json["msgWaveTime_"].asDouble()),

	spinnerAnimation_(game->getResources()->getSpriteSheetTexture(Resources::ss_SpinnerTime), &spinnerAnimData_, true)
{
	///end init list

	initState();

	Physical::setWorldPos(Vector2D(-game_->getWindowWidth(), 0));
	moving_ = true;
	fromLeft_ = true;
}

SpinnerState::~SpinnerState() {
	closeState();
}

void SpinnerState::initState() {
	//manager
	manager_ = new SpinnerManager(game_, this);
	gameObjects_.push_back(manager_);
	manager_->registerListener(this);

	//msg
	snpinerMsg_ = new Entity(game_);
	gameObjects_.push_back(snpinerMsg_);

	double //centered
		w = game_->getWindowWidth() * 0.6,
		h = game_->getWindowHeight() * 0.25,
		x = game_->getWindowWidth() / 2 - w / 2;

	snpinerMsg_->setPosition(Vector2D(x, msgY_));
	snpinerMsg_->setWidth(w);
	snpinerMsg_->setHeight(h);

	//spinnerMsg_RC_ = ImageRenderer(game_->getResources()->getImageTexture(Resources::i_spinnerTimeMsg), &spinnerMsgData_);
	//spinnerMsg_RC_.waveAlpha(msgWaveMin_, msgWaveMax_, msgWaveTime_);

	snpinerMsg_->addComponent(&spinnerAnimation_);

	//mini players animations
	for (size_t i = 0; i < numPlayers_; i++) {
		AnimationRenderer mini(game_->getResources()->getSpriteSheetTexture(Resources::ss_PlayerHandsMoving), &miniAnimData_, true);
		mini.setColor(Resources::getSDLColor(Resources::_DEFAULT_PLAYERS_COLORS_ID_[i]));
		mini_player_Animation_.push_back(mini);
	}

	//mini players entities
	double //centered
		wOffset = miniPlayersOffset_.getX() - miniPlayerW_,
		wTotal = (miniPlayerW_ + wOffset) * numPlayers_ - wOffset,
		xTotal = game_->getWindowWidth() / 2 - wTotal / 2;

	Vector2D topLeft(xTotal, miniPlayerY_);

	for (size_t i = 0; i < numPlayers_; i++) {
		Spinner* miniPlayer_ = new Spinner(game_);

		miniPlayer_->setPosition(topLeft + miniPlayersOffset_ * i);
		miniPlayer_->setWidth(miniPlayerW_);
		miniPlayer_->setHeight(miniPlayerH_);

		miniPlayer_->addComponent(&mini_player_Animation_[i]);
		miniPlayer_->registerListener(this);

		mini_players_.push_back(miniPlayer_);
		gameObjects_.push_back(miniPlayer_);
	}
}

void SpinnerState::closeState() {
	delete manager_;
	delete snpinerMsg_;
}

///////////////////////////////////////////////////////////////////////////////

void SpinnerState::render(Uint32 time) {
	GameState::render(time);
}

void SpinnerState::update(Uint32 time) {
	if (moving_) MoveWorld();
	else GameState::update(time);
}

void SpinnerState::handleEvents(Uint32 time, const SDL_Event event) {
	GameState::handleEvents(time, event);
}

///////////////////////////////////////////////////////////////////////////////

void SpinnerState::receive(Message* msg) {
	if (msg == nullptr) return; //shold not happen but anyway

	if (*nextMinigame_ == STATE_NULL) {
		*nextMinigame_ = msg->id_;

		for (auto miniPlayer: mini_players_) {
			miniPlayer->resizeToScale(miniplayersScaleEnd_, miniplayersScaleTime_);
		}
	}
	else switch (msg->id_) {
	case BOARD_SPINNED_SIZE:
		moving_ = true;
	}
}

void SpinnerState::MoveWorld() {
	Physical::moveWorldPos(outWorldVel_);
	double worldX = Physical::getWorldPos().getX();

	if (fromLeft_ && worldX >= 0) {
		moving_ = false;
		fromLeft_ = false;
		Physical::resetWorldPos();
	}
	else if (worldX > game_->getWindowWidth()) {
		Physical::resetWorldPos();
		sendToGSM(&Message(STATE_POP));
	}
}

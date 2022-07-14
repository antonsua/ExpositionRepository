#include "BoardState.h"

BoardState::BoardState(Game* game) :
	GameState(game, idName_),
	jsonReader(game->getResources()->getJsonFile(Resources::j_Board)),

	//read const from json
#define json jsonData["BoardState"] //Macro to short

	idName_(json["idName_"].asString()),

	_LAST_ROUND_(json["_LAST_ROUND_"].asUInt()),
	_FIRST_ROUND_(json["_FIRST_ROUND_"].asUInt()),
	_ROLLS_PER_ROUND_(json["_ROLLS_PER_ROUND_"].asUInt()),

	numPlayers_(json["numPlayers_"].asUInt()),
	numSquares_(json["numSquares_"].asUInt()),
	startMsgWaveReps_(json["startMsgWaveReps_"].asUInt()),
	startMsgWaveTime_(json["startMsgWaveTime_"].asUInt()),

	outWorldPos_(json["outWorldPos_"].asDouble()),
	outWorldVel_(Vector2D(json["outWorldVel_"]["x"].asDouble(),
		json["outWorldVel_"]["y"].asDouble())),

	startMsgWtimes_(json["startMsgWtimes_"].asDouble()),
	startMsgHtimes_(json["startMsgHtimes_"].asDouble()),
	startMsgWaveMin_(json["startMsgWaveMin_"].asDouble()),
	startMsgWaveMax_(json["startMsgWaveMax_"].asDouble()),

	topLeftRoundCounter_(Vector2D(json["topLeftRoundCounter_"]["x"].asDouble(),
		json["topLeftRoundCounter_"]["y"].asDouble())),
	roundCounterW_(json["roundCounterW_"].asDouble()),
	roundCounterH_(json["roundCounterH_"].asDouble()),

	//init managers
	playersManager_(game, numPlayers_, this),
	squaresManager_(game, numPlayers_, numSquares_, this),
	dicesManager_(game, numPlayers_, this),
	beesManager_(game, numPlayers_, this),
	padsManager_(game, numPlayers_),

	//init components
	debug_IC_(game),
	simulator_(game, numPlayers_) {
	///end init list

	//SDL_ShowCursor(0);
	//Entity::toggleDebugGlobal();

	ImageRenderer startingMsg_, endingMsg_;
	spriteData bigMsgData_;

	initState();
	initRoundCounter();
	initBigMsg();
	resetBoard();
}

BoardState::~BoardState() {
	closeState();
}

void BoardState::initState() {
	//commented debug stuff out

	///gameObjects_.push_back(&simulator_);
	gameObjects_.push_back(&squaresManager_);
	gameObjects_.push_back(&dicesManager_);
	gameObjects_.push_back(&beesManager_);
	gameObjects_.push_back(&playersManager_);
	gameObjects_.push_back(&debug_IC_);
	gameObjects_.push_back(&padsManager_);

	//for rolls, init, gameOver...
	///registerListener(&simulator_);
	registerListener(&squaresManager_);
	registerListener(&playersManager_);
	registerListener(&dicesManager_);
	registerListener(&beesManager_);
	registerListener(&debug_IC_);
	registerListener(&padsManager_);

	//bee messaging
	beesManager_.registerListener(&squaresManager_);
	squaresManager_.registerListener(&beesManager_);
	dicesManager_.registerListener(&beesManager_);

	//player turn over
	playersManager_.registerListener(this);
	playersManager_.registerListener(&dicesManager_);

	//inputs
	///simulator_.registerListener(this);
	dicesManager_.registerListener(this);
	debug_IC_.registerListener(this);
	padsManager_.registerListener(this);

	//debug logging
	///debug_IC_.registerListener(&simulator_);
	squaresManager_.registerListener(&debug_IC_);
	playersManager_.registerListener(&debug_IC_);

	//send(&Message(BOARD_INIT)); //already called in reset
}

void BoardState::initBigMsg() {
	bigMsg_ = new Entity(game_);
	gameObjects_.push_back(bigMsg_);

	double //centered
		w = game_->getWindowWidth() * startMsgWtimes_,
		h = game_->getWindowHeight() * startMsgHtimes_,
		x = game_->getWindowWidth() / 2 - w / 2,
		y = game_->getWindowHeight() / 2 - h / 2;

	bigMsg_->setPosition(Vector2D(x, y));
	bigMsg_->setWidth(w);
	bigMsg_->setHeight(h);

	bigMsgData_ = { Vector2D(1,1), Vector2D(0,0), false, true, };

	startingMsg_ = ImageRenderer(game_->getResources()->getImageTexture(Resources::i_startMsg), &bigMsgData_);
	endingMsg_ = ImageRenderer(game_->getResources()->getImageTexture(Resources::i_endMsg), &bigMsgData_);
	startingMsg_.registerListener(this);
	endingMsg_.registerListener(this);

	bigMsg_->addComponent(&startingMsg_);
	startingMsg_.setAlpha(0);
	startingMsg_.waveAlpha(startMsgWaveMin_, startMsgWaveMax_, startMsgWaveTime_, BOARD_STARTMSG_WAVE);
	starting_ = true;
}

void BoardState::initRoundCounter() {
	roundCounter_ = new Entity(game_);
	gameObjects_.push_back(roundCounter_);

	roundCounter_->setPosition(topLeftRoundCounter_);
	roundCounter_->setWidth(roundCounterW_);
	roundCounter_->setHeight(roundCounterH_);

	roundCounterMsgData_ = { Vector2D(1,1), Vector2D(0,0), false, false, };

	string msg = "Round " + to_string(_FIRST_ROUND_) + " / " + to_string(_LAST_ROUND_);
	roundCounterMsg_ = Message_RC(Resources::f_Hack_128, Resources::c_White, msg, &roundCounterMsgData_);

	roundCounter_->addComponent(&roundCounterMsg_);
}

void BoardState::closeState() {
	if (bigMsg_ != nullptr) {
		delete bigMsg_;
	}
	if (roundCounter_ != nullptr) {
		delete roundCounter_;
	}
}

///////////////////////////////////////////////////////////////////////////////

void BoardState::receive(Message* msg) {
	switch (msg->id_) {
	case BOARD_RESET:
		resetBoard();
		break;
	case BOARD_LOG_CONTROLS:
		logControls();
		break;

	case BOARD_UPDATE_PLAYERS:
		send(msg); //resend
		break;

	case BOARD_STARTMSG_WAVE:
		if (++waveCounter_ == startMsgWaveReps_) {
			waveCounter_ = 0;
			startingMsg_.stopWaveAlpha(0);
			startingMsg_.fadeToAlpha(0, startMsgWaveTime_, BOARD_STARTMSG_FADED);
		}
		break;
	case BOARD_STARTMSG_FADED:
		bigMsg_->delComponent(&startingMsg_);
		starting_ = false;
		preLaunchSpinner();
		break;

	case BOARD_ENDMSG_WAVE:
		if (++waveCounter_ == startMsgWaveReps_) {
			endingMsg_.stopWaveAlpha(0);
			endingMsg_.fadeToAlpha(0, startMsgWaveTime_, BOARD_ENDMSG_FADED);
		}
		break;
	case BOARD_ENDMSG_FADED:
		preLaunchPodium();
		break;

	case BOARD_ROLL_NumP: //individual rolls used for debug
	{
		//cast for specific msg type
		BoardMessage_numPlayerInfo* specificMsg =
			static_cast<BoardMessage_numPlayerInfo*> (msg);

		rollSquare(specificMsg->numPlayer_, !specificMsg->bees_, false);
		break;
	}

	case BOARD_SELECTED: //just roll selection w/ number of rolls
	{
		BoardMessage_DiceInfo* specificMsg =
			static_cast<BoardMessage_DiceInfo*> (msg);

		rolling_ = true;

		if (!playersTurnsOrder_.empty()) {
			for (size_t i = 0; i < specificMsg->rolls_; i++)
				rollSquare(playersTurnsOrder_.top(), false, i == specificMsg->rolls_ - 1);

			playersTurnsOrder_.pop();
		}

		//send(&Message(BOARD_POP_QUEUE)); //update queue //done asynchronously
		break;
	}

	case BOARD_ROLL_End:
		//send(&Message(BOARD_UPDATE_PLAYERS)); //update positions
		break;

	case BOARD_PLAYER_TURNOVER:
		rolling_ = false;
		send(msg, &dicesManager_);
		send(msg, &padsManager_);
		if (round_ > _LAST_ROUND_) {
			endGame();
		}
		break;

	case BOARD_END_TURN:
		if (!ending_) {
			preLaunchSpinner();
		}
		break;

	case BOARD_SELECT:
	case BOARD_UP:
	case BOARD_DOWN:
	case BOARD_RIGHT:
	case BOARD_LEFT:
		if (!rolling_ && !blockGameObjects()) send(msg, &dicesManager_);
		break;
	}
}

///////////////////////////////////////////////////////////////////

void BoardState::resetBoard() {
	round_ = _FIRST_ROUND_;
	roll_ = 0;
	paused_ = false;
	rolling_ = false;
	ending_ = false;
	fromMini_ = false;

	resetPlayersOrder();
	minigameID_ = STATE_NULL;

	send(&Message(BOARD_RESET));

	moveFromLeft();
}

void BoardState::resetPlayersOrder() {
	//empty if any left
	while (!playersTurnsOrder_.empty()) playersTurnsOrder_.pop();

	for (size_t i = 0; i < numPlayers_; i++)
		playersTurnsOrder_.push(numPlayers_ - i - 1);
}

void BoardState::rollSquare(int numPlayer, bool simulation, bool lastRoll) {
	send(&BoardMessage_RollInfo(round_, roll_));
	roll_++;

	send(&BoardMessage_PlayerInfo(playersManager_.getPlayers()[numPlayer], simulation, lastRoll));

	//std::cout << "roll: " << roll_ << " round: " << round_ << std::endl;

	if (roll_ == _ROLLS_PER_ROUND_) {
		roll_ = 0;
		round_++;

		if (round_ <= _LAST_ROUND_) {
			roundCounterMsg_.setMsg("Round " + to_string(round_) + " / " + to_string(_LAST_ROUND_));
		}
	}
}

///////////////////////////////////////////////////////////////////

void BoardState::preLaunchMinigame(MessageId msg) {
	paused_ = true;
	minigameID_ = msg;
}

void BoardState::launchMinigame() {
	while (!playersTurnsOrder_.empty()) playersTurnsOrder_.pop(); //for debugging behaviour
	sendToGSM(&StateMessage_Minigame(minigameID_, &playersTurnsOrder_));
	minigameID_ = STATE_NULL;
}

void BoardState::preLaunchSpinner() {
	moving_ = true;
}

void BoardState::launchSpinner() {
	paused_ = true;
	moving_ = false;
	Physical::resetWorldPos();
	sendToGSM(&StateMessage_Spinner(&minigameID_, numPlayers_));
}

void BoardState::endedMinigame() {
	paused_ = false;
	fromMini_ = true;

	send(&BoardMessage_ResetDices(playersTurnsOrder_.top()));
	send(&BoardMessage_QueueInfo(&playersTurnsOrder_));

	moveFromLeft();
}

///////////////////////////////////////////////////////////////////

//propagates the event and then if no one handles it, tries ti handle
void BoardState::handleEvents(Uint32 time, SDL_Event event) {
	if (blockGameObjects()) return;

	//events that need to prevent propagation are handled here
	bool propagation = true, minigame = true;
	MessageId idMini;

	if (event.type == SDL_KEYDOWN) {
		switch (event.key.keysym.sym) {
		case SDLK_KP_1:
			idMini = STATE_SUMO;
			break;
		case SDLK_KP_2:
			idMini = STATE_PONG;
			break;
		case SDLK_KP_3:
			idMini = STATE_APPLE;
			break;
		case SDLK_KP_4:
			idMini = STATE_PLATFORM;
			break;
		case SDLK_KP_5:
			idMini = STATE_RACE;
			break;
		case SDLK_KP_6:
			idMini = STATE_DODGE;
			break;
		case SDLK_KP_0:
			idMini = STATE_DEMO;
			break;

		default:
			minigame = false;
			break;
		}

		if (minigame) //need to break
		{
			propagation = false;
			preLaunchMinigame(idMini);
		}
		////launch minigame too if all dices selected
		//else if (event.key.keysym.sym == SDLK_SPACE
		//	&& playersTurnsOrder_.empty()) {
		//	propagation = false;
		//	preLaunchSpinner();
		//}
		//else
		if (event.key.keysym.sym == SDLK_m) { //debug
			propagation = false;
			preLaunchSpinner();
		}
	}
	if (propagation) {
		GameState::handleEvents(time, event);
	}
}
void BoardState::logControls() {
	cout << "//  * M : Test configured miniGame" << endl;
	cout << "//  " << endl;
}

//controls logic and calls all gameobjects' update
void BoardState::update(Uint32 time) {

	if (paused_) { //paused launch minigame - end minigame
		if (minigameID_ != STATE_NULL) { launchMinigame(); }
		else endedMinigame();
	}

	else if (moving_) moveWorld();
	else GameState::update(time);
}

void BoardState::render(Uint32 time) {
	if (paused_) return;

	GameState::render(time);
}

void BoardState::moveWorld() {
	Physical::moveWorldPos(outWorldVel_);
	double worldX = Physical::getWorldPos().getX();

	if (fromLeft_ && worldX >= 0) {
		moving_ = false;
		fromLeft_ = false;
		Physical::resetWorldPos();
		if (fromMini_) {
			fromMini_ = false;
			send(&Message(BOARD_GO_QUEUE));
		}
	}
	else if (worldX > outWorldPos_ * game_->getWindowWidth()) {
		if (ending_) {
			launchPodium();
		}
		else {
			launchSpinner();
		}
	}
}

///////////////////////////////////////////////////////////////////////////////

void BoardState::moveFromLeft() {
	moving_ = true;
	fromLeft_ = true;

	double x = outWorldPos_ * game_->getWindowWidth();
	Physical::setWorldPos(Vector2D(-x, 0));
}

void BoardState::endGame() {
	send(&BoardMessage_GameOverResults(playersManager_.getPlayersScores()));
	send(&Message(ENDING));

	bigMsg_->addComponent(&endingMsg_);
	endingMsg_.waveAlpha(startMsgWaveMin_, startMsgWaveMax_, startMsgWaveTime_, BOARD_ENDMSG_WAVE);
	ending_ = true;
}

void BoardState::preLaunchPodium() {
	moving_ = true;
	bigMsg_->delComponent(&endingMsg_);
}

void BoardState::launchPodium() {
	ending_ = false;
	moving_ = false;
	Physical::resetWorldPos();

	playersTurnsOrder_ = playersManager_.getPlayersOrdered();
	sendToGSM(&StateMessage_Minigame(STATE_PODIUM_END, &playersTurnsOrder_));
}

bool BoardState::blockGameObjects() {
	return (moving_ || paused_ || starting_ || ending_);
}
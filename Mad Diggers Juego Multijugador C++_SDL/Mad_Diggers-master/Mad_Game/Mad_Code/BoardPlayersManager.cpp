#include "BoardPlayersManager.h"

const Resources::ColorId BoardPlayersManager::_COLOR_PLAYER_NAME_TEXT_ = Resources::c_Black;

const Resources::FontId BoardPlayersManager::_F_DEFAULT_TEXT_ = Resources::f_Hack_Italic_128;
const Resources::FontId BoardPlayersManager::_F_POINTSEVENTS_ = Resources::f_Hack_128;

const Resources::ColorId BoardPlayersManager::_C_POINTS_TEXT_ = Resources::c_White;
const Resources::ColorId BoardPlayersManager::_C_POINTSEVENTS_ADD_ = Resources::c_Honey;
const Resources::ColorId BoardPlayersManager::_C_POINTSEVENTS_SUB_ = Resources::c_Grey;

///////////////////////////////////////////////////////////////////

BoardPlayersManager::BoardPlayersManager(Game* game, int numPlayers, jsonReader* jr) :
	GameObject(game),

	////init consts from json
#define json jr->read()["BoardPlayersManager"] //Macro to short

	playerWidth_(json["playerWidth_"].asUInt()),
	playerHeight_(json["playerHeight_"].asUInt()),

	boardVerticalGap_(json["boardVerticalGap_"].asUInt()),
	topLeftBoardCorner_(Vector2D(json["topLeftBoardCorner_"]["x"].asUInt(),
		json["topLeftBoardCorner_"]["y"].asUInt())),

	playerHeadScale_(Vector2D(json["playerHeadScale_"]["x"].asDouble(),
		json["playerHeadScale_"]["y"].asDouble())),
	playerHeadOffset_(Vector2D(json["playerHeadOffset_"]["x"].asDouble(),
		json["playerHeadOffset_"]["y"].asDouble())),

	pointsTextScale_(Vector2D(json["pointsTextScale_"]["x"].asDouble(),
		json["pointsTextScale_"]["y"].asDouble())),
	pointsTextOffset_(Vector2D(json["pointsTextOffset_"]["x"].asDouble(),
		json["pointsTextOffset_"]["y"].asDouble())),
	pointsEventsTextScale_(Vector2D(json["pointsEventsTextScale_"]["x"].asDouble(),
		json["pointsEventsTextScale_"]["y"].asDouble())),
	pointsEventsTextOffset_(Vector2D(json["pointsEventsTextOffset_"]["x"].asDouble(),
		json["pointsEventsTextOffset_"]["y"].asDouble())),
	pointsEventsInternOffset_(Vector2D(json["pointsEventsInternOffset_"]["x"].asDouble(),
		json["pointsEventsInternOffset_"]["y"].asDouble())),
	pointsShowUpScale_(json["pointsShowUpScale_"].asDouble()),
	pointsShowUpOffset_(json["pointsShowUpOffset_"].asDouble()),

	playerQueuedScaleX_(json["playerQueuedScaleX_"].asFloat()),
	playerQueuedScaleY_(json["playerQueuedScaleY_"].asFloat()),
	playerQueuedOffset_(Vector2D(json["playerQueuedOffset_"]["x"].asUInt(),
		json["playerQueuedOffset_"]["y"].asUInt())),
	playerQueuedBoardCorner_(Vector2D(json["playerQueuedBoardCorner_"]["x"].asUInt(),
		json["playerQueuedBoardCorner_"]["y"].asUInt())),

	bubbleOffset_(Vector2D(json["bubbleOffset_"]["x"].asDouble(),
		json["bubbleOffset_"]["y"].asDouble())),
	bubbleScale_(Vector2D(json["bubbleScale_"]["x"].asDouble(),
		json["bubbleScale_"]["y"].asDouble())),

	showUpOffset_(Vector2D(json["showUpOffset_"]["x"].asDouble(),
		json["showUpOffset_"]["y"].asDouble())),
	showUpScale_(Vector2D(json["showUpScale_"]["x"].asDouble(),
		json["showUpScale_"]["y"].asDouble())),
	showUpDelay_(json["showUpDelay_"].asInt()),

	playerInitialNumber_(json["playerInitialNumber_"].asUInt()),
	playerInitialPoints_(json["playerInitialPoints_"].asUInt()),
	playerPointsMinDigits_(json["playerPointsMinDigits_"].asUInt()),
	playerPointsEventsFadeTime_(json["playerPointsEventsFadeTime_"].asUInt()),
	playerUpdatePositionsTime_(json["playerUpdatePositionsTime_"].asUInt()),

	spinnerMsgFade_(json["spinnerMsgFade_"].asUInt()),
	spinnerAnimTimes_(json["spinnerAnimTimes_"].asUInt()),

	spinnerAnimation_(game->getResources()->getSpriteSheetTexture(Resources::ss_SpinnerTime), &spinnerAnimData_, false),

	//init variables
	numPlayers_(numPlayers) {
	///end init list

	//spinnerMsg_RC_ = ImageRenderer(game->getResources()->getImageTexture(Resources::i_spinnerTimeMsg), &spinnerMsgData_);
	//spinnerMsg_RC_.registerListener(this);

	//spinnerAnimation_ = AnimationRenderer(game->getResources()->getSpriteSheetTexture(Resources::ss_SpinnerTime), &spinnerAnimData_, false);
	spinnerAnimation_.registerListener(this);

	//points
	pointsData_.resize(numPlayers);
	points_RC_.resize(numPlayers);
	//points events
	pointsEvents_Vector_RC_.resize(numPlayers);
	pointsEventsData_.resize(numPlayers);
	for (size_t i = 0; i < numPlayers; i++)
		pointsEventsData_[i] = { pointsEventsTextScale_, pointsEventsTextOffset_ + pointsEventsInternOffset_ * i, false, false, };

	//data for msgs
	bubbleData_ = { bubbleScale_, bubbleOffset_, false, false, };
	headData_ = { playerHeadScale_, playerHeadOffset_, false, false, };

	for (size_t i = 0; i < numPlayers; i++) {
		//player heads
		ShapeRenderer head(game, Resources::s_playerHead, Resources::_DEFAULT_PLAYERS_COLORS_ID_[i], &headData_);
		head_players_RC_.push_back(head);

		//mini player animations
		AnimationRenderer mini(game->getResources()->getSpriteSheetTexture(Resources::ss_PlayerIdleNet), &miniAnimData_, true);
		mini.setColor(Resources::getSDLColor(Resources::_DEFAULT_PLAYERS_COLORS_ID_[i]));
		mini_player_Animation_.push_back(mini);

		//bubbles
		ShapeRenderer bubble(game, Resources::s_bocadillo, Resources::_DEFAULT_PLAYERS_COLORS_ID_[i], &bubbleData_);
		shape_bubble_RC_.push_back(bubble);

		//points
		pointsData_[i] = { pointsTextScale_, pointsTextOffset_, false, false, };
		points_RC_[i] = Value_RC(playerPointsMinDigits_, _F_DEFAULT_TEXT_, _C_POINTS_TEXT_, &pointsData_[i]);

		//TODO add more feedback like this
		points_RC_[i].setAlpha(0);
		points_RC_[i].fadeToAlpha(1, 3000);

		//points events
		pointsEvents_Vector_RC_[i].resize(numPlayers);
		for (size_t j = 0; j < numPlayers; j++) {
			pointsEvents_Vector_RC_[i][j] = Message_RC(_F_POINTSEVENTS_, _C_POINTSEVENTS_ADD_, "", &pointsEventsData_[j]);
			pointsEvents_Vector_RC_[i][j].toggleActive();
			pointsEvents_Vector_RC_[i][j].registerListener(this);
		}
	}
}

BoardPlayersManager::~BoardPlayersManager() {

	for (auto player : players_) {
		delete player;
	}

	for (auto playerQ : playersQueued_) {
		delete playerQ;
	}

	delete snpinerMsg_;
}

///////////////////////////////////////////////////////////////////////////////

void BoardPlayersManager::handleEvents(Uint32 time, const SDL_Event & event) {
	//for (auto player : players_)
	//{
	//	if (player->isActive()) player->handleEvents(time, event);
	//}
}

void BoardPlayersManager::update(Uint32 time) {
	for (auto player : players_) {
		if (player->isActive()) player->update(time);
	}
}

void BoardPlayersManager::render(Uint32 time) {

	for (auto player : players_) {
		if (player->isActive()) player->render(time);
	}

	for (auto playerQueued : drawingQueue_) {
		if (playerQueued->isActive()) playerQueued->render(time);
	}

	if (snpinerMsg_->isActive()) snpinerMsg_->render(time);
}

///////////////////////////////////////////////////////////////////////////////

void BoardPlayersManager::receive(Message* msg) {
	if (isActive()) switch (msg->id_) {
	case BOARD_INIT:
	case BOARD_RESET:
		initPlayers();
		initQueuedPlayers();
		break;
	case BOARD_LOG_STRING:
		send(msg);
		break;

	case ENDING:
		snpinerMsg_->toggleActive(); //no need
		break;

	case BOARD_FADE_spinner:
		send(&Message(BOARD_END_TURN));
		break;
	case ANIMATION_LOOPED:
		if (++animReps_ == spinnerAnimTimes_) {
			animReps_ = 0;
			send(&Message(BOARD_END_TURN));
		}
		break;
	case BOARD_UPDATE_QUEUE: {
		//cast for specific msg type
		BoardMessage_QueueInfo* specificMsg =
			static_cast<BoardMessage_QueueInfo*> (msg);

		spinnerAnimation_.cancel();
		snpinerMsg_->delComponent(&spinnerAnimation_);
		//spinnerMsg_RC_.setAlpha(1);

		for (size_t i = 0; i < mini_player_Animation_.size(); i++) {
			mini_player_Animation_[i].start(); //fix speed
		}

		orderDrawingQueue(*specificMsg->p_playersTurnsOrder_);
		break;
	}
	case BOARD_GO_QUEUE:
		showUpPlayer(false);
		//send(&BoardMessage_SelectorColor(showUpPlayerNumber_));
		break;

	case BOARD_ROLL_PointsEvents: {
		//cast for specific msg type
		BoardMessage_PointsEvents* specificMsg =
			static_cast<BoardMessage_PointsEvents*> (msg);

		updatePointEvents(specificMsg->points_, specificMsg->numPlayer_);
		break;
	}

	case BOARD_PLAYER_TURNOVER:
		waitingFade_ = true;
		if (waitingFade_ && pointsFading_ == 0) endPointsUpdates();
		break;
	case BOARD_ROLL_PointsFaded:
		pointsFading_--;
		if (waitingFade_ && pointsFading_ == 0) endPointsUpdates();
		break;

	case BOARD_POP_QUEUE:
		mini_player_Animation_[showUpPlayerNumber_].cancel();

		if (waitingForReverseShow_) //to start to show the next one
		{
			waitingForReverseShow_ = false;
			pointsData_[showUpPlayerNumber_].offset_ = pointsTextOffset_;
			nextTurnActions();
		}
		else if (++updatedPlayers_ == numPlayers_) { //wait for all to update
			updatedPlayers_ = 0;
			endTurnActions();
		}
		break;

	case BOARD_UPDATE_PLAYERS: //debug/unused
		updatePlayersPos();
		break;
	}
}

void BoardPlayersManager::endPointsUpdates() {
	waitingFade_ = false;
	//pointsFading_ = 0;
	updatePlayersPos();
}

void BoardPlayersManager::endTurnActions() {
	//update drawed queue
	drawingQueue_.pop_back();
	renderQueuedPlayerPos();

	//switch player back
	waitingForReverseShow_ = true;
	showUpPlayer(true);
}

void BoardPlayersManager::nextTurnActions() {
	//next player show up
	p_playersTurnsOrder_.pop();
	if (!p_playersTurnsOrder_.empty()) //check not the last
	{
		showUpPlayerNumber_ = p_playersTurnsOrder_.top();
		showUpPlayer(false);
	}
	else {
		snpinerMsg_->addComponent(&spinnerAnimation_);
		spinnerAnimation_.start();
		//spinnerMsg_RC_.fadeToAlpha(0, spinnerMsgFade_, BOARD_FADE_spinner);
	}

	//tell the board
	send(&BoardMessage_SelectorColor(showUpPlayerNumber_));
}

///////////////////////////////////////////////////////////////////////////////

void BoardPlayersManager::initPlayers() {
	waitingFade_ = false;
	waitingForReverseShow_ = false;

	setAllInactive();

	for (size_t i = 0; i < numPlayers_; i++) {
		double posX = topLeftBoardCorner_.getX();
		double posY = topLeftBoardCorner_.getY() + i * (playerHeight_ + boardVerticalGap_);
		Vector2D pos(posX, posY);

		createPlayer(i, playerInitialPoints_, pos);
	}

	//showUpPlayer(false);
}

void BoardPlayersManager::setAllInactive() {
	numOfActivePlayers_ = 0;
	for (auto player : players_) {
		player->setActive(false);
	}
}

void BoardPlayersManager::createPlayer(int numPlayer, int points, Vector2D pos) {
	BoardPlayer* tmpPlayer = getPlayer(numPlayer); //gets an inactive or new one

	tmpPlayer->setPoints(points);

	tmpPlayer->setPosition(pos);
	tmpPlayer->setWidth(playerWidth_);
	tmpPlayer->setHeight(playerHeight_);
}

///////////////////////////////////////////////////////////////////////////////

void BoardPlayersManager::initQueuedPlayers() {

	//spinner msg
	snpinerMsg_ = new Entity(game_);
	snpinerMsg_->setWidth(playerWidth_ * playerQueuedScaleX_ * (numPlayers_ - 1.5));
	snpinerMsg_->setHeight(playerHeight_ * playerQueuedScaleY_);
	snpinerMsg_->setPosition(playerQueuedBoardCorner_ + playerQueuedOffset_);
	//snpinerMsg_->addComponent(&spinnerMsg_RC_);

	//clean first
	playersQueued_.clear();
	drawingQueue_.clear();
	while (!p_playersTurnsOrder_.empty()) p_playersTurnsOrder_.pop();

	for (size_t i = 0; i < numPlayers_; i++) {
		Entity* tmp = new Entity(game_);

		tmp->setWidth(playerWidth_ * playerQueuedScaleX_);
		tmp->setHeight(playerHeight_ * playerQueuedScaleY_);

		tmp->addComponent(&mini_player_Animation_[i]);

		playersQueued_.push_back(tmp);
		drawingQueue_.push_front(tmp);
		p_playersTurnsOrder_.push(numPlayers_ - 1 - i);
	}
	showUpPlayerNumber_ = p_playersTurnsOrder_.top();
	renderQueuedPlayerPos();
}

void BoardPlayersManager::orderDrawingQueue(std::stack<int> p_playersTurnsOrder) {
	drawingQueue_.clear();
	p_playersTurnsOrder_ = p_playersTurnsOrder;
	showUpPlayerNumber_ = p_playersTurnsOrder_.top();

	while (!p_playersTurnsOrder.empty()) {
		drawingQueue_.push_front(playersQueued_[p_playersTurnsOrder.top()]);

		p_playersTurnsOrder.pop();
	}

	renderQueuedPlayerPos();
}

void BoardPlayersManager::renderQueuedPlayerPos() {
	int order = drawingQueue_.size();
	for (auto playerQueued : drawingQueue_) {
		double posX = playerQueuedBoardCorner_.getX() + order * playerQueuedOffset_.getX();
		double posY = playerQueuedBoardCorner_.getY() + order * playerQueuedOffset_.getY();
		playerQueued->setPosition(Vector2D(posX, posY));
		order--;
	}
}

///////////////////////////////////////////////////////////////////////////////

void BoardPlayersManager::showUpPlayer(bool reverse) {
	//get shorter references
	BoardPlayer* player = players_[showUpPlayerNumber_];
	spriteData* data = &pointsData_[showUpPlayerNumber_];
	Vector2D pos = player->getPosition();

	//addapt scales + move
	if (reverse) {
		//still not perfect but smoother
		data->offset_ = pointsTextOffset_ * (1 + (pointsShowUpOffset_ - 1) / 2);
		data->scale_ = pointsTextScale_;
		pos = pos - showUpOffset_;
		player->resizeToScale(Vector2D(1, 1), showUpDelay_);
	}
	else {
		data->offset_ = data->offset_ * pointsShowUpOffset_;
		data->scale_ = data->scale_ * pointsShowUpScale_;
		pos = pos + showUpOffset_;
		player->resizeToScale(showUpScale_, showUpDelay_);
	}
	player->moveToPoint(pos, showUpDelay_);
}

void BoardPlayersManager::updatePointEvents(int points, int numPlayer) {
	//when a take happens two players get involved -> only update showUp one
	if (numPlayer == showUpPlayerNumber_) {
		//get the first free msg
		Message_RC* freeMsg = nullptr;
		bool found = false;
		auto it = pointsEvents_Vector_RC_[numPlayer].begin();
		while (!found && it != pointsEvents_Vector_RC_[numPlayer].end()) {
			if (!it->isActive()) {
				freeMsg = &(*it);
				freeMsg->toggleActive();
				found = true;
			}
			else ++it;
		}

		//set msg
		if (points > 0) {
			freeMsg->setMsg("+" + to_string(points));
			freeMsg->setColor(_C_POINTSEVENTS_ADD_);
		}
		else if (points < 0) {
			freeMsg->setMsg(to_string(points));
			freeMsg->setColor(_C_POINTSEVENTS_SUB_);
		}
		else {
			freeMsg->setMsg("-0"); //better represented
			freeMsg->setColor(_C_POINTSEVENTS_SUB_);
		}

		//set effects
		pointsFading_++;
		freeMsg->setAlpha(1);
		freeMsg->fadeToAlpha(0, playerPointsEventsFadeTime_); //fade out
	}
}

void BoardPlayersManager::updatePlayersPos() {
	queue<int> playerQueue = getOrderedPlayers();
	updatedPlayers_ = 0;

	int order = 0;
	while (!playerQueue.empty()) {
		BoardPlayer* player = players_[playerQueue.front()];
		playerQueue.pop();

		double posX = player->getPosition().getX(); //preserve
		double posY = topLeftBoardCorner_.getY() + order * (playerHeight_ + boardVerticalGap_);

		//preserve position if scaled
		double diff = player->getHeight() / 2 - playerHeight_ / 2;
		//std::cout << "diff: " << diff << std::endl;
		posY -= diff;

		player->moveToPoint(Vector2D(posX, posY), playerUpdatePositionsTime_);
		order++;
	}
}

#include <algorithm> //to sort
#include<functional>
queue<int> BoardPlayersManager::getOrderedPlayers(bool reversed) {
	vector<pair<int, int>> playersNumVect; //get just number and points
	for (auto player : players_) {
		pair<int, int> pair(player->getNumPlayer(), player->getPoints());
		playersNumVect.push_back(pair);
	}

	//sort by points (inline lambda funcion)
	if (reversed) {
		sort(playersNumVect.begin(), playersNumVect.end(),
			[](const pair<int, int> & a, const pair<int, int> & b) -> bool {
			return a.second < b.second;
		});
	}
	else {
		sort(playersNumVect.begin(), playersNumVect.end(),
			[](const pair<int, int> & a, const pair<int, int> & b) -> bool {
			return a.second > b.second;
		});
	}

	//build final queue
	queue<int> playerQueue;
	for (auto pair : playersNumVect) {
		playerQueue.push(pair.first);
	}
	return playerQueue;
}

///////////////////////////////////////////////////////////////////////////////

BoardPlayer * BoardPlayersManager::getPlayer(int numPlayer) {
	numOfActivePlayers_++;
	//bool found = false; //lazy boi

	std::vector<BoardPlayer*>::iterator it = players_.begin();
	while (it != players_.end()) {
		if (!(*it)->isActive()) return resetPlayer(*it, numPlayer);
		else ++it;
	}

	//no inactive found
	BoardPlayer* tmpPlayer = new BoardPlayer(game_, numPlayer);
	tmpPlayer->addComponent(&points_RC_[numPlayer]);
	tmpPlayer->addComponent(&head_players_RC_[numPlayer]);

	for (size_t i = 0; i < numPlayers_; i++)
		tmpPlayer->addComponent(&pointsEvents_Vector_RC_[numPlayer][i]);

	tmpPlayer->registerListener(this);

	players_.push_back(tmpPlayer);
	return tmpPlayer;
}

BoardPlayer* BoardPlayersManager::resetPlayer(BoardPlayer* player, int numPlayer) {
	player->toggleActive();
	int inactiveNum = player->getNumPlayer();
	if (inactiveNum != numPlayer) {
		player->setNumPlayer(numPlayer);
		player->switchComponents(&points_RC_[inactiveNum], &points_RC_[numPlayer]);
		player->switchComponents(&head_players_RC_[inactiveNum], &head_players_RC_[numPlayer]);

		for (size_t i = 0; i < numPlayers_; i++)
			player->switchComponents(&pointsEvents_Vector_RC_[inactiveNum][i], &pointsEvents_Vector_RC_[numPlayer][i]);
	}
	return player;
}

///////////////////////////////////////////////////////////////////////////////

std::vector<BoardPlayer*>& BoardPlayersManager::getPlayers() {
	return players_;
}

std::vector<int> BoardPlayersManager::getPlayersScores() {
	vector<int> scores;

	for (auto player : players_) scores.push_back(player->getPoints());

	return scores;
}

std::stack<int> BoardPlayersManager::getPlayersOrdered() {
	stack<int> ordererd;
	queue<int> orderQueue = getOrderedPlayers(true);

	while (!orderQueue.empty()) {
		ordererd.push(orderQueue.front());
		orderQueue.pop();
	}
	return ordererd;
}

#include "BoardSquaresManager.h"

const Resources::ColorId BoardSquaresManager::_DEFAULT_SQUARES_COLOR_ID_ = Resources::c_Honey;

const Resources::FontId BoardSquaresManager::_DEFAULT_TEXT_FONT_ID_ = Resources::f_Hack_128;
const Resources::ColorId BoardSquaresManager::_DEFAULT_TEXT_COLOR_ID_ = Resources::c_Black;

//////////////////////////////////////////////////////////////////////////////

BoardSquaresManager::BoardSquaresManager(Game* game, int numPlayers, int numSquares, jsonReader* jr) :
	GameObject(game),

	//init const from json
#define json jr->read()["BoardSquaresManager"] //Macro to short

	sumPointsIfOwner_(json["sumPointsIfOwner_"].asBool()),

	squaresWidth_(json["squaresWidth_"].asUInt()),
	squaresHeight_(json["squaresHeight_"].asUInt()),

	squareTextScale_(Vector2D(json["squareTextScale_"]["x"].asDouble(),
		json["squareTextScale_"]["y"].asDouble())),
	squareTextOffset_(Vector2D(json["squareTextOffset_"]["x"].asDouble(),
		json["squareTextOffset_"]["y"].asDouble())),

	horizontalGap_(json["horizontalGap_"].asDouble()),
	verticalGap_(json["verticalGap_"].asDouble()),

	hexTiled_(json["hexTiled_"].asBool()),
	horizontalHexGap_(json["horizontalHexGap_"].asDouble()),
	verticalHexGap_(json["verticalHexGap_"].asDouble()),

	squaresInitialNumber_(json["squaresInitialNumber_"].asUInt()),

	cols_(json["cols_"].asUInt()),
	topLeftBoardCorner_(Vector2D(json["topLeftBoardCorner_"]["x"].asUInt(),
		json["topLeftBoardCorner_"]["y"].asUInt())),
	squareMinDigits_(json["squareMinDigits_"].asUInt()),

	//init variables
	numSquares_(numSquares),
	squaresColor_(Resources::getSDLColor(_DEFAULT_SQUARES_COLOR_ID_)),

	//init colors components
	rect_base_RC_(FillRectRenderer(&squaresColor_)),
	shape_base_RC_(game, Resources::s_hexagon, _DEFAULT_SQUARES_COLOR_ID_) ///TODO
{
	//init value component
	valueData_ = { squareTextScale_, squareTextOffset_, false, false, };
	value_RC_ = Value_RC(squareMinDigits_, _DEFAULT_TEXT_FONT_ID_, _DEFAULT_TEXT_COLOR_ID_, &valueData_);

	//init colors and image components
	playersColors_.resize(numPlayers);
	for (size_t i = 0; i < numPlayers; i++)
	{
		playersColors_[i] = Resources::getSDLColor(Resources::_DEFAULT_PLAYERS_COLORS_ID_[i]);
		rect_players_RC_.push_back(FillRectRenderer(&playersColors_[i]));

		ShapeRenderer shape(game, Resources::s_hexagon, Resources::_DEFAULT_PLAYERS_COLORS_ID_[i]);
		shape_players_RC_.push_back(shape);
	}
}

BoardSquaresManager::~BoardSquaresManager()
{
	for (auto square : squares_)
	{
		delete square;
	}
}

///////////////////////////////////////////////////////////////////////////////

void BoardSquaresManager::handleEvents(Uint32 time, const SDL_Event & event)
{
	//for (auto square : bees_)
	//{
	//	if (square->isActive()) square->handleEvents(time, event);
	//}
}

void BoardSquaresManager::update(Uint32 time)
{
	//for (auto square : bees_)
	//{
	//	if (square->isActive()) square->update(time);
	//}
}

void BoardSquaresManager::render(Uint32 time)
{
	for (auto square : squares_)
	{
		if (square->isActive()) square->render(time);
	}
}

///////////////////////////////////////////////////////////////////////////////

void BoardSquaresManager::receive(Message* msg)
{
	if (isActive()) switch (msg->id_)
	{
	case BOARD_INIT:
	case BOARD_RESET:
		initSquares();
		break;

	case BOARD_ROLL_P: {
		//cast for specific msh type
		BoardMessage_PlayerInfo* specificMsg =
			static_cast<BoardMessage_PlayerInfo*> (msg);

		startRoll(specificMsg->player_, specificMsg->simulation_, specificMsg->lastRoll_);
		break;
	}

	case BOARD_ROLL_BeeSquared: {
		BoardMessage_BeeSquared* specificMsg =
			static_cast<BoardMessage_BeeSquared*> (msg);

		preInteractRoll(specificMsg->bee_);
		break;
	}

	case BOARD_ROLL_BeeEnd: {
		BoardMessage_BeeFinished* specificMsg =
			static_cast<BoardMessage_BeeFinished*> (msg);

		interactRoll(specificMsg->player_, specificMsg->squareNum_, specificMsg->lastRoll_);
		break;
	}
	}
}

///////////////////////////////////////////////////////////////////

void BoardSquaresManager::startRoll(BoardPlayer * player, bool simulation, bool lastRoll)
{
	//get rnd square and its position
	int rnd = game_->getRnd(squares_.size() - 1);
	Vector2D squarePos = squares_[rnd]->getPosition();

	if (simulation) interactRoll(player, rnd, lastRoll); //directly
	else send(&BoardMessage_BeeRollInfo(player, rnd, squarePos, lastRoll));
}

void BoardSquaresManager::preInteractRoll(BoardBee * bee)
{
	BoardSquare* square = squares_[bee->getSquareNum()];
	BoardPlayer* player = bee->getOwner();

	if (square->isUnowned())
	{
		if (!square->preOwned_)
		{
			square->preOwned_ = true;
			if (!hexTiled_) square->switchComponents(&rect_base_RC_, &rect_players_RC_[player->getNumPlayer()]);
			else square->switchComponents(&shape_base_RC_, &shape_players_RC_[player->getNumPlayer()]);
			bee->squared_ = FREE;
		}
		else bee->squared_ = OWNED;

	}
	else if (square->getOwner() == player)
	{
		bee->squared_ = OWNED;
	}
	else
	{
		bee->squared_ = TAKEN;
		bee->setTakenOwner(square->getOwner());
	}
}

void BoardSquaresManager::interactRoll(BoardPlayer * player, int squareNum, bool lastRoll)
{
	BoardSquare* square = squares_[squareNum];
	send(&BoardMessage_String("\t  Square " + to_string(squareNum + squaresInitialNumber_) + " "));

	if (square->isUnowned())
	{
		send(&BoardMessage_String("(FREE) \n"));
		square->setOwner(player);
		if (lastRoll) player->setLastRoll();
		player->addPoints(square->getValue());
	}
	else if (square->getOwner() == player)
	{
		send(&BoardMessage_String("(ALREADY OWNED) \n"));
		if (sumPointsIfOwner_) player->addPoints(square->getValue());
		//else
		//{
		//	if (lastRoll) player->setLastRoll();
		//	if (lastRoll) player->sendAlreadyOwner();
		//}
		else if (lastRoll) player->forceLastRoll(); //prevent bug
	}
	else
	{
		send(&BoardMessage_String("(TAKEN) \n"));
		int pointsSubtracted = player->subtractPoints(square->getValue());

		if (pointsSubtracted == 0)
		{
			if (lastRoll) player->forceLastRoll(); //prevent bug
		}
		else
		{
			if (lastRoll) player->setLastRoll();
			square->getOwner()->addPoints(pointsSubtracted); //issue? cause unactive?
		}
	}

	send(&Message(BOARD_ROLL_End));
}

///////////////////////////////////////////////////////////////////////////////

void BoardSquaresManager::initSquares()
{
	setAllInactive();

	for (size_t i = 0; i < numSquares_; i++)
	{
		Vector2D pos;

		if (!hexTiled_)
		{
			pos.setX(topLeftBoardCorner_.getX() + getBoardCol(i) * (squaresWidth_ + horizontalGap_));
			pos.setY(topLeftBoardCorner_.getY() + getBoardFil(i) * (squaresHeight_ + verticalGap_));
		}
		else //hexagonal tiles -> odd fils offseted
		{
			pos.setX(topLeftBoardCorner_.getX() + getBoardCol(i) * (squaresWidth_ + horizontalHexGap_));
			pos.setX(pos.getX() + (getBoardFil(i) % 2) * squaresWidth_ / 2);
			pos.setY(topLeftBoardCorner_.getY() + getBoardFil(i) * (squaresHeight_ + verticalHexGap_));
		}

		int value = i + squaresInitialNumber_;

		createSquare(value, i, pos);
	}
}

void BoardSquaresManager::setAllInactive()
{
	numOfActiveSquares_ = 0;
	for (auto square : squares_)
	{
		square->setActive(false);
	}
}

void BoardSquaresManager::createSquare(int value, int boardPosition, Vector2D pos)
{
	BoardSquare* tmpSquare = getSquare(); //gets an inactive or new one

	tmpSquare->setValue(value);
	tmpSquare->setBoardPosition(boardPosition);

	tmpSquare->setPosition(pos);
	tmpSquare->setWidth(squaresWidth_);
	tmpSquare->setHeight(squaresHeight_);

	tmpSquare->preOwned_ = false; //base value
}

///////////////////////////////////////////////////////////////////////////////

BoardSquare * BoardSquaresManager::getSquare()
{
	numOfActiveSquares_++;
	//bool found = false; //lazy boi

	std::vector<BoardSquare*>::iterator it = squares_.begin();
	while (it != squares_.end())
	{
		if (!(*it)->isActive()) return resetSquare(*it);
		else ++it;
	}

	//no inactive found
	BoardSquare* tmpBoardSquare = new BoardSquare(game_);
	if (!hexTiled_) tmpBoardSquare->addComponent(&rect_base_RC_);
	else tmpBoardSquare->addComponent(&shape_base_RC_);
	tmpBoardSquare->addComponent(&value_RC_);

	squares_.push_back(tmpBoardSquare);
	return tmpBoardSquare;
}

BoardSquare * BoardSquaresManager::resetSquare(BoardSquare* square)
{
	square->toggleActive();
	if (!square->isUnowned())
	{
		const int playerNum = square->getOwner()->getNumPlayer();
		if (!hexTiled_) square->switchComponents(&rect_players_RC_[playerNum], &rect_base_RC_);
		else square->switchComponents(&shape_players_RC_[playerNum], &shape_base_RC_);
		square->setUnowned(); //remove owner
	}
	return square;
}

///////////////////////////////////////////////////////////////////////////////

int BoardSquaresManager::getBoardCol(int boardPositon)
{
	return boardPositon % cols_;
}

int BoardSquaresManager::getBoardFil(int boardPositon)
{
	return (boardPositon - getBoardCol(boardPositon)) / cols_;
}

std::vector<BoardSquare*>& BoardSquaresManager::getSquares()
{
	return squares_;
}
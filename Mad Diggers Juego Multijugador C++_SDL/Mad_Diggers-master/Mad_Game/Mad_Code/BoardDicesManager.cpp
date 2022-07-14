#include "BoardDicesManager.h"

const Resources::ColorId BoardDicesManager::_DEFAULT_DICES_COLOR_ID_ = Resources::c_Honey;
const Resources::ColorId BoardDicesManager::_DEFAULT_USED_COLOR_ID_ = Resources::c_Grey_dark;

const Resources::FontId BoardDicesManager::_DEFAULT_TEXT_FONT_ID_ = Resources::f_Hack_128;
const Resources::ColorId BoardDicesManager::_DEFAULT_MSG_NAME_TEXT_COLOR_ID_ = Resources::c_White;

const vector<Resources::ShapeId> BoardDicesManager::_DEFAULT_DICES_SHAPES_ID_ = {
	Resources::s_dice4,
	Resources::s_dice3,
	Resources::s_dice2,
	Resources::s_dice1,
};

///////////////////////////////////////////////////////////////////

BoardDicesManager::BoardDicesManager(Game* game, int numPlayers, jsonReader* jr) :
	GameObject(game),

	////init consts from json
#define json jr->read()["BoardDicesManager"] //Macro to short

	dicesWidth_(json["dicesWidth_"].asDouble()),
	dicesHeight_(json["dicesHeight_"].asDouble()),
	selectorScale_(1.1),
	selectorDelay_(250),

	boardHorizGap_(json["boardHorizGap_"].asUInt()),
	topLeftBoardCorner_(Vector2D(json["topLeftBoardCorner_"]["x"].asDouble(),
		json["topLeftBoardCorner_"]["y"].asDouble())),

	msgTextScale_(Vector2D(json["msgTextScale_"]["x"].asDouble(),
		json["msgTextScale_"]["y"].asDouble())),
	msgTextOffset_(Vector2D(json["msgTextOffset_"]["x"].asDouble(),
		json["msgTextOffset_"]["y"].asDouble())),

	rollsTextScaleX_(json["rollsTextScaleX_"].asFloat()),
	rollsTextScaleY_(json["rollsTextScaleY_"].asFloat()),
	rollsTextOffset_(Vector2D(json["rollsTextOffset_"]["x"].asDouble(),
		json["rollsTextOffset_"]["y"].asDouble())),

	rollsMinDigits_(json["rollsMinDigits_"].asUInt()),

	//init variables
	numDices_(numPlayers)
{
	//shape_selector_RC_ = ShapeRenderer(game_, Resources::s_diceSelector, _DEFAULT_USED_COLOR_ID_);
	shape_selector_RC_ = ShapeRenderer(game_, Resources::s_diceSelector, Resources::_DEFAULT_PLAYERS_COLORS_ID_[0]);
	shape_selector_RC_.setAlpha(0);
	shape_selector_RC_.fadeToAlpha(1, 2000);

	for (size_t i = 0; i < numDices_; i++) //get dices values
	{
		dicesValues_.push_back(json["diceValues_"][i].asUInt());
		shape_dices_RC_.push_back(ShapeRenderer(game_, _DEFAULT_DICES_SHAPES_ID_[i], _DEFAULT_DICES_COLOR_ID_));
	}

	//msg component
	textMsgData_ = { msgTextScale_, msgTextOffset_, false, false, };
	text_msg_RC_ = Message_RC(_DEFAULT_TEXT_FONT_ID_, _DEFAULT_MSG_NAME_TEXT_COLOR_ID_, json["msgText_"].asString(), &textMsgData_);
	text_msg_RC_.waveAlpha(0.75, 1, 2000);
}

BoardDicesManager::~BoardDicesManager()
{
	for (auto dices : dices_)
	{
		delete dices;
	}

	delete selector_;
	delete msg_;
}

///////////////////////////////////////////////////////////////////////////////

void BoardDicesManager::handleEvents(Uint32 time, const SDL_Event & event)
{
	//for (auto dices : dicess_)
	//{
	//	if (dices->isActive()) dices->handleEvents(time, event);
	//}
}

void BoardDicesManager::update(Uint32 time)
{
	//for (auto dices : dicess_)
	//{
	//	if (dices->isActive()) dices->update(time);
	//}
	if (selector_->isActive()) selector_->update(time);
}

void BoardDicesManager::render(Uint32 time)
{
	for (auto dices : dices_)
	{
		if (dices->isActive()) dices->render(time);
	}

	if (msg_->isActive()) msg_->render(time);
	if (selector_->isActive()) selector_->render(time);
}

///////////////////////////////////////////////////////////////////////////////

void BoardDicesManager::receive(Message* msg)
{
	if (isActive()) switch (msg->id_)
	{
	case BOARD_INIT:
	case BOARD_RESET:
		initDices();
		break;
	case BOARD_RESET_DICES:
		shape_selector_RC_.setColor(
			Resources::_DEFAULT_PLAYERS_COLORS_ID_[static_cast<BoardMessage_SelectorColor*> (msg)->playerNumber_]);
		initDices();
		break;

	case BOARD_RIGHT: {
		if (selectedDices_ == numDices_) break;

		numSelected_++;
		if (numSelected_ == numDices_) numSelected_ = 0;
		selector_->moveToPoint(getUpdatedSelectorPos(), selectorDelay_);

		break;
	}
	case BOARD_LEFT: {
		if (selectedDices_ == numDices_) break;

		numSelected_--;
		if (numSelected_ < 0) numSelected_ = numDices_ - 1;
		selector_->moveToPoint(getUpdatedSelectorPos(), selectorDelay_);
		break;
	}
	case BOARD_SELECT: {
		if (select())
		{
			selectedDices_++;
			Vector2D dicePos = dices_[numSelected_]->getPosition();
			send(&BoardMessage_BeeSpawnPoint(&dicePos));
			send(&BoardMessage_DiceInfo(dices_[numSelected_]->getRolls()));
			shape_selector_RC_.setColor(_DEFAULT_USED_COLOR_ID_);
		}
		break;
	}
	case BOARD_PLAYER_TURNOVER:
		if (selectedDices_ == numDices_) break;
		BoardMessage_SelectorColor * specificMsg =
			static_cast<BoardMessage_SelectorColor*> (msg);

		shape_selector_RC_.setColor(Resources::_DEFAULT_PLAYERS_COLORS_ID_[specificMsg->playerNumber_]);
		break;
	}
}

///////////////////////////////////////////////////////////////////////////////

void BoardDicesManager::initMsg()
{
	msg_ = new Entity(game_);
	msg_->addComponent(&text_msg_RC_);

	msg_->setWidth(dicesWidth_ * msgTextScale_.getX());
	msg_->setHeight(dicesHeight_ * msgTextScale_.getY());

	BoardDice* d = dices_[0]; //first dice
	double w = d->getWidth();
	double h = d->getHeight();

	//the components has offset already, but this corrects based on dice size
	msg_->setPosition(d->getPosition() + Vector2D(w / 2, -h / 2));
}

void BoardDicesManager::initSelector()
{
	numSelected_ = 0;
	selector_ = new Entity(game_);
	//selector_->addComponent(&rect_selection_RC_);

	selector_->addComponent(&shape_selector_RC_);

	selector_->setWidth(dicesWidth_);
	selector_->setHeight(dicesHeight_);

	selector_->setScale(Vector2D(selectorScale_, selectorScale_));

	selector_->setPosition(getUpdatedSelectorPos());
}

Vector2D BoardDicesManager::getUpdatedSelectorPos()
{
	BoardDice* d = dices_[numSelected_];

	double w = selector_->getWidth() - d->getWidth();
	double h = selector_->getHeight() - d->getHeight();

	double x = d->getPosition().getX() - w / 2;
	double y = d->getPosition().getY() - h / 2;

	return Vector2D(x, y);
}

bool BoardDicesManager::select()
{
	BoardDice* d = dices_[numSelected_];

	//if not used
	bool use = false;
	if (!d->isUsed())
	{
		use = true;
		d->setUsed(true);
		shape_dices_RC_[numSelected_].setColor(_DEFAULT_USED_COLOR_ID_);
	}
	return use;
}

///////////////////////////////////////////////////////////////////////////////

void BoardDicesManager::initDices()
{
	setAllInactive();
	selectedDices_ = 0;

	for (size_t i = 0; i < numDices_; i++)
	{
		double posX = topLeftBoardCorner_.getX() + i * (dicesWidth_ + boardHorizGap_);
		double posY = topLeftBoardCorner_.getY();
		Vector2D pos(posX, posY);

		createDice(i, false, pos);
	}

	initSelector();
	initMsg();
}

void BoardDicesManager::setAllInactive()
{
	numOfActiveDices_ = 0;
	for (auto dices : dices_)
	{
		dices->setActive(false);
	}
}

void BoardDicesManager::createDice(int numDice, bool used, Vector2D pos)
{
	BoardDice* tmpDice = getDice(numDice); //gets an inactive or new one

	tmpDice->setUsed(used);
	tmpDice->setRolls(dicesValues_[numDice]);

	tmpDice->setPosition(pos);
	tmpDice->setWidth(dicesWidth_);
	tmpDice->setHeight(dicesHeight_);
}

///////////////////////////////////////////////////////////////////////////////

BoardDice * BoardDicesManager::getDice(int numDice)
{
	numOfActiveDices_++;
	//bool found = false; //lazy boi

	std::vector<BoardDice*>::iterator it = dices_.begin();
	while (it != dices_.end())
	{
		if (!(*it)->isActive()) return resetDice(*it, numDice);
		else ++it;
	}

	//no inactive found
	BoardDice* tmpDice = new BoardDice(game_);
	tmpDice->addComponent(&shape_dices_RC_[numDice]);

	dices_.push_back(tmpDice);
	return tmpDice;
}

BoardDice* BoardDicesManager::resetDice(BoardDice* dice, int numDice)
{
	dice->toggleActive();
	dice->delAllComponents(); //in this case we can

	shape_dices_RC_[numDice].setColor(_DEFAULT_DICES_COLOR_ID_); //recolor
	dice->addComponent(&shape_dices_RC_[numDice]);

	return dice;
}

///////////////////////////////////////////////////////////////////////////////

std::vector<BoardDice*>& BoardDicesManager::getDices()
{
	return dices_;
}

#include "BoardBeesManager.h"

//////////////////////////////////////////////////////////////////////////////

BoardBeesManager::BoardBeesManager(Game* game, int numPlayers, jsonReader* jr) :
	GameObject(game),

	//init const from json
#define json jr->read()["BoardBeesManager"] //Macro to short

	beesWidth_(json["beesWidth_"].asUInt()),
	beesHeight_(json["beesHeight_"].asUInt()),
	beesDir_(Vector2D(json["beesDir_"]["x"].asInt(),
		json["beesDir_"]["y"].asInt())),

	beesTime_(json["beesTime_"].asUInt()),
	complexMove_(json["complexMove_"].asBool()),

	beesRepMin_(json["beesRepMin_"].asUInt()),
	beesRepMax_(json["beesRepMax_"].asUInt()),

	beesRotMin_(json["beesRotMin_"].asUInt()),
	beesRotMax_(json["beesRotMax_"].asUInt()),
	beesDisMin_(json["beesDisMin_"].asUInt()),
	beesDisMax_(json["beesDisMax_"].asUInt()),

	topLeftCorner_(Vector2D(json["topLeftCorner_"]["x"].asUInt(),
		json["topLeftCorner_"]["y"].asUInt())),
	botRightCorner_(Vector2D(json["botRightCorner_"]["x"].asUInt(),
		json["botRightCorner_"]["y"].asUInt())),

	bubbleOffset_(Vector2D(json["bubbleOffset_"]["x"].asDouble(),
		json["bubbleOffset_"]["y"].asDouble())),
	bubbleScale_(Vector2D(json["bubbleScale_"]["x"].asDouble(),
		json["bubbleScale_"]["y"].asDouble())),

	resizeScale_(Vector2D(json["resizeScale_"]["x"].asDouble(),
		json["resizeScale_"]["y"].asDouble())),
	resizeTime_(json["resizeTime_"].asUInt()),

	spawnPoint_(Vector2D(json["spawnPoint_"]["x"].asUInt(),
		json["spawnPoint_"]["y"].asUInt())),

	lastMovesMargin_(json["lastMovesMargin_"].asDouble())
{
	bubbleData_ = { bubbleScale_, bubbleOffset_, false, false, };

	shape_honey_bee_RC_ = ShapeRenderer(game, Resources::s_bee, Resources::c_Honey);

	//init colors and image components
	for (size_t i = 0; i < numPlayers; i++)
	{
		ShapeRenderer shape(game, Resources::s_bee, Resources::_DEFAULT_PLAYERS_COLORS_ID_[i]);
		shape_bees_RC_.push_back(shape);
		ShapeRenderer bubble(game, Resources::s_bocadillo, Resources::_DEFAULT_PLAYERS_COLORS_ID_[i], &bubbleData_);
		shape_bubble_RC_.push_back(bubble);
	}
}

BoardBeesManager::~BoardBeesManager()
{
	for (auto bee : bees_)
	{
		delete bee;
	}
}

///////////////////////////////////////////////////////////////////////////////

void BoardBeesManager::handleEvents(Uint32 time, const SDL_Event & event)
{
	if (!debug_) return;
	//for (auto bee : bees_)
	//{
	//	if (bee->isActive()) bee->handleEvents(time, event);
	//}

	if (event.type == SDL_MOUSEBUTTONDOWN && !bees_.empty()) //for testing moveToPoint
	{
		SDL_Point p;

		//left click only last
		if (SDL_GetMouseState(&p.x, &p.y) & SDL_BUTTON(SDL_BUTTON_LEFT)) {
			bees_.back()->setRepetitions(beesRepMin_);
			bees_.back()->moveToPoint(Vector2D(p.x, p.y), beesTime_);
		}

		//right click all bees
		if (SDL_GetMouseState(&p.x, &p.y) & SDL_BUTTON(SDL_BUTTON_RIGHT)) {
			for (auto bee : bees_)
			{
				if (bee->isActive())
				{
					bee->setRepetitions(beesRepMin_);
					bee->moveToPoint(Vector2D(p.x, p.y), beesTime_);
				}
			}
		}
	}
}

void BoardBeesManager::update(Uint32 time)
{
	for (auto bee : bees_)
	{
		if (bee->isActive()) bee->update(time);
	}
}

void BoardBeesManager::render(Uint32 time)
{
	for (auto bee : bees_)
	{
		if (bee->isActive()) bee->render(time);
	}
}

///////////////////////////////////////////////////////////////////////////////

void BoardBeesManager::receive(Message* msg)
{
	if (isActive()) switch (msg->id_)
	{
	case BOARD_INIT:
	case BOARD_RESET:
	case BOARD_RESET_DICES:
		initBees();
		break;

	case BOARD_ROLL_BeeSpawn: {
		//cast for specific msh type
		BoardMessage_BeeSpawnPoint* specificMsg =
			static_cast<BoardMessage_BeeSpawnPoint*> (msg);

		spawnPoint_ = *specificMsg->pos_;
		break;
	}

	case BOARD_ROLL_Bee: {
		//cast for specific msh type
		BoardMessage_BeeRollInfo* specificMsg =
			static_cast<BoardMessage_BeeRollInfo*> (msg);

		flyingBees_++;
		createBee(specificMsg->pos_, specificMsg->squareNum_, specificMsg->player_, specificMsg->lastRoll_);
		break;
	}

	case BOARD_BEE_Reached: {
		BoardMessage_BeeReached* specificMsg =
			static_cast<BoardMessage_BeeReached*> (msg);

		endBeeMove(specificMsg->bee_);
		break;
	}

	case BOARD_BEE_Resize: {
		BoardMessage_BeeResized* specificMsg =
			static_cast<BoardMessage_BeeResized*> (msg);
		endBeeResize(specificMsg->bee_, false);
		break;
	}
	case BOARD_BEE_ResetSize: {
		BoardMessage_BeeResetSize* specificMsg =
			static_cast<BoardMessage_BeeResetSize*> (msg);

		//if already owned do nothing
		if (specificMsg->bee_->squared_ != OWNED) endBeeResize(specificMsg->bee_, true);
		break;
	}
	}
}

void BoardBeesManager::setGotoPos(BoardBee * bee)
{
	switch (bee->getRepetitions())
	{
	case 0: //already there
		endBeeDance(bee);
		break;

	case 1: //last one
		bee->moveSmoothToPoint(bee->getSquarePos(), 2 * beesTime_);
		break;

	default:
		Vector2D p;

		//random one (very limited w/ rotation and distance)
		if (complexMove_) p = getDefinitivePoint(bee);
		else p = getSimplePosition(bee); //or simpler

		bee->moveSmoothToPoint(p, beesTime_);
		break;
	}
}

void BoardBeesManager::endBeeDance(BoardBee * bee)
{
	bee->resizeToScale(resizeScale_, resizeTime_);
}

void BoardBeesManager::endBeeResize(BoardBee * bee, bool ending)
{
	if (ending) //resized back to normal
	{
		//move to a point in the middle
		bee->moveSmoothToPoint(midPoint(lastMovesMargin_), beesTime_ / 2);
	}
	else //reached the minimun size
	{
		send(&BoardMessage_BeeSquared(bee)); //board sets the bee squared

		switch (bee->squared_)
		{
		case FREE:
			bee->switchComponents( //switch color to honey
				&shape_bees_RC_[bee->getOwner()->getNumPlayer()],
				&shape_honey_bee_RC_);
			bee->resizeToScale(Vector2D::_UNIT_, resizeTime_);
			break;

		case TAKEN:
			bee->switchComponents(  //switch color to takenOwner
				&shape_bees_RC_[bee->getOwner()->getNumPlayer()],
				&shape_bees_RC_[bee->getTakenOwner()->getNumPlayer()]);
			bee->resizeToScale(Vector2D(1.35, 1.35), resizeTime_);
			break;

		case OWNED: //do not even resiza
			flyingBees_--;
			send(&BoardMessage_BeeFinished(bee->getOwner(), bee->getSquareNum(), flyingBees_ == 0));
			break;
		}
	}
}

void BoardBeesManager::endBeeMove(BoardBee * bee)
{
	if (bee->squared_ == FLYING) setGotoPos(bee); //normal flying
	else
	{
		if (!bee->isLastMove()) //reached the middle
		{
			double w = bee->getOwner()->getWidth(), h = bee->getOwner()->getHeight();
			Vector2D pos(w / 2 - bee->getWidth() / 2, h / 2 - bee->getHeight() / 2);
			pos = pos + bee->getOwner()->getPosition(); //get player-bee centered pos

			bee->setCloseEnough(h / 2); //loose
			bee->moveSmoothToPoint(pos, beesTime_);

			bee->setLastMove(true);
		}
		else //finally reached the player
		{
			if (bee->squared_ != FREE) //but yet have to move to the next one
			{
				double
					margin = 3,
					w = bee->getTakenOwner()->getWidth(),
					h = bee->getTakenOwner()->getHeight();
				Vector2D pos(w / margin - bee->getWidth() / margin, h / margin - bee->getHeight() / margin);
				pos = pos + bee->getTakenOwner()->getPosition(); //get player center pos


				if (bee->squared_ != OWNED) //first move to the left and change color
				{
					bee->setVelocity(Vector2D(1, bee->getVelocity().getY() / 2)); //modify path

					bee->setCloseEnough(h); //looser
					pos.setX(pos.getX() - w * 4);
					bee->moveSmoothToPoint(pos, beesTime_);

					bee->switchComponents( //switch color to honey
						&shape_bees_RC_[bee->getTakenOwner()->getNumPlayer()],
						&shape_honey_bee_RC_);

					bee->squared_ = OWNED;
				}
				else //finally to the center of the player
				{
					bee->setCloseEnough(h / 2); //loose
					bee->moveSmoothToPoint(pos, beesTime_);
					bee->squared_ = FREE;
				}
			}
			else
			{
				flyingBees_--;
				send(&BoardMessage_BeeFinished(bee->getOwner(), bee->getSquareNum(), flyingBees_ == 0));
				bee->toggleActive();
			}
		}
	}
}

///////////////////////////////////////////////////////////////////////////////

Vector2D BoardBeesManager::getSimplePosition(BoardBee * bee)
{
	Vector2D p;
	const sector s = bee->sector_, ls = bee->lastSector_; //based on sector and lastSector

	const double
		minX = topLeftCorner_.getX(),
		maxX = botRightCorner_.getX(),
		midX = minX + (maxX - minX) / 2,
		minY = topLeftCorner_.getY(),
		maxY = botRightCorner_.getY(),
		midY = minY + (maxY - minY) / 2;

	//simpler
	if ((s == np && ls == pp) || (s == pp && ls == np))
	{
		p = Vector2D(game_->getRnd(minX, maxX),
			game_->getRnd(midY, maxY));

		if (p.getX() > midX) bee->sector_ = pn;
		else bee->sector_ = nn;
	}
	else if ((s == nn && ls == pn) || (s == pn && ls == nn))
	{
		p = Vector2D(game_->getRnd(minX, maxX),
			game_->getRnd(minY, midY));

		if (p.getX() > midX) bee->sector_ = pp;
		else bee->sector_ = np;
	}
	else if ((s == np && ls == nn) || (s == nn && ls == np))
	{
		p = Vector2D(game_->getRnd(midX, maxX),
			game_->getRnd(minY, maxY));

		if (p.getY() > midY) bee->sector_ = pn;
		else bee->sector_ = pp;
	}
	else if ((s == pp && ls == pn) || (s == pn && ls == pp))
	{
		p = Vector2D(game_->getRnd(minX, midX),
			game_->getRnd(minY, maxY));

		if (p.getY() > midY) bee->sector_ = nn;
		else bee->sector_ = np;
	}

	//diagonals
	else if ((s == np && ls == pn) || (s == pn && ls == np))
	{
		double x = game_->getRnd(minX, maxX);
		if (x > midX)
		{
			p = Vector2D(x, game_->getRnd(minY, midY));
			bee->sector_ = pp;
		}
		else
		{
			p = Vector2D(x, game_->getRnd(midY, maxY));
			bee->sector_ = nn;
		}
	}
	else if ((s == nn && ls == pp) || (s == pp && ls == nn))
	{
		double x = game_->getRnd(minX, maxX);
		if (x > midX)
		{
			p = Vector2D(x, game_->getRnd(midY, maxY));
			bee->sector_ = pn;
		}
		else
		{
			p = Vector2D(x, game_->getRnd(minY, midY));
			bee->sector_ = np;
		}
	}

	bee->lastSector_ = s;
	return p;
}

bool BoardBeesManager::isInside(Vector2D point)
{
	double x = point.getX(), y = point.getY();

	return (topLeftCorner_.getX() < x && botRightCorner_.getX() > x)
		&& (topLeftCorner_.getY() < y && botRightCorner_.getY() > y);
}

Vector2D BoardBeesManager::getDefinitivePoint(BoardBee * bee)
{
	Vector2D p;
	do {
		// do-while the point is inside (very case-optimized chill)
		// basically checks a rnd point in 4 cones (front, side, other side, back)

		//if the bee is too close to a wall, easily gets away with any side cone
		//if it is corenerd, the back cone does the job

		double dis = game_->getRnd(beesDisMin_, beesDisMax_);

		//get rnd rotation
		int sign = 1 - 2 * game_->getRnd(1); // 1 or -1
		double rotation = sign * game_->getRnd(beesRotMin_, beesRotMax_);

		p = getPoint(bee, dis, rotation); //basic point in frontal cone

		if (!isInside(p)) //if not inside
		{
			//first try max rot w/ half the distance
			dis /= 2;
			rotation = beesRotMax_ * sign;
			p = getPoint(bee, dis, rotation);

			if (!isInside(p))
			{
				//almost perperdicular w/ inversed sign
				dis = game_->getRnd(beesDisMin_, beesDisMax_);
				rotation = (90 + game_->getRnd(beesRotMin_, beesRotMax_)) * -sign;
				p = getPoint(bee, dis, rotation);

				if (!isInside(p))
				{
					//inversed cone
					dis = -game_->getRnd(beesDisMin_, beesDisMax_);
					rotation = sign * game_->getRnd(beesRotMin_, beesRotMax_);
					p = getPoint(bee, dis, rotation);
				}
			}
		}
	} while (!isInside(p));

	//std::cout << "^gud" << std::endl << std::endl;
	return p;
}

#include <math.h>
#define M_TO_RADIANS 2 * M_PI / 360

//could be a Vector2D method
Vector2D BoardBeesManager::getPoint(BoardBee * bee, double dis, double rot)
{
	//apply to direction
	Vector2D dir = bee->getDirection();
	dir.rotate(rot);

	//get relative components based on dir angle
	double angle = dir.angle(Vector2D::getDefaultZeroAngle());
	double xRelative = dis * cos(angle * M_TO_RADIANS);
	double yRelative = -dis * sin(angle * M_TO_RADIANS);

	//get real point applying relative components to bee position
	Vector2D point(bee->getPosition().getX() + xRelative, bee->getPosition().getY() + yRelative);

	//std::cout << std::endl << "p: " << point << " - rot" << rot << " - dis" << dis << std::endl;
	return point;
}

Vector2D BoardBeesManager::midPoint(double margin)
{
	//send to the middle of the board (little rnd margin)
	const double
		minX = botRightCorner_.getX() / 2 - margin,
		maxX = botRightCorner_.getX() / 2 + margin,
		minY = botRightCorner_.getY() / 2 - margin,
		maxY = botRightCorner_.getY() / 2 + margin;

	return Vector2D(game_->getRnd(minX, maxX), game_->getRnd(minY, maxY));
}

///////////////////////////////////////////////////////////////////////////////

void BoardBeesManager::initBees()
{
	setAllInactive();
}

void BoardBeesManager::setAllInactive()
{
	numOfActiveBees_ = 0;
	for (auto bee : bees_)
	{
		bee->setActive(false);
		bee->cancelMovement();
	}
}

void BoardBeesManager::createBee(Vector2D squarePos, int squareNum, BoardPlayer* player, bool lastBee)
{
	BoardBee* tmpBee = getBee(player->getNumPlayer()); //gets an inactive or new one

	tmpBee->setOwner(player);
	tmpBee->setSquarePos(squarePos);
	tmpBee->setSquareNum(squareNum);
	tmpBee->setLastBee(lastBee);

	tmpBee->setPosition(spawnPoint_);
	tmpBee->setWidth(beesWidth_);
	tmpBee->setHeight(beesHeight_);
	tmpBee->setDirection(beesDir_);

	tmpBee->setScale(Vector2D::_UNIT_);

	//starting values
	tmpBee->setLastMove(false);
	tmpBee->lastSector_ = pn;
	tmpBee->sector_ = nn;
	tmpBee->squared_ = FLYING;
	tmpBee->setCloseEnough(0); //quick reset

	int r = game_->getRnd(beesRepMin_, beesRepMax_);
	//std::cout << r << std::endl;
	tmpBee->setRepetitions(r);
	setGotoPos(tmpBee);
}

///////////////////////////////////////////////////////////////////////////////

BoardBee * BoardBeesManager::getBee(int numPlayer)
{
	numOfActiveBees_++;
	//bool found = false; //lazy boi

	std::vector<BoardBee*>::iterator it = bees_.begin();
	while (it != bees_.end())
	{
		if (!(*it)->isActive()) return resetBee(*it, numPlayer);
		else ++it;
	}

	//no inactive found
	BoardBee* tmpBee = new BoardBee(game_);
	tmpBee->addComponent(&shape_bees_RC_[numPlayer]);

	tmpBee->registerListener(this); //only once
	bees_.push_back(tmpBee);
	return tmpBee;
}

BoardBee * BoardBeesManager::resetBee(BoardBee* bee, int numPlayer)
{
	bee->toggleActive();

	int oldNumPlayer = bee->getOwner()->getNumPlayer();
	bee->delComponent(&shape_bees_RC_[oldNumPlayer]);	//if exist
	bee->delComponent(&shape_honey_bee_RC_);			//one or the other
	bee->addComponent(&shape_bees_RC_[numPlayer]);

	return bee;
}

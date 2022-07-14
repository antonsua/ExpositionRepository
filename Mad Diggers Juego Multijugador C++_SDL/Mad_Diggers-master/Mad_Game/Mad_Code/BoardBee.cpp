#include "BoardBee.h"


BoardBee::BoardBee(Game* game) : Entity(game)
{
	//toggleDebugSingle();
}

BoardBee::~BoardBee()
{
}

///////////////////////////////////////////////////////////////////

void BoardBee::setSquarePos(Vector2D squarePos)
{
	squarePos_ = squarePos;
}

Vector2D BoardBee::getSquarePos()
{
	return squarePos_;
}

void BoardBee::setSquareNum(int squareNum)
{
	squareNum_ = squareNum;
}

int BoardBee::getSquareNum()
{
	return squareNum_;
}

//////////////////////////////////////////////////////////////////////////////

void BoardBee::setOwner(BoardPlayer* player)
{
	owner_ = player;
	setTakenOwner(player);
}
void BoardBee::setTakenOwner(BoardPlayer * player)
{
	takenOwner_ = player;
}
BoardPlayer * BoardBee::getOwner()
{
	return owner_;
}

BoardPlayer * BoardBee::getTakenOwner()
{
	return takenOwner_;
}

bool BoardBee::isUnowned()
{
	return owner_ == nullptr;
}

void BoardBee::setUnowned()
{
	owner_ = nullptr;
}

//////////////////////////////////////////////////////////////////////////////

void BoardBee::setRepetitions(int repetitions)
{
	repetitions_ = repetitions;
}

int BoardBee::getRepetitions()
{
	return repetitions_;
}

void BoardBee::setLastBee(bool lastBee)
{
	lastBee_ = lastBee;
}

bool BoardBee::isLastBee()
{
	return lastBee_;
}

void BoardBee::setLastMove(bool lastMove)
{
	lastMove_ = lastMove;
}

bool BoardBee::isLastMove()
{
	return lastMove_;
}

void BoardBee::endMovement(bool timeOut)
{
	//if its the last we cannot just stop even if too much time
	if (repetitions_ == 1 && timeOut) repetitions_++;
	else repetitions_--;

	send(&BoardMessage_BeeReached(this));
}

void BoardBee::endResizing()
{
	if (scale_ >= Vector2D::_UNIT_)
		send(&BoardMessage_BeeResetSize(this));
	else send(&BoardMessage_BeeResized(this));
}

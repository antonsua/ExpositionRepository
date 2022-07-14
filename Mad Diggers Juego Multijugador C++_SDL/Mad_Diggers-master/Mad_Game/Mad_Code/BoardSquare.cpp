#include "BoardSquare.h"
#include "BoardState.h" //for debug mode

///////////////////////////////////////////////////////////////////

BoardSquare::BoardSquare(Game* game) : Entity(game), owner_(nullptr)
{
}

BoardSquare::~BoardSquare()
{
}

///////////////////////////////////////////////////////////////////

void BoardSquare::setValue(int value)
{
	value_ = value;
}
int BoardSquare::getValue()
{
	return value_;
}

void BoardSquare::setBoardPosition(int boardPos)
{
	boardPosition_ = boardPos;
}
int BoardSquare::getBoardPosition()
{
	return boardPosition_;
}

///////////////////////////////////////////////////////////////////

void BoardSquare::setOwner(BoardPlayer* player)
{
	owner_ = player;
}
BoardPlayer* BoardSquare::getOwner()
{
	return owner_;
}

bool BoardSquare::isUnowned()
{
	return owner_ == nullptr;
}

void BoardSquare::setUnowned()
{
	owner_ = nullptr;
}

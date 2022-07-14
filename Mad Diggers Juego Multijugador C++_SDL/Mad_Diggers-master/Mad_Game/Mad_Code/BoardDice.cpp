#include "BoardDice.h"


BoardDice::BoardDice(Game* game) : Entity(game), used_(false)
{
}

BoardDice::~BoardDice()
{
}

//////////////////////////////////////////////////////////////////////////////

int BoardDice::getRolls()
{
	return rolls_;
}

void BoardDice::setRolls(int rolls)
{
	rolls_ = rolls;
}

bool BoardDice::isUsed()
{
	return used_;
}

void BoardDice::setUsed(bool b)
{
	used_ = b;
}
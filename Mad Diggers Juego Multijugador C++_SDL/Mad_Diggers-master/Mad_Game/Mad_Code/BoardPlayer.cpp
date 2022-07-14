#include "BoardPlayer.h"
#include "BoardSquare.h" //fowarded

#include "BoardState.h" //for debug mode

///////////////////////////////////////////////////////////////////

BoardPlayer::BoardPlayer(Game* game, int numPlayer) : Entity(game),
numPlayer_(numPlayer), boardPlacePosition_(numPlayer_)
{
}

BoardPlayer::~BoardPlayer()
{
}

void BoardPlayer::update(Uint32 time)
{
	updatePoints(time);
	Entity::update(time);
}

#define MS_IN_SECOND 1000 //ms
void BoardPlayer::updatePoints(Uint32 time)
{
	if (showPoints_ != realPoints_)
	{
		//check duration for delta
		if (timer_ == 0) timer_ = time;
		else
		{
			Uint32 delta = time - timer_;
			timer_ = time;

			if (addingUpdate_)
			{
				if (showPoints_ > realPoints_) showPoints_ = realPoints_;
				else showPoints_ += (updatePoints_perSecond_ / MS_IN_SECOND) * delta;
			}
			else
			{
				if (showPoints_ < realPoints_) showPoints_ = realPoints_;
				else showPoints_ -= (updatePoints_perSecond_ / MS_IN_SECOND) * delta;
			}

			if (showPoints_ == realPoints_) endUpdatePoints();
		}
	}
}

void BoardPlayer::endUpdatePoints()
{
	timer_ = 0;
	if (lastRoll_)
	{
		lastRoll_ = false;
		send(&Message(BOARD_PLAYER_TURNOVER)); //update positions
	}
}

///////////////////////////////////////////////////////////////////

void BoardPlayer::addPoints(int pointsToAdd)
{
	send(&BoardMessage_String("\t\t* P" + to_string(numPlayer_) + ": " + to_string(realPoints_)));

	realPoints_ += pointsToAdd;

	send(&BoardMessage_String(" + " + to_string(pointsToAdd) + " -> " + to_string(realPoints_) + "\n"));
	send(&BoardMessage_PointsEvents(pointsToAdd, numPlayer_));
}

int BoardPlayer::subtractPoints(int pointsToSub)
{
	send(&BoardMessage_String("\t\t* P" + to_string(numPlayer_) + ": " + to_string(realPoints_)));

	int pointsSubtracted = pointsToSub;
	realPoints_ -= pointsToSub;

	if (realPoints_ < 0) {
		pointsSubtracted = pointsToSub + realPoints_;
		realPoints_ = 0;
	}

	send(&BoardMessage_String(" - " + to_string(pointsSubtracted) + " -> " + to_string(realPoints_) + "\n"));
	send(&BoardMessage_PointsEvents(-pointsSubtracted, numPlayer_));
	return pointsSubtracted;
}

void BoardPlayer::sendAlreadyOwner()
{
	send(&Message(BOARD_ROLL_PointsOwned));
}

int BoardPlayer::getPoints()
{
	return (int)showPoints_;
}

void BoardPlayer::setPoints(int points)
{
	showPoints_ = points;
	realPoints_ = points;
}

///////////////////////////////////////////////////////////////////

void BoardPlayer::setNumPlayer(int numPlayer)
{
	numPlayer_ = numPlayer;
}

int BoardPlayer::getNumPlayer()
{
	return numPlayer_;
}

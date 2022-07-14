//Mad_Diggers

#ifndef BOARDBEE_H_
#define BOARDBEE_H_

#include "Entity.h"
#include "BoardPlayer.h"

enum sector { pp, np, nn, pn };
enum squared { FLYING, FREE, OWNED, TAKEN };

class BoardBee : public Entity, public Emitter
{
public:
	BoardBee(Game* game);
	~BoardBee();

	void setOwner(BoardPlayer* player);
	void setTakenOwner(BoardPlayer* player);
	BoardPlayer* getOwner();
	BoardPlayer* getTakenOwner();
	bool isUnowned();
	void setUnowned();

	void setSquarePos(Vector2D squarePos);
	Vector2D getSquarePos();
	void setSquareNum(int squareNum);
	int getSquareNum();

	void setRepetitions(int repetitions);
	int getRepetitions();

	void setLastBee(bool lastBee);
	bool isLastBee();

	void setLastMove(bool lastBee);
	bool isLastMove();

	//public as this is just a fix to improved the simplified bee movement
	sector lastSector_, sector_;
	squared squared_;

protected:
	virtual void endMovement(bool timeOut);
	virtual void endResizing();
	int repetitions_;

private:
	BoardPlayer *owner_, *takenOwner_; //player owner pointer

	Vector2D squarePos_;
	int squareNum_;
	bool lastBee_, lastMove_;
};

#endif /* BOARDBEE_H_ */

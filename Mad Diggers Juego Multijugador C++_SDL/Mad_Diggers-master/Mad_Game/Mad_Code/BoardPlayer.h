//Mad_Diggers

#ifndef PLAYER_H_
#define PLAYER_H_

#include "Entity.h"
#include "Emitter.h"

class BoardSquare;

class BoardPlayer : public Entity, public Emitter
{
public:
	BoardPlayer(Game* game, int numPlayer);
	~BoardPlayer();

	virtual int getSomeValue() { return getPoints(); } //to avoid some cast

	virtual void update(Uint32 time);

	///////////////////////////////////////////////////////////////////

	void setLastRoll() { lastRoll_ = true; };
	void forceLastRoll() { lastRoll_ = true; endUpdatePoints(); };

	void addPoints(int points);
	int subtractPoints(int points); //returns the quantity substracted
	void sendAlreadyOwner();
	int getPoints();
	void setPoints(int points);

	void setNumPlayer(int points);
	int getNumPlayer();

protected:
	void updatePoints(Uint32 time);
	void endUpdatePoints();

	virtual void endMovement(bool timeOut) { send(&Message(BOARD_POP_QUEUE)); };

private:
	//smooth points
	double showPoints_, realPoints_;
	const double updatePoints_perSecond_ = 64;
	bool addingUpdate_ = true, lastRoll_ = false;
	Uint32 timer_ = 0;

	int numPlayer_;						//unique player number

	int boardPlacePosition_;			//game's position based on points
	vector<BoardSquare*> squaresOwned_; //pointers to the squares //not used atm
};

#endif /* PLAYER_H_ */

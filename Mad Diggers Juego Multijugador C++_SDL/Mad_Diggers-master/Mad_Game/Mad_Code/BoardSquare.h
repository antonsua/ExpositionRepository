//Mad_Diggers

#ifndef BOARDSQUARE_H_
#define BOARDSQUARE_H_

#include "Entity.h"
#include "BoardPlayer.h"

class BoardSquare : public Entity
{
public:
	BoardSquare(Game* game);
	~BoardSquare();

	virtual int getSomeValue() { return getValue(); } //to avoid some cast

	///////////////////////////////////////////////////////////////////

	void setValue(int value);
	int getValue();

	void setBoardPosition(int boardPos);
	int getBoardPosition();

	void setOwner(BoardPlayer* player);
	BoardPlayer* getOwner();

	bool isUnowned();
	void setUnowned();

	bool preOwned_; //fix a bug

private:
	int value_;				//numeric value of the square
	int boardPosition_;		//position in which was generated
	BoardPlayer* owner_;				//player owner pointer
};

#endif /* BOARDSQUARE_H_ */

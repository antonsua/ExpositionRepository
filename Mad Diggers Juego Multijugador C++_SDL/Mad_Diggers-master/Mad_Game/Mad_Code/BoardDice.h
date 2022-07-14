//Mad_Diggers

#ifndef BOARDDICE_H_
#define BOARDDICE_H_

#include "Entity.h"

class BoardDice : public Entity
{
public:
	BoardDice(Game* game);
	~BoardDice();

	virtual int getSomeValue() { return getRolls(); } //to avoid some cast

	int getRolls();
	void setRolls(int rolls);

	bool isUsed();
	void setUsed(bool b);

private:
	int rolls_;
	bool used_;
};

#endif /* BOARDDICE_H_ */

#pragma once
#include "Entity.h"
#include "ShapeRenderer.h"
#include "Value_RC.h"

typedef struct Point {
	double x, y;
}Point;

const Vector2D T1_INI_POS(0, -150);
const Vector2D T2_INI_POS_2P(650, -150);
const Vector2D T2_INI_POS_4P(200, -150);
const Vector2D T3_INI_POS(450, -150);
const Vector2D T4_INI_POS(650, -150);

const int WIDTH = 150;
const int HEIGHT = 900;
const Vector2D TREE_VALUERC_SCALE(0.5, 0.1);
const Vector2D OFFSET(10, 0);

class AppleTree : public Entity
{

public:

	AppleTree(Game* game, int colorIdentifier, int numPlayers);
	~AppleTree();

	virtual int getSomeValue() { return getTicks(); } //to avoid some cast

	void addTicks(int num) { ticks_ += num; };
	void setTicks(int num) { ticks_ = num; };
	int getTicks() const { return ticks_; };
	int getColor() const { return colorIdentifier_; };

	Point getl2();
	Point getr2();


private:
	void setColisionBox();
	void setPos(int colorID);
	Resources::ColorId getColor();

	int ticks_;
	int colorIdentifier_;
	int numPlayers;

	ShapeRenderer renderComp_;
	Value_RC valueRC_;
	spriteData nameData_;

	Point l2, r2;


};




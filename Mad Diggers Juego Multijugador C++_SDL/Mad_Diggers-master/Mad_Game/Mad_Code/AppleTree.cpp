#include "AppleTree.h"




AppleTree::AppleTree(Game* game, int colorIdentifier,int numPlayers) : Entity(game),colorIdentifier_(colorIdentifier),
ticks_(0),numPlayers(numPlayers),renderComp_ (game, Resources::s_tree, getColor())

{
	setWidth(WIDTH);
	setHeight(HEIGHT);
	setPos(colorIdentifier);
	setColisionBox();

	nameData_ = { TREE_VALUERC_SCALE, OFFSET, false, false, };
	valueRC_ = Value_RC(2, Resources::f_NESChimera_64, Resources::c_Black,&nameData_);

	addComponent(&renderComp_);
	addComponent(&valueRC_);
}

AppleTree::~AppleTree()
{
}

Point AppleTree::getl2()
{
	return l2;
}

Point AppleTree::getr2()
{
	return r2;
}

void AppleTree::setColisionBox()
{
	l2.x = getPosition().getX();
	l2.y = getPosition().getY();
	r2.x = l2.x + getWidth();
	r2.y = l2.y + getHeight();
}

void AppleTree::setPos(int colorID)
{
	switch (colorID)
	{
	case 1:
		setPosition(T1_INI_POS);
		break;
	case 2:
		if(numPlayers == 4)
		setPosition(T2_INI_POS_4P);
		else setPosition(T2_INI_POS_2P);
		break;
	case 3:
		setPosition(T3_INI_POS);
		break;
	case 4:
		setPosition(T4_INI_POS);
		break;

	}
}

Resources::ColorId AppleTree::getColor()
{
	switch (colorIdentifier_)
	{
	case 1:
		return Resources::c_Red;
		break;
	case 2:
		return Resources::c_Green;
		break;
	case 3:
		return Resources::c_Blue;
		break;
	case 4:
		return Resources::c_Pink;
		break;

	}
	
}

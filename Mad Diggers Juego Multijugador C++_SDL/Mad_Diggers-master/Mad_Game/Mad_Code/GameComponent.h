//Mad_Diggers

#ifndef GAMECOMPONENT_H_
#define GAMECOMPONENT_H_

#include "GameObject.h"

class GameComponent : public GameObject
{
public:
	GameComponent(Game* game);
	virtual ~GameComponent();

	//nothing especial atm
};

#endif /* GAMECOMPONENT_H_ */

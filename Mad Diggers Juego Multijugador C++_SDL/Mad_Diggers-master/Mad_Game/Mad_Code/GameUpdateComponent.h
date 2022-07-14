//Mad_Diggers

#ifndef GAMEUPDATECOMPONENT_H_
#define GAMEUPDATECOMPONENT_H_

#include "GameComponent.h"

class GameUpdateComponent : public GameComponent
{
public:
	GameUpdateComponent(Game* game);
	virtual ~GameUpdateComponent();

	virtual void handleEvents(Uint32 time, const SDL_Event& event) {};
	virtual void update(Uint32 time) = 0; //still virtual
	virtual void render( Uint32 time) {};
};

#endif /* GAMEUPDATECOMPONENT_H_ */

//Mad_Diggers

#ifndef GAMEINPUTCOMPONENT_H_
#define GAMEINPUTCOMPONENT_H_

#include "GameComponent.h"

class GameInputComponent : public GameComponent
{
public:
	GameInputComponent(Game* game);
	virtual ~GameInputComponent();

	virtual void handleEvents(Uint32 time, const SDL_Event& event) = 0; //still virtual
	virtual void update(Uint32 time) {};
	virtual void render(Uint32 time) {};
};

#endif /* GAMEINPUTCOMPONENT_H_ */

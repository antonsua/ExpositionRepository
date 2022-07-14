#ifndef GAMERENDERCOMPONENT_H_
#define GAMERENDERCOMPONENT_H_

#include "GameComponent.h"

class GameRenderComponent : public GameComponent
{
public:
	GameRenderComponent(Game* game);
	virtual ~GameRenderComponent();

	virtual void handleEvents(Uint32 time, const SDL_Event& event) {};
	virtual void update(Uint32 time) {};
	virtual void render(Uint32 time) = 0; //still virtual
};

#endif /* GAMERENDERCOMPONENT_H_ */
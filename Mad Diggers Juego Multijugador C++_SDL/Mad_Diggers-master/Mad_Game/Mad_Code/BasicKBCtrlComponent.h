#ifndef BASICKBCTRLCOMPONENT_H_
#define BASICKBCTRLCOMPONENT_H_

#include "EntityInputComponent.h"

class BasicKBCtrlComponent: public EntityInputComponent
{
public:
	BasicKBCtrlComponent(SDL_Keycode left, SDL_Keycode right, SDL_Keycode up, SDL_Keycode down, SDL_Keycode stop);
	virtual ~BasicKBCtrlComponent();

	virtual void handleEvents(Entity* o, Uint32 time, const SDL_Event& event);

private:
	SDL_Keycode left_;
	SDL_Keycode right_;
	SDL_Keycode up_;
	SDL_Keycode down_;
	SDL_Keycode stop_;
};

#endif /* BASICKBCTRLCOMPONENT_H_ */

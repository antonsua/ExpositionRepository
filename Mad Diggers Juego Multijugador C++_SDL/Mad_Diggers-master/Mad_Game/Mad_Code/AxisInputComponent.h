#ifndef AXISINPUTCOMPONENT_H_
#define AXISINPUTCOMPONENT_H_

#include "GamePadComponent.h"
#include "Emitter.h"
#include "Listener.h"

/*
*
*/
class AxisInputComponent : public GamePadComponent, public Listener {

public:

	//typeMv variable refers to the type of beeMovement: vertical(false) and horizontal(true)  
	AxisInputComponent(MessageId Input1, MessageId Input2,
		SDL_JoystickID controllerId, MessageId uInput1, MessageId uInput2,
		SDL_Keycode key1, SDL_Keycode key2);
	virtual ~AxisInputComponent();

	virtual void handleEvents(Entity* o, Uint32 time, const SDL_Event& event);

private:
	Controller controller_;
	MessageId Input1_;
	MessageId Input2_;
	MessageId uInput1_;
	MessageId uInput2_;
	SDL_Keycode key1_;
	SDL_Keycode key2_;
	bool typeMv_, gamepadActive = false;
	bool keysHeld[2] = { false };

	void receive(Message* msg);
};

#endif /* AXISINPUTCOMPONENT_H_ */

#include "AxisInputComponent.h"

AxisInputComponent::AxisInputComponent(MessageId Input1, MessageId Input2,
	SDL_JoystickID controllerId, MessageId uInput1, MessageId uInput2,
	SDL_Keycode key1, SDL_Keycode key2) :
	Input1_(Input1), Input2_(Input2), GamePadComponent(controllerId),
	uInput1_(uInput1), uInput2_(uInput2), key1_(key1), key2_(key2)
{
	controller_.controllerId = controllerId;
	initGamePads();
}

AxisInputComponent::~AxisInputComponent() {
}

void AxisInputComponent::handleEvents(Entity* o, Uint32 time,
	const SDL_Event& event) {

	if (event.type == SDL_KEYDOWN) {
		if (event.key.keysym.sym == key1_) {
			keysHeld[0] = true;
		}
		else if (event.key.keysym.sym == key2_) {
			keysHeld[1] = true;
		}
	}

	else if (event.type == SDL_KEYUP) {
		if (event.key.keysym.sym == key1_)
			keysHeld[0] = false;

		else if (event.key.keysym.sym == key2_)
			keysHeld[1] = false;
	}			

	if (keysHeld[0] || keysHeld[1]) {
		if (keysHeld[0]) {
			send(&Message(MOVE_1));
			/*if (typeMv_)
				velocity.set(-vel_, 0);
			else
				velocity.set(0, -vel_);*/
		}
		else {
			send(&Message(MOVE_2));
			/*if (typeMv_)
				velocity.set(vel_, 0);
			else
				velocity.set(0, vel_);*/
		}
	}
	else if(!gamepadActive) send(&Message(NO_MOVE));
}

void AxisInputComponent::receive(Message * msg)
{
	if (msg->id_ == Input1_) {
		gamepadActive = true;
		send(&Message(MOVE_1));
	}
	else if (msg->id_ == Input2_) {
		gamepadActive =  true;
		send(&Message(MOVE_2));
	}
	else if (msg->id_ == uInput1_ || msg->id_ == uInput2_) {
		gamepadActive = false;
		send(&Message(NO_MOVE));
	}
}


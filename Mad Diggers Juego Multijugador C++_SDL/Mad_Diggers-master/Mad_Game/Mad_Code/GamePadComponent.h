#ifndef GAMEPADCOMPONENT_H_
#define GAMEPADCOMPONENT_H_

#include "EntityInputComponent.h"
#include "Emitter.h"

/*


class GamePadComponent : public EntityInputComponent
{
public:
	GamePadComponent();
	~GamePadComponent();
	void initGamePads();

private:
	SDL_GameController * controller_;
	const int JOYSTICK_DEADZONE = 8000;
	const int JOYSTICK_MAX_VALUE = 32768;

protected:
	struct Controller
	{
		SDL_JoystickID controllerId = NULL;
		SDL_GameControllerButton button0_ = SDL_CONTROLLER_BUTTON_INVALID;
		SDL_GameControllerButton button1_ = SDL_CONTROLLER_BUTTON_INVALID;
		SDL_GameControllerButton button2_ = SDL_CONTROLLER_BUTTON_INVALID;
		SDL_GameControllerButton button3_ = SDL_CONTROLLER_BUTTON_INVALID;
		SDL_GameControllerButton button4_ = SDL_CONTROLLER_BUTTON_INVALID;
		SDL_GameControllerButton button5_ = SDL_CONTROLLER_BUTTON_INVALID;
		SDL_GameControllerButton button6_ = SDL_CONTROLLER_BUTTON_INVALID;
		SDL_GameControllerButton button7_ = SDL_CONTROLLER_BUTTON_INVALID;
		SDL_GameControllerButton button8_ = SDL_CONTROLLER_BUTTON_INVALID;
		SDL_GameControllerButton button9_ = SDL_CONTROLLER_BUTTON_INVALID;
		SDL_GameControllerButton button10_ = SDL_CONTROLLER_BUTTON_INVALID;
		SDL_GameControllerButton button11_ = SDL_CONTROLLER_BUTTON_INVALID;
		SDL_GameControllerAxis leftAxis0_ = SDL_CONTROLLER_AXIS_INVALID;
		SDL_GameControllerAxis leftAxis1_ = SDL_CONTROLLER_AXIS_INVALID;
		SDL_GameControllerAxis rightAxis0_ = SDL_CONTROLLER_AXIS_INVALID;
		SDL_GameControllerAxis rightAxis1_ = SDL_CONTROLLER_AXIS_INVALID;
		SDL_GameControllerAxis triggerLeft_ = SDL_CONTROLLER_AXIS_INVALID;
		SDL_GameControllerAxis triggerRight_ = SDL_CONTROLLER_AXIS_INVALID;
	};

	virtual void handleEvents(Entity* o, Uint32 time, const SDL_Event& event);
	int getJoyDeadzone() const;
	int getJoyMaxValue() const;
};
*/

struct Controller
{
	SDL_JoystickID controllerId = NULL;
	Message A_, B_, X_, Y_,
		DPAD_UP_, DPAD_DOWN_, DPAD_LEFT_, DPAD_RIGHT_,
		RB_, LB_,
		START_,
		BACK_,
		GUIDE_,
		JOYRIGHT_UP_, JOYRIGHT_DOWN_, JOYRIGHT_RIGHT_, JOYRIGHT_LEFT_,
		JOYLEFT_UP_, JOYLEFT_DOWN_, JOYLEFT_RIGHT_, JOYLEFT_LEFT_,
		RT_, LT_;
};

class GamePadComponent : public EntityInputComponent, public Emitter
{
public:
	GamePadComponent(int controllerId);
	~GamePadComponent();
	GamePadComponent() {};
	void initGamePads();
	virtual void handleEvents(Entity* o, Uint32 time, const SDL_Event& event);

private:
	Controller gamePad_;
	SDL_GameController * controller_;
	int controllerId_;
	const int JOYSTICK_DEADZONE = 8000;
	const int JOYSTICK_MAX_VALUE = 32768;

protected:
	int getJoyDeadzone() const;
	int getJoyMaxValue() const;
};

#endif /*GAMEPADCOMPONENT_H_ */


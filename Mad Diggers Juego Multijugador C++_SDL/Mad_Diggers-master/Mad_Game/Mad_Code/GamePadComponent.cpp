#include "GamePadComponent.h"

GamePadComponent::GamePadComponent(int controllerId)
{
	gamePad_.controllerId = controllerId;
	initGamePads();
	
}


GamePadComponent::~GamePadComponent()
{
}

void GamePadComponent::initGamePads() {
	// Initialize GamePad/Controller
	if (SDL_NumJoysticks() < 1)
		std::cout << " Warning: No gamepad conected \n";
	else
	{
		for (int i = 0; i < SDL_NumJoysticks(); i++)
		{
			if (SDL_IsGameController(i))
				controller_ = SDL_GameControllerOpen(i);
			if (controller_ == nullptr)
			{
				std::cout << " Warning: Unable to open Game Controller \n";
			}
			std::cout << " GamePad connected successfully: " << i + 1 << endl;
		}
	}
}

void GamePadComponent::handleEvents(Entity* o, Uint32 time, const SDL_Event& event)
{
	if (event.type == SDL_CONTROLLERBUTTONDOWN) {
		if (event.cbutton.which == gamePad_.controllerId) {
			switch (event.cbutton.button)
			{
			case SDL_CONTROLLER_BUTTON_A:
				send(&PressedAPAD(gamePad_.controllerId));
				break;

			case SDL_CONTROLLER_BUTTON_B:
				gamePad_.B_ = Message(B);
				send(&gamePad_.B_);
				break;
			case SDL_CONTROLLER_BUTTON_X:
				gamePad_.X_ = Message(X);
				send(&gamePad_.X_);
				break;

			case SDL_CONTROLLER_BUTTON_Y:
				gamePad_.Y_ = Message(Y);
				send(&gamePad_.Y_);
				break;

			case SDL_CONTROLLER_BUTTON_BACK:
				gamePad_.BACK_ = Message(BACK);
				send(&gamePad_.BACK_);
				break;

			case SDL_CONTROLLER_BUTTON_START:
				gamePad_.START_ = Message(START);
				send(&gamePad_.START_);
				break;

			case SDL_CONTROLLER_BUTTON_GUIDE:
				gamePad_.GUIDE_ = Message(GUIDE);
				send(&gamePad_.GUIDE_);
				break;

			case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
				gamePad_.DPAD_DOWN_ = Message(DPAD_DOWN);
				send(&gamePad_.DPAD_DOWN_);
				break;
			case SDL_CONTROLLER_BUTTON_DPAD_UP:
				gamePad_.DPAD_UP_ = Message(DPAD_UP);
				send(&gamePad_.DPAD_UP_);
				break;
			case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
				gamePad_.DPAD_RIGHT_ = Message(DPAD_RIGHT);
				send(&gamePad_.DPAD_RIGHT_);
				break;
			case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
				gamePad_.DPAD_LEFT_ = Message(DPAD_LEFT);
				send(&gamePad_.DPAD_LEFT_);
				break;
			case SDL_CONTROLLER_BUTTON_LEFTSHOULDER:
				gamePad_.LB_ = Message(LB);
				send(&gamePad_.LB_);
				break;
			case SDL_CONTROLLER_BUTTON_RIGHTSHOULDER:
				gamePad_.RB_ = Message(RB);
				send(&gamePad_.RB_);
				break;
			}
		}
	}
	else if (event.type == SDL_CONTROLLERAXISMOTION) {
		if (event.cbutton.which == gamePad_.controllerId) {
			if (event.caxis.axis == SDL_CONTROLLER_AXIS_LEFTX) {
				if (event.caxis.value < -JOYSTICK_DEADZONE && event.caxis.value >= -JOYSTICK_MAX_VALUE)
				{
					gamePad_.JOYLEFT_LEFT_ = Message(JOYLEFT_LEFT);
					send(&gamePad_.JOYLEFT_LEFT_);
				}
				else if (event.caxis.value > JOYSTICK_DEADZONE && event.caxis.value <= JOYSTICK_MAX_VALUE)
				{
					gamePad_.JOYLEFT_RIGHT_ = Message(JOYLEFT_RIGHT);
					send(&gamePad_.JOYLEFT_RIGHT_);
				}
			}
			else if (event.caxis.axis == SDL_CONTROLLER_AXIS_LEFTY) {
				if (event.caxis.value < -JOYSTICK_DEADZONE && event.caxis.value >= -JOYSTICK_MAX_VALUE)
				{
					gamePad_.JOYLEFT_UP_ = Message(JOYLEFT_UP);
					send(&gamePad_.JOYLEFT_UP_);
				}
				else if (event.caxis.value > JOYSTICK_DEADZONE && event.caxis.value <= JOYSTICK_MAX_VALUE)
				{
					gamePad_.JOYLEFT_DOWN_ = Message(JOYLEFT_DOWN);
					send(&gamePad_.JOYLEFT_DOWN_);
				}
			}
			else if (event.caxis.axis == SDL_CONTROLLER_AXIS_RIGHTX) {
				if (event.caxis.value < -JOYSTICK_DEADZONE && event.caxis.value >= -JOYSTICK_MAX_VALUE)
				{
					gamePad_.JOYRIGHT_LEFT_ = Message(JOYRIGHT_LEFT);
					send(&gamePad_.JOYRIGHT_LEFT_);
				}
				else if (event.caxis.value > JOYSTICK_DEADZONE && event.caxis.value <= JOYSTICK_MAX_VALUE)
				{
					gamePad_.JOYRIGHT_RIGHT_ = Message(JOYRIGHT_RIGHT);
					send(&gamePad_.JOYRIGHT_RIGHT_);
				}
			}
			else if (event.caxis.axis == SDL_CONTROLLER_AXIS_RIGHTY) {
				if (event.caxis.value < -JOYSTICK_DEADZONE && event.caxis.value >= -JOYSTICK_MAX_VALUE)
				{
					gamePad_.JOYRIGHT_UP_ = Message(JOYRIGHT_UP);
					send(&gamePad_.JOYRIGHT_UP_);
				}
				else if (event.caxis.value > JOYSTICK_DEADZONE && event.caxis.value <= JOYSTICK_MAX_VALUE)
				{
					gamePad_.JOYRIGHT_DOWN_ = Message(JOYRIGHT_DOWN);
					send(&gamePad_.JOYRIGHT_DOWN_);
				}
			}
			else if (event.caxis.axis == SDL_CONTROLLER_AXIS_TRIGGERLEFT) {
				if (event.caxis.value > JOYSTICK_DEADZONE && event.caxis.value <= JOYSTICK_MAX_VALUE)
				{
					gamePad_.LT_ = Message(LT);
					send(&gamePad_.LT_);
				}
			}
			else if (event.caxis.axis == SDL_CONTROLLER_AXIS_TRIGGERRIGHT) {
				if (event.caxis.value > JOYSTICK_DEADZONE && event.caxis.value <= JOYSTICK_MAX_VALUE)
				{
					gamePad_.RT_ = Message(RT);
					send(&gamePad_.RT_);
				}
			}
		}
	}

	else if (event.type == SDL_CONTROLLERBUTTONUP) {
	if (event.cbutton.which == gamePad_.controllerId) 
		switch (event.cbutton.button)
		{
		case SDL_CONTROLLER_BUTTON_A:
			/*gamePad_.A_ = new Message(A);
			send(gamePad_.A_);*/
			gamePad_.A_ = Message(uA);
			send(&gamePad_.A_);
			break;

		case SDL_CONTROLLER_BUTTON_B:
			gamePad_.B_ = Message(uB);
			send(&gamePad_.B_);
			break;
		case SDL_CONTROLLER_BUTTON_X:
			gamePad_.X_ = Message(uX);
			send(&gamePad_.X_);
			break;

		case SDL_CONTROLLER_BUTTON_Y:
			gamePad_.Y_ = Message(uY);
			send(&gamePad_.Y_);
			break;

		case SDL_CONTROLLER_BUTTON_BACK:
			gamePad_.BACK_ = Message(uBACK);
			send(&gamePad_.BACK_);
			break;

		case SDL_CONTROLLER_BUTTON_START:
			gamePad_.START_ = Message(uSTART);
			send(&gamePad_.START_);
			break;

		case SDL_CONTROLLER_BUTTON_GUIDE:
			gamePad_.GUIDE_ = Message(uGUIDE);
			send(&gamePad_.GUIDE_);
			break;

		case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
			gamePad_.DPAD_DOWN_ = Message(uDPAD_DOWN);
			send(&gamePad_.DPAD_DOWN_);
			break;
		case SDL_CONTROLLER_BUTTON_DPAD_UP:
			gamePad_.DPAD_UP_ = Message(uDPAD_UP);
			send(&gamePad_.DPAD_UP_);
			break;
		case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
			gamePad_.DPAD_RIGHT_ = Message(uDPAD_RIGHT);
			send(&gamePad_.DPAD_RIGHT_);
			break;
		case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
			gamePad_.DPAD_LEFT_ = Message(uDPAD_LEFT);
			send(&gamePad_.DPAD_LEFT_);
			break;
		case SDL_CONTROLLER_BUTTON_LEFTSHOULDER:
			gamePad_.LB_ = Message(uLB);
			send(&gamePad_.LB_);
			break;
		case SDL_CONTROLLER_BUTTON_RIGHTSHOULDER:
			gamePad_.RB_ = Message(uRB);
			send(&gamePad_.RB_);
			break;
		}
	}
}

int GamePadComponent::getJoyDeadzone() const
{
	return JOYSTICK_DEADZONE;
}

int GamePadComponent::getJoyMaxValue() const
{
	return JOYSTICK_MAX_VALUE;
}

/*
GamePadComponent::GamePadComponent()
{
}


GamePadComponent::~GamePadComponent()
{
}

void GamePadComponent::initGamePads() {
	// Initialize GamePad/Controller
	if (SDL_NumJoysticks() < 1)
		std::cout << " Warning: No gamepad conected \n";
	else
	{
		for (int i = 0; i < SDL_NumJoysticks(); i++)
		{
			if (SDL_IsGameController(i))
				controller_ = SDL_GameControllerOpen(i);
			if (controller_ == nullptr)
			{
				std::cout << " Warning: Unable to open Game Controller \n";
			}
			std::cout << " GamePad connected successfully: " << i + 1 << endl;
		}
	}
}

void GamePadComponent::handleEvents(Entity* o, Uint32 time, const SDL_Event& event)
{
}

int GamePadComponent::getJoyDeadzone() const 
{
	return JOYSTICK_DEADZONE;
}

int GamePadComponent::getJoyMaxValue() const
{
	return JOYSTICK_MAX_VALUE;
}
*/
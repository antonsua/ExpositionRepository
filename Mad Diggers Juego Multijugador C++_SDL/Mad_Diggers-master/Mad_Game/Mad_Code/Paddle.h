//Mad_diggers
#pragma once
#include "Entity.h"
#include "jsonReader.h"

#include "AxisInputComponent.h"
#include "GamePadComponent.h"

#include "PaddlePhysicsComponent.h"
#include "ImageRenderer.h"


class Paddle : public Entity, public jsonReader {
public:
	//This doesn't initialize position. It must be done in the state
	Paddle(Game* game, int id, Resources::ImageId paddleId, MessageId input1, MessageId input2, MessageId uInput1, MessageId uInput2,
		Vector2D offset, bool horiz, SDL_JoystickID controllerId, SDL_Keycode key1, SDL_Keycode key2);
	virtual ~Paddle();
	virtual void receive(Message* message);
	void setId(int id);

	AxisInputComponent * getAxisInpComp();

private:
	ImageRenderer* imageRen_;
	spriteData renderData_;

	int id_;
	//SDL_Color* color_;
	bool horiz_;
	PaddlePhysicsComponent* padPhys_;
	AxisInputComponent* axisInp_;
	GamePadComponent* gamePad_;
	const double _PAD_SPEED_;
	const double _PAD_WIDTH_;
	const double _PAD_HEIGHT_;
	/*SDL_Color padColor_;
	SDL_Keycode input1_, input2_;
	Vector2D offset_;*/
};

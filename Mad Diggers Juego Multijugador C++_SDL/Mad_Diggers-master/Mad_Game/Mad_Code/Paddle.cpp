#include "Paddle.h"
#include "PongMiniGame.h"
//#include "ImageRenderer.h"

Paddle::Paddle(Game * game, int id, Resources::ImageId paddleId, MessageId input1, MessageId input2, MessageId uInput1, MessageId uInput2,
	Vector2D offset, bool horiz, SDL_JoystickID controllerId, SDL_Keycode key1, SDL_Keycode key2) :
	Entity(game), /*color_(padColor),*/ id_(id), jsonReader(game->getResources()->getJsonFile(Resources::j_PongMinigame)),
	_PAD_WIDTH_(jsonData["_PAD_WIDTH_"].asDouble()), _PAD_HEIGHT_(jsonData["_PAD_HEIGHT_"].asDouble()), _PAD_SPEED_(jsonData["_PAD_SPEED_"].asDouble())
{
	readFromJson(game_->getResources()->getJsonFile(Resources::j_PongMinigame));
	if (horiz) {
		setWidth(_PAD_HEIGHT_);
		setHeight(_PAD_WIDTH_);
	}
	else {
		setWidth(_PAD_WIDTH_);
		setHeight(_PAD_HEIGHT_);
	}

	padPhys_ = new PaddlePhysicsComponent(!horiz, offset.getX(), offset.getY(), _PAD_SPEED_);
	axisInp_ = new AxisInputComponent(input1, input2, controllerId, uInput1, uInput2, key1, key2);
	gamePad_ = new GamePadComponent(id_);
	axisInp_->registerListener(padPhys_);
	gamePad_->registerListener(axisInp_);


	//addComponent(new FillRectRenderer(& color_));
	switch (id_)
	{
	case 0:
		renderData_ = { Vector2D(5.5, 1.8), Vector2D(0,0), false, false, };
		break;
	case 1:
		renderData_ = { Vector2D(5.5, 1.8), Vector2D(1.8, 0), false, false, };
		break;
	case 2:
		renderData_ = { Vector2D(1.8, 5.5), Vector2D(0,0), false, false, };
		break;
	case 3:
		renderData_ = { Vector2D(1.8, 5.5), Vector2D(0, 1.8), false, false, };
		break;
	}
	imageRen_ = new ImageRenderer(game->getResources()->getImageTexture(paddleId), &renderData_);
	addComponent(imageRen_);

	addComponent(gamePad_);
	addComponent(padPhys_);
	addComponent(axisInp_);
}

Paddle::~Paddle()
{
	delete imageRen_;
	delete padPhys_;
	delete axisInp_;
	delete gamePad_;
}

void Paddle::receive(Message* message){
	if (message->id_ == MINIGAME_ROUND_OVER) {
		Message_BallLimits* m = static_cast<Message_BallLimits*>(message);
		if (m->player_ == id_) {
			delAllComponents();
		}
	}
}

void Paddle::setId(int id) {
	id_ = id;
}

AxisInputComponent * Paddle::getAxisInpComp()
{
	return axisInp_;
}

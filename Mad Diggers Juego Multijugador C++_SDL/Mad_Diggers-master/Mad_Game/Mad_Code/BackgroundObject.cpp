#include "BackgroundObject.h"


BackgroundObject::BackgroundObject(Game* game_, Resources::ImageId backgroundImage) : Entity(game_)
{
	readFromJson(game_->getResources()->getJsonFile(Resources::j_BackgroundObject));

	REDUCTION_FACTOR = jsonData["REDUCTION_FACTOR"].asFloat();
	MINIMUM_SIZE = jsonData["MINIMUM_SIZE_2P"].asUInt();


	setHeight(jsonData["height"].asUInt());
	setWidth(jsonData["width"].asUInt());

	renderData_ = { Vector2D(1,1), Vector2D(jsonData["xOffset"].asUInt(), jsonData["yOffset"].asUInt()), false, false, };
	renderer_ = ImageRenderer(game_->getResources()->getImageTexture(backgroundImage), &renderData_);
	addComponent(&renderer_);

	this->c.x = jsonData["circle"]["x"].asUInt();
	this->c.y = jsonData["circle"]["y"].asUInt();
	this->c.r = getWidth() / 2;
}


BackgroundObject::~BackgroundObject()
{
}

void BackgroundObject::update(Uint32 time)
{
	if (startReduction_) {
		if (getWidth() > MINIMUM_SIZE) {
			setWidth(this->getWidth() - REDUCTION_FACTOR);
			setHeight(this->getHeight() - REDUCTION_FACTOR);
			setPosition(Vector2D(getPosition().getX() + REDUCTION_FACTOR / 2, getPosition().getY() + REDUCTION_FACTOR / 2));
			c.r = getWidth() / 2;
		}
	}

}

void BackgroundObject::receive(Message * msg)
{
	switch (msg->id_)
	{
	case ANIMATION_ENDED:
		startReduction_ = true;
		break;
	}
}

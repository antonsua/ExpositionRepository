#include "BlockPong.h"


BlockPong::BlockPong(Game* game, Resources::ShapeId shapeId, Vector2D offset) :
	Entity(game)
{
	setWidth(offset.getX());
	setHeight(offset.getY());

	//wtf compa¿ todos estos new sin referencia son memoria sin borrar
	shapeRen_ = ShapeRenderer(game, shapeId, Resources::c_Honey);
	addComponent(&shapeRen_);
}

BlockPong::BlockPong(Game * game, Resources::ImageId imageId, Vector2D offset, bool orientation) :
	Entity(game)
{
	setWidth(offset.getX());
	setHeight(offset.getY());

	if(orientation) renderData_ = { Vector2D(0.6, 1), Vector2D(0, 0), false, false, };
	else renderData_ = { Vector2D(1, 0.8), Vector2D(0, 0), false, false, };

	imageRen_ = ImageRenderer(game->getResources()->getImageTexture(imageId), &renderData_);
	addComponent(&imageRen_);
}


BlockPong::~BlockPong()
{
}

void BlockPong::setFinalPos(Vector2D finalPos)
{
	finalPos_ = finalPos;
}

Vector2D BlockPong::getFinalPos()
{
	return finalPos_;
}


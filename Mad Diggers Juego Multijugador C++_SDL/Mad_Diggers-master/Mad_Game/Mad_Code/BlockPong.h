#pragma once
#include "Entity.h"

#include "ShapeRenderer.h"
#include "ImageRenderer.h"


class BlockPong : public Entity
{
public:
	BlockPong(Game* game, Resources::ShapeId shapeId, Vector2D offset);
	BlockPong(Game* game, Resources::ImageId imageId, Vector2D offset, bool orientation);
	virtual ~BlockPong();

	void setFinalPos(Vector2D finalPos);
	Vector2D getFinalPos();

private:
	Vector2D finalPos_;

	ShapeRenderer shapeRen_;
	ImageRenderer imageRen_;
	spriteData renderData_;
};


#include "ImageRepeatRender.h"



ImageRepeatRender::ImageRepeatRender(): ImageRenderer()
{
}

ImageRepeatRender::ImageRepeatRender(Texture* image, double width, double height):ImageRenderer(image), width_(width), height_(height)
{
}


ImageRepeatRender::~ImageRepeatRender()
{
}

void ImageRepeatRender::render(Entity* o, Uint32 time) {

	double x, y, w, h;
	x = o->getPosition().getX();
	y = o->getPosition().getY();
	w = o->getWidth();
	h = o->getHeight();

	//TODO: add bool for angle
	if (fading_) fade(time);
	if (alpha_ > 0)
	{
		if (alpha_ < 1) image_->modulateAlpha(alpha_);
		double angle = o->getDirection().angle(Vector2D::getDefaultZeroAngle());
		int i, j;
		i = 0;
		while (i*height_ < h)
		{
			j = 0;
			while (j*width_ < w)
			{
				image_->render(o->getGame()->getRenderer(), RECT(x + width_ * j, y + height_ * i, width_, height_), angle);
				j++;
			}
			i++;
		}
	}
}
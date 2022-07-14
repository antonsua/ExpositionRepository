#include "ImageRenderer.h"

spriteData defaultSpriteData =
{
	Vector2D(1.0, 1.0),
	Vector2D(0.0, 0.0),
	true, false,
};

ImageRenderer::ImageRenderer() : data_(&defaultSpriteData)
{
}

ImageRenderer::ImageRenderer(Texture* image) :
	image_(image), data_(&defaultSpriteData)
{
}

ImageRenderer::ImageRenderer(spriteData * data) :
	image_(nullptr), data_(data)
{
	SDL_assert(data_->scale_.getX() > 0.09 && data_->scale_.getY() > 0.09); //negative scale
}

ImageRenderer::ImageRenderer(Texture * image, spriteData * data) :
	image_(image), data_(data)
{
	SDL_assert(data_->scale_.getX() > 0.09 && data_->scale_.getY() > 0.09); //negative scale
}


ImageRenderer::~ImageRenderer()
{
}

///////////////////////////////////////////////////////////////////

void ImageRenderer::setImage(Texture * image)
{
	//if (image_ != nullptr) image_->close(); //closed by original image holder
	image_ = image;
}

void ImageRenderer::render(Entity* o, Uint32 time)
{
	if (image_ == nullptr) return; //guard to avoid nesting

	// ALPHA
	if (fading_) fade(time);
	if (alpha_ > 0)
	{
		if (alpha_ < 1) image_->modulateAlpha(alpha_);

		// TRANSFORMATIONS
		double x, y, w, h;
		const double wS = data_->scale_.getX(), hS = data_->scale_.getY();

		//apply scale
		w = o->getWidth() * wS;
		h = o->getHeight() * hS;

		//center scaled
		x = o->getWidth() * (1 - wS) / 2;
		y = o->getHeight() * (1 - hS) / 2;

		//apply offset
		Vector2D pos;
		if (data_->drawRealPosition_) pos = o->getObjectPosition();
		else pos = o->getPosition();

		x += pos.getX() + data_->offset_.getX();
		y += pos.getY() + data_->offset_.getY();

		if (flipOn_) image_->render(o->getGame()->getRenderer(), RECT(x, y, w, h), flip_);

		// RENDER
		else if (data_->rotation_)
		{
			//double angle = o->getDirection().angle(Vector2D::getDefaultZeroAngle());
			double angle = o->getDirection().angle(Vector2D(1, 0));
			image_->render(o->getGame()->getRenderer(), RECT(x, y, w, h), angle);
		}

		else  image_->render(o->getGame()->getRenderer(), RECT(x, y, w, h));
	}
}

///////////////////////////////////////////////////////////////////

void ImageRenderer::setAlpha(float alpha0to1)
{
	alpha_ = alpha0to1;
}

void ImageRenderer::fadeToAlpha(float alpha0to1, Uint32 timeMS, MessageId fadeEndMsg)
{
	alphaTarget_ = alpha0to1;
	fadeEndMsg_ = fadeEndMsg;

	if (alphaTarget_ != alpha_)
	{
		fading_ = true;
		fadeTime_ = 0;

		fadeSpeed_ = (alphaTarget_ - alpha_) / timeMS;

		fadingOut_ = fadeSpeed_ < 0;
	}
}

void ImageRenderer::waveAlpha(float alpha0to1Min, float alpha0to1Max, Uint32 timeMS, MessageId fadeEndMsg)
{
	waving_ = true;
	waveAlphaMin_ = alpha0to1Min;
	waveAlphaMax_ = alpha0to1Max;
	wavingTime_ = timeMS;

	fadeToAlpha(alpha0to1Min, timeMS, fadeEndMsg);
}

void ImageRenderer::stopWaveAlpha(float alpha0to1Min)
{
	waving_ = false;
}

void ImageRenderer::stopFading() {
	fading_ = false;
}

void ImageRenderer::fade(Uint32 time)
{
	if (fadeTime_ == 0) fadeTime_ = time; //start
	else
	{
		//check duration for delta
		Uint32 delta = time - fadeTime_;
		fadeTime_ = time;

		alpha_ = alpha_ + fadeSpeed_ * delta;

		if ((fadingOut_ && alpha_ <= alphaTarget_) || (!fadingOut_ && alpha_ >= alphaTarget_))
		{
			alpha_ = alphaTarget_;
			fading_ = false;
			fadeEnd();
			if (waving_) {
				if (alpha_ == waveAlphaMin_) fadeToAlpha(waveAlphaMax_, wavingTime_, fadeEndMsg_);
				else fadeToAlpha(waveAlphaMin_, wavingTime_, fadeEndMsg_);
			}
		}
	}
}

void ImageRenderer::activateFlip()
{
	flipOn_ = true;
}
void ImageRenderer::setFlipOrientation(SDL_RendererFlip flip)
{
	flip_ = flip;
}

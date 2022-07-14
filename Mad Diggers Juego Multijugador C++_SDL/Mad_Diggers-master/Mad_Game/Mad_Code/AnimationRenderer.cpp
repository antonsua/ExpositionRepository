#include "animationRenderer.h"
#include "SDLGame.h"

AnimationRenderer::AnimationRenderer(Texture* image, spriteSheetData* data, bool autoStart) :
	image_(image), data_(data), on_(false), autoStart_(autoStart), lastframe_(0)
{
}

AnimationRenderer::~AnimationRenderer() {
}

///////////////////////////////////////////////////////////////////

void AnimationRenderer::setImage(Texture * image)
{
	if (image_ != nullptr) image_->close();
	image_ = image;
}

void AnimationRenderer::setColor(SDL_Color* color) {
	color_ = color;
}

void AnimationRenderer::start()
{
	//auto set start / end if 0 0
	if (data_->frameStartCol_ == 0) data_->frameStartCol_ = 1;
	if (data_->frameStartFil_ == 0) data_->frameStartFil_ = 1;
	if (data_->frameEndCol_ == 0) data_->frameEndCol_ = image_->getCols();
	if (data_->frameEndFil_ == 0) data_->frameEndFil_ = image_->getFils();

	SDL_assert(data_->frameStartCol_ > 0 && data_->frameStartFil_ > 0); //frames start 1,1
	SDL_assert(data_->frameEndCol_ <= image_->getCols() //end withing texture limits
		&& data_->frameEndFil_ <= image_->getFils());
	SDL_assert(data_->scale_.getX() > 0.09 && data_->scale_.getY() > 0.09); //negative scale

	on_ = true;
	frameTimer_ = 0;
	lastframe_ = 0;
	frameCol_ = data_->frameStartCol_ - 1;
	frameFil_ = data_->frameStartFil_ - 1;
}

void AnimationRenderer::cancel() {
	on_ = false;
}

void AnimationRenderer::stop()
{
	on_ = false;
	send(&Message(ANIMATION_ENDED));
}

///////////////////////////////////////////////////////////////////

void AnimationRenderer::render(Entity* o, Uint32 time)
{
	if (autoStart_) //allowing pointer to data_ to be nullptr or incomplete at creation
	{
		autoStart_ = false;
		start();
	}

	if (on_ || data_->stay_) //not rendering always
	{
		//UPDATE CLIP FRAME
		updateFrame(time);
		SDL_Rect clip = image_->getRectFrame(frameCol_, frameFil_);


		//TRANSFORMATIONS
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

		//RENDER
		if (color_ != nullptr) {
			image_->modulateColor(*color_);
		}

		if (data_->rotation_)
		{
			//double angle = o->getDirection().angle(Vector2D::getDefaultZeroAngle());
			double angle = o->getDirection().angle(Vector2D(1, 0));
			image_->render(o->getGame()->getRenderer(), RECT(x, y, w, h), angle, &clip);
		}
		else image_->render(o->getGame()->getRenderer(), RECT(x, y, w, h), &clip);
	}
}

void AnimationRenderer::updateFrame(Uint32 time)
{
	if (on_)
	{
		if (lastframe_ == 0) lastframe_ = time; //avoid start lag
		frameTimer_ += time - lastframe_;
		lastframe_ = time;

		if (frameTimer_ >= MS_IN_SECOND / data_->fps_) //next frame
		{
			//if it is the last one
			if (frameCol_ == data_->frameEndCol_ - 1 && frameFil_ == data_->frameEndFil_ - 1)
			{
				if (data_->loop_) //loop or not
				{
					send(&Message(ANIMATION_LOOPED));
					frameCol_ = data_->frameStartCol_ - 1;
					frameFil_ = data_->frameStartFil_ - 1;
				}
				else stop(); //stop
			}

			else //not the last frame
			{
				frameTimer_ -= MS_IN_SECOND / data_->fps_; //preserve extra ms
				frameCol_++;

				if (frameCol_ == image_->getCols()) //last col
				{
					frameCol_ = 0;
					frameFil_++;

					//you write the last frame, so no need to check last fil for loop

					//if (frameFil_ == image_->getFils()) //last fil
					//{
					//	if (data_->loop_) //loop or not
					//	{
					//		frameCol_ = data_->frameStartCol_ - 1;
					//		frameFil_ = data_->frameStartFil_ - 1;
					//	}
					//	else on_ = false;
					//}
				}
			}
		}
	}
}
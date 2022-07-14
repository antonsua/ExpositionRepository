#include "Transformable.h"

Transformable::Transformable() : Physical(), scale_(Vector2D::_UNIT_)
{
}

Transformable::~Transformable() {
}

///////////////////////////////////////////////////////////////////////////////

void Transformable::update(Uint32 time)
{
	if (resize_) resize(time);

	if (move_) move(time);
	else if (moveSmooth_) moveSmooth(time);
}

void Transformable::cancelMovement()
{
	move_ = false;
	moveSmooth_ = false;

	smoothOrigin_.setNull();
	smoothPoint_.setNull();
	smoothVel_.setNull();

	smoothTime_ = 0;
	smoothTotalTime_ = 0;
}

void Transformable::calcelResizing()
{
	resize_ = false;

	resizeVel_.setNull();
	resizeScale_.setNull();

	resizeTime_ = 0;
}

///////////////////////////////////////////////////////////////////////////////

void Transformable::resizeToScale(Vector2D scale, Uint32 duration)
{
	calcelResizing();
	if (scale_ != scale)
	{
		resize_ = true;

		//get scaleUnits/ms
		Vector2D vec = scale - scale_;
		resizeVel_ = Vector2D(vec.getX() / duration, vec.getY() / duration);

		resiceOrigin_ = scale_;
		resizeScale_ = scale;
	}
	else endResizing();
}

void Transformable::moveToPoint(Vector2D point, Uint32 duration)
{
	cancelMovement();
	move_ = true;

	//get pixels/ms
	Vector2D vec = point - position_;
	smoothVel_ = Vector2D(vec.getX() / duration, vec.getY() / duration);

	//setCloseEnough(smoothVel_.magnitude() * velMulCloseEnough_); //auto adjust
	smoothOrigin_ = position_; //store origin
	smoothPoint_ = point;

	checkEnd(false);
	//checkEndSimple();
}

void Transformable::moveSmoothToPoint(Vector2D point, Uint32 maxDuration)
{
	cancelMovement();
	moveSmooth_ = true;

	//setCloseEnough(5);

	setMaxTime(maxDuration);
	smoothPoint_ = point;

	checkEnd(false);
}

///////////////////////////////////////////////////////////////////////////////

void Transformable::setCloseEnough(double margin)
{
	closeEnough_ = margin;
	if (closeEnough_ < minCloseEnough_) closeEnough_ = minCloseEnough_;
}

void Transformable::setMaxTime(Uint32 ms)
{
	maxTime_ = ms;
	if (maxTime_ < minMaxTime_) closeEnough_ = minMaxTime_;
}

bool Transformable::isMoving()
{
	return move_ || moveSmooth_;
}

bool Transformable::isResizing()
{
	return resize_;
}

///////////////////////////////////////////////////////////////////////////////

double Transformable::getWidth() const
{
	return width_ * scale_.getX();
}

double Transformable::getHeight() const
{
	return height_ * scale_.getY();
}

void Transformable::resize(Uint32 time)
{
	if (resizeTime_ == 0) resizeTime_ = time; //start
	else
	{
		//check duration for delta
		Uint32 delta = time - resizeTime_;
		resizeTime_ = time;

		scale_ = scale_ + resizeVel_ * delta;

		//preserve center
		double offsetX = width_ * resizeVel_.getX() * delta;
		double offsetY = height_ * resizeVel_.getY() * delta;
		Vector2D corrector(offsetX / 2, offsetY / 2);
		position_ = position_ - corrector;

		if (move_) smoothPoint_ = smoothPoint_ - corrector; //resize - move correction

		//CHECK END
		Vector2D scaleDiff = scale_ - resiceOrigin_;
		Vector2D targetDiff = resizeScale_ - resiceOrigin_;

		//compere differences from original scale and actual scale to target
		if (scaleDiff.magnitude() + resizeEnough_ >= targetDiff.magnitude())
		{
			scale_ = resizeScale_;
			calcelResizing();
			endResizing();
		}
	}
}

///////////////////////////////////////////////////////////////////////////////

void Transformable::move(Uint32 time)
{
	if (smoothTime_ == 0) smoothTime_ = time; //start
	else
	{
		//check duration for delta
		Uint32 delta = time - smoothTime_;
		smoothTime_ = time;

		position_ = position_ + smoothVel_ * delta;

		checkEndSimple();
	}
}

void Transformable::checkEndSimple()
{
	//distance to origin from position
	Vector2D posDiff = position_ - smoothOrigin_;

	//distance to origin from smoothPoint
	Vector2D smoothDiff = smoothPoint_ - smoothOrigin_;

	//current distance to origin is greater than smoothpoint to origin
	if (posDiff.magnitude() >= smoothDiff.magnitude())
	{
		position_ = smoothPoint_;
		cancelMovement();
		endMovement(false);
	}
	//std::cout << "p: " << posDiff.magnitude() << " s: " << smoothDiff.magnitude() << std::endl;
}

void Transformable::checkEnd(bool maxTime)
{
	//stop if close enough
	Vector2D diff = smoothPoint_ - position_;

	//or too much time
	bool timeOut = false;
	if (maxTime && smoothTotalTime_ > maxTime_) timeOut = true;

	if (diff.magnitude() < closeEnough_ || timeOut)
	{
		cancelMovement();
		endMovement(timeOut);
	}
	//std::cout << "d: " << diff.magnitude() << std::endl;
}

///////////////////////////////////////////////////////////////////////////////

void Transformable::moveSmooth(Uint32 time)
{
	if (smoothTime_ == 0) smoothTime_ = time; //start
	else
	{
		//check duration for delta
		Uint32 delta = time - smoothTime_;
		smoothTime_ = time;
		smoothTotalTime_ += delta;

		smoothMovement(delta);
		checkEnd(true);
	}
}

void Transformable::smoothMovement(Uint32 delta)
{
	//std::cout << "0: v" << velocity_ << " - m" << velocity_.magnitude()
	//	<< " - d" << direction_ << " - p" << position_ << std::endl;

	//update smoothDirection
	Vector2D smoothDir = smoothPoint_ - position_;
	smoothDir.normalize();

	//throttle
	velocity_ = velocity_ + smoothDir * thrust_;

	//update spriteDirection
	direction_ = velocity_;
	direction_.normalize();

	if (velocity_.magnitude() > maxVel_) //keep under max
	{
		velocity_.normalize();
		velocity_ = velocity_ * maxVel_;
	}
	//if to small set 0
	else if (velocity_.magnitude() < epsilon_) velocity_.setNull();

	//apply final velocity
	position_ = position_ + velocity_ * delta / reductionFactor_;

	//std::cout << "1: v" << velocity_ << " - m" << velocity_.magnitude()
	//	<< " - d" << direction_ << " - p" << position_ << std::endl;
}


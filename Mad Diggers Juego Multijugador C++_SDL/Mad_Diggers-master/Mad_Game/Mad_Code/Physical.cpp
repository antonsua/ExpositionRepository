#include "Physical.h"

Vector2D Physical::worldPosition_ = Vector2D(0, 0);


Physical::Physical() : width_(), height_(), position_(), velocity_(), acceleration_()
{
	direction_ = Vector2D::getDefaultZeroAngle();
}

Physical::~Physical() {
}

///////////////////////////////////////////////////////////////////////////////

double Physical::getWidth() const {
	return width_;
}

void Physical::setWidth(double width) {
	width_ = width;
}

double Physical::getHeight() const {
	return height_;
}

void Physical::setHeight(double height) {
	height_ = height;
}

void Physical::scale(double s) {
	width_ *= s;
	height_ *= s;
}

const Vector2D& Physical::getDirection() const {
	return direction_;
}

void Physical::setDirection(const Vector2D &vel) {
	direction_.set(vel);
	direction_.normalize();
}

///////////////////////////////////////////////////////////////////////////////

const Vector2D Physical::getPosition() const
{
	return position_ + worldPosition_;
}

void Physical::setPosition(const Vector2D &pos)
{
	position_.set(pos);
}

const Vector2D& Physical::getObjectPosition() const
{
	return position_;
}

const Vector2D & Physical::getWorldPos()
{
	return worldPosition_;
}

void Physical::setWorldPos(Vector2D &pos)
{
	worldPosition_.set(pos);
}
void Physical::resetWorldPos()
{
	worldPosition_.setNull();
}
void Physical::moveWorldPos(Vector2D pos)
{
	worldPosition_ = worldPosition_ + pos;
}
///////////////////////////////////////////////////////////////////////////////

const Vector2D& Physical::getVelocity() const {
	return velocity_;
}

void Physical::setVelocity(const Vector2D &vel) {
	velocity_.set(vel);
}

const Vector2D & Physical::getAcceleration() const
{
	return acceleration_;
}

void Physical::setAcceleration(const Vector2D & acc)
{
	acceleration_.set(acc);
}

///////////////////////////////////////////////////////////////////////////////
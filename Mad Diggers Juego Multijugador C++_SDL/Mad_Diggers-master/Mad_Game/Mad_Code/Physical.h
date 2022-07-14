//Mad_Diggers

#ifndef PHYSICAL_H_
#define PHYSICAL_H_

#include "Game.h"
#include "Vector2D.h"

struct Circle
{
	double x, y;
	double r;
};

class Physical
{
public:
	Physical(); //no instance use
	virtual ~Physical();

	virtual double getWidth() const;
	void setWidth(double width);
	virtual double getHeight() const;
	void setHeight(double height);
	void scale(double s);

	const Vector2D& getDirection() const;
	void setDirection(const Vector2D &vel);

	const Vector2D getPosition() const;
	void setPosition(const Vector2D &pos);

	const Vector2D& getVelocity() const;
	void setVelocity(const Vector2D &vel);

	const Vector2D& getAcceleration() const;
	void setAcceleration(const Vector2D &acc);

	const Vector2D& getObjectPosition() const;
	static const Vector2D& getWorldPos();
	static void setWorldPos(Vector2D &pos);
	static void resetWorldPos();
	static void moveWorldPos(Vector2D pos);

	virtual Circle getCircle() { return c; };

protected:
	Circle c; //not all entities need circles

	double width_;  // width
	double height_; // height
	Vector2D direction_; // angle in degrees (0) is considered facing left

	Vector2D position_; // position
	Vector2D velocity_; // vel
	Vector2D acceleration_; // acc

	static Vector2D worldPosition_;
};

#endif /* PHYSICALOBJECT_H_ */

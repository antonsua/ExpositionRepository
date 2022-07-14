//Mad_Diggers

#ifndef VECTOR2D_H_
#define VECTOR2D_H_

#include <iostream>

class Vector2D
{
private:
	double x_;  // first coordinate
	double y_;  // second coordinate

	static const Vector2D _DEFAULT_ZERO_ANGLE_; //0 degrees (initialized in cpp)
	static const Vector2D _NULL_; //0 0

public:
	Vector2D();
	Vector2D(const Vector2D &v);
	Vector2D(double x, double y);
	virtual ~Vector2D();

	static const Vector2D _UNIT_; //1 1

	///////////////////////////////////////////////////////////////////

	bool null() { return x_ == _NULL_.getX() && y_ == _NULL_.getY(); };
	void setNull() { x_ = _NULL_.getX(); y_ = _NULL_.getY(); };

	//returns the angle used as 0 degrees
	static const Vector2D& getDefaultZeroAngle() { return _DEFAULT_ZERO_ANGLE_; };

	double getX() const;
	double getY() const;
	void setX(double x);
	void setY(double y);

	void set(const Vector2D &v);
	void set(double x, double y);

	///////////////////////////////////////////////////////////////////

	//returns the vector's module
	double magnitude() const;

	//rotates the vector anti-clockwise
	void rotate(double degrees);

	//returns the vector's angle with respect to defaultZeroAngle_
	double angle() const;
	//returns the vector's angle with respect to given angle
	double angle(const Vector2D& v) const;

	//normalizes the vector (same angle but each component <= 1)
	void normalize();

	///////////////////////////////////////////////////////////////////

	bool operator==(const Vector2D& v) const;
	bool operator!=(const Vector2D& v) const;
	bool operator>(const Vector2D& v) const;
	bool operator>=(const Vector2D& v) const;
	bool operator<(const Vector2D& v) const;
	bool operator<=(const Vector2D& v) const;

	// = vector2D(x1 - x2, y1 - y2)
	Vector2D operator-(const Vector2D& v) const;
	// = vector2D(x1 + x2, y1 + y2)
	Vector2D operator+(const Vector2D& v) const;

	// = vector2D(x1 * d, y1 * d)
	Vector2D operator*(double d) const;
	// = vector2D(x1 / d, y1 / d)
	Vector2D operator/(double d) const;

	// = double(d * x1 + d * y1)
	double operator *(const Vector2D& d) const;

	//multiply both
	Vector2D operator *(const Vector2D& d);
	//divide both
	Vector2D operator /(const Vector2D& d);

	//Easy cout (x, y)
	friend std::ostream& operator<<(std::ostream& os, const Vector2D &v);
};

#endif /* VECTOR2D_H_ */

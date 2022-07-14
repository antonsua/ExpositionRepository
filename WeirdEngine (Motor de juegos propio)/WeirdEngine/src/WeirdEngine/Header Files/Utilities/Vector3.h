#pragma once
#ifndef VECTOR3_H
#define VECTOR3_H

#include <string>

class Vector3 {
public:
	float x;
	float y;
	float z;

public:
	Vector3();
	Vector3(float x, float y, float z);
	~Vector3();

	bool operator==(const Vector3& v) const;
	bool operator!=(const Vector3& v) const;
	Vector3& operator+=(const Vector3& v);
	Vector3& operator-=(const Vector3& v);
	Vector3& operator*=(const Vector3& v);
	Vector3& operator*=(float n);
	Vector3& operator/=(const Vector3& v);
	Vector3& operator/=(float n);
	Vector3& operator+=(float n);
	Vector3& operator-=(float n);

	Vector3& operator=(const Vector3& v);
	Vector3	operator+(const Vector3& v) const;
	Vector3	operator-(const Vector3& v) const;
	Vector3	operator*(const Vector3& v) const;
	Vector3	operator/(const Vector3& v) const;
	Vector3	operator*(float n) const;
	Vector3	operator/(float n) const;

	void normalize();
	double magnitudeSquared() const;
	double magnitude() const;
	Vector3 normalized() const;
	Vector3 cross(const Vector3& v);
	double dot(const Vector3& v);

	Vector3& set(float x, float y, float z);

	std::string toString() const;
};

#endif
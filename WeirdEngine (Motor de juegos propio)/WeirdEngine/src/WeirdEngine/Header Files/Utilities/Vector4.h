#pragma once
#ifndef VECTOR4_H
#define VECTOR4_H

#include <string>

class Vector4 {
public:
	float x;
	float y;
	float z;
	float w;

public:
	Vector4();
	Vector4(float x, float y, float z, float w);
	~Vector4();

	bool operator==(const Vector4& v) const;
	bool operator!=(const Vector4& v) const;
	Vector4& operator+=(const Vector4& v);
	Vector4& operator-=(const Vector4& v);
	Vector4& operator*=(const Vector4& v);
	Vector4& operator*=(float n);
	Vector4& operator/=(const Vector4& v);
	Vector4& operator/=(float n);
	Vector4& operator+=(float n);
	Vector4& operator-=(float n);

	Vector4& operator=(const Vector4& v);
	Vector4	operator+(const Vector4& v) const;
	Vector4	operator-(const Vector4& v) const;
	Vector4	operator*(const Vector4& v) const;
	Vector4	operator/(const Vector4& v) const;
	Vector4	operator*(float n) const;
	Vector4	operator/(float n) const;

	void normalize();
	double magnitudeSquared() const;
	double magnitude() const;
	Vector4 normalized() const;
	double dot(const Vector4& v);

	Vector4& set(float x, float y, float w, float z);

	std::string toString() const;
};

#endif
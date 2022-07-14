#include "Utilities\Vector4.h"

Vector4::Vector4() {
	x = 0;
	y = 0;
	z = 0;
	w = 0;
}

Vector4::Vector4(float x, float y, float z, float w) : x(x), y(y), w(w), z(z) {}

Vector4::~Vector4() {}

bool Vector4::operator==(const Vector4& v) const {
	return (v.x == x) && (v.y == y) && (v.w == w) && (v.z == z);
}

bool Vector4::operator!=(const Vector4& v) const {
	return (v.x != x) || (v.y != y) || (v.w != w) || (v.z != z);
}

Vector4& Vector4::operator+=(const Vector4& v) {
	x += v.x; y += v.y; z += v.z; w += v.w;
	return *this;
}

Vector4& Vector4::operator-=(const Vector4& v) {
	x -= v.x; y -= v.y; z -= v.z; w -= v.w;
	return *this;
}

Vector4& Vector4::operator*=(float n) {
	x *= n;
	y *= n;
	w *= n;
	z *= n;
	return *this;
}

Vector4& Vector4::operator*=(const Vector4& v) {
	x *= v.x;
	y *= v.y;
	w *= v.w;
	z *= v.z;
	return *this;
}

Vector4& Vector4::operator+=(float n) {
	x += n;
	y += n;
	w += n;
	z += n;
	return *this;
}

Vector4& Vector4::operator-=(float n) {
	x -= n;
	y -= n;
	w -= n;
	z -= n;
	return *this;
}

Vector4& Vector4::operator/=(float n) {
	double d = 1.0f / n;
	x *= d;
	y *= d;
	w *= d;
	z *= d;
	return *this;
}

Vector4& Vector4::operator/=(const Vector4& v) {
	x /= v.x;
	y /= v.y;
	w /= v.w;
	z /= v.z;
	return *this;
}

Vector4& Vector4::operator=(const Vector4& v) {
	x = v.x; y = v.y; w = v.w; z = v.z;
	return *this;
}

Vector4 Vector4::operator+(const Vector4& v) const {
	Vector4 res;
	res.x = x + v.x;
	res.y = y + v.y;
	res.w = w + v.w;
	res.z = z + v.z;
	return res;
}

Vector4 Vector4::operator-(const Vector4& v) const {
	Vector4 res;
	res.x = x - v.x;
	res.y = y - v.y;
	res.w = w - v.w;
	res.z = z - v.z;
	return res;
}

Vector4 Vector4::operator*(float n) const {
	Vector4 res;
	res.x = x * n;
	res.y = y * n;
	res.w = w * n;
	res.z = z * n;
	return res;
}

Vector4 Vector4::operator*(const Vector4& v) const {
	Vector4 res;
	res.x = x * v.x;
	res.y = y * v.y;
	res.w = w * v.w;
	res.z = z * v.z;
	return res;
}

Vector4 Vector4::operator/(float n) const {
	Vector4 res;
	res.x = x / n;
	res.y = y / n;
	res.w = w / n;
	res.z = z / n;
	return res;
}

Vector4 Vector4::operator/(const Vector4& v) const {
	Vector4 res;
	res.x = x / v.x;
	res.y = y / v.y;
	res.w = w / v.w;
	res.z = z / v.z;
	return res;
}

void Vector4::normalize() {
	*this /= magnitude();
}

Vector4 Vector4::normalized() const {
	if (x == 0 && y == 0 && w == 0 && z == 0) return *this;
	Vector4 aux = *this / magnitude();
	return aux;
}

double Vector4::dot(const Vector4& v)
{
	return x * v.x + y * v.y + w * v.w + z * v.z;
}

Vector4& Vector4::set(float x, float y, float w, float z) {
	this->x = x;
	this->y = y;
	this->w = w;
	this->z = z;
	return *this;
}

std::string Vector4::toString() const {
	return std::to_string(x) + " " + std::to_string(y) + " " + std::to_string(w) +" " + std::to_string(z);
}

double Vector4::magnitudeSquared() const {
	return x * x + y * y + w * w + z * z;
}

double Vector4::magnitude() const {
	return sqrt(magnitudeSquared());
}
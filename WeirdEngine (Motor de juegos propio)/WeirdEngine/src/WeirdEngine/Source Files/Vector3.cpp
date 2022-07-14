#include "Utilities\Vector3.h"

Vector3::Vector3() {
	x = 0;
	y = 0;
	z = 0;
}

Vector3::Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

Vector3::~Vector3() {}

bool Vector3::operator==(const Vector3& v) const {
	return (v.x == x) && (v.y == y) && (v.z == z);
}

bool Vector3::operator!=(const Vector3& v) const {
	return (v.x != x) || (v.y != y) || (v.z != z);
}

Vector3& Vector3::operator+=(const Vector3& v) {
	x += v.x; y += v.y; z += v.z;
	return *this;
}

Vector3& Vector3::operator-=(const Vector3& v) {
	x -= v.x; y -= v.y; z -= v.z;
	return *this;
}

Vector3& Vector3::operator*=(float n) {
	x *= n;
	y *= n;
	z *= n;
	return *this;
}

Vector3& Vector3::operator*=(const Vector3& v) {
	x *= v.x;
	y *= v.y;
	z *= v.z;
	return *this;
}

Vector3& Vector3::operator+=(float n) {
	x += n;
	y += n;
	z += n;
	return *this;
}

Vector3& Vector3::operator-=(float n) {
	x -= n;
	y -= n;
	z -= n;
	return *this;
}

Vector3& Vector3::operator/=(float n) {
	double d = 1.0f / n;
	x *= d;
	y *= d;
	z *= d;
	return *this;
}

Vector3& Vector3::operator/=(const Vector3& v) {
	x /= v.x;
	y /= v.y;
	z /= v.z;
	return *this;
}

Vector3& Vector3::operator=(const Vector3& v) {
	x = v.x; y = v.y; z = v.z;
	return *this;
}

Vector3 Vector3::operator+(const Vector3& v) const {
	Vector3 res;
	res.x = x + v.x;
	res.y = y + v.y;
	res.z = z + v.z;
	return res;
}

Vector3 Vector3::operator-(const Vector3& v) const {
	Vector3 res;
	res.x = x - v.x;
	res.y = y - v.y;
	res.z = z - v.z;
	return res;
}

Vector3 Vector3::operator*(float n) const {
	Vector3 res;
	res.x = x * n;
	res.y = y * n;
	res.z = z * n;
	return res;
}

Vector3 Vector3::operator*(const Vector3& v) const {
	Vector3 res;
	res.x = x * v.x;
	res.y = y * v.y;
	res.z = z * v.z;
	return res;
}

Vector3 Vector3::operator/(float n) const {
	Vector3 res;
	res.x = x / n;
	res.y = y / n;
	res.z = z / n;
	return res;
}

Vector3 Vector3::operator/(const Vector3& v) const {
	Vector3 res;
	res.x = x / v.x;
	res.y = y / v.y;
	res.z = z / v.z;
	return res;
}

void Vector3::normalize() {
	*this /= magnitude();
}

Vector3 Vector3::normalized() const {
	if (x == 0 && y == 0 && z == 0) return *this;
	Vector3 aux = *this / magnitude();
	return aux;
}

Vector3 Vector3::cross(const Vector3& v)
{
	return Vector3(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
}

double Vector3::dot(const Vector3& v)
{
	return x * v.x + y * v.y + z * v.z;
}

Vector3& Vector3::set(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
	return *this;
}

std::string Vector3::toString() const {
	return std::to_string(x) + " " + std::to_string(y) + " " + std::to_string(z);
}

double Vector3::magnitudeSquared() const {
	return x * x + y * y + z * z;
}

double Vector3::magnitude() const {
	return sqrt(magnitudeSquared());
}
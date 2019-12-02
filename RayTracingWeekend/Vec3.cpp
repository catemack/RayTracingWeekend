#include "Vec3.h"

Vec3::Vec3(float x, float y, float z) : x(x), y(y), z(z) {}

inline Vec3& Vec3::operator+=(const Vec3& other) {
	x += other.x;
	y += other.y;
	z += other.z;
	return *this;
}

inline Vec3& Vec3::operator-=(const Vec3& other) {
	x -= other.x;
	y -= other.y;
	z -= other.z;
	return *this;
}

inline Vec3& Vec3::operator*=(const Vec3& other) {
	x *= other.x;
	y *= other.y;
	z *= other.z;
	return *this;
}

inline Vec3& Vec3::operator/=(const Vec3& other) {
	x /= other.x;
	y /= other.y;
	z /= other.z;
	return *this;
}

inline Vec3& Vec3::operator*=(const float t) {
	x *= t;
	y *= t;
	z *= t;
	return *this;
}

inline Vec3& Vec3::operator/=(const float t) {
	x /= t;
	y /= t;
	z /= t;
	return *this;
}

inline void Vec3::makeUnit() {
	float length = this->length();
	x /= length;
	y /= length;
	z /= length;
}

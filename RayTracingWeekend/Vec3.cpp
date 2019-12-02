#include "Vec3.h"

Vec3::Vec3(float x, float y, float z) : x(x), y(y), z(z) {}

inline float Vec3::length() const {
	return sqrt(x * x + y * y + z * z);
}

inline float Vec3::lengthSquared() const {
	return x * x + y * y + z * z;
}

inline const Vec3& Vec3::operator+() const {
	return *this;
}

inline Vec3 Vec3::operator-() const {
	return Vec3(-x, -y, -z);
}

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

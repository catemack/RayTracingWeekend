#include "Vec3.h"

Vec3::Vec3(float x, float y, float z) : x(x), y(y), z(z) {}

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

inline std::istream& operator>>(std::istream& is, Vec3 &t) {
	is >> t.x >> t.y >> t.z;
	return is;
}

inline std::ostream& operator<<(std::ostream& os, const Vec3& t) {
	os << t.x << " " << t.y << " " << t.z;
	return os;
}

inline void Vec3::makeUnit() {
	float length = this->length();
	x /= length;
	y /= length;
	z /= length;
}

inline Vec3 operator+(const Vec3& v1, const Vec3& v2) {
	return Vec3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

inline Vec3 operator-(const Vec3& v1, const Vec3& v2) {
	return Vec3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

inline Vec3 operator*(const Vec3& v1, const Vec3& v2) {
	return Vec3(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
}

inline Vec3 operator/(const Vec3 v1, const Vec3& v2) {
	return Vec3(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z);
}

inline Vec3 operator*(float t, const Vec3& v) {
	return Vec3(t * v.x, t * v.y, t * v.z);
}

inline Vec3 operator/(Vec3 v, float t) {
	return Vec3(v.x / t, v.y / t, v.z / t);
}

inline Vec3 operator*(const Vec3& v, float t) {
	return Vec3(v.x * t, v.y * t, v.z * t);
}

inline float dot(const Vec3& v1, const Vec3& v2) {
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

inline Vec3 cross(const Vec3& v1, const Vec3& v2) {
	return Vec3((v1.y * v2.z - v1.z * v2.y),
		(-(v1.x * v2.z - v1.z * v2.x)),
		(v1.x * v2.y - v1.y * v2.x));
}

inline Vec3 unitVector(Vec3 v) {
	return v / v.length();
}

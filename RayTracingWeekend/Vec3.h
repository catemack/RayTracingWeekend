#pragma once

#include <math.h>
#include <stdlib.h>
#include <iostream>

class Vec3
{
public:
	Vec3(float x, float y, float z);

	inline const Vec3& operator+() const;
	inline Vec3 operator-() const;
	
	inline Vec3& operator+=(const Vec3 &other);
	inline Vec3& operator-=(const Vec3 &other);
	inline Vec3& operator*=(const Vec3 &other);
	inline Vec3& operator/=(const Vec3& other);
	inline Vec3& operator*=(const float t);
	inline Vec3& operator/=(const float t);

	inline float length() const;
	inline float lengthSquared() const;
	inline void makeUnit();

	float x, y, z;
};

inline std::istream& operator>>(std::istream& is, Vec3& t) {
	is >> t.x >> t.y >> t.z;
	return is;
}

inline std::ostream& operator<<(std::ostream& os, const Vec3& t) {
	os << t.x << " " << t.y << " " << t.z;
	return os;
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

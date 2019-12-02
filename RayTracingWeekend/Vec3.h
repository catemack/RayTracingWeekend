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


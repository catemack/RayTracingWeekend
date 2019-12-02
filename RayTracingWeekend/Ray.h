#pragma once
#include "Vec3.h"

class Ray
{
public:
	Ray(const Vec3& a, const Vec3& b);

	Vec3 origin() const;
	Vec3 direction() const;
	Vec3 pointAt(float t) const;

private:
	Vec3 A, B;
};


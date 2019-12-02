#pragma once

#include "Hitable.h"

class Sphere : public Hitable
{
public:
	Sphere(Vec3 cen, float r) : center(cen), radius(r) {};

	virtual bool hit(const Ray& r, float tMin, float tMax, hitRecord& record) const;

	Vec3 center;
	float radius;
};

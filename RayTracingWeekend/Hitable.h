#pragma once

#include "Ray.h"

struct hitRecord {
	float t;
	Vec3 p;
	Vec3 normal;
};

class Hitable
{
public:
	virtual bool hit(const Ray& r, float tMin, float tMax, hitRecord& record) const = 0;
};
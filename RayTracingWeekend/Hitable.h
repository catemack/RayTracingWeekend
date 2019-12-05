#pragma once

#include "Material.h"
#include "Ray.h"
#include "HitRecord.h"

class Material;

class Hitable
{
public:
	virtual bool hit(const Ray& r, float tMin, float tMax, HitRecord& record) const = 0;
};

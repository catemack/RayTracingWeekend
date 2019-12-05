#pragma once

#include "Common.h"
#include "Hitable.h"
#include "HitRecord.h"
#include "Ray.h"

class Material {
public:
	virtual bool scatter(const Ray& r_in, const HitRecord& record, Vec3& attenuation, Ray& scattered) const = 0;
};

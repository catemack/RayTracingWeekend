#pragma once

#include "Common.h"
#include "Hitable.h"
#include "Material.h"
#include "Ray.h"

class Sphere : public Hitable
{
public:
	Sphere(Vec3 cen, float r, std::shared_ptr<Material> mat) : center(cen), radius(r), material(mat) {};

	virtual bool hit(const Ray& r, float tMin, float tMax, HitRecord& record) const;

	Vec3 center;
	float radius;
	std::shared_ptr<Material> material;
};

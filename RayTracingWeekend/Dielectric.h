#pragma once

#include "Material.h"

class Dielectric : public Material
{
public:
	Dielectric(float ri) : refIndex(ri) {}

	virtual bool scatter(const Ray& rIn, const HitRecord& record, Vec3& attenuation, Ray& scattered) const;

private:
	float refIndex;
};

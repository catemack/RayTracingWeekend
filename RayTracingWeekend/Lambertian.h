#pragma once

#include "Material.h"

class Lambertian : public Material
{
public:
	Lambertian(const Vec3& a) : albedo(a) {}

	virtual bool scatter(const Ray& rIn, const HitRecord& record, Vec3& attenuation, Ray& scattered) const;

private:
	Vec3 albedo;
};


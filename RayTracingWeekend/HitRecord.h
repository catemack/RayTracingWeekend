#pragma once

#include "Common.h"
#include "Material.h"

class Material;

struct HitRecord {
	float t;
	Vec3 p;
	Vec3 normal;
	std::shared_ptr<Material> material;
};

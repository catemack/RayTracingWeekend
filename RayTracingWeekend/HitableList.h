#pragma once

#include "Hitable.h"

class HitableList : public Hitable
{
public:
	HitableList(std::vector<std::unique_ptr<Hitable>> l) : list(std::move(l)) {}

	virtual bool hit(const Ray& r, float tMin, float tMax, HitRecord& record) const;

	std::vector<std::unique_ptr<Hitable>> list;
};

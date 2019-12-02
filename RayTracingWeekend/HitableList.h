#pragma once

#include <vector>
#include <memory>
#include "Hitable.h"

class HitableList : public Hitable
{
public:
	//HitableList() {}
	//HitableList(std::vector<std::unique_ptr<Hitable>> l) : list(l) {}
	HitableList(Hitable** l, int n) { list = l; listSize = n; }

	virtual bool hit(const Ray& r, float tMin, float tMax, hitRecord& record) const;

	//std::vector<std::unique_ptr<Hitable>> list;
	Hitable** list;
	int listSize;
};

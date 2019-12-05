#include "HitableList.h"

bool HitableList::hit(const Ray& r, float tMin, float tMax, HitRecord& record) const {
	HitRecord tempRecord;
	bool hitAnything = false;
	double closest = tMax;

	for (auto& hitable : list) {
		if (hitable->hit(r, tMin, closest, tempRecord)) {
			hitAnything = true;
			closest = tempRecord.t;
			record = tempRecord;
		}
	}

	return hitAnything;
}

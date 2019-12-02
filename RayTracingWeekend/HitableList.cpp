#include "HitableList.h"

bool HitableList::hit(const Ray& r, float tMin, float tMax, hitRecord& record) const {
	hitRecord tempRecord;
	bool hitAnything = false;
	double closest = tMax;

	/*for (auto& hitable : list) {
		if (hitable->hit(r, tMin, closest, tempRecord)) {
			hitAnything = true;
			closest = tempRecord.t;
			record = tempRecord;
		}
	}*/

	for (int i = 0; i < listSize; i++) {
		if (list[i]->hit(r, tMin, closest, tempRecord)) {
			hitAnything = true;
			closest = tempRecord.t;
			record = tempRecord;
		}
	}

	return hitAnything;
}

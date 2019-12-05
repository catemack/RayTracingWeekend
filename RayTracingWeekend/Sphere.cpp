#include "Sphere.h"

bool Sphere::hit(const Ray& r, float tMin, float tMax, HitRecord& record) const {
	Vec3 oc = r.origin() - center;

	float a = dot(r.direction(), r.direction());
	float b = dot(oc, r.direction());
	float c = dot(oc, oc) - radius * radius;

	float discriminant = b * b - a * c;
	if (discriminant > 0) {
		float temp = (-b - sqrt(discriminant)) / a;
		if (temp < tMax && temp > tMin) {
			record.t = temp;
			record.p = r.pointAt(record.t);
			record.normal = (record.p - center) / radius;
			record.material = material;
			return true;
		}

		temp = (-b + sqrt(discriminant)) / a;
		if (temp < tMax && temp > tMin) {
			record.t = temp;
			record.p = r.pointAt(record.t);
			record.normal = (record.p - center) / radius;
			record.material = material;
			return true;
		}
	}

	return false;
}

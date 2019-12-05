#include "Lambertian.h"

bool Lambertian::scatter(const Ray& r_in, const HitRecord& record, Vec3& attenuation, Ray& scattered) const {
	Vec3 target = record.p + record.normal + randomPointInUnitSphere();
	scattered = Ray(record.p, target - record.p);
	attenuation = albedo;
	return true;
}

#include "Metal.h"

bool Metal::scatter(const Ray& rIn, const HitRecord& record, Vec3& attenuation, Ray& scattered) const {
	Vec3 reflected = reflect(unitVector(rIn.direction()), record.normal);
	scattered = Ray(record.p, reflected);
	attenuation = albedo;
	return (dot(scattered.direction(), record.normal) > 0);
}

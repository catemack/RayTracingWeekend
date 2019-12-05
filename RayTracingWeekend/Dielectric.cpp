#include "Dielectric.h"

bool Dielectric::scatter(const Ray& rIn, const HitRecord& record, Vec3& attenuation, Ray& scattered) const {
	Vec3 outwardNormal;
	Vec3 reflected = reflect(rIn.direction(), record.normal);
	float ni_over_nt;
	attenuation = Vec3(1.0, 1.0, 1.0);
	Vec3 refracted;
	float reflectProb;
	float cosine;

	if (dot(rIn.direction(), record.normal) > 0) {
		outwardNormal = -record.normal;
		ni_over_nt = refIndex;
		cosine = dot(rIn.direction(), record.normal) / rIn.direction().length();
		cosine = sqrt(1 - refIndex * refIndex * (1 - cosine * cosine));
	}
	else {
		outwardNormal = record.normal;
		ni_over_nt = 1.0 / refIndex;
		cosine = -dot(rIn.direction(), record.normal) / rIn.direction().length();
	}

	if (refract(rIn.direction(), outwardNormal, ni_over_nt, refracted)) {
		reflectProb = schlick(cosine, refIndex);
	}
	else {
		reflectProb = 1.0;
	}

	if (randomFloat() < reflectProb) {
		scattered = Ray(record.p, reflected);
	}
	else {
		scattered = Ray(record.p, refracted);
	}

	return true;
}

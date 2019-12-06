#include "Camera.h"

Camera::Camera(Vec3 lookFrom, Vec3 lookAt, Vec3 up, float vfov, float aspect, float aperture, float focusDist) {
	lensRadius = aperture / 2;

	float theta = vfov * PI / 180;
	float halfHeight = tan(theta / 2);
	float halfWidth = aspect * halfHeight;

	origin = lookFrom;

	w = unitVector(lookFrom - lookAt); // camera back
	u = unitVector(cross(up, w)); // camera right
	v = cross(w, u); // camera up

	lowerLeft = origin - halfWidth * focusDist * u - halfHeight * focusDist * v - focusDist * w;
	horizontal = 2 * halfWidth * u;
	vertical = 2 * halfHeight * v;
}

Ray Camera::getRay(float s, float t) const {
	Vec3 randomOnDisk = lensRadius * randomPointInUnitDisk();
	Vec3 offset = u * randomOnDisk.x + v * randomOnDisk.y;
	return Ray(origin + offset, lowerLeft + s * horizontal + t * vertical - origin - offset);
}

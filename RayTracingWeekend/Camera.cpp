#include "Camera.h"

Camera::Camera(Vec3 lookFrom, Vec3 lookAt, Vec3 up, float vfov, float aspect) {
	Vec3 u, v, w;
	float theta = vfov * PI / 180;
	float halfHeight = tan(theta / 2);
	float halfWidth = aspect * halfHeight;

	origin = lookFrom;

	w = unitVector(lookFrom - lookAt); // camera back
	u = unitVector(cross(up, w)); // camera right
	v = cross(w, u); // camera up

	lowerLeft = origin - halfWidth * u - halfHeight * v - w;
	horizontal = 2 * halfWidth * u;
	vertical = 2 * halfHeight * v;
}

Ray Camera::getRay(float u, float v) {
	return Ray(origin, lowerLeft + u * horizontal + v * vertical - origin);
}

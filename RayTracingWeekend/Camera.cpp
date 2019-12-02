#include "Camera.h"

Camera::Camera() :
	lowerLeft(-2.0, -1.0, -1.0),
	horizontal(4.0, 0.0, 0.0),
	vertical(0.0, 2.0, 0.0),
	origin(0.0, 0.0, 0.0)
{
}

Ray Camera::getRay(float u, float v) {
	return Ray(origin, lowerLeft + u * horizontal + v * vertical - origin);
}

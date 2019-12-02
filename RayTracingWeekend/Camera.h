#pragma once

#include "Ray.h"

class Camera
{
public:
	Camera();

	Ray getRay(float u, float v);

private:
	Vec3 origin;
	Vec3 lowerLeft;
	Vec3 horizontal;
	Vec3 vertical;
};


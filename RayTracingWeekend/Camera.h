#pragma once

#include "Common.h"
#include "Ray.h"

class Camera
{
public:
	Camera(Vec3 lookFrom, Vec3 lookAt, Vec3 up, float vfov, float aspect);

	Ray getRay(float u, float v);

private:
	Vec3 origin;
	Vec3 lowerLeft;
	Vec3 horizontal;
	Vec3 vertical;
};


#pragma once

#include <fstream>
#include <limits>
#include <functional>
#include <random>
#include <memory>
#include <vector>

#include "Vec3.h"

const float PI = 3.1415927;

// Generates a random float [0.0, 1.0)
static inline float randomFloat() {
	static std::uniform_real_distribution<float> distribution(0.0, 1.0);
	static std::mt19937 generator;
	static std::function<float()> randGenerator =
		std::bind(distribution, generator);
	return randGenerator();
}

static Vec3 randomPointInUnitSphere() {
	Vec3 p;

	// Sample points inside unit cube until we get one inside the sphere
	do {
		p = 2.0 * Vec3(randomFloat(), randomFloat(), randomFloat()) - Vec3(1, 1, 1);
	} while (p.lengthSquared() >= 1.0);

	return p;
}

static Vec3 randomPointInUnitDisk() {
	Vec3 p;

	do {
		p = 2.0 * Vec3(randomFloat(), randomFloat(), 0) - Vec3(1, 1, 0);
	} while (dot(p, p) >= 1.0);

	return p;
}

static Vec3 reflect(const Vec3& v, const Vec3& n) {
	return v - 2 * dot(v, n) * n;
}

static bool refract(const Vec3& v, const Vec3& n, float ni_over_nt, Vec3& refracted) {
	Vec3 uv = unitVector(v);
	float dt = dot(uv, n);
	float discriminant = 1.0 - ni_over_nt * ni_over_nt * (1.0 - dt * dt);

	if (discriminant > 0) {
		refracted = ni_over_nt * (uv - n * dt) - n * sqrt(discriminant);
		return true;
	}
	else
		return false;
}

static float schlick(float cosine, float refIndex) {
	float r0 = (1 - refIndex) / (1 + refIndex);
	r0 = r0 * r0;
	return r0 + (1 - r0) * powf((1 - cosine), 5);
}

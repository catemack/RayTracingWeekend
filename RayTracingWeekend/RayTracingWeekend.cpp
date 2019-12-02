#include <iostream>
#include <fstream>
#include <limits>
#include <functional>
#include <random>

#include "Sphere.h"
#include "HitableList.h"
#include "Camera.h"

// Generates a random float [0.0, 1.0)
inline float randomFloat() {
	static std::uniform_real_distribution<float> distribution(0.0, 1.0);
	static std::mt19937 generator;
	static std::function<float()> randGenerator =
		std::bind(distribution, generator);
	return randGenerator();
}

Vec3 randomPointInUnitSphere() {
	Vec3 p;

	// Sample points inside unit cube until we get one inside the sphere
	do {
		p = 2.0 * Vec3(randomFloat(), randomFloat(), randomFloat()) - Vec3(1, 1, 1);
	} while (p.lengthSquared() >= 1.0);

	return p;
}

// Consumes a ray and returns a color
// Color is based on the normal of the first intersection
// Otherwise, apply a blue-white gradient based on height
Vec3 color(const Ray& r, Hitable *world) {
	hitRecord record;
	if (world->hit(r, 0.001, std::numeric_limits<float>::infinity(), record)) {
		Vec3 target = record.p + record.normal + randomPointInUnitSphere();
		return 0.5 * color(Ray(record.p, target - record.p), world);
	}
	else {
		Vec3 unitDirection = unitVector(r.direction());
		float t = 0.5 * (unitDirection.y + 1.0);

		return (1.0 - t) * Vec3(1.0, 1.0, 1.0) + t * Vec3(0.5, 0.7, 1.0);
	}
}

int main()
{
	int nx = 200; // image width
	int ny = 100; // image height
	int ns = 100; // number of samples for anti-aliasing
	float gamma = 2.0;

	// Initialize the output file
	std::ofstream fout("output.ppm");

	// PPM file info (dimensions, color max)
	fout << "P3\n" << nx << " " << ny << "\n255\n";

	// Initialize some spheres
	std::vector<std::unique_ptr<Hitable>> list;
	list.push_back(std::make_unique<Sphere>(Vec3(0, 0, -1), 0.5));
	list.push_back(std::make_unique<Sphere>(Vec3(0, -100.5, -1), 100));

	// Initialize the world and camera
	Hitable* world = new HitableList(std::move(list));
	Camera camera;

	// For each pixel
	for (int j = ny - 1; j >= 0; j--) {
		for (int i = 0; i < nx; i++) {
			// Take ns samples for anti-aliasing
			Vec3 col(0, 0, 0);
			for (int s = 0; s < ns; s++) {
				float u = (float(i) + randomFloat()) / float(nx);
				float v = (float(j) + randomFloat()) / float(ny);

				Ray r = camera.getRay(u, v);
				col += color(r, world);
			}
			col /= float(ns);

			// Gamma correction
			col = Vec3(powf(col.x, 1.0 / gamma), powf(col.y, 1.0 / gamma), powf(col.z, 1.0 / gamma));

			int ir = int(255.99 * col.x);
			int ig = int(255.99 * col.y);
			int ib = int(255.99 * col.z);

			fout << ir << " " << ig << " " << ib << std::endl;
		}
	}

	// Close file stream
	fout.close();
}

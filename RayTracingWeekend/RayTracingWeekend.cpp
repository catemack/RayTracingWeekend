// RayTracingWeekend.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <limits>
#include <functional>
#include <random>

#include "Sphere.h"
#include "HitableList.h"
#include "Camera.h"

inline float randomFloat() {
	static std::uniform_real_distribution<float> distribution(0.0, 1.0);
	static std::mt19937 generator;
	static std::function<float()> randGenerator =
		std::bind(distribution, generator);
	return randGenerator();
}

Vec3 color(const Ray& r, Hitable *world) {
	hitRecord record;
	if (world->hit(r, 0.0, std::numeric_limits<float>::infinity(), record)) {
		return 0.5 * Vec3(record.normal.x + 1, record.normal.y + 1, record.normal.z + 1);
	}
	else {
		Vec3 unitDirection = unitVector(r.direction());
		float t = 0.5 * (unitDirection.y + 1.0);

		return (1.0 - t) * Vec3(1.0, 1.0, 1.0) + t * Vec3(0.5, 0.7, 1.0);
	}
}

int main()
{
	int nx = 200;
	int ny = 100;
	int ns = 100;

	std::ofstream fout("output.ppm");

	fout << "P3\n" << nx << " " << ny << "\n255\n";

	std::vector<std::unique_ptr<Hitable>> list;
	list.push_back(std::make_unique<Sphere>(Vec3(0, 0, -1), 0.5));
	list.push_back(std::make_unique<Sphere>(Vec3(0, -100.5, -1), 100));

	Hitable* world = new HitableList(std::move(list));
	Camera camera;

	for (int j = ny - 1; j >= 0; j--) {
		for (int i = 0; i < nx; i++) {
			Vec3 col(0, 0, 0);
			for (int s = 0; s < ns; s++) {
				float u = (float(i) + randomFloat()) / float(nx);
				float v = (float(j) + randomFloat()) / float(ny);

				Ray r = camera.getRay(u, v);
				col += color(r, world);
			}
			col /= float(ns);

			int ir = int(255.99 * col.x);
			int ig = int(255.99 * col.y);
			int ib = int(255.99 * col.z);

			fout << ir << " " << ig << " " << ib << std::endl;
		}
	}

	fout.close();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

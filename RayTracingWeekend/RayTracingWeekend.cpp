// RayTracingWeekend.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>

#include "ray.h"

Vec3 color(const Ray& r) {
	Vec3 unitDirection = unitVector(r.direction());
	float t = 0.5 * (unitDirection.y + 1.0);

	return (1.0 - t) * Vec3(1.0, 1.0, 1.0) + t * Vec3(0.5, 0.7, 1.0);
}

int main()
{
	int nx = 200;
	int ny = 100;

	std::ofstream fout("output.ppm");

	fout << "P3\n" << nx << " " << ny << "\n255\n";

	Vec3 lowerLeft(-2.0, -1.0, -1.0);
	Vec3 horizontal(4.0, 0.0, 0.0);
	Vec3 vertical(0.0, 2.0, 0.0);
	Vec3 origin(0.0, 0.0, 0.0);

	for (int j = ny - 1; j >= 0; j--) {
		for (int i = 0; i < nx; i++) {
			//Vec3 col(float(i) / float(nx), float(j) / float(ny), 0.2);

			float u = float(i) / float(nx);
			float v = float(j) / float(ny);

			Ray r(origin, lowerLeft + u * horizontal + v * vertical);
			Vec3 col = color(r);

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

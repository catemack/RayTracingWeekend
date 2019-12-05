#include "Common.h"
#include "Sphere.h"
#include "Lambertian.h"
#include "Metal.h"
#include "Dielectric.h"
#include "HitableList.h"
#include "Camera.h"

const int maxDepth = 50;

// Consumes a ray and returns a color
// Color is based on the normal of the first intersection
// Otherwise, apply a blue-white gradient based on height
Vec3 color(const Ray& r, Hitable *world, int depth) {
	HitRecord record;
	if (world->hit(r, 0.001, std::numeric_limits<float>::infinity(), record)) {
		Ray scattered;
		Vec3 attenuation;

		if (depth < maxDepth && record.material->scatter(r, record, attenuation, scattered)) {
			return attenuation * color(scattered, world, depth + 1);
		}

		Vec3 target = record.p + record.normal + randomPointInUnitSphere();
		return 0.5 * color(Ray(record.p, target - record.p), world, depth + 1);
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
	int ns = 50; // number of samples for anti-aliasing
	float gamma = 2.0;

	// Initialize the output file
	std::ofstream fout("output.ppm");

	// PPM file info (dimensions, color max)
	fout << "P3\n" << nx << " " << ny << "\n255\n";

	// Initialize some spheres
	std::vector<std::unique_ptr<Hitable>> list;
	list.push_back(std::make_unique<Sphere>(Vec3(0, 0, -1), 0.5, std::make_shared<Lambertian>(Vec3(0.8, 0.3, 0.3))));
	list.push_back(std::make_unique<Sphere>(Vec3(0, -100.5, -1), 100, std::make_shared<Lambertian>(Vec3(0.8, 0.8, 0.0))));
	list.push_back(std::make_unique<Sphere>(Vec3(1, 0, -1), 0.5, std::make_shared<Metal>(Vec3(0.8, 0.6, 0.2))));
	list.push_back(std::make_unique<Sphere>(Vec3(-1, 0, -1), 0.5, std::make_shared<Dielectric>(1.5)));

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
				col += color(r, world, 0);
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

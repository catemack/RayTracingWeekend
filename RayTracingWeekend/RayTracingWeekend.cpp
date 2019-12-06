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
Vec3 color(const Ray& r, const Hitable *world, int depth) {
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

Hitable* randomScene() {
	std::vector<std::unique_ptr<Hitable>> out;

	out.push_back(std::make_unique<Sphere>(Vec3(0, -1000, -1), 1000, std::make_shared<Lambertian>(Vec3(0.5, 0.5, 0.5))));

	for (int i = -10; i <= 10; i++) {
		for (int j = -10; j <= 10; j++) {
			Vec3 pos(i + 0.9 * randomFloat(), 0.2, j + 0.9 * randomFloat());
			float size = randomFloat() / 4.0;
			float randMaterial = randomFloat();
			if (randMaterial < 0.8) {
				out.push_back(std::make_unique<Sphere>(pos, size, std::make_shared<Lambertian>(Vec3(
					randomFloat() * randomFloat(),
					randomFloat() * randomFloat(),
					randomFloat() * randomFloat()))));
			}
			else if (randMaterial < 0.95) {
				out.push_back(std::make_unique<Sphere>(pos, size, std::make_shared<Metal>(Vec3(
					0.5 * (1.0 + randomFloat()), 0.5 * (1.0 + randomFloat()), 0.5 * (1.0 + randomFloat())))));
			}
			else {
				out.push_back(std::make_unique<Sphere>(pos, size, std::make_shared<Dielectric>(1.5)));
			}
		}
	}

	out.push_back(std::make_unique<Sphere>(Vec3(0, 1, 0), 1.0, std::make_shared<Lambertian>(Vec3(0.8, 0.3, 0.3))));
	out.push_back(std::make_unique<Sphere>(Vec3(-4, 1, 0), 1.0, std::make_shared<Metal>(Vec3(0.7, 0.6, 0.5))));
	out.push_back(std::make_unique<Sphere>(Vec3(4, 1, 0), 1.0, std::make_shared<Dielectric>(1.5)));

	return new HitableList(std::move(out));
}

void render(const int nx, const int ny, const int ns, const float gamma, const Camera& camera, const Hitable* world, std::shared_ptr<std::vector<std::vector<Vec3>>> result) {
	for (int j = 0; j < ny; j++) {
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

			(*result)[ny-j-1][i] = Vec3(ir, ig, ib);
		}
	}
}

int main()
{
	int nx = 400; // image width
	int ny = 200; // image height
	int ns = 10; // number of samples for anti-aliasing
	float gamma = 2.0;
	const int numThreads = 2;

	// Initialize the world and camera
	Hitable* world = randomScene();

	Vec3 lookFrom(13, 5, 3);
	Vec3 lookAt(0, 0, 0);
	float distToFocus = 1.0;
	float aperture = 0.002;

	Camera camera(lookFrom, lookAt, Vec3(0, 1, 0), 20, float(nx) / float(ny), aperture, distToFocus);

	// Spin up the threads
	std::vector<std::shared_ptr<std::vector<std::vector<Vec3>>>> results;
	std::vector<std::thread> threads;
	for (int i = 0; i < numThreads; i++) {
		// Set up the result container for the thread
		std::vector<std::vector<Vec3>> result(ny, std::vector<Vec3>(nx));
		auto resultPtr = std::make_shared<std::vector<std::vector<Vec3>>>(result);
		results.push_back(resultPtr);

		// Spin up the thread
		threads.push_back(std::thread(render, nx, ny, ns, gamma, camera, world, resultPtr));
	}

	// Wait for the threads
	for (std::thread& t : threads) {
		if (t.joinable())
			t.join();
	}

	// Average the results
	std::vector<std::vector<Vec3>> finalResult(ny, std::vector<Vec3>(nx));
	for (int j = 0; j < ny; j++) {
		std::vector<Vec3> result;

		for (int i = 0; i < nx; i++) {
			Vec3 pixel(0.0, 0.0, 0.0);

			for (int k = 0; k < numThreads; k++)
				pixel += (*(results[k]))[ny-j-1][i];

			pixel /= numThreads;
			result.push_back(pixel);
		}

		finalResult.at(ny-j-1) = result;
	}

	// Initialize the output file
	std::ofstream fout("output.ppm");

	// PPM file info (dimensions, color max)
	fout << "P3\n" << nx << " " << ny << "\n255\n";

	for (auto col : finalResult) {
		for (auto pixel : col) {
			fout << pixel.x << " " << pixel.y << " " << pixel.z << std::endl;
		}
	}

	// Close file stream
	fout.close();
}

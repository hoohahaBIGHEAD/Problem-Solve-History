#include <omp.h>
#include <stdio.h>
#include<stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

#define CUDA 0
#define OPENMP 1
#define SPHERES 20

#define rnd( x ) (x * rand() / RAND_MAX)
#define INF 2e10f
#define DIM 2048

struct Sphere {
	float   r, b, g;
	float   radius;
	float   x, y, z;
	float hit(float ox, float oy, float* n) {
		float dx = ox - x;
		float dy = oy - y;
		if (dx * dx + dy * dy < radius * radius) {
			float dz = sqrtf(radius * radius - dx * dx - dy * dy);
			*n = dz / sqrtf(radius * radius);
			return dz + z;
		}
		return -INF;
	}
};

void kernel(int x, int y, Sphere* temp_s, unsigned char* bitmap)
{
	int offset = x + y * DIM;
	float ox = (x - DIM / 2);
	float oy = (y - DIM / 2);

	float r = 0, g = 0, b = 0;
	float   maxz = -INF;

	for (int i = 0; i < SPHERES; i++) {
		float   n;
		float   t = temp_s[i].hit(ox, oy, &n);
		if (t > maxz) {
			float fscale = n;
			r = temp_s[i].r * fscale;
			g = temp_s[i].g * fscale;
			b = temp_s[i].b * fscale;
			maxz = t;
		}
	}

	bitmap[offset * 4 + 0] = (int)(r * 255);
	bitmap[offset * 4 + 1] = (int)(g * 255);
	bitmap[offset * 4 + 2] = (int)(b * 255);
	bitmap[offset * 4 + 3] = 255;
}

void ppm_write(unsigned char* bitmap, int xdim, int ydim, FILE* fp)
{
	int i, x, y;
	fprintf(fp, "P3\n");
	fprintf(fp, "%d %d\n", xdim, ydim);
	fprintf(fp, "255\n");
	for (y = 0; y < ydim; y++) {
		for (x = 0; x < xdim; x++) {
			i = x + y * xdim;
			fprintf(fp, "%d %d %d ", bitmap[4 * i], bitmap[4 * i + 1], bitmap[4 * i + 2]);
		}
		fprintf(fp, "\n");
	}
}

int main(int argc, char* argv[]) {

	int no_threads = 1;	//default
	int option;
	unsigned char* bitmap;

	clock_t start, end;
	srand(time(NULL));

	if (argc != 2) {
		printf("> type number of threads\n");
		printf("for example, '> openmp_ray.exe 8' means executing OpenMP with 8 threads\n");
		exit(0);
	}

	FILE* fp = fopen("result.ppm", "w");
	option = OPENMP;
	no_threads = atoi(argv[1]);

	Sphere* temp_s = (Sphere*)malloc(sizeof(Sphere) * SPHERES);
	for (int i = 0; i < SPHERES; i++) {
		temp_s[i].r = rnd(1.0f);
		temp_s[i].g = rnd(1.0f);
		temp_s[i].b = rnd(1.0f);
		temp_s[i].x = rnd(2000.0f) - 1000;
		temp_s[i].y = rnd(2000.0f) - 1000;
		temp_s[i].z = rnd(2000.0f) - 1000;
		temp_s[i].radius = rnd(200.0f) + 40;
	}

	bitmap = (unsigned char*)malloc(sizeof(unsigned char) * DIM * DIM * 4);

	start = clock();
	omp_set_dynamic(0);
	omp_set_num_threads(no_threads);
#pragma omp parallel for
	for (int x = 0; x < DIM; x++) {
		for (int y = 0; y < DIM; y++)
			kernel(x, y, temp_s, bitmap);
	}
	ppm_write(bitmap, DIM, DIM, fp);

	fclose(fp);
	free(bitmap);
	free(temp_s);
	end = clock();
	double result = (double)(end - start);
	printf("OpenMP (%d threads) ray tracing: %.4f sec\n", no_threads, result / 1000);
	printf(" [result.ppm] was generated.\n");

	return 0;
}


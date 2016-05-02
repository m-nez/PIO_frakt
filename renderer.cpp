#include "renderer.hpp"

Renderer::Renderer() {

}

Renderer::Renderer(std::string id, void (*function)(Plane*)) {
	this->id = id;
	this->function = function;
}

void Renderer::render() {
	function(plane);
}

static void color(double x, unsigned char* pixel) {
	unsigned char color_min[] = {0, 255, 255};
	unsigned char color_max[] = {255, 0, 0};

	for(int i = 0; i < 3; ++i) {
		pixel[i] = color_min[i] * (1.0 - x)  + color_max[i] * x;
	}
}

void test_func(Plane* plane) {
	int i, j, k;
	double val;
	double x, y;
	double dx = (plane->right - plane->left) / plane->width; /* Left -> Right */
	double dy = -(plane->up - plane->down) / plane->height; /* Up -> Down */

	for(i = 0, y = plane->up; i < plane->height; ++i, y += dy) {
		for(j = 0, x = plane->left; j < plane->width; j++, x += dx) {
			val = (x + y*y*y)/2;
			for (k = 0; k < 10; ++k) {
				val = val * val - 2 + ((x*x+y*y)/16);
			}

			val += 2;
			val /= 4;

			color(val, plane->data + (i*plane->width + j)*3);
		}
	}
}

void set_Mandelbrot(Plane* plane) {
	int i, j, k;
	double series[2];
	double tmpserie;
	double val;
	double x, y;
	double dx = (plane->right - plane->left) / (double)(plane->width); /* Left -> Right */
	double dy = -(plane->up - plane->down) / (double)(plane->height); /* Up -> Down */

	for(i = 0, y = plane->up; i < plane->height; ++i, y += dy) {
		for(j = 0, x = plane->left; j < plane->width; j++, x += dx) {
			series[0]=0;
			series[1]=0;
			for (k = 0; k < 10000; ++k) {
				tmpserie = series[0]*series[0] - series[1]*series[1] + x;
				series[1] = 2*series[0]*series[1] + y;
				series[0] = tmpserie;
				if ((series[0]*series[0] + series[1]*series[1]) > 4)
					break;
			}

			val = (double)k/10000;

			color( val, plane->data + (i*plane->width + j)*3);
		}
	}
}

void set_Julia(Plane* plane) {
	int i, j, k;
	double series[2];
	double tmpserie;
	double c[2] = {-0.123, 0.745};
	double val;
	double x, y;
	double dx = (plane->right - plane->left) / plane->width; /* Left -> Right */
	double dy = -(plane->up - plane->down) / plane->height; /* Up -> Down */

	for(i = 0, y = plane->up; i < plane->height; ++i, y += dy) {
		for(j = 0, x = plane->left; j < plane->width; j++, x += dx) {
			series[0]=x;
			series[1]=y;
			for (k = 0; k < 1000; ++k) {
				tmpserie = series[0]*series[0] - series[1]*series[1] + c[0];
				series[1] = 2*series[0]*series[1] + c[1];
				series[0] = tmpserie;
				if ((series[0]*series[0] + series[1]*series[1]) > 4)
					break;
			}

			val = (double)k/1000;

			color( val, plane->data + (i*plane->width + j)*3);
		}
	}
}

void cubic_Julia(Plane* plane) {
	int i, j, k;
	double series[2];
	double tmpserie;
	double c[2] = {-0.123,0.745};
	double val;
	double x, y;
	double dx = (plane->right - plane->left) / plane->width; /* Left -> Right */
	double dy = -(plane->up - plane->down) / plane->height; /* Up -> Down */

	for(i = 0, y = plane->up; i < plane->height; ++i, y += dy) {
		for(j = 0, x = plane->left; j < plane->width; j++, x += dx) {
			series[0]=x;
			series[1]=y;
			for (k = 0; k < 1000; ++k) {
				tmpserie = series[0]*series[0]*series[0] - 3*series[0]*series[1]*series[1] + c[0];
				series[1] = 3*series[0]*series[0]*series[1] - series[1]*series[1]*series[1] + c[1];
				series[0] = tmpserie;
				if ((series[0]*series[0] + series[1]*series[1]) > 4)
					break;
			}

			val = (double)k/1000;

			color( val, plane->data + (i*plane->width + j)*3);
		}
	}
}

static r_keys r_map[] = {
	{"test", test_func},
	{"Mandelbrot", set_Mandelbrot},
	{"Julia", set_Julia},
	{"Cubic Julia", cubic_Julia}
};

#define NUM_RENDERERS (sizeof(r_map)/sizeof(r_keys))

Renderer* package_renderers(Plane* plane, int* count) {
	Renderer* rs = new Renderer[NUM_RENDERERS];
	for(unsigned int i = 0; i < NUM_RENDERERS; ++i) {
		rs[i].set_plane(plane);
		rs[i].set_id(r_map[i].id);
		rs[i].set_function(r_map[i].function);
	}

	*count = NUM_RENDERERS;
	return rs;
}

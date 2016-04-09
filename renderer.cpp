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


static r_keys r_map[] = {
	{"test", test_func}
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

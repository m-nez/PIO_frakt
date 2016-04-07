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

void test_func(Plane* plane) {
	int i, j, k;
	for (i = 0; i < plane->width * plane->height * 3; ++i) {
		plane->data[i] = 0;
	}

	for(i = 0; i < plane->height; ++i) {
		for(j = i; j < plane->width; j++) {
			for(k = 0; k < 3; ++k) {
				plane->data[(i*plane->width + j)*3 + k] = j % 255;
			}
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

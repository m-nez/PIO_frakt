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

static inline void black_yellow(double x, unsigned char* pixel) {
	unsigned char pal[][3] = {{0, 0, 0}, {0, 16, 128}, {255, 0, 0}, {255, 255, 48}};
	for(int i = 0; i < 3; ++i) {
		pixel[i] = (pal[0][i] * (1.0- x) + pal[1][i] * x ) * (1.0 - x)  + x * (pal[2][i] * (1-x) + pal[3][i] * x);
	}
}

static inline void black_blue(double x, unsigned char* pixel) {
	unsigned char pal[][3] = {{0, 0, 0}, {13, 25, 255}, {36, 39, 208}, {57, 229, 235}};
	for(int i = 0; i < 3; ++i) {
		pixel[i] = (pal[0][i] * (1.0- x) + pal[1][i] * x ) * (1.0 - x)  + x * (pal[2][i] * (1-x) + pal[3][i] * x);
	}
}

static inline void color(double x, unsigned char* pixel) {
	for (int i = 0; i < 3;++i) {
		pixel[i] = 255 * x;
	}
}

static inline void green_yellow(double x, unsigned char* pixel) {
	unsigned char pal[][3] = {{19, 65, 0}, {255, 255, 255}, {252, 255, 23}, {225, 208, 36}};
	for(int i = 0; i < 3; ++i) {
		pixel[i] = (pal[0][i] * (1.0- x) + pal[1][i] * x ) * (1.0 - x)  + x * (pal[2][i] * (1-x) + pal[3][i] * x);
	}
}

static inline void red_white(double x, unsigned char* pixel) {
	unsigned char pal[][3] = {{95, 5, 0}, {255, 255, 255}, {252, 255, 23}, {255, 255, 255}};
	for(int i = 0; i < 3; ++i) {
		pixel[i] = (pal[0][i] * (1.0- x) + pal[1][i] * x ) * (1.0 - x)  + x * (pal[2][i] * (1-x) + pal[3][i] * x);
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
			for (k = 0; k < 100; ++k) {
				tmpserie = series[0]*series[0] - series[1]*series[1] + x;
				series[1] = 2*series[0]*series[1] + y;
				series[0] = tmpserie;
				if ((series[0]*series[0] + series[1]*series[1]) > 4)
					break;
			}

			val = (double)k/100;

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
			for (k = 0; k < 100; ++k) {
				tmpserie = series[0]*series[0] - series[1]*series[1] + c[0];
				series[1] = 2*series[0]*series[1] + c[1];
				series[0] = tmpserie;
				if ((series[0]*series[0] + series[1]*series[1]) > 4)
					break;
			}

			val = (double)k/100;

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
			for (k = 0; k < 100; ++k) {
				tmpserie = series[0]*series[0]*series[0] - 3*series[0]*series[1]*series[1] + c[0];
				series[1] = 3*series[0]*series[0]*series[1] - series[1]*series[1]*series[1] + c[1];
				series[0] = tmpserie;
				if ((series[0]*series[0] + series[1]*series[1]) > 4)
					break;
			}

			val = (double)k/100;

			color( val, plane->data + (i*plane->width + j)*3);
		}
	}
}

static r_keys r_map[] = {
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

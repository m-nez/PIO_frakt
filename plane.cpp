#include "plane.hpp"
#include <stdio.h>

void Plane::resize(int width, int height) {
	this->width = width;
	this->height = height;
	if (data != 0) {
		delete data;
	}

	data = new unsigned char[width * height *3];
}

Plane::Plane(int width, int height) {
	data = 0;
	resize(width, height);
}

Plane::~Plane() {
	if (data != 0) {
		delete data;
	}
}

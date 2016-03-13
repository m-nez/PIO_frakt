#include "plane.hpp"
#include "bmp.hpp"

int Plane::parse_args(int argc, char** argv) {
	return 0;
}

Plane::Plane(int argc, char** argv) {
	parse_args(argc, argv);
}

int Plane::to_file() {
	to_bmp(name, width, height, data);
}

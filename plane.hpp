#ifndef _PLANE_HPP
#define _PLANE_HPP

#include <string>

class Plane {
	private:
		std::string name;
		int up;
		int down;
		int left;
		int right;
		int width;
		int height;
		unsigned char* data;
	public:
		int to_file();
		int parse_args(int argc, char** argv);
		Plane();
		Plane(int argc, char** argv);
};
#endif

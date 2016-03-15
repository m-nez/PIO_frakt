#ifndef _PLANE_HPP
#define _PLANE_HPP

#include <string>

class Plane {
	private:
		std::string name;
		double up;
		double down;
		double left;
		double right;
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

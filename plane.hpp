#ifndef _PLANE_HPP
#define _PLANE_HPP

class Plane {
	public:
		double up;
		double down;
		double left;
		double right;
		int width;
		int height;
		unsigned char* data;

		void resize(int width, int heght);
		Plane(int width, int height);
		~Plane();
};

#endif

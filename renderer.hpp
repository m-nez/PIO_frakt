#ifndef _RENDERER_HPP
#define _RENDERER_HPP

#include "plane.hpp"
#include <string>

typedef void (*RendererFunction) (Plane*);

class Renderer {
	private:
		Plane* plane;
		void (*function)(Plane*);
		int custom;
		std::string id;
	public:
		std::string get_id() {return id;};
		void set_id(std::string id) { this->id = id; };
		void set_plane(Plane* plane) { this->plane = plane; };
		void set_function(void (*function)(Plane*)) {
			this->function = function;
		};
		RendererFunction get_function() {return function;};


		void render();
		Renderer(std::string id, void (*function)(Plane*));
		Renderer();
};

Renderer* package_renderers(Plane* plane, int* count);

typedef struct {
	const char* id;
	void (*function)(Plane*);
} r_keys;

#endif

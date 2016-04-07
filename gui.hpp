#ifndef _GUI_HPP
#define _GUI_HPP

#include <gtk/gtk.h>
#include <gdk-pixbuf/gdk-pixbuf.h>
#include "plane.hpp"
#include "renderer.hpp"

class GUI {
	private:
		int width;
		int height;
		Plane* plane;
		Renderer* rs;
		int rs_count;
		int rs_current;
		void init();
	public:
		void render();
		GtkWidget* fract;
		GUI();
		~GUI();
		int run();
		int get_width() { return width; };
		int get_height() { return height; };
};

#endif

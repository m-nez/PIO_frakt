#ifndef _WINDOW_HPP
#define _WINDOW_HPP

#include <gtk/gtk.h>

class Window {
	public:
		GtkWidget* window;
		GtkWidget* fract_image;
		GtkWidget* fract_event_box;

		Window();
};

#endif

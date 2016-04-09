#ifndef _WINDOW_HPP
#define _WINDOW_HPP

#include <gtk/gtk.h>
#include <gdk-pixbuf/gdk-pixbuf.h>

class Window {
	public:
		GtkBuilder* builder;

		GtkWidget* window;

		GtkWidget* up_entry;
		GtkWidget* down_entry;
		GtkWidget* left_entry;
		GtkWidget* right_entry;

		GtkWidget* render_button;

		GtkWidget* drawing_area_fract;
		GdkPixbuf* pixbuf;

		Window();
};

#endif

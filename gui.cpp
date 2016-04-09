#include "gui.hpp"
#include <stdio.h>

void GUI::init() {
	plane = new Plane(width, height);
	rs = package_renderers(plane, &rs_count);
	rs_current = 0;
}

void GUI::render() {
	rs[rs_current].render();
	if (window->pixbuf) {
		g_object_unref(window->pixbuf);
	}
	window->pixbuf = gdk_pixbuf_new_from_data (
			plane->data,
			GDK_COLORSPACE_RGB,
			FALSE,
			8,
			plane->width,
			plane->height,
			plane->width*3,
			NULL,
			NULL);

}

GUI::GUI() {
	width = 800;
	height = 600;
	window = new Window;

	init();
}

GUI::~GUI() {
	delete plane;
	delete window;
}

static gboolean
draw_callback (GtkWidget *widget, cairo_t *cr, gpointer user_data)
{
  	GUI* gptr = (GUI*) user_data;
	Window* w = gptr->get_window();

	gdk_cairo_set_source_pixbuf (cr,
			w->pixbuf,
			0.0,
			0.0);

	cairo_paint(cr);

	return FALSE;
}

static void
da_allocate_callback(GtkWidget    *widget,
		GdkRectangle *allocation,
		gpointer      user_data)
{
  	GUI* gptr = (GUI*) user_data;
	Plane* plane = gptr->get_plane();
	plane->resize(allocation->width, allocation->height);
	gptr->render();
}


static void activate(GtkApplication *app, gpointer user_data)
{
	GUI* gptr = (GUI*) user_data;
	Window* w = gptr->get_window();

	w->builder = gtk_builder_new_from_file ("builder.ui");

	gptr->render();

	w->window = GTK_WIDGET(gtk_builder_get_object(w->builder, "window"));
	w->drawing_area_fract = GTK_WIDGET(gtk_builder_get_object(w->builder, "drawingarea_fract"));
	g_signal_connect (w->drawing_area_fract, "draw", G_CALLBACK(draw_callback), gptr);
	g_signal_connect (w->drawing_area_fract, "size-allocate", G_CALLBACK(da_allocate_callback), gptr);

	gtk_application_add_window(app, GTK_WINDOW(w->window));
}



int GUI::run() {
	GtkApplication *app;
	int status;
	app = gtk_application_new("org.gnome.fract",G_APPLICATION_FLAGS_NONE);

	g_signal_connect (app, "activate", G_CALLBACK(activate), this);
	status = g_application_run(G_APPLICATION (app), 0, NULL);
	g_object_unref(app);
	return status;
}

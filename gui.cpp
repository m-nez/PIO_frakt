#include "gui.hpp"
#include <stdio.h>

void GUI::init() {
	plane = new Plane(width, height);
	rs = package_renderers(plane, &rs_count);
	rs_current = 0;
}

void GUI::render() {
	rs[rs_current].render();

	GdkPixbuf* pixbuf = gdk_pixbuf_new_from_data (
			plane->data,
			GDK_COLORSPACE_RGB,
			FALSE,
			8,
			plane->width,
			plane->height,
			plane->width*3,
			NULL,
			NULL);

	fract = gtk_image_new_from_pixbuf(pixbuf);
}

GUI::GUI() {
	width = 800;
	height = 600;

	init();
}

GUI::~GUI() {
	delete plane;
}

static void activate(GtkApplication *app, gpointer user_data)
{
	GtkWidget* window;
	GtkWidget* image;
	GUI* gptr = (GUI*) user_data;

	window = gtk_application_window_new(app);
	gtk_window_set_title(GTK_WINDOW (window), "Fractal Generator");
	gtk_window_set_default_size(GTK_WINDOW(window), gptr->get_width(), gptr->get_height());

	gptr->render();
	image = gptr->fract;

	gtk_container_add(GTK_CONTAINER(window), GTK_WIDGET(image));

	gtk_widget_show_all(GTK_WIDGET(window));
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

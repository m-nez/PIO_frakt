#include "gui.hpp"
#include <stdio.h>

void GUI::init() {
	plane = new Plane(width, height);
	rs = package_renderers(plane, &rs_count);
	rs_current = 0;
}

void GUI::render() {
	rs[rs_current].render();
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
button_press_callback (GtkWidget      *event_box,
                       GdkEventButton *event,
                       gpointer        data)
{
  	GUI* gptr = (GUI*) data;
	Window* w = gptr->get_window();
	Plane* plane = gptr->get_plane();
	
	/* TEST ONLY */
	plane->up		/= 0.9;
	plane->down		/= 0.9;
	plane->left		/= 0.9;
	plane->right	/= 0.9;

	gptr->render();

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

	gtk_image_set_from_pixbuf(GTK_IMAGE(w->fract_image), pixbuf);
	g_object_unref(pixbuf);

  return TRUE;
}


static void activate(GtkApplication *app, gpointer user_data)
{
	GUI* gptr = (GUI*) user_data;
	Window* w = gptr->get_window();

	w->window = gtk_application_window_new(app);
	gtk_window_set_title(GTK_WINDOW (w->window), "Fractal Generator");
	gtk_window_set_default_size(GTK_WINDOW(w->window), gptr->get_width(), gptr->get_height());

	w->fract_image = gtk_image_new();
	w->fract_event_box = gtk_event_box_new();
	gtk_container_add(GTK_CONTAINER(w->fract_event_box), w->fract_image);
	g_signal_connect(G_OBJECT(w->fract_event_box),
			"button_press_event",
			G_CALLBACK(button_press_callback),
			gptr);

	gptr->render();

	gtk_container_add(GTK_CONTAINER(w->window), GTK_WIDGET(w->fract_event_box));

	gtk_widget_show_all(GTK_WIDGET(w->window));
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

#include "gui.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void GUI::init() {
	plane = new Plane(width, height);
	rs = package_renderers(plane, &rs_count);
	rs_current = 0;
}

void GUI::render() {
	rs_current = gtk_combo_box_get_active((GtkComboBox*)window->combobox);
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

static void
save_file(GtkWidget *widget, gpointer user_data) 
{
	GUI* gptr = (GUI*) user_data;
	Window* w = gptr->get_window();
	Plane* p = gptr->get_plane();
	int width = atoi(gtk_entry_get_text((GtkEntry*)w->width_entry));
	int height = atoi(gtk_entry_get_text((GtkEntry*)w->height_entry));
	Plane plane(width, height);
	plane.up = p->up;
	plane.down = p->down;
	plane.left = p->left;
	plane.right = p->right;
	Renderer renderer("", gptr->get_rs()[gptr->get_rs_current()].get_function());
	renderer.set_plane(&plane);
	renderer.render();
	
	GError *error = NULL;

	GdkPixbuf* pixbuf = gdk_pixbuf_new_from_data (
			plane.data,
			GDK_COLORSPACE_RGB,
			FALSE,
			8,
			plane.width,
			plane.height,
			plane.width*3,
			NULL,
			NULL);

	gdk_pixbuf_savev (pixbuf, "New.bmp", "bmp", NULL, NULL, &error); 
	g_object_unref(pixbuf);
}

static void
parse_args_callback(GtkWidget *widget,
		gpointer user_data)
{
	GUI* gptr = (GUI*) user_data;
	Plane* plane = gptr->get_plane();
	Window* w = gptr->get_window();

	plane->up = atof(gtk_entry_get_text((GtkEntry*)w->up_entry));
	plane->down = atof(gtk_entry_get_text((GtkEntry*)w->down_entry));
	plane->right = atof(gtk_entry_get_text((GtkEntry*)w->right_entry));
	plane->left = atof(gtk_entry_get_text((GtkEntry*)w->left_entry));

	gptr->render();
	gtk_widget_queue_draw(w->drawing_area_fract);
}

static void write_plane_to_gui(GUI* gptr) {
	Plane* plane = gptr->get_plane();
	Window* win = gptr->get_window();
	char buff[64];

	snprintf(buff, sizeof(buff), "%g", plane->left);
	gtk_entry_set_text((GtkEntry*)win->left_entry, buff);
	snprintf(buff, sizeof(buff), "%g", plane->right);
	gtk_entry_set_text((GtkEntry*)win->right_entry, buff);
	snprintf(buff, sizeof(buff), "%g", plane->up);
	gtk_entry_set_text((GtkEntry*)win->up_entry, buff);
	snprintf(buff, sizeof(buff), "%g", plane->down);
	gtk_entry_set_text((GtkEntry*)win->down_entry, buff);
}

static void
button_press_callback(GtkWidget *widget,
               GdkEvent  *event,
               gpointer   user_data)
{
	GdkEventButton* event_button = (GdkEventButton*) event;
	GUI* gptr = (GUI*) user_data;
	Plane* plane = gptr->get_plane();
	Window* w = gptr->get_window();
	double d;
	int md;
	double dx, dy;
	switch (event_button->button) {
		case 1:
			w->ex1 = event_button->x;
			w->ey1 = event_button->y;
			break;
		case 2:
			dx = (plane->right - plane->left)/2;
			dy = (plane->up - plane->down)/2;
			plane->left -= dx;
			plane->right += dx;
			plane->up += dy;
			plane->down -= dy;
			write_plane_to_gui(gptr);
			gptr->render();
			gtk_widget_queue_draw(w->drawing_area_fract);
			break;
		case 3:
			d = fabs(plane->down - plane->up) > fabs(plane->right - plane->left) ?
				fabs(plane->down - plane->up) :
				fabs(plane->right - plane->left);
			md = plane->width > plane->height ? plane->width : plane->height;
			plane->down = plane->up - d * plane->height / md;
			plane->right = plane->left + d * plane->width / md;
			write_plane_to_gui(gptr);
			gptr->render();
			gtk_widget_queue_draw(w->drawing_area_fract);
			break;
		default:
			break;
	}
}



static void
button_release_callback(GtkWidget *widget,
               GdkEvent  *event,
               gpointer   user_data)
{
	double x1, y1, x2, y2, w, h, l, r, u, d;
	GdkEventButton* event_button = (GdkEventButton*) event;
	if (event_button->button != 1) {
		return;
	}
	GUI* gptr = (GUI*) user_data;
	Plane* plane = gptr->get_plane();
	Window* win = gptr->get_window();
	x1 = win->ex1;
	y1 = win->ey1;
	x2 = event_button->x;
	y2 = event_button->y;
	w = plane->width;
	h = plane->height;
	l = plane->left;
	r = plane->right;
	u = plane->up;
	d = plane->down;

	plane->left = l * (1.0 - x1/w) + r * x1/w;
	plane->right = l * (1.0 - x2/w) + r * x2/w;
	plane->up = u * (1.0 - y1/h) + d * y1/h;
	plane->down = u * (1.0 - y2/h) + d * y2/h;

	write_plane_to_gui(gptr);

	gptr->render();
	gtk_widget_queue_draw(win->drawing_area_fract);
}

static void activate(GtkApplication *app, gpointer user_data)
{
	GUI* gptr = (GUI*) user_data;
	Window* w = gptr->get_window();

	w->builder = gtk_builder_new_from_file ("builder.ui");
	w->save_button = GTK_WIDGET(gtk_builder_get_object(w->builder, "button_save"));
	w->window = GTK_WIDGET(gtk_builder_get_object(w->builder, "window"));
	w->drawing_area_fract = GTK_WIDGET(gtk_builder_get_object(w->builder, "drawingarea_fract"));
	w->left_entry = GTK_WIDGET(gtk_builder_get_object(w->builder, "entry1"));
	w->right_entry = GTK_WIDGET(gtk_builder_get_object(w->builder, "entry2"));
	w->up_entry = GTK_WIDGET(gtk_builder_get_object(w->builder, "entry3"));
	w->down_entry = GTK_WIDGET(gtk_builder_get_object(w->builder, "entry4"));
	w->width_entry = GTK_WIDGET(gtk_builder_get_object(w->builder, "entry5"));
	w->height_entry = GTK_WIDGET(gtk_builder_get_object(w->builder, "entry6"));
	w->render_button = GTK_WIDGET(gtk_builder_get_object(w->builder, "button_render"));
	w->combobox = GTK_WIDGET(gtk_builder_get_object(w->builder, "combobox"));

	gtk_entry_set_text((GtkEntry*)w->left_entry, "-1.0");
	gtk_entry_set_text((GtkEntry*)w->right_entry, "1.0");
	gtk_entry_set_text((GtkEntry*)w->up_entry, "1.0");
	gtk_entry_set_text((GtkEntry*)w->down_entry, "-1.0");
	gtk_entry_set_text((GtkEntry*)w->width_entry, "800");
	gtk_entry_set_text((GtkEntry*)w->height_entry, "600");


	for(int i = 0; i < gptr->get_rs_count(); ++i) {
		gtk_combo_box_text_append_text (
				(GtkComboBoxText*)w->combobox,
			   	gptr->get_rs()[i].get_id().c_str());
	}
	gtk_combo_box_set_active((GtkComboBox*)w->combobox, 0);

	gdk_window_set_events(
			gtk_widget_get_window(w->drawing_area_fract),
			GDK_ALL_EVENTS_MASK);

	g_signal_connect (w->drawing_area_fract, "draw", G_CALLBACK(draw_callback), gptr);
	g_signal_connect (w->drawing_area_fract, "size-allocate", G_CALLBACK(da_allocate_callback), gptr);
	g_signal_connect (w->render_button, "clicked", G_CALLBACK(parse_args_callback), gptr);
	g_signal_connect (w->drawing_area_fract, "button-press-event", G_CALLBACK(button_press_callback), gptr);
	g_signal_connect (w->drawing_area_fract, "button-release-event", G_CALLBACK(button_release_callback), gptr);
	g_signal_connect (w->save_button, "clicked", G_CALLBACK (save_file), gptr);

	gptr->render();
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

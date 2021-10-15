#include <gtk/gtk.h>
#include "gtk.h"

TBOOLEAN gtk_application_prefer_dark_theme = FALSE;
float *gtk_height;
float *gtk_width;

static gboolean initialised = 0;
gboolean updating = 0;
gboolean drawing = 0;
GtkWidget *window;
GtkWidget *area;
cairo_surface_t *surface;
cairo_t *cr;

static void draw(GtkDrawingArea* self, cairo_t* cr, gint width, gint height,
                 gpointer user_data)
{
    while (updating)
        g_usleep(1000);

    drawing = TRUE;

    gdouble sx = (gdouble)(width)  / cairo_image_surface_get_width(surface);
    gdouble sy = (gdouble)(height) / cairo_image_surface_get_height(surface);

    cairo_scale(cr, sx, sy);
    cairo_set_source_surface(cr, surface, 0, 0);
    cairo_paint(cr);

    drawing = FALSE;
}

static void resize(GtkDrawingArea* self, gint width, gint height,
                   gpointer user_data)
{
    *gtk_height = height;
    *gtk_width = width;
}

gboolean show(gpointer user_data)
{
    gtk_widget_show(GTK_WIDGET(user_data));
    return FALSE;
}

static void activate(GtkApplication *self, gpointer user_data)
{
    if (gtk_application_prefer_dark_theme)
        g_object_set(gtk_settings_get_default(),
                     "gtk-application-prefer-dark-theme", TRUE, NULL);
 
    window = gtk_application_window_new(self);
    gtk_widget_set_size_request(window, *gtk_width, *gtk_height);
    gtk_window_set_title(GTK_WINDOW(window), "GNUPLOT (GTK)");
    gtk_window_set_hide_on_close(GTK_WINDOW(window), TRUE);

    area = gtk_drawing_area_new();
    gtk_drawing_area_set_draw_func(GTK_DRAWING_AREA(area), draw,
                                   NULL,  NULL);

    g_signal_connect_after(area, "resize", G_CALLBACK(resize), NULL);
    gtk_window_set_child(GTK_WINDOW(window), area);
    g_idle_add(show, window);

    initialised = TRUE;
}

gpointer gmain(gpointer user_data)
{
    GtkApplication *application;
    application = gtk_application_new("org.gnuplot.terminal",
                                      G_APPLICATION_FLAGS_NONE);

    g_signal_connect(G_APPLICATION(application), "activate",
                     G_CALLBACK(activate), NULL);

    gint status = g_application_run(G_APPLICATION(application), 0, NULL);
    g_object_unref(application);
}

static void initialise()
{
    surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32,
                                         *gtk_width, *gtk_height);
    cr = cairo_create(surface);

    g_thread_new("gtk.main", gmain, NULL);

    while (!initialised)
        g_usleep(1000);
}

void gtk_queue_draw(cairo_surface_t *plot)
{
    if (!initialised)
        initialise();

    if (GTK_IS_WIDGET(area)) {
        g_idle_add(show, window);

        gint width = cairo_image_surface_get_width(plot);
        gint height = cairo_image_surface_get_height(plot);

        if (width  != cairo_image_surface_get_width(surface)   || 
            height != cairo_image_surface_get_height(surface)) {

            while (drawing)
                g_usleep(1000);

            updating = TRUE;

            cairo_destroy(cr);
            cairo_surface_destroy(surface);

            surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32,
                                                 width, height);
            cr = cairo_create(surface);
        }

        cairo_set_source_surface(cr, plot, 0, 0);
        cairo_paint(cr);

        updating = FALSE;

        gtk_widget_queue_draw(area);
    }
}

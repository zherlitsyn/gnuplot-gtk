#include "gp_cairo.h"
#include "gtk.h"

extern void gp_exit_cleanup(void);
extern plot_struct plot;

uint8_t gtk_initialized = FALSE;
uint8_t gtk_drawing = FALSE;
uint8_t gtk_pages = 0;
float *gtk_width;
float *gtk_height;

cairo_surface_t *surface;
GtkApplication *application;
GtkWidget *scrolled_window;
GtkWidget *window;
GtkWidget *area;
pthread_t thread;

static void
gtk_draw(GtkDrawingArea *area, cairo_t *cr, int32_t w, int32_t h, gpointer data)
{
    if(surface != NULL)
    {
    double wscale = (double)(w) /
                    cairo_image_surface_get_width(surface);
    
    double hscale = (double)(h) /
                    cairo_image_surface_get_height(surface);

    cairo_scale(cr, wscale, hscale);
        cairo_set_source_surface(cr, surface, 0, 0);
        cairo_paint(cr);
//printf("%f,%f (%lf, %lf)\n", *gtk_width, *gtk_height, plot.device_xmax, plot.device_ymax);
        //surface = NULL;
        gtk_drawing = FALSE;
    }
}

gboolean
gtk_resize(GtkWidget *widget, int32_t w, int32_t h, gpointer data)
{
  //  printf("%i,%i\n", w, h);

    *gtk_width = (float) w;
    *gtk_height = (float) h;
    return TRUE;
}

void
gtk_activate(GtkApplication *application, gpointer data)
{  
    window = gtk_application_window_new(application);
    gtk_window_set_default_size(GTK_WINDOW(window), 640, 480);
    gtk_window_set_title(GTK_WINDOW(window), "GNUPLOT (GTK)");

    g_signal_connect_after(window, "destroy", G_CALLBACK(gtk_free), NULL);

    if(gtk_pages)
    {
        GtkWidget *header = gtk_header_bar_new();
        GtkAdjustment *adjustment = gtk_adjustment_new(0.0, 0.0, gtk_pages, 1.0, 1.0, 0.0);
        GtkWidget *button = gtk_spin_button_new(adjustment, 1.0, 0);
     //g_signal_connect(button, "value-changed", G_CALLBACK(value_changed), vadjustment);
        gtk_header_bar_pack_start(GTK_HEADER_BAR(header), button);
        gtk_window_set_titlebar(GTK_WINDOW(window), header);
    }

    scrolled_window = gtk_scrolled_window_new();

    area = gtk_drawing_area_new();
    gtk_drawing_area_set_content_width (GTK_DRAWING_AREA(area), 640);
    gtk_drawing_area_set_content_height (GTK_DRAWING_AREA(area), (480 - 64) * gtk_pages);
    gtk_drawing_area_set_draw_func(GTK_DRAWING_AREA(area), gtk_draw,
                                   NULL, NULL);

    g_signal_connect_after(area, "resize", G_CALLBACK(gtk_resize), NULL);

    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scrolled_window), area);
    gtk_window_set_child(GTK_WINDOW(window), scrolled_window);
    gtk_widget_show(window);
    gtk_widget_show(scrolled_window);
}

static void 
*gtk_main(void *data)
{
    application = gtk_application_new("org.gnuplot.terminal",
                                      G_APPLICATION_FLAGS_NONE);

    g_signal_connect(G_APPLICATION(application), "activate",
                     G_CALLBACK(gtk_activate), NULL);

    int32_t status = g_application_run(G_APPLICATION(application), 0, NULL);

    printf("GTK EXIT: %i", status);

    g_object_unref(application);
    pthread_exit(&status);
}


cairo_t *cr;

void
gtk_init()
{
            surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 640, 480);
            cr = cairo_create(surface);

    pthread_create(&thread, NULL, gtk_main, NULL);
    gtk_initialized = TRUE;
}

void
gtk_free()
{
    gp_exit_cleanup();
    exit(0);
}


void
gtk_queue_draw()
{
    if(GTK_IS_WIDGET(area))
    {
        cairo_surface_t *tmp = cairo_get_target(plot.cr);
        int w = cairo_image_surface_get_width(tmp);
        int h = cairo_image_surface_get_height(tmp);

        if(w != cairo_image_surface_get_width(surface) || 
           h != cairo_image_surface_get_width(surface))
        {
            surface = NULL;
            cairo_destroy(cr);
            cairo_surface_destroy(surface);
            surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, w, h);
            cr = cairo_create(surface);
        }

/*        surface = NULL;
        cairo_surface_destroy(surface);


        //int s = cairo_image_surface_get_stride(tmp);
*/

        cairo_set_source_surface(cr, tmp, 0, 0);
        cairo_paint(cr);

        //surface = cairo_image_surface_create_for_data(cairo_image_surface_get_data(tmp),
        //                                              CAIRO_FORMAT_ARGB32, w, h, s); 

        //surface = 
    //    gtk_drawing = TRUE;
        gtk_widget_queue_draw(area);
//        while(gtk_drawing != FALSE)
  //          usleep(1);
    }
}

#ifndef GTK_H
#define GTK_H

    #include <cairo.h>
    #include "syscfg.h"

    extern TBOOLEAN gtk_application_prefer_dark_theme;
    extern float *gtk_height;
    extern float *gtk_width;

    void gtk_queue_draw(cairo_surface_t *surface);

#endif

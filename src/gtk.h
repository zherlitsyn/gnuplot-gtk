#ifndef GTK_H
#define GTK_H

    #include <gtk/gtk.h>
    #include <stdint.h>
    
    extern uint8_t gtk_initialized;
    extern uint8_t gtk_drawing;
    extern uint8_t gtk_pages;
    extern float *gtk_width;
    extern float *gtk_height;

    void gtk_queue_draw();
    void gtk_init();
    void gtk_free();

#endif

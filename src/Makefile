SOURCES=hidden3d.c voxelgrid.c matrix.c multiplot.c graphics.c datablock.c pm3d.c \
vplot.c specfun.c bitmap.c parse.c datafile.c util3d.c encoding.c eval.c plot3d.c \
variable.c stdfn.c breaders.c time.c save.c mouse.c external.c libcerf.c jitter.c \
scanner.c fit.c internal.c util.c readline.c tabulate.c stats.c show.c getcolor.c \
contour.c command.c standard.c set.c interpol.c alloc.c version.c color.c unset.c \
gpexecute.c graph3d.c dynarray.c axis.c misc.c tables.c gadgets.c plot2d.c term.c \
gp_cairo.c gp_cairo_helpers.c history.c boundary.c help.c complexfun.c xdg.c gtk.c

INCLUDE=-I/usr/include/pango-1.0 -I/usr/include/cairo -I/usr/lib/glib-2.0/include \
-I/usr/include/harfbuzz -I/usr/include/gdk-pixbuf-2.0 -I/usr/include/graphene-1.0 \
-I/usr/lib/graphene-1.0/include -I/usr/include/gio-unix-2.0 -I/usr/include/blkid  \
-I/usr/include/freetype2 -I/usr/include/libpng16 -I/usr/include/libmount          \
-I/usr/include/glib-2.0 -I/usr/include/gtk-4.0 -I/usr/include/fribidi             \
-I/usr/include/lzo -I/usr/include/pixman-1 -I.

LIBS=-lm -lcairo -lglib-2.0 -lgobject-2.0 -lpango-1.0 -lpangocairo-1.0 -lharfbuzz \
-lgdk_pixbuf-2.0 -lcairo-gobject -lgraphene-1.0 -lgio-2.0 -lgtk-4 -pthread

CFLAGS=-Wstringop-overflow=0 -Ofast -pipe -mavx -flto -funswitch-loops            \
-funroll-loops

OBJECTS=$(SOURCES:%.c=%.o)

DEFS=-DHAVE_CONFIG_H

TARGET=plot.c

CC=gcc

all: $(OBJECTS)
	$(CC) $(DEFS) $(CFLAGS) $(INCLUDE) $(TARGET) $(LIBS) $(OBJECTS) -o gnuplot_gtk

%.o: %.c
	@echo Compiling target: $< ...
	$(CC) $(DEFS) $(CFLAGS) $(INCLUDE) -c $<

clean:
	@rm gnuplot_gtk *.o

.PHONY: all clean

CFLAGS=-g `pkg-config --cflags imlib2` -DHPGL
LDFLAGS=-g `pkg-config --libs imlib2`

all: crosshatch

crosshatch: crosshatch.o

.PHONY: clean

clean:
	rm -f *.o crosshatch *.*~

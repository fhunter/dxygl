CFLAGS=-g -Wall -Werror
LDFLAGS=-g -lm

all: hp2dxy

hp2dxy: hp2dxy.o

.PHONY: clean

clean:
	rm -f *.o *.*~ hp2dxy

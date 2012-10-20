CFLAGS=-g
LDFLAGS=-g -lfl

all: hp2dxy

%.c: %.yy
	flex -o $@ $^

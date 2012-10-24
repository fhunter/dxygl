CFLAGS=-g
LDFLAGS=-g -lfl -lm

all: hp2dxy

%.c: %.yy
	flex -o $@ $^

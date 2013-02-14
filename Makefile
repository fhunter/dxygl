CFLAGS=-g
LDFLAGS=-g -lfl -lm

all: hp2dxy

hp2dxy: y.tab.c hp2dxy.c

%.c: %.l
	flex -o $@ $^

y.tab.h y.tab.c: hp2dxy.y
	yacc -d $^

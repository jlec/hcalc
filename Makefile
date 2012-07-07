CC = gcc
CFLAGS = -g -O2 -MMD

OBJS = \
	hcalc.o \
	input.o \
	setupx.o \
	images.o \
	draw.o \
	$E

hcalc : $(OBJS)
	gcc -o $@ $^ -L/usr/X11R6/lib -lXpm -lX11

clean :
	-rm -f *.o *.d *~ \#* hcalc core

tar :
	tar cvfz distrib.tar.gz *.c *.h Makefile *.xpm

D=$(wildcard *.d)
ifneq ($D,)
include $D
endif

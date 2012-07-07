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
	gcc -o $@ $^ -L/usr/X11/lib -lXpm -lX11

clean :
	-rm -f *.o *.d *~ \#* hcalc core

tar :
	tar cvfz hcalc.tar.gz *.c *.h Makefile *.xpm README

D=$(wildcard *.d)
ifneq ($D,)
include $D
endif

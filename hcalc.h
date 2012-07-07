/* Copyright 1998 DJ Delorie <dj@delorie.com>
   Distributed under the terms of the GNU GPL
   http://www.delorie.com/store/hcalc/
*/
#include <stdio.h>

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>
#include <X11/Xatom.h>

extern Display *display;
extern int screen;
extern Visual *visual;
extern Colormap cmap;
extern Window window;
extern Window rootwin;
extern GC gc;
extern Atom wm_protocols_atom;
extern Atom delete_atom;
extern Atom paste_atom;
extern XEvent event;

extern Pixmap face;
extern Pixmap chars;

int bit_on;
int bit_off;

extern int char_to_x[256];
extern char charmap[];
#define MAXCHARS 15

#define WIDTH 125
#define HEIGHT 147

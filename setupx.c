/* Copyright 1998 DJ Delorie <dj@delorie.com>
   Distributed under the terms of the GNU GPL
   http://www.delorie.com/store/hcalc/
*/
#include "hcalc.h"

Display *display=0;
int screen=0;
Visual *visual=0;
Colormap cmap=0;
Window window=0;
Window rootwin=0;
GC gc=0;
Atom wm_protocols_atom=0;
Atom delete_atom=0;
Atom paste_atom=0;
XEvent event;

int bit_on, bit_off;

void
setup_x(int argc, char **argv)
{
  char *name = "hcalc";
  XSizeHints size_hints;
  XTextProperty xtp;
  XSetWindowAttributes attributes;
  XColor color;

  display = XOpenDisplay(0);
  screen = XDefaultScreen(display);
  cmap = XDefaultColormap(display, screen);
  visual = XDefaultVisual(display, screen);
  rootwin = XDefaultRootWindow(display);
  gc = XCreateGC(display, rootwin, 0, 0);

  wm_protocols_atom = XInternAtom(display, "WM_PROTOCOLS", 0);
  delete_atom = XInternAtom(display, "WM_DELETE_WINDOW", 0);
  paste_atom = XInternAtom(display, "PASTE_DATA", 0);

  size_hints.flags = PSize;
  size_hints.width = WIDTH;
  size_hints.height = HEIGHT;
  size_hints.x = 0;
  size_hints.y = 0;

  window = XCreateWindow(display,
			 rootwin,
			 size_hints.x, size_hints.y,
			 size_hints.width, size_hints.height,
			 0,
			 CopyFromParent, /* depth */
			 InputOutput,
			 CopyFromParent, /* visual */
			 0, 0);

  XSetWMNormalHints(display, window, &size_hints);

  XStringListToTextProperty(&name, 1, &xtp);
  XSetWMName(display, window, &xtp);
  XFree(xtp.value);

  XSetWMProtocols(display, window, &delete_atom, 1);

  attributes.event_mask = ExposureMask | ButtonPressMask | KeyPressMask;
  XChangeWindowAttributes(display, window, CWEventMask, &attributes);

  XMapWindow(display, window);
  XFlush(display);

  color.red   = 0x6666;
  color.green = 0xffff;
  color.blue  = 0x6666;
  color.flags = DoRed | DoGreen | DoBlue;
  XAllocColor(display, cmap, &color);
  bit_on = color.pixel;

  color.red   = 0x3333;
  color.green = 0xcccc;
  color.blue  = 0x3333;
  color.flags = DoRed | DoGreen | DoBlue;
  XAllocColor(display, cmap, &color);
  bit_off = color.pixel;
}

void
process_input()
{
  char c;
  KeySym keysym;
  char tmp[16], *tp;
  XTextProperty tprop;

  while (1)
  {
    XNextEvent(display, &event);
    if (event.xany.window == window)
    {
      switch (event.type)
      {
      case Expose:
	if (event.xexpose.count == 0)
	  redraw();
	break;
      case KeyPress:
	if (XLookupString(&event.xkey, &c, 1, &keysym, 0) == 1)
	{
	  if (c == 3)
	    exit(0);
	  key(c);
	}
	else
	{
	  switch (keysym)
	  {
	  case XK_F1:
	    key('D');
	    break;
	  case XK_F2:
	    key('H');
	    break;
	  case XK_F3:
	    key('O');
	    break;
	  case XK_F4:
	    key('B');
	    break;
	  }
	}
	break;
      case ButtonPress:
	button(event.xbutton.button, event.xbutton.x, event.xbutton.y);
	break;

      case SelectionRequest:
	send_current_display();
	break;

      case SelectionNotify:
	if (event.xselection.property == paste_atom)
	{
	  XGetTextProperty(display, window, &tprop, paste_atom);
	  complete_paste(tprop.value, tprop.nitems);
	}
	break;
      }
    }
  }
}

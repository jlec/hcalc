/* Copyright 1998 DJ Delorie <dj@delorie.com>
   Distributed under the terms of the GNU GPL
   http://www.delorie.com/store/hcalc/
   Revisions copyright 2007, 
   Theodore Kilgore <kilgota@auburn.edu>
*/
#include "hcalc.h"
#include <string.h>

static unsigned char shown_offsets[15];
static int shown_bitmask;
static int show_bits;

#define CHARS_LEFT	12 
#define CHARS_TOP	12 

#define BITS_LEFT_X	184 
#define BITS_TOP_1	12  
#define BITS_BOT_1	20  
#define BITS_TOP_0	20  
#define BITS_BOT_0	24  

void
redraw_chars()
{
  int i;
  for (i=0; i<15; i++)
  {
    XCopyArea(display, chars, window, gc,
    	      shown_offsets[i], 0, 10, 14,
	      CHARS_LEFT+12*i, CHARS_TOP);
	/*    printf("i=%i\n",i); */
	/*    printf("shown_offsets[%i]=%i\n", i, shown_offsets[i]); */
   }
}

void
redraw()
{
  XCopyArea(display, face, window, gc, 0, 0, WIDTH, HEIGHT, 0, 0);

  if (show_bits)
  {
    int i, x;
    XSetForeground(display, gc, bit_off);
    for (i=0; i<32; i++)
    {
      x = BITS_LEFT_X - 4*i - 6*(i/4);
      if (!(shown_bitmask & (1<<i)))
        XDrawLine(display, window, gc, x, BITS_TOP_0, x, BITS_BOT_0);
    }
    XSetForeground(display, gc, bit_on);
    for (i=0; i<32; i++)
    {
      x = BITS_LEFT_X - 4*i - 6*(i/4);
      if (shown_bitmask & (1<<i))
	XDrawLine(display, window, gc, x, BITS_TOP_1, x, BITS_BOT_1);
    }
  }
  else
    redraw_chars();
}

set_bits(int b)
{
  shown_bitmask = b;
  show_bits = 1;
  redraw();
}

set_string(char *s)
{
  char tmp[16];
  int i;
  sprintf(tmp, "%15.15s", s);
  for (i=0; i<15; i++)
    shown_offsets[i] = char_to_x[tmp[i]];
  if (show_bits == 0)
    redraw_chars();
  else
  {
    show_bits = 0;
    redraw();
  }
}

void
send_current_display()
{
  char tmp[40], *tp=tmp;
  int i;
  XEvent e;

  if (show_bits)
  {
    for (i=31; i>0; i--)
      if (shown_bitmask & (1<<i))
        break;
    for (; i>=0; i--)
    {
      if (shown_bitmask & (1<<i))
    	*tp++ = '1';
      else
        *tp++ = '0';
    }
  }
  else
  {
    for (i=0; i<15; i++)
    {
      char c = charmap[shown_offsets[i]/12];
      if (c != ' ' && c != ',')
        *tp++ = c;
    }
  }
        
  *tp = 0;

  e.type = SelectionNotify;
  e.xselection.display = display;
  e.xselection.requestor = event.xselectionrequest.requestor;
  e.xselection.selection = event.xselectionrequest.selection;
  e.xselection.target = event.xselectionrequest.target;
  e.xselection.property = event.xselectionrequest.property;
  e.xselection.time = event.xselectionrequest.time;

  if (event.xselectionrequest.target != XA_STRING)
  {
    e.xselection.property = None;
  }
  else
  {
    XChangeProperty(display, e.xselection.requestor, e.xselection.property,
        	    XA_STRING, 8, PropModeReplace, tmp, strlen(tmp));
  }
  XSendEvent(display, e.xselection.requestor, False, 0, &e);
}

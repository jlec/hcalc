/* Copyright 1998 DJ Delorie <dj@delorie.com>
   Distributed under the terms of the GNU GPL
   http://www.delorie.com/store/hcalc/
*/
#include "hcalc.h"
#include <X11/xpm.h>

#define xpm face_data
#include "face.xpm"
#undef xpm
#define xpm chars_data
#include "chars.xpm"
#undef xpm

Pixmap face;
Pixmap chars;

char charmap[] = " 0123456789ABCDEF-x,.ro+";
int char_to_x[256];

void
load_pixmaps()
{
  int i, c;

  XpmAttributes attr;
  attr.valuemask = 0;
  XpmCreatePixmapFromData(display, window, face_data, &face, 0, &attr);
  XpmCreatePixmapFromData(display, window, chars_data, &chars, 0, &attr);

  for (i=0; i<256; i++)
  {
    char_to_x[i] = 0;
    for (c=0; charmap[c]; c++)
      if (charmap[c] == i)
	char_to_x[i] = c*6;
  }
}

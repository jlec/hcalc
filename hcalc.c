/* Copyright 1998 DJ Delorie <dj@delorie.com>
   Distributed under the terms of the GNU GPL
   http://www.delorie.com/store/hcalc/
*/
#include "hcalc.h"

int
main(int argc, char **argv)
{
  setbuf(stdout, 0);
  setup_x(argc, argv);
  load_pixmaps();
  process_input();
}

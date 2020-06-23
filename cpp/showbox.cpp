#include "showbox.h"
#include "shownodelist.h"
#include "println.h"

static int show_box_breadth(void) { return int_par(show_box_breadth_code); }
static int show_box_depth(void) { return int_par(show_box_depth_code); }

void showbox(halfword p)
{  
	depththreshold = show_box_depth();
	breadthmax = show_box_breadth();
	if (breadthmax <= 0)
		breadthmax = 5;
	if (poolptr+depththreshold >= poolsize)
		depththreshold = poolsize-poolptr-1;
	shownodelist(p);
	println();
}

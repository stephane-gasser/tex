#include "showbox.h"
#include "shownodelist.h"
#include "println.h"

void showbox(halfword p)
{  
	depththreshold = int_par(show_box_depth_code);
	breadthmax = int_par(show_box_breadth_code);
	if (breadthmax <= 0)
		breadthmax = 5;
	if (poolptr+depththreshold >= poolsize)
		depththreshold = poolsize-poolptr-1;
	shownodelist(p);
	println();
}

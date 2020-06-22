#include "showbox.h"
#include "shownodelist.h"
#include "println.h"

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

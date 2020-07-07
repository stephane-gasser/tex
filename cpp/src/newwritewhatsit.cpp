#include "newwritewhatsit.h"
#include "newwhatsit.h"
#include "lecture.h"

void newwritewhatsit(smallnumber w)
{
	newwhatsit(curchr, w);
	if (w != write_node_size)
		curval = scanfourbitint();
	else
	{
		curval = scanint();
		if (curval < 0)
			curval = 17;
		else 
			if (curval > 15)
				curval = 16;
	}
	write_stream(tail) = curval;
}

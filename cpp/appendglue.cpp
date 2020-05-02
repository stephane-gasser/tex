#include "appendglue.h"
#include "scanglue.h"
#include "newglue.h"

void appendglue(void)
{
	auto s = curchr;
	switch (s)
	{
		case 0: 
			curval = 4;
			break;
		case 1: 
			curval = 8;
			break;
		case 2: 
			curval = 12;
			break;
		case 3: 
			curval = 16;
			break;
		case 4: 
			scanglue(2);
			break;
		case 5: 
			scanglue(3);
	}
	tail_append(newglue(curval));
	if (s >= 4)
	{
		link(curval)--;
		if (s > 4)
			subtype(tail) = 99;
	}
}

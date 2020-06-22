#include "strtoks.h"
#include "getavail.h"
#include "overflow.h"

halfword strtoks(poolpointer b)
{
	str_room(1);
	halfword p = temp_head;
	link(p) = 0;
	for (auto k = b; k < poolptr; k++)
	{
		halfword t = strpool[k];
		if (t == ' ')
			t = space_token;
		else
			t += other_token;
		fast_store_new_token(p, t);
	}
	poolptr = b;
	return p;
}


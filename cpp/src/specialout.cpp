#include "specialout.h"
#include "movement.h"
#include "impression.h"
#include "erreur.h"
#include "dviswap.h"
#include "dvifour.h"

void specialout(halfword p)
{
	synch_h();
	synch_v();
	auto oldsetting = selector;
	selector = new_string;
	print(tokenlist(link(write_tokens(p)), 0, poolsize-poolptr));
	selector = oldsetting;
	str_room(1); 
	if (cur_length() < 256)
	{
		dvi_out(xxx1);
		dvi_out(cur_length());
	}
	else
	{
		dvi_out(xxx4);
		dvifour(cur_length());
	}
	for (auto k = strstart[strptr]; k < poolptr; k++)
		dvi_out(strpool[k]);
	poolptr = strstart[strptr];
}

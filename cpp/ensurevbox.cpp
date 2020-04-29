#include "ensurevbox.h"
#include "printnl.h"
#include "print.h"
#include "boxerror.h"

void ensurevbox(eightbits n)
{
	auto p = eqtb[3678+n].hh.rh;
	if (p && type(p) == hlist_node)
	{
		if (interaction == 3)
			printnl(262); //! 
		print(988); //Insertions can only be added to a vbox
		helpptr = 3;
		helpline[2] = 989; //Tut tut: You're trying to \insert into a
		helpline[1] = 990; //\box register that now contains an \hbox.
		helpline[0] = 991; //Proceed, and I'll discard its present contents.
		boxerror(n);
	}
}


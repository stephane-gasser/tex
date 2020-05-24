#include "ensurevbox.h"
#include "printnl.h"
#include "print.h"
#include "boxerror.h"
#include "texte.h"

void ensurevbox(eightbits n)
{
	auto p = box(n);
	if (p && type(p) == hlist_node)
	{
		printnl("! ");
		print("Insertions can only be added to a vbox");
		helpptr = 3;
		helpline[2] = "Tut tut: You're trying to \\insert into a";
		helpline[1] = "\\box register that now contains an \\hbox.";
		helpline[0] = "Proceed, and I'll discard its present contents.";
		boxerror(n);
	}
}


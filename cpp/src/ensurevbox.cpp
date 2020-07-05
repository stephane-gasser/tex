#include "ensurevbox.h"
#include "impression.h"
#include "erreur.h"
#include "texte.h"

static void erreurEnsurevbox(eightbits n)
{
	print_err("Insertions can only be added to a vbox");
	helpptr = 3;
	helpline[2] = "Tut tut: You're trying to \\insert into a";
	helpline[1] = "\\box register that now contains an \\hbox.";
	helpline[0] = "Proceed, and I'll discard its present contents.";
	boxerror(n);
}

void ensurevbox(eightbits n)
{
	auto p = box(n);
	if (p && type(p) == hlist_node)
		erreurEnsurevbox(n);
}


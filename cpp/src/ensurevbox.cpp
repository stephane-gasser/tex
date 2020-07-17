#include "ensurevbox.h"
#include "impression.h"
#include "erreur.h"
#include "texte.h"

void ensurevbox(eightbits n)
{
	auto p = box(n);
	if (p && type(p) == hlist_node)
		boxerror(n, "Insertions can only be added to a vbox", "Tut tut: You're trying to \\insert into a\n\\box register that now contains an \\hbox.\nProceed, and I'll discard its present contents.", curalign);
}


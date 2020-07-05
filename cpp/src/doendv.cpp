#include "doendv.h"
#include "erreur.h"
#include "endgraf.h"
#include "fincol.h"
#include "finrow.h"
#include "offsave.h"

void doendv(void)
{
	baseptr = inputptr;
	inputstack[baseptr] = curinput;
	while (inputstack[baseptr].indexfield != 2 && inputstack[baseptr].locfield == 0 && inputstack[baseptr].statefield == 0)
		baseptr--;
	if (inputstack[baseptr].indexfield != 2 || inputstack[baseptr].locfield || inputstack[baseptr].statefield)
		fatalerror("(interwoven alignment preambles are not allowed)");
	if (curgroup == 6)
	{
		endgraf();
		if (fincol())
			finrow();
	}
	else
		offsave();
}

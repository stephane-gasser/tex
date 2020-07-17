#include "doendv.h"
#include "erreur.h"
#include "endgraf.h"
#include "fincol.h"
#include "finrow.h"
#include "offsave.h"

void doendv(eightbits cmd, halfword chr, halfword tok, halfword &loop, halfword &span, halfword &align)
{
	baseptr = inputptr;
	inputstack[baseptr] = curinput;
	while (inputstack[baseptr].indexfield != 2 && inputstack[baseptr].locfield == 0 && inputstack[baseptr].statefield == 0)
		baseptr--;
	if (inputstack[baseptr].indexfield != 2 || inputstack[baseptr].locfield || inputstack[baseptr].statefield)
		fatalerror("(interwoven alignment preambles are not allowed)", align);
	if (curgroup == align_group)
	{
		endgraf();
		if (fincol(tok, loop, span, align))
			finrow(loop, span, align);
	}
	else
		offsave(cmd, chr, tok);
}

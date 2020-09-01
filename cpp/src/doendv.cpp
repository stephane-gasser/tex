#include "doendv.h"
#include "erreur.h"
#include "endgraf.h"
#include "fincol.h"
#include "finrow.h"
#include "offsave.h"

void doendv(Token t, AlignRecordNode* &loop)
{
	baseptr = inputptr;
	inputstack[baseptr] = curinput;
	while (inputstack[baseptr].indexfield != v_template && inputstack[baseptr].locfield == 0 && inputstack[baseptr].statefield == token_list)
		baseptr--;
	if (inputstack[baseptr].indexfield != v_template || inputstack[baseptr].locfield || inputstack[baseptr].statefield != token_list)
		fatalerror("(interwoven alignment preambles are not allowed)");
	if (curgroup == align_group)
	{
		endgraf();
		if (fincol(t, loop))
			finrow(loop);
	}
	else
		offsave(t);
}

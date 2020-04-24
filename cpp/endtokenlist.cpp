#include "endtokenlist.h"
#include "flushlist.h"
#include "deletetokenref.h"
#include "fatalerror.h"
#include "pauseforinstructions.h"

void endtokenlist(void)
{
	if (curinput.indexfield >= 3)
	{
		if (curinput.indexfield <= 4)
			flushlist(curinput.startfield);
		else
		{
			deletetokenref(curinput.startfield);
			if (curinput.indexfield == 5)
				for (;paramptr > curinput.limitfield; paramptr--)
					flushlist(paramstack[paramptr]);
		}
	}
	else 
		if (curinput.indexfield == 1)
			if (alignstate > 500000)
				alignstate = 0;
			else
				fatalerror(595); //(interwoven alignment preambles are not allowed)
	inputptr--;
	curinput = inputstack[inputptr];
	if (interrupt)
		pauseforinstructions();
}

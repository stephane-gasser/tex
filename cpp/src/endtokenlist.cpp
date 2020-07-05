#include "endtokenlist.h"
#include "flushlist.h"
#include "deletetokenref.h"
#include "erreur.h"
#include "pauseforinstructions.h"
#include "popinput.h"

void endtokenlist(void)
{
	if (token_type >= backed_up)
	{
		if (token_type <= inserted)
			flushlist(start);
		else
		{
			deletetokenref(start);
			if (token_type == macro)
				for (;paramptr > param_start; paramptr--)
					flushlist(paramstack[paramptr]);
		}
	}
	else 
		if (token_type == u_template)
			if (alignstate > 500000)
				alignstate = 0;
			else
				fatalerror("(interwoven alignment preambles are not allowed)");
	pop_input();
	check_interrupt();
}

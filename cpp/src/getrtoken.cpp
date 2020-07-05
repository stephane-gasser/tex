#include "getrtoken.h"
#include "gettoken.h"
#include "impression.h"
#include "backinput.h"
#include "erreur.h"
#include "texte.h"

static void erreurGetrtoken(void)
{
	print_err("Missing control sequence inserted");
	helpptr = 5;
	helpline[4] = "Please don't say `\\def cs{...}', say `\\def\\cs{...}'.";
	helpline[3] = "I've inserted an inaccessible control sequence so that your";
	helpline[2] = "definition will be completed without mixing me up too badly.";
	helpline[1] = "You can recover graciously from this error, if you're";
	helpline[0] = "careful; see exercise 27.2 in The TeXbook.";
	inserror();
}

void getrtoken(void)
{
	while (true)
	{
		do
			gettoken();
		while (curtok == space_token);
		if (curcs == 0 || curcs > frozen_control_sequence)
		{
			erreurGetrtoken();
			if (curcs == 0)
				backinput();
			curtok = frozen_protection+cs_token_flag;
			continue;
		}
		break;
	}
}

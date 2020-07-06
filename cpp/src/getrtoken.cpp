#include "getrtoken.h"
#include "gettoken.h"
#include "impression.h"
#include "backinput.h"
#include "erreur.h"
#include "texte.h"

void getrtoken(void)
{
	while (true)
	{
		do
			gettoken();
		while (curtok == space_token);
		if (curcs == 0 || curcs > frozen_control_sequence)
		{
			inserror("Missing control sequence inserted", "Please don't say `\\def cs{...}', say `\\def\\cs{...}'.\nI've inserted an inaccessible control sequence so that your\ndefinition will be completed without mixing me up too badly.\nYou can recover graciously from this error, if you're\ncareful; see exercise 27.2 in The TeXbook.");
			if (curcs == 0)
				backinput();
			curtok = frozen_protection+cs_token_flag;
			continue;
		}
		break;
	}
}

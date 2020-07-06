#include "scanleftbrace.h"
#include "getxtoken.h"
#include "impression.h"
#include "erreur.h"
#include "texte.h"

void scanleftbrace(void)
{
	do  
		getxtoken();
	while (curcmd == spacer || curcmd == escape);
	if (curcmd != left_brace)
	{
		backerror("Missing { inserted", "A left brace was mandatory here, so I've put one in.\nYou might want to delete and/or insert some corrections\nso that I will find a matching right brace soon.\n(If you're confused by all this, try typing `I}' now.)");
		curtok = left_brace_token+'{';
		curcmd = left_brace;
		curchr = '{'; 
		alignstate++;
	}
}

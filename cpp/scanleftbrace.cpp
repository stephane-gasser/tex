#include "scanleftbrace.h"
#include "getxtoken.h"
#include "printnl.h"
#include "print.h"
#include "backerror.h"
#include "texte.h"

void scanleftbrace(void)
{
	do  
		getxtoken();
	while (curcmd == spacer || curcmd == escape);
	if (curcmd != left_brace)
	{
		printnl("! ");
		print("Missing { inserted");
		helpptr = 4;
		helpline[3] = txt("A left brace was mandatory here, so I've put one in.");
		helpline[2] = txt("You might want to delete and/or insert some corrections");
		helpline[1] = txt("so that I will find a matching right brace soon.");
		helpline[0] = txt("(If you're confused by all this, try typing `I}' now.)");
		backerror();
		curtok = left_brace*0x01'00+'{';
		curcmd = 1;
		curchr = '{'; 
		alignstate++;
	}
}

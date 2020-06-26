#include "scanleftbrace.h"
#include "getxtoken.h"
#include "impression.h"
#include "backerror.h"
#include "texte.h"

void scanleftbrace(void)
{
	do  
		getxtoken();
	while (curcmd == spacer || curcmd == escape);
	if (curcmd != left_brace)
	{
		print_err("Missing { inserted");
		helpptr = 4;
		helpline[3] = "A left brace was mandatory here, so I've put one in.";
		helpline[2] = "You might want to delete and/or insert some corrections";
		helpline[1] = "so that I will find a matching right brace soon.";
		helpline[0] = "(If you're confused by all this, try typing `I}' now.)";
		backerror();
		curtok = (left_brace<<8)+'{';
		curcmd = 1;
		curchr = '{'; 
		alignstate++;
	}
}

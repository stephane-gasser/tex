#include "scanleftbrace.h"
#include "getxtoken.h"
#include "printnl.h"
#include "print.h"
#include "backerror.h"

void scanleftbrace(void)
{
	do  
		getxtoken();
	while (curcmd == spacer || curcmd == escape);
	if (curcmd != left_brace)
	{
		printnl(262); //! 
		print(657); //Missing { inserted
		helpptr = 4;
		helpline[3] = 658; //A left brace was mandatory here, so I've put one in.
		helpline[2] = 659; //You might want to delete and/or insert some corrections
		helpline[1] = 660; //so that I will find a matching right brace soon.
		helpline[0] = 661; //(If you're confused by all this, try typing `I}' now.)
		backerror();
		curtok = left_brace*0x01'00+'{';
		curcmd = 1;
		curchr = '{'; 
		alignstate++;
	}
}

#include "scanfontident.h"
#include "getxtoken.h"
#include "scanfourbitint.h"
#include "printnl.h"
#include "print.h"
#include "backerror.h"

void scanfontident(void)
{
	do
		getxtoken();
	while (curcmd == 10);
	internalfontnumber f;
	if (curcmd == 88)
		f = eqtb[3934].hh.rh;
	else 
		if (curcmd == 87)
			f = curchr;
		else 
			if (curcmd == 86)
			{
				halfword m = curchr;
				scanfourbitint();
				f = eqtb[m+curval].hh.rh;
			}
			else
			{
				if (interaction == 3)
					printnl(262); //! 
				print(816); //Missing font identifier
				helpptr = 2;
				helpline[1] = 817; //I was looking for a control sequence whose
				helpline[0] = 818; //2current meaning has been defined by \font.
				backerror();
				f = 0;
			}
	curval = f;
}

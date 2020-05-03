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
	while (curcmd == spacer);
	internalfontnumber f;
	if (curcmd == def_font)
		f = cur_font();
	else 
		if (curcmd == set_font)
			f = curchr;
		else 
			if (curcmd == def_family)
			{
				halfword m = curchr;
				scanfourbitint();
				f = equiv(m+curval);
			}
			else
			{
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

#include "findfontdimen.h"
#include "scanint.h"
#include "scanfontident.h"
#include "deleteglueref.h"
#include "overflow.h"
#include "printnl.h"
#include "print.h"
#include "printesc.h"
#include "printint.h"
#include "error.h"

void findfontdimen(bool writing)
{
	scanint();
	int n = curval;
	scanfontident();
	internalfontnumber f = curval;
	if (n <= 0)
		curval = fmemptr;
	else
	{
		if (writing && n <= 4 && n >= 2 && fontglue[f])
		{
			deleteglueref(fontglue[f]);
			fontglue[f] = 0;
		}
		if (n > fontparams[f])
			if (f < fontptr)
				curval = fmemptr;
			else
			{
				do
				{
					if (fmemptr == fontmemsize)
						overflow(823, fontmemsize); //font memory
					fontinfo[fmemptr++].int_ = 0;
					fontparams[f]++;
				} while (n != fontparams[f]);
				curval = fmemptr-1;
			}
		else
			curval = n+parambase[f];
	}
	if (curval == fmemptr)
	{
		printnl(262); //! 
		print(801); //Font 
		printesc(hash[font_id_base+f].rh);
		print(819); // has only 
		printint(fontparams[f]);
		print(820); // fontdimen parameters
		helpptr = 2;
		helpline[1] = 821; //To increase the number of font parameters, you must
		helpline[0] = 822; //use \fontdimen immediately after the \font is loaded.
		error();
	}
}

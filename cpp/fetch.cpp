#include "fetch.h"
#include "printnl.h"
#include "print.h"
#include "printsize.h"
#include "printchar.h"
#include "printint.h"
#include "error.h"
#include "charwarning.h"

void fetch(halfword a)
{
	curc = subtype(a);
	curf = fam_fnt(type(a)+cursize);
	if (curf == 0)
	{
		printnl(262); //! 
		print(338); //
		printsize(cursize);
		printchar(' ');
		printint(type(a));
		print(883); // is undefined (character 
		print(curc);
		printchar(')');
		{
		helpptr = 4;
		helpline[3] = 884; //Somewhere in the math formula just ended, you used the
		helpline[2] = 885; //stated character from an undefined font family. For example,
		helpline[1] = 886; //plain TeX doesn't allow \it or \sl in subscripts. Proceed,
		helpline[0] = 887; //and I'll try to forget that I needed that character.
		}
		error();
		curi = nullcharacter;
		link(a) = 0;
	}
	else
	{
		if (curc >= fontbc[curf] && curc <= fontec[curf])
			curi = char_info(curf, curc);
		else
			curi = nullcharacter;
		if (skip_byte(curi) <= 0)
		{
			charwarning(curf, curc);
			link(a) = 0;
		}
	}
}

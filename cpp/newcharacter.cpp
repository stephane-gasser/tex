#include "newcharacter.h"
#include "getavail.h"
#include "charwarning.h"

halfword newcharacter(internalfontnumber f, eightbits c)
{
	if (fontbc[f] <= c)
		if (fontec[f] >= c)
			if ((skip_byte(char_info(f, c)) > 0))
			{
				auto p = getavail();
				type(p) = f;
				subtype(p) = c;
				return p;
			}
	charwarning(f, c);
	return 0;
}

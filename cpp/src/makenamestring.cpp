#include "makenamestring.h"
#include "makestring.h"

std::string makenamestring(void)
{
	if (poolptr+namelength > poolsize || strptr == maxstrings || cur_length() > 0)
		return "?";
	else
	{
		for (int k = 1; k <= namelength; k++)
			append_char(xord[nameoffile[k]]);
		return makestring();
	}
}

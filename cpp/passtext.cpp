#include "passtext.h"
#include "getnext.h"

void passtext(void)
{
	auto savescannerstatus = scannerstatus;
	scannerstatus = 1;
	int l = 0;
	skipline = line;
	while (true)
	{
		getnext();
		if (curcmd == 106)
		{
			if (l == 0)
				break;
			if (curchr == 2)
				l--;
		}
		else 
			if (curcmd == 105)
				l++;
	}
	scannerstatus = savescannerstatus;
}

#include "passtext.h"
#include "getnext.h"

void passtext(void)
{
	auto savescannerstatus = scannerstatus;
	scannerstatus = skipping;
	int l = 0;
	skipline = line;
	while (true)
	{
		auto [cmd, chr, cs] = getnext();
		if (cmd == fi_or_else)
		{
			if (l == 0)
				break;
			if (chr == fi_code)
				l--;
		}
		else 
			if (cmd == if_test)
				l++;
	}
	scannerstatus = savescannerstatus;
}

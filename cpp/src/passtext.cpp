#include "passtext.h"
#include "getnext.h"
#include "fichier.h"

void passtext(void)
{
	auto savescannerstatus = scannerstatus;
	scannerstatus = skipping;
	int l = 0;
	skipline = line;
	while (true)
	{
		auto t = getnext();
		if (t.cmd == fi_or_else)
		{
			if (l == 0)
				break;
			if (t.chr == fi_code)
				l--;
		}
		else 
			if (t.cmd == if_test)
				l++;
	}
	scannerstatus = savescannerstatus;
}

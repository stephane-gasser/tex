#include "scanfilename.h"
#include "beginname.h"
#include "getxtoken.h"
#include "backinput.h"
#include "morename.h"
#include "endname.h"

void scanfilename(void)
{
	nameinprogress = true;
	beginname();
	do
		getxtoken();
	while (curcmd == 10);
	while (true)
	{
		if (curcmd > 12 || curchr > 255)
		{
			backinput();
			break;
		}
		if (!morename(curchr))
			break;
		getxtoken();
	}
	endname();
	nameinprogress = false;
}

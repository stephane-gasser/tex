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
	while (curcmd == spacer);
	while (true)
	{
		if (curcmd > other_char || curchr > 255)
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

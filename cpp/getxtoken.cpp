#include "getxtoken.h"
#include "getnext.h"
#include "macrocall.h"
#include "expand.h"

void getxtoken(void)
{
	while (true)
	{
		getnext();
		if (curcmd <= max_command)
			break;
		if (curcmd >= call)
			if (curcmd < end_template)
				macrocall();
			else
			{
				curcs = frozen_endv;
				curcmd = ignore;
				break;
			}
		else
		expand();
	}
	if (curcs == 0)
		curtok = (curcmd*0x1'00)+curchr;
	else
		curtok = cs_token_flag+curcs;
}

#include "thetoks.h"
#include "getxtoken.h"
#include "scansomethinginternal.h"
#include "getavail.h"
#include "impression.h"
#include "deleteglueref.h"
#include "strtoks.h"

halfword thetoks(void)
{
	getxtoken();
	scansomethinginternal(tok_val, false);
	if (curvallevel >= ident_val)
	{
		halfword p = temp_head;
		link(p) = 0;
		if (curvallevel == ident_val)
			store_new_token(p, cs_token_flag+curval);
		else 
			if (curval)
			{
				auto r = link(curval);
				while (r)
				{
					fast_store_new_token(p, info(r));
					r = link(r);
				}
			}
		return p;
	}
	oldsetting = selector;
	selector = new_string;
	auto b = poolptr;
	switch (curvallevel)
	{
		case int_val: 
			print(std::to_string(curval));
			break;
		case dimen_val:
			print(asScaled(curval)+"pt");
			break;
		case glue_val:
			printspec(curval, "pt");
			deleteglueref(curval);
			break;
		case mu_val:
			printspec(curval, "mu");
			deleteglueref(curval);
	}
	selector = oldsetting;
	return strtoks(b);
}

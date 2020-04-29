#include "package.h"
#include "hpack.h"
#include "unsave.h"
#include "vpackage.h"
#include "popnest.h"
#include "boxend.h"

void package(smallnumber c)
{
	scaled d = eqtb[5837].int_;
	unsave();
	saveptr -= 3;
	if (curlist.modefield == -102)
		curbox = hpack(mem[curlist.headfield].hh.rh, savestack[saveptr+2].int_, savestack[saveptr+1].int_);
	else
	{
		curbox = vpackage(mem[curlist.headfield].hh.rh, savestack[saveptr+2].int_, savestack[saveptr+1].int_, d);
		if (c == 4)
		{
			scaled h = 0;
			auto p = link(curbox+5);
			if (p && type(p) <= 2)
				h = mem[p+3].int_;
			mem[curbox+2].int_ = mem[curbox+2].int_-h+mem[curbox+3].int_;
			mem[curbox+3].int_ = h;
		}
	}
	popnest();
	boxend(savestack[saveptr].int_);
}

#include "mathglue.h"
#include "xovern.h"
#include "multandadd.h"
#include "xnoverd.h"
#include "getnode.h"

halfword mathglue(halfword g, scaled m)
{
	int n = xovern(m, unity);
	scaled f = remainder_;
	if (f < 0)
	{
		n--;
		f += unity;
	}
	auto p = getnode(4);
	width(p) = multandadd(n, width(g), xnoverd(width(g), f, unity), max_dimen);
	stretch_order(p) = stretch_order(g);
	if (stretch_order(p) == normal)
		stretch(p) = multandadd(n, stretch(g), xnoverd(stretch(g), f, unity), max_dimen);
	else
		stretch(p) = stretch(g);
	shrink_order(p) = shrink_order(g);
	if (shrink_order(p) == normal)
		shrink(p) = multandadd(n, shrink(g), xnoverd(shrink(g), f, unity), max_dimen);
	else
		shrink(p) = shrink(g);
	return p;
}


#include "mathglue.h"
#include "xovern.h"
#include "multandadd.h"
#include "xnoverd.h"
#include "noeud.h"

halfword mathglue(halfword g, scaled m)
{
	int n = xovern(m, unity);
	scaled f = remainder_;
	if (f < 0)
	{
		n--;
		f += unity;
	}
	auto p = getnode(glue_spec_size);
	width(p) = mu_mult(n, width(g));
	stretch_order(p) = stretch_order(g);
	if (stretch_order(p) == normal)
		stretch(p) = mu_mult(n, stretch(g));
	else
		stretch(p) = stretch(g);
	shrink_order(p) = shrink_order(g);
	if (shrink_order(p) == normal)
		shrink(p) = mu_mult(n, shrink(g));
	else
		shrink(p) = shrink(g);
	return p;
}


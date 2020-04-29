#include "newskipparam.h"
#include "newspec.h"
#include "newglue.h"

halfword newskipparam(smallnumber n)
{
	tempptr = newspec(eqtb[glue_base+n].hh.rh);
	auto p = newglue(tempptr);
	link(tempptr) = 0;
	subtype(p) = n+1;
	return p;
}

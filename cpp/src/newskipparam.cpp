#include "newskipparam.h"
#include "newspec.h"
#include "newglue.h"

halfword newskipparam(smallnumber n)
{
	tempptr = newspec(glue_par(n));
	auto p = newglue(tempptr);
	link(tempptr) = 0;
	subtype(p) = n+1;
	return p;
}

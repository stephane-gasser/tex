#include "newskipparam.h"
#include "newspec.h"
#include "newglue.h"
#include "constantes.h"

halfword newskipparam(smallnumber n)
{
	tempptr = newspec(eqtb[glue_base+n].hh.rh);
	auto p = newglue(tempptr);
	mem[tempptr].hh.rh = 0;
	mem[p].hh.b1 = n+1;
	return p;
}

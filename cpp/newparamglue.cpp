#include "newparamglue.h"
#include "getnode.h"
#include "constantes.h"

halfword newparamglue(smallnumber n)
{
	auto p = getnode(2);
	mem[p].hh.b0 = 10;
	mem[p].hh.b1 = n+1;
	mem[p+1].hh.rh = 0;
	auto q = eqtb[glue_base+n].hh.rh;
	mem[p+1].hh.lh = q;
	mem[q].hh.rh++;
	return p;
}

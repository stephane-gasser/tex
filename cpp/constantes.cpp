#include "constantes.h"
#include "globals.h"

halfword& link(halfword p)
{
	return mem[p].hh.rh;
}

halfword& info(halfword p)
{
	return mem[p].hh.lh;
}

quarterword& type(halfword p)
{
	return mem[p].hh.b0;
}

quarterword& subtype(halfword p)
{
	return mem[p].hh.b1;
}

int cat_code(int c)
{
	return eqtb[cat_code_base+c].hh.rh;
}

int &int_par(int c)
{
	return eqtb[int_base+c].int_;
}


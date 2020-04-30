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

quarterword& save_type(halfword p)
{
	return savestack[p].hh.b0;
}

quarterword& save_level(halfword p)
{
	return savestack[p].hh.b1;
}

halfword& save_index(halfword p)
{
	return savestack[p].hh.rh;
}

quarterword& eq_level(halfword p)
{
	return eqtb[p].hh.b1;
}

quarterword& eq_type(halfword p)
{
	return eqtb[p].hh.b0;
}

halfword& equiv(halfword p)
{
	return eqtb[p].hh.rh;
}

halfword& skip(halfword p)
{
	return equiv(skip_base+p);
}

halfword& mu_skip(halfword p)
{
	return equiv(mu_skip_base+p);
}

halfword& glue_par(halfword p)
{
	return equiv(glue_base+p);
}

halfword& fam_fnt(halfword p)
{
	return equiv(math_font_base+p);
}

halfword& box(halfword p)
{
	return equiv(box_base+p);
}


halfword& cur_font(void)
{
	return equiv(cur_font_loc);
}

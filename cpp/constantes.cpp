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

halfword& cat_code(halfword p)
{
	return equiv(cat_code_base+p);
}

int &int_par(halfword p)
{
	return eqtb[int_base+p].int_;
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

halfword& par_shape_ptr(void)
{
	return equiv(par_shape_loc);
}

halfword& output_routine(void)
{
	return equiv(output_routine_loc);
}

halfword& every_par(void)
{
	return equiv(every_par_loc);
}

halfword& every_math(void)
{
	return equiv(every_math_loc);
}

halfword& every_display(void)
{
	return equiv(every_display_loc);
}

halfword& every_hbox(void)
{
	return equiv(every_hbox_loc);
}

halfword& every_vbox(void)
{
	return equiv(every_vbox_loc);
}

halfword& every_job(void)
{
	return equiv(every_job_loc);
}

halfword& every_cr(void)
{
	return equiv(every_cr_loc);
}

halfword& err_help(void)
{
	return equiv(err_help_loc);
}

halfword& baseline_skip(void)
{
	return glue_par(baseline_skip_code);
}

halfword& left_skip(void)
{
	return glue_par(left_skip_code);
}

halfword& right_skip(void)
{
	return glue_par(right_skip_code);
}

halfword& split_top_skip(void)
{
	return glue_par(split_top_skip_code);
};


halfword& space_skip(void)
{
	return glue_par(space_skip_code);
}

halfword& xspace_skip(void)
{
	return glue_par(xspace_skip_code);
}

halfword& lc_code(halfword p)
{
	return equiv(lc_code_base+p);
}

halfword& sf_code(halfword p)
{
	return equiv(sf_code_base+p);
}

halfword& math_code(halfword p)
{
	return equiv(math_code_base+p);
}

int& count(halfword p)
{
	return eqtb[count_base+p].int_;
}

int& dimen(halfword p)
{
	return eqtb[scaled_base+p].int_;
}

halfword& uc_code(halfword p)
{
	return equiv(uc_code_base+p);
}

int& dimen_par(halfword p)
{
	return eqtb[dimen_base+p].int_;
}

int& del_code(halfword p)
{
	return eqtb[del_code_base+p].int_;
}

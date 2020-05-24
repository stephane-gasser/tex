#include "constantes.h"
#include "globals.h"

halfword& link(halfword p)
{
	return mem[p].hh.rh;
}

halfword& math_type(halfword p)
{
	return mem[p].hh.rh;
}

halfword& glue_ref_count(halfword p)
{
	return mem[p].hh.rh;
}

halfword& info(halfword p)
{
	return mem[p].hh.lh;
}

halfword& node_size(halfword p)
{
	return mem[p].hh.lh;
}

quarterword& type(halfword p)
{
	return mem[p].hh.b0;
}

quarterword& font(halfword p)
{
	return mem[p].hh.b0;
}

quarterword& stretch_order(halfword p)
{
	return mem[p].hh.b0;
}

quarterword& subtype(halfword p)
{
	return mem[p].hh.b1;
}

quarterword& character(halfword p)
{
	return mem[p].hh.b1;
}

quarterword& fitness(halfword p)
{
	return mem[p].hh.b1;
}

quarterword& shrink_order(halfword p)
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


void tail_append(halfword p)
{
	link(tail) = p;
	tail = link(tail);
}

float &glue_set(halfword p)
{
	return mem[p+glue_offset].gr;
}

quarterword& glue_order(halfword p)
{
	return subtype(p+list_offset);
}

quarterword& glue_sign(halfword p)
{
	return type(p+list_offset);
}

halfword& list_ptr(halfword p)
{
	return link(p+list_offset);
}

int& width(halfword p)
{
	return mem[p+width_offset].int_;
}

int& thickness(halfword p)
{
	return mem[p+width_offset].int_;
}

int& depth(halfword p)
{
	return mem[p+depth_offset].int_;
}

int& height(halfword p)
{
	return mem[p+height_offset].int_;
}

int& shift_amount(halfword p)
{
	return mem[p+4].int_;
}

int& stretch(halfword p)
{
	return mem[p+2].int_;
}

int& shrink(halfword p)
{
	return mem[p+3].int_;
}

int& glue_stretch(halfword p)
{
	return mem[p+glue_offset].int_;
}

int& glue_shrink(halfword p)
{
	return mem[p+4].int_;
}

halfword& preamble(void)
{
	return link(align_head);
}


int& u_part(halfword p)
{
	return mem[p+height_offset].int_;
}

int&v_part(halfword p)
{
	return mem[p+depth_offset].int_;
}


int& penalty(halfword p)
{
	return mem[p+1].int_;
}

halfword& line_number(halfword p)
{
	return info(p+1);
}

halfword& llink(halfword p)
{
	return info(p+1);
}

halfword& pre_break(halfword p)
{
	return info(p+1);
}

halfword& rlink(halfword p)
{
	return link(p+1);
}

halfword& break_node(halfword p)
{
	return link(p+1);
}

halfword& post_break(halfword p)
{
	return link(p+1);
}

halfword& leader_ptr(halfword p)
{
	return link(p+1);
}

halfword& glue_ptr(halfword p)
{
	return info(p+1);
}


int& float_cost(halfword p)
{
	return mem[p+1].int_;
}

halfword& ins_ptr(halfword p)
{
	return info(p+4);
}

halfword& split_top_ptr(halfword p)
{
	return link(p+4);
}

int& mark_ptr(halfword p)
{
	return mem[p+1].int_;
}

int& adjust_ptr(halfword p)
{
	return mem[p+1].int_;
}

halfword accent_chr(halfword p)
{
	return p+4;
}

halfword left_delimiter(halfword p)
{
	return p+4;
}

halfword right_delimiter(halfword p)
{
	return p+5;
}

quarterword& small_fam(halfword p)
{
	return mem[p].qqqq.b0;
}

quarterword& small_char(halfword p)
{
	return mem[p].qqqq.b1;
}

quarterword& large_fam(halfword p)
{
	return mem[p].qqqq.b2;
}

quarterword& large_char(halfword p)
{
	return mem[p].qqqq.b3;
}

halfword nucleus(halfword p)
{
	return p+1;
}

halfword delimiter(halfword p)
{
	return p+1;
}

int& new_hlist(halfword p)
{
	return mem[nucleus(p)].int_;
}

halfword numerator(halfword p)
{
	return p+2;
}

halfword denominator(halfword p)
{
	return p+3;
}

halfword supscr(halfword p)
{
	return p+2;
}

halfword subscr(halfword p)
{
	return p+3;
}


halfword lig_char(halfword p)
{
	return p+1;
}

int& if_line_field(halfword p)
{
	return mem[p+1].int_;
}

halfword& lig_ptr(halfword p)
{
	return link(lig_char(p));
}

halfword& display_mlist(halfword p)
{
	return info(p+1);
}

halfword& text_mlist(halfword p)
{
	return link(p+1);
}

halfword& script_mlist(halfword p)
{
	return info(p+2);
}

halfword& script_script_mlist(halfword p)
{
	return link(p+2);
}

int& saved(halfword p)
{
	return savestack[saveptr+p].int_;
}

int& total_demerits(halfword p)
{
	return mem[p+2].int_;
}

bool is_char_node(halfword p)
{
	return p >= himemmin;
}

int char_width(internalfontnumber f, fourquarters i)
{
	return fontinfo[widthbase[f]+i.b0].int_;
}

int char_height(internalfontnumber f, fourquarters i)
{
	return fontinfo[heightbase[f]+i.b1/16].int_;
}

int& param(smallnumber p, internalfontnumber f)
{
	return fontinfo[p+parambase[f]].int_;
}

fourquarters char_info(internalfontnumber f, smallnumber q)
{
	return fontinfo[charbase[f]+q].qqqq;
}

int mathex(smallnumber p)
{
	return param(p, fam_fnt(3+cursize));
}

int default_rule_thickness(void)
{
	return mathex(8);
}

int mathsy(smallnumber p, smallnumber c)
{
	return param(p, fam_fnt(2+c));
}

int num1(smallnumber c)
{
	return mathsy(8, c);
}

int num2(smallnumber c)
{
	return mathsy(9, c);
}

int num3(smallnumber c)
{
	return mathsy(10, c);
}

int denom1(smallnumber c)
{
	return mathsy(11, c);
}

int denom2(smallnumber c)
{
	return mathsy(12, c);
}

int axis_height(smallnumber c)
{
	return mathsy(22, c);
}

int delim1(smallnumber c)
{
	return mathsy(20, c);
}

int delim2(smallnumber c)
{
	return mathsy(21, c);
}

int math_x_height(smallnumber c)
{
	return mathsy(5, c);
}

int& location(halfword p)
{
	return mem[p+2].int_;
}

int math_quad(smallnumber c)
{
	return mathsy(6, c);
}

int sup_drop(smallnumber c)
{
	return mathsy(18, c);
}

int sub_drop(smallnumber c)
{
	return mathsy(19, c);
}

int sup1(smallnumber c)
{
	return mathsy(13, c);
}

int sup2(smallnumber c)
{
	return mathsy(14, c);
}

int sup3(smallnumber c)
{
	return mathsy(15, c);
}

int sub1(smallnumber c)
{
	return mathsy(16, c);
}

int sub2(smallnumber c)
{
	return mathsy(17, c);
}

void copy_to_cur_active(void)
{
	for (int i = 1; i < 6; i++)
		curactivewidth[i] = activewidth[i];
}

void update_width(halfword r)
{
	for (int i = 1; i < 6; i++)
		curactivewidth[i] += mem[r+i].int_;
}

void set_break_width_to_background(void)
{
	for (int i = 1; i < 6; i++)
		breakwidth[i] = background[i];
}

void convert_to_break_width(halfword prev_r)
{
	for (int i = 1; i < 6; i++)
		mem[prev_r+i].int_ += -curactivewidth[i]+breakwidth[i];
}

void store_break_width(void)
{
	for (int i = 1; i < 6; i++)
		activewidth[i] = breakwidth[i];
}

void new_delta_to_break_width(halfword q)
{
	for (int i = 1; i < 6; i++)
		mem[q+i].int_ = breakwidth[i]-curactivewidth[i];
}

void new_delta_from_break_width(halfword q)
{
	for (int i = 1; i < 6; i++)
		mem[q+i].int_ = curactivewidth[i]-breakwidth[i];
}

void combine_two_deltas(halfword prev_r, halfword r)
{
	for (int i = 1; i < 6; i++)
		mem[prev_r+i].int_ += mem[r+i].int_;
}

void downdate_width(halfword prev_r)
{
	for (int i = 1; i < 6; i++)
		curactivewidth[i] -= mem[prev_r+i].int_;
}

void update_active(halfword r)
{
	for (int i = 1; i < 6; i++)
		activewidth[i] += mem[r+i].int_;
}

void store_background(void)
{
	for (int i = 1; i <= 6; i++)
		activewidth[i] = background[i];
}

int char_italic(internalfontnumber f, fourquarters q)
{
	return fontinfo[italicbase[f]+q.b2/4].int_;
}


int char_depth(internalfontnumber f, fourquarters q)
{
	return fontinfo[depthbase[f]+q.b1%16].int_;
}

int char_tag(fourquarters q)
{
	return q.b2%4;
}

bool char_exists(fourquarters q)
{
	return q.b0 > 0;
}

quarterword skip_byte(fourquarters q)
{
	return q.b0;
}

quarterword next_char(fourquarters q)
{
	return q.b1;
}

quarterword op_byte(fourquarters q)
{
	return q.b2;
}

quarterword rem_byte(fourquarters q)
{
	return q.b3;
}

quarterword ext_top(fourquarters q)
{
	return q.b0;
}

quarterword ext_mid(fourquarters q)
{
	return q.b1;
}

quarterword ext_bot(fourquarters q)
{
	return q.b2;
}

quarterword ext_rep(fourquarters q)
{
	return q.b3;
}


int lig_kern_start(internalfontnumber f, fourquarters i)
{
	return ligkernbase[f]+rem_byte(i);
}

int lig_kern_restart(internalfontnumber f, fourquarters i)
{
	return ligkernbase[f]+256*op_byte(i)+rem_byte(i);
}

int char_kern(internalfontnumber f, fourquarters i)
{
	return fontinfo[kernbase[f]+256*op_byte(i)+rem_byte(i)].int_;
}

int big_op_spacing1(void)
{
	return mathex(9);
}

int big_op_spacing2(void)
{
	return mathex(10);
}

int big_op_spacing3(void)
{
	return mathex(11);
}

int big_op_spacing4(void)
{
	return mathex(12);
}

int big_op_spacing5(void)
{
	return mathex(13);
}

halfword& next(halfword p)
{
	return hash[p].lh;
}

halfword& text(halfword p)
{
	return hash[p].rh;
}

int length(halfword p)
{
	return strstart[p+1]-strstart[p];
}

bool hash_is_full(void)
{
	return hashused == hash_base;
}

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

halfword& extra_info(halfword p)
{
	return info(p+list_offset);
}

halfword& token_ref_count(halfword p)
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

quarterword& fam(halfword p)
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

quarterword& span_count(halfword p)
{
	return mem[p].hh.b1;
}

quarterword& subtype(halfword p)
{
	return mem[p].hh.b1;
}

quarterword& replace_count(halfword p)
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

quarterword& what_rhm(halfword p)
{
	return subtype(p+1);
}

quarterword& glue_order(halfword p)
{
	return subtype(p+list_offset);
}

quarterword& what_lhm(halfword p)
{
	return type(p+1);
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


halfword& what_lang(halfword p)
{
	return link(p+1);
}

halfword& broken_ins(halfword p)
{
	return info(p+1);
}

halfword& rlink(halfword p)
{
	return link(p+1);
}

halfword& broken_ptr(halfword p)
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

halfword& best_ins_ptr(halfword p)
{
	return info(p+2);
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

halfword& write_stream(halfword p)
{
	return info(p+1);
}
halfword& display_mlist(halfword p)
{
	return info(p+1);
}

halfword& write_tokens(halfword p)
{
	return link(p+1);
}

halfword& text_mlist(halfword p)
{
	return link(p+1);
}

halfword& script_mlist(halfword p)
{
	return info(p+2);
}

halfword& last_ins_ptr(halfword p)
{
	return link(p+2);
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

halfword& open_name(halfword p)
{
	return link(p+1);
}

halfword& open_area(halfword p)
{
	return info(p+2);
}

halfword& open_ext(halfword p)
{
	return link(p+2);
}

void flush_string(void)
{
	strptr--;
	poolptr = strstart[strptr];
}

void append_char(ASCIIcode c)
{
	strpool[poolptr++] = c;
}


int cur_length(void)
{
	return poolptr-strstart[strptr];
}

void flush_char(void)
{
	poolptr--;
}

halfword& font_id_text(halfword p)
{
	return text(font_id_base+p);
}

halfword &loc = curinput.locfield;

quarterword &state = curinput.statefield;
quarterword &index = curinput.indexfield;
halfword &start = curinput.startfield;
halfword &limit = curinput.limitfield;
std::string &name = curinput.namefield;
scaled &act_width = activewidth[1];

bool is_running(int d)
{
	return d == null_flag;
}

scaled &page_goal = pagesofar[0];
scaled &page_total = pagesofar[1];
scaled &page_shrink = pagesofar[6];
scaled &page_depth = pagesofar[7];

int pretolerance(void)
{
	return int_par(pretolerance_code);
}

int& tolerance(void)
{
	return int_par(tolerance_code);
}

int line_penalty(void)
{
	return int_par(line_penalty_code);
}

int pre_display_penalty(void)
{
	return int_par(pre_display_penalty_code);
}

int post_display_penalty(void)
{
	return int_par(post_display_penalty_code);
}

int floating_penalty(void)
{
	return int_par(floating_penalty_code);
}

int widow_penalty(void)
{
	return int_par(widow_penalty_code);
}

int hyphen_penalty(void)
{
	return int_par(hyphen_penalty_code);
}

int ex_hyphen_penalty(void)
{
	return int_par(ex_hyphen_penalty_code);
}

int bin_op_penalty(void)
{
	return int_par(bin_op_penalty_code);
}

int rel_penalty(void)
{
	return int_par(rel_penalty_code);
}

int broken_penalty(void)
{
	return int_par(broken_penalty_code);
}
	
int club_penalty(void)
{
	return int_par(club_penalty_code);
}

int inter_line_penalty(void)
{
	return int_par(inter_line_penalty_code);
}


int display_widow_penalty(void)
{
	return int_par(display_widow_penalty_code);
}

int double_hyphen_demerits(void)
{
	return int_par(double_hyphen_demerits_code);
}

int final_hyphen_demerits(void)
{
	return int_par(final_hyphen_demerits_code);
}

int adj_demerits(void)
{
	return int_par(adj_demerits_code);
}

int& mag(void)
{
	return int_par(mag_code);
}

int delimiter_factor(void)
{
	return int_par(delimiter_factor_code);
}

int looseness(void)
{
	return int_par(looseness_code);
}

int& time(void)
{
	return int_par(time_code);
}

int& day(void)
{
	return int_par(day_code);
}

int& month(void)
{
	return int_par(month_code);
}

int& year(void)
{
	return int_par(year_code);
}


int show_box_breadth(void)
{
	return int_par(show_box_breadth_code);
}

int show_box_depth(void)
{
	return int_par(show_box_depth_code);
}

int hbadness(void)
{
	return int_par(hbadness_code);
}

int& vbadness(void)
{
	return int_par(vbadness_code);
}

int pausing(void)
{
	return int_par(pausing_code);
}

int tracing_commands(void)
{
	return int_par(tracing_commands_code);
}

int tracing_online(void)
{
	return int_par(tracing_online_code);
}

int tracing_macros(void)
{
	return int_par(tracing_macros_code);
}

int uc_hyph(void)
{
	return int_par(uc_hyph_code);
}

int tracing_lost_chars(void)
{
	return int_par(tracing_lost_chars_code);
}

int holding_inserts(void)
{
	return int_par(holding_inserts_code);
}

int& max_dead_cycles(void)
{
	return int_par(max_dead_cycles_code);
}

int left_hyphen_min(void)
{
	return int_par(left_hyphen_min_code);
}

int right_hyphen_min(void)
{
	return int_par(right_hyphen_min_code);
}

int language(void)
{
	return int_par(language_code);
}

int& end_line_char(void)
{
	return int_par(end_line_char_code);
}

int global_defs(void)
{
	return int_par(global_defs_code);
}

int& hang_after(void)
{
	return int_par(hang_after_code);
}

int& escape_char(void)
{
	return int_par(escape_char_code);
}

int cur_fam(void)
{
	return int_par(cur_fam_code);
}

int& new_line_char(void)
{
	return int_par(new_line_char_code);
}

int default_hyphen_char(void)
{
	return int_par(default_hyphen_char_code);
}

int default_skew_char(void)
{
	return int_par(default_skew_char_code);
}

int error_context_lines(void)
{
	return int_par(error_context_lines_code);
}

int& tracing_stats(void)
{
	return int_par(tracing_stats_code);
}

int tracing_output(void)
{
	return int_par(tracing_output_code);
}

int math_surround(void)
{
	return dimen_par(math_surround_code);
}

int pre_display_size(void)
{
	return dimen_par(pre_display_size_code);
}

int display_width(void)
{
	return dimen_par(display_width_code);
}

int display_indent(void)
{
	return dimen_par(display_indent_code);
}

int& overfull_rule(void)
{
	return dimen_par(overfull_rule_code);
}

int line_skip_limit(void)
{
	return dimen_par(line_skip_limit_code);
}

int& vfuzz(void)
{
	return dimen_par(vfuzz_code);
}

int hsize(void)
{
	return dimen_par(hsize_code);
}

int vsize(void)
{
	return dimen_par(vsize_code);
}


int split_max_depth(void)
{
	return dimen_par(split_max_depth_code);
}

int hfuzz(void)
{
	return dimen_par(hfuzz_code);
}

int hang_indent(void)
{
	return dimen_par(hang_indent_code);
}

int par_indent(void)
{
	return dimen_par(par_indent_code);
}

int delimiter_shortfall(void)
{
	return dimen_par(delimiter_shortfall_code);
}

int script_space(void)
{
	return dimen_par(script_space_code);
}

int emergency_stretch(void)
{
	return dimen_par(emergency_stretch_code);
}

int h_offset(void)
{
	return dimen_par(h_offset_code);
}

int v_offset(void)
{
	return dimen_par(v_offset_code);
}

int null_delimiter_space(void)
{
	return dimen_par(null_delimiter_space_code);
}

int box_max_depth(void)
{
	return dimen_par(box_max_depth_code);
}

alphafile& cur_file(void)
{
	return inputfile[index];
}

halfword &top_mark = curmark[top_mark_code];;
halfword &first_mark = curmark[first_mark_code];
halfword &bot_mark = curmark[bot_mark_code];
halfword &split_first_mark = curmark[split_first_mark_code];
halfword &split_bot_mark = curmark[split_bot_mark_code];

void scanned_result(int c, char l)
{
	curval = c;
	curvallevel = l;
}


void append_to_name(int &k, char c)
{
	k++;
	if (k <= filenamesize)
		nameoffile[k] = xchr[c];
}

int& slant(internalfontnumber f)
{
	return param(slant_code, f);
}

int& space(internalfontnumber f)
{
	return param(space_code, f);
}

int& space_stretch(internalfontnumber f)
{
	return param(space_stretch_code, f);
}

int& space_shrink(internalfontnumber f)
{
	return param(space_shrink_code, f);
}

int& x_height(internalfontnumber f)
{
	return param(x_height_code, f);
}

int& quad(internalfontnumber f)
{
	return param(quad_code, f);
}

int& extra_space(internalfontnumber f)
{
	return param(extra_space_code, f);
}

constexpr float billion = 1000000000.;

float vet_glue(float g)
{
	float gluetemp = g;
	if (gluetemp > billion)
		return billion;
	if (gluetemp < -billion)
		return -billion;
	return g;
}

halfword& trie_link(halfword p)
{
	return trie[p].rh;
}

halfword& trie_back(halfword p)
{
	return trie[p].lh;
}

quarterword& trie_char(halfword p)
{
	return trie[p].b1;
}

quarterword& trie_op(halfword p)
{
	return trie[p].b0;
}

triepointer &trie_root = triel[0];
triepointer *trie_ref = triehash;

void set_cur_lang(void)
{
	curlang = (language() <= 0 || language() > 255) ? 0 : language(); 
}


halfword &contrib_tail = nest[0].tailfield;

bool fam_in_range(void)
{
	return  cur_fam() >= 0 && cur_fam() < 16;
}


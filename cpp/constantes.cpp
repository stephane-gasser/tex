#include "constantes.h"
#include "globals.h"

halfword& link(halfword p) { return mem[p].hh.rh; }
halfword& math_type(halfword p) { return mem[p].hh.rh; }
halfword& glue_ref_count(halfword p) { return mem[p].hh.rh; }
halfword& info(halfword p) { return mem[p].hh.lh; }
halfword& extra_info(halfword p) { return info(p+list_offset); }
halfword& token_ref_count(halfword p) { return mem[p].hh.lh; }
halfword& node_size(halfword p) { return mem[p].hh.lh; }
quarterword& type(halfword p) { return mem[p].hh.b0; }
quarterword& fam(halfword p) { return mem[p].hh.b0; }
quarterword& font(halfword p) { return mem[p].hh.b0; }
quarterword& stretch_order(halfword p) { return mem[p].hh.b0; }
quarterword& span_count(halfword p) { return mem[p].hh.b1; }
quarterword& subtype(halfword p) { return mem[p].hh.b1; }
quarterword& replace_count(halfword p) { return mem[p].hh.b1; }
quarterword& character(halfword p) { return mem[p].hh.b1; }
quarterword& fitness(halfword p) { return mem[p].hh.b1; }
quarterword& shrink_order(halfword p) { return mem[p].hh.b1; }
halfword& cat_code(halfword p) { return equiv(cat_code_base+p); }
quarterword& save_type(halfword p) { return savestack[p].hh.b0; }
quarterword& save_level(halfword p) { return savestack[p].hh.b1; }
halfword& save_index(halfword p) { return savestack[p].hh.rh; }
quarterword& eq_level(halfword p) { return eqtb[p].hh.b1; }
quarterword& eq_type(halfword p) { return eqtb[p].hh.b0; }
halfword& equiv(halfword p) { return eqtb[p].hh.rh; }
halfword& skip(halfword p) { return equiv(skip_base+p); }
halfword& fam_fnt(halfword p) { return equiv(math_font_base+p); }
halfword& box(halfword p) { return equiv(box_base+p); }
halfword& cur_font(void) { return equiv(cur_font_loc); }
halfword& par_shape_ptr(void) { return equiv(par_shape_loc); }
halfword& every_math(void) { return equiv(every_math_loc); }
halfword& every_cr(void) { return equiv(every_cr_loc); }
halfword& err_help(void) { return equiv(err_help_loc); }
halfword& lc_code(halfword p) { return equiv(lc_code_base+p); }
halfword& sf_code(halfword p) { return equiv(sf_code_base+p); }
halfword& math_code(halfword p) { return equiv(math_code_base+p); }
int& count(halfword p) { return eqtb[count_base+p].int_; }
int& dimen(halfword p) { return eqtb[scaled_base+p].int_; }
int& del_code(halfword p) { return eqtb[del_code_base+p].int_; }
float &glue_set(halfword p) { return mem[p+glue_offset].gr; }
quarterword& what_rhm(halfword p) { return subtype(p+1); }
quarterword& glue_order(halfword p) { return subtype(p+list_offset); }
quarterword& what_lhm(halfword p) { return type(p+1); }
quarterword& glue_sign(halfword p) { return type(p+list_offset); }
halfword& list_ptr(halfword p) { return link(p+list_offset); }
int& width(halfword p) { return mem[p+width_offset].int_; }
int& thickness(halfword p) { return mem[p+width_offset].int_; }
int& depth(halfword p) { return mem[p+depth_offset].int_; }
int& height(halfword p) { return mem[p+height_offset].int_; }
int& shift_amount(halfword p) { return mem[p+4].int_; }
int& stretch(halfword p) { return mem[p+2].int_; }
int& shrink(halfword p) { return mem[p+3].int_; }
int& glue_stretch(halfword p) { return mem[p+glue_offset].int_; }
int& glue_shrink(halfword p) { return mem[p+4].int_; }
halfword& preamble(void) { return link(align_head); }
int& u_part(halfword p) { return mem[p+height_offset].int_; }
int&v_part(halfword p) { return mem[p+depth_offset].int_; }
int& penalty(halfword p) { return mem[p+1].int_; }
halfword& line_number(halfword p) { return info(p+1); }
halfword& llink(halfword p) { return info(p+1); }
halfword& pre_break(halfword p) { return info(p+1); }
halfword& what_lang(halfword p) { return link(p+1); }
halfword& broken_ins(halfword p) { return info(p+1); }
halfword& rlink(halfword p) { return link(p+1); }
halfword& break_node(halfword p) { return link(p+1); }
halfword& post_break(halfword p) { return link(p+1); }
halfword& leader_ptr(halfword p) { return link(p+1); }
halfword& glue_ptr(halfword p) { return info(p+1); }
int& float_cost(halfword p) { return mem[p+1].int_; }
halfword& best_ins_ptr(halfword p) { return info(p+2); }
halfword& ins_ptr(halfword p) { return info(p+4); }
halfword& split_top_ptr(halfword p) { return link(p+4); }
int& mark_ptr(halfword p) { return mem[p+1].int_; }
int& adjust_ptr(halfword p) { return mem[p+1].int_; }
halfword accent_chr(halfword p) { return p+4; }
halfword left_delimiter(halfword p) { return p+4; }
halfword right_delimiter(halfword p) { return p+5; }
quarterword& small_fam(halfword p) { return mem[p].qqqq.b0; }
quarterword& small_char(halfword p) { return mem[p].qqqq.b1; }
quarterword& large_fam(halfword p) { return mem[p].qqqq.b2; }
quarterword& large_char(halfword p) { return mem[p].qqqq.b3; }
halfword nucleus(halfword p) { return p+1; }
halfword delimiter(halfword p) { return p+1; }
int& new_hlist(halfword p) { return mem[nucleus(p)].int_; }
halfword numerator(halfword p) { return p+2; }
halfword denominator(halfword p) { return p+3; }
halfword supscr(halfword p) { return p+2; }
halfword subscr(halfword p) { return p+3; }
halfword lig_char(halfword p) { return p+1; }
int& if_line_field(halfword p) { return mem[p+1].int_; }
halfword& lig_ptr(halfword p) { return link(lig_char(p)); }
halfword& write_stream(halfword p) { return info(p+1); }
halfword& display_mlist(halfword p) { return info(p+1); }
halfword& write_tokens(halfword p) { return link(p+1); }
halfword& text_mlist(halfword p) { return link(p+1); }
halfword& script_mlist(halfword p) { return info(p+2); }
halfword& last_ins_ptr(halfword p) { return link(p+2); }
halfword& script_script_mlist(halfword p) { return link(p+2); }
int& saved(halfword p) { return savestack[saveptr+p].int_; }
int& total_demerits(halfword p) { return mem[p+2].int_; }
bool is_char_node(halfword p) { return p >= himemmin; }
int char_width(internalfontnumber f, fourquarters i) { return fontinfo[widthbase[f]+i.b0].int_; }
int char_height(internalfontnumber f, fourquarters i) { return fontinfo[heightbase[f]+i.b1/16].int_; }
int& param(smallnumber p, internalfontnumber f) { return fontinfo[p+parambase[f]].int_; }
fourquarters char_info(internalfontnumber f, smallnumber q) { return fontinfo[charbase[f]+q].qqqq; }
int mathex(smallnumber p) { return param(p, fam_fnt(3+cursize)); }
int default_rule_thickness(void) { return mathex(8); }
int mathsy(smallnumber p, smallnumber c) { return param(p, fam_fnt(2+c)); }
int axis_height(smallnumber c) { return mathsy(22, c); }
int math_x_height(smallnumber c) { return mathsy(5, c); }
int& location(halfword p) { return mem[p+2].int_; }
int math_quad(smallnumber c) { return mathsy(6, c); }
int char_italic(internalfontnumber f, fourquarters q) { return fontinfo[italicbase[f]+q.b2/4].int_; }
int char_depth(internalfontnumber f, fourquarters q) { return fontinfo[depthbase[f]+q.b1%16].int_; }
int char_tag(fourquarters q) { return q.b2%4; }
bool char_exists(fourquarters q) { return q.b0 > 0; }
quarterword skip_byte(fourquarters q) { return q.b0; }
quarterword next_char(fourquarters q) { return q.b1; }
quarterword op_byte(fourquarters q) { return q.b2; }
quarterword rem_byte(fourquarters q) { return q.b3; }
int lig_kern_start(internalfontnumber f, fourquarters i) { return ligkernbase[f]+rem_byte(i); }
int lig_kern_restart(internalfontnumber f, fourquarters i) { return ligkernbase[f]+256*op_byte(i)+rem_byte(i); }
int char_kern(internalfontnumber f, fourquarters i) { return fontinfo[kernbase[f]+256*op_byte(i)+rem_byte(i)].int_; }
halfword& text(halfword p) { return hash[p].rh; }
int length(halfword p) { return strstart[p+1]-strstart[p]; }
halfword& open_name(halfword p) { return link(p+1); }
halfword& open_area(halfword p) { return info(p+2); }
halfword& open_ext(halfword p) { return link(p+2); }
int cur_length(void) { return poolptr-strstart[strptr]; }
bool is_running(int d) { return d == null_flag; }
alphafile& cur_file(void) { return inputfile[index]; }
int& space(internalfontnumber f) { return param(space_code, f); }
int& space_stretch(internalfontnumber f) { return param(space_stretch_code, f); }
int& space_shrink(internalfontnumber f) { return param(space_shrink_code, f); }
int& x_height(internalfontnumber f) { return param(x_height_code, f); }
int& quad(internalfontnumber f) { return param(quad_code, f); }
halfword& trie_link(halfword p) { return trie[p].rh; }
quarterword& trie_char(halfword p) { return trie[p].b1; }
quarterword& trie_op(halfword p) { return trie[p].b0; }
halfword& every_vbox(void) { return equiv(every_vbox_loc); }
bool fam_in_range(void) { return cur_fam() >= 0 && cur_fam() < 16; }
void set_cur_lang(void) { curlang = (language() <= 0 || language() > 255) ? 0 : language(); }
void append_char(ASCIIcode c) { strpool[poolptr++] = c; }
void flush_char(void) { poolptr--; }

void tail_append(halfword p) 
{
	link(tail) = p;
	tail = link(tail);
}

void flush_string(void)
{
	strptr--;
	poolptr = strstart[strptr];
}

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

float vet_glue(float g)
{
	constexpr float billion = 1000000000.;
	float gluetemp = g;
	if (gluetemp > billion)
		return billion;
	if (gluetemp < -billion)
		return -billion;
	return g;
}

halfword &loc = curinput.locfield;
quarterword &state = curinput.statefield;
quarterword &index = curinput.indexfield;
halfword &start = curinput.startfield;
halfword &limit = curinput.limitfield;
std::string &name = curinput.namefield;
scaled &act_width = activewidth[1];
scaled &page_goal = pagesofar[0];
scaled &page_total = pagesofar[1];
scaled &page_shrink = pagesofar[6];
scaled &page_depth = pagesofar[7];
halfword &top_mark = curmark[top_mark_code];
halfword &first_mark = curmark[first_mark_code];
halfword &bot_mark = curmark[bot_mark_code];
halfword &split_first_mark = curmark[split_first_mark_code];
halfword &split_bot_mark = curmark[split_bot_mark_code];
triepointer &trie_root = triel[0];
triepointer *trie_ref = triehash;
halfword &contrib_tail = nest[0].tailfield;


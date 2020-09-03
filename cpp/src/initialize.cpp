#include "initialize.h"
#include "texte.h"
#include "cesure.h"
#include "police.h"
#include "equivalent.h"
#include "alignement.h"
#include "buildpage.h"

void Initialize(void)
{
	for (int i = 0; i < 256; i++)
		xchr[i] = ' ';
	for (int i = -128; i < 127; i++)
		xord[i] = 127;
	for (int i = 32; i < 127; i++)
		xchr[i] = xord[i] = i;
	mode = vmode;
	tail = head = contrib_head = new LinkedNode;
	prev_depth = ignore_depth;
	mode_line = 0;
	prev_graf = 0;
	pagetail = page_head;
	page_head->link = nullptr;
	page_depth = 0;
	for (int k = 0; k <= fontmax; k++)
		fonts[k].used = false;
	for (int k = 1; k < 20; k++)
		mem[k].int_ = 0;
	fil_glue->stretch = unity;
	fil_glue->stretch_order = fil;
	fill_glue->stretch = unity;
	fill_glue->stretch_order = fill;
	ss_glue->stretch = unity;
	ss_glue->stretch_order = fil;
	ss_glue->shrink = unity;
	ss_glue->shrink_order = fil;
	fil_neg_glue->stretch = -unity;
	fil_neg_glue->stretch_order = fil;
	for (int k = hi_mem_stat_min; k <= mem_top; k++)
		mem[k].int_ = 0;
	omit_template = new TokenNode(end_template_token);
	end_span->Link = 256;
	end_span->info = nullptr;
	page_ins_head = new PageInsNode;
	page_ins_head->subtype = 255;
	page_ins_head->type = split_up;
	page_ins_head->link = page_ins_head;
	page_head = new GlueNode(zero_glue);
	temp_head = new TokenNode;
	hold_head = new LinkedNode;
	adjust_head = new LinkedNode;
	null_list = new LinkedNode;
	lig_trick = new CharNode(fonts[null_font], 0);
	garbage = new LinkedNode;
	backup_head = new LinkedNode;
	eqtb_cs[undefined_control_sequence-hash_base].type = undefined_cs;
	eqtb_cs[undefined_control_sequence-hash_base].level = level_zero;
	eqtb_cs[undefined_control_sequence-hash_base].index = /*0*/nullptr;
	for (int k = 0; k < hash_base-active_base; k++)
		eqtb_active[k] = eqtb_cs[undefined_control_sequence-hash_base];
	for (int k = 0; k < undefined_control_sequence-hash_base; k++)
		eqtb_cs[k] = eqtb_cs[undefined_control_sequence-hash_base];
	eqtb_glue[0].index = zero_glue;
	eqtb_glue[0].level = level_one;
	eqtb_glue[0].type = glue_ref;
	for (int k = 1; k < local_base-glue_base; k++)
		eqtb_glue[k] = eqtb_glue[0];
	zero_glue->glue_ref_count += local_base-glue_base;
	eqtb_local[0].index = /*shape 0 ??*/nullptr;
	eqtb_local[0].type = shape_ref;
	eqtb_local[0].level = level_one;
	for (int k = 1; k < box_base-local_base; k++)
		eqtb_local[k] = eqtb_cs[undefined_control_sequence-local_base];
	eqtb_local[box_base-local_base].index = /*box[0] ??*/nullptr;
	eqtb_local[box_base-local_base].type = box_ref;
	eqtb_local[box_base-local_base].level = level_one;
	for (int k = box_base+1; k < cur_font_loc; k++)
		eqtb_local[k-local_base] = eqtb_local[box_base-local_base];
	eqtb_local[cur_font_loc-local_base].index = /*null_font*/nullptr;
	eqtb_local[cur_font_loc-local_base].type = data;
	eqtb_local[cur_font_loc-local_base].level = level_one;
	for (int k = cur_font_loc+1; k < cat_code_base; k++)
		eqtb_local[k-local_base] = eqtb_local[cur_font_loc-local_base];
	eqtb_local[cat_code_base-local_base].index = /*0 ?*/nullptr;
	eqtb_local[cat_code_base-local_base].type = data;
	eqtb_local[cat_code_base-local_base].level = level_one;
	for (int k = cat_code_base+1; k < int_base; k++)
		eqtb_local[k-local_base] = eqtb_local[cat_code_base-local_base];
	for (int k = 0; k < 256; k++)
	{
		cat_code(k) = other_char;
		math_code(k) = k;
		sf_code(k) = 1000;
	}
	cat_code('\r') = car_ret;
	cat_code(' ') = spacer;
	cat_code('\\') = escape;
	cat_code('%') = comment;
	cat_code(127) = invalid_char;
	cat_code('\0') = ignore;
	for (int k = '0'; k <= '9'; k++)
		math_code(k) = k+var_code;
	for (int k = 'A'; k <= 'Z'; k++)
	{
		cat_code(k) = letter;
		cat_code(k+'a'-'A') = letter;
		math_code(k) = k+var_code+0x1'00;
		math_code(k+'a'-'A') = k+var_code+0x1'00+'a'-'A';
		lc_code(k) = k+'a'-'A';
		lc_code(k+'a'-'A') = k+'a'-'A';
		uc_code(k) = k;
		uc_code(k+'a'-'A') = k;
		sf_code(k) = 999;
	}
	for (int k = 0; k < del_code_base-int_base; k++)
		eqtb_int[k].int_ = 0;
	mag() = 1000;
	tolerance() = 10000;
	hang_after() = 1;
	max_dead_cycles() = 25;
	escape_char() = '\\';
	end_line_char() = '\r';
	for (int k = 0; k < 256; k++)
		del_code(k) = -1;
	del_code('.') = 0;
	for (int k = 0; k <= eqtb_size-dimen_base; k++)
		eqtb_dimen[k].int_ = 0;
	eqtb_cs[frozen_dont_expand-hash_base].type = dont_expand;
	eqtb_cs[frozen_dont_expand-hash_base].text = "notexpanded:";
	fonts[null_font].name = "nullfont"; 
	fonts[null_font].area = "";
	fonts[null_font].hyphenchar = '-';
	fonts[null_font].skewchar = -1;
	fonts[null_font].bcharlabel = non_address;
	fonts[null_font].bchar = non_char;
	fonts[null_font].falsebchar = non_char;
	fonts[null_font].bc = 1;
	fonts[null_font].ec = 0;
	fonts[null_font].size = 0;
	fonts[null_font].dsize = 0;
	fonts[null_font].glue = zero_glue/* ou nullptr ?*/;
	fonts[null_font].params = 7;
	fonts[null_font].charbase = 0;
	fonts[null_font].widthbase = 0;
	fonts[null_font].heightbase = 0;
	fonts[null_font].depthbase = 0;
	fonts[null_font].italicbase = 0;
	fonts[null_font].ligkernbase = 0;
	fonts[null_font].kernbase = 0;
	fonts[null_font].extenbase = 0;
	fonts[null_font].parambase = -1;
	for (auto &fi: Font::info)
		fi.int_ = 0;
	trie_root = 0;
	trieNode[0].c = 0;
	eqtb_cs[frozen_control_sequence-hash_base].text = "inaccessible";
	eqtb_cs[end_write-hash_base].text = "endwrite";
	eqtb_cs[end_write-hash_base].level = level_one;
	eqtb_cs[end_write-hash_base].type = outer_call;
	eqtb_cs[end_write-hash_base].index = /*0*/nullptr;
}

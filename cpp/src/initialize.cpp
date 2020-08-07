#include "initialize.h"
#include "texte.h"
#include "cesure.h"
#include "police.h"

static halfword& uc_code(halfword p) { return equiv(uc_code_base+p); }

void Initialize(void)
{
	for (int i = 0; i < 256; i++)
	{
		xchr[i] = i < 32 ? ' ' : i < 127 ? i : ' ';
	    xord[char(i)] = i < 32 ? 127 : i < 127 ? i : 127;
	}
	interaction = error_stop_mode;
	errorcount = 0;
	useerrhelp = false;
	nestptr = 0;
	maxneststack = 0;
	mode = vmode;
	tail = head = contrib_head = new LinkedNode;
	prev_depth = -0x1'00'00*1000;
	mode_line = 0;
	prev_graf = 0;
	shownmode = 0;
	pagecontents = 0;
	pagetail = page_head;
	page_head->link = nullptr;
	lastglue = nullptr;
	lastpenalty = 0;
	lastkern = 0;
	page_depth = 0;
	pagemaxdepth = 0;
	for (int k = int_base; k < 6107; k++)
    	xeqlevel[k] = 1;
	nonewcontrolsequence = true;
	hash[514].lh = 0;
	hash[514].rh = 0;
	for (int k = 515; k < 2881; k++)
	    hash[k] = hash[514];
	saveptr = 0;
	curlevel = 1;
	curgroup = 0;
	curboundary = 0;
	maxsavestack = 0;
	magset = 0;
	radix = 0;
	curorder = 0;
	for (int k = 0; k < 17; k++)
	    readopen[k] = closed;
	condptr = 0;
	iflimit = 0;
	curif = 0;
	ifline = 0;
	TEXformatdefault = "TeXformats:plain.fmt";
	for (int k = 0; k <= fontmax; k++)
		fonts[k].used = false;
	nullcharacter.b0 = 0;
	nullcharacter.b1 = 0;
	nullcharacter.b2 = 0;
	nullcharacter.b3 = 0;
	totalpages = 0;
	maxv = 0;
	maxh = 0;
	maxpush = 0;
	lastbop = -1;
	doingleaders = false;
	deadcycles = 0;
	curs = -1;
	halfbuf = dvibufsize/2;
	dvilimit = dvibufsize;
	dviptr = 0;
	dvioffset = 0;
	dvigone = 0;
	downptr = 0;
	rightptr = 0;
	adjusttail = nullptr;
	lastbadness = 0;
	packbeginline = 0;
	alignptr = 0;
	curalign = 0;
	curspan = 0;
	curhead = nullptr;
	curtail = nullptr;
	for (int z = 0; z < 308; z++)
	{
		hyphword[z] = "";
		hyphlist[z] = 0;
	}
	hyphcount = 0;
	outputactive = false;
	insertpenalties = 0;
	ligaturepresent = false;
	cancelboundary = false;
	lfthit = false;
	rthit = false;
	insdisc = false;
	longhelpseen = false;
	for (int k = 0; k < 18; k++)
		writeopen[k] = false;
	for (int k = 1; k < 20; k++)
		mem[k].int_ = 0;
/*	for (int k = 0; k <= lo_mem_stat_max; k += glue_spec_size)
	{
		glue_ref_count(k) = 1;
		stretch_order(k) = normal;
		shrink_order(k) = normal;
	}*/
	
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
	rover = lo_mem_stat_max+1;
	link(rover) = empty_flag;
	node_size(rover) = 1000;
	llink(rover) = rover;
	rlink(rover) = rover;
	lomemmax = rover+1000;
	link(lomemmax) = 0;
	info(lomemmax) = 0;
	for (int k = hi_mem_stat_min; k <= mem_top; k++)
		mem[k] = mem[lomemmax];
	omit_template = new TokenNode(end_template_token);
	end_span->link = 256;
	end_span->info = nullptr;
	type(active->num) = 1;
	line_number(active->num) = empty_flag;
	subtype(active->num) = 0; // the |subtype| is never examined by the algorithm
	page_ins_head = new PageInsNode;
	page_ins_head->subtype = 255;
	page_ins_head->type = split_up;
	page_ins_head->link = page_ins_head;
	page_head = new GlueNode(zero_glue);
	temp_head = new TokenNode;
	hold_head = new LinkedNode;
	adjust_head = new LinkedNode;
	null_list = new LinkedNode;
	lig_trick = new LinkedNode;
	garbage = new LinkedNode;
	backup_head = new LinkedNode;
	avail = 0;
	memend = mem_top;
	himemmin = hi_mem_stat_min;
	varused = 20;
	dynused = hi_mem_stat_usage;
	eq_type(undefined_control_sequence) = undefined_cs;
	equiv(undefined_control_sequence) = 0;
	eq_level(undefined_control_sequence) = 0;
	for (int k = 1; k < undefined_control_sequence; k++)
		eqtb[k] = eqtb[undefined_control_sequence];
	equiv(glue_base) = 0;
	eq_level(glue_base) = 1;
	eq_type(glue_base) = glue_ref;
	for (int k = glue_base+1; k < local_base; k++)
		eqtb[k] = eqtb[glue_base];
	zero_glue->glue_ref_count += local_base-glue_base;
	equiv(local_base) = 0;
	eq_type(local_base) = shape_ref;
	eq_level(local_base) = 1;
	for (int k = local_base+1; k < box_base; k++)
		eqtb[k] = eqtb[undefined_control_sequence];
	equiv(box_base) = 0;
	eq_type(box_base) = box_ref;
	eq_level(box_base) = 1;
	for (int k = box_base+1; k < cur_font_loc; k++)
		eqtb[k] = eqtb[box_base];
	equiv(cur_font_loc) = null_font;
	eq_type(cur_font_loc) = data;
	eq_level(cur_font_loc) = 1;
	for (int k = cur_font_loc+1; k < cat_code_base; k++)
		eqtb[k] = eqtb[cur_font_loc];
	equiv(cat_code_base) = 0;
	eq_type(cat_code_base) = data;
	eq_level(cat_code_base) = 1;
	for (int k = cat_code_base+1; k < int_base; k++)
		eqtb[k] = eqtb[cat_code_base];
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
	for (int k = int_base; k < del_code_base; k++)
		eqtb[k].int_ = 0;
	mag() = 1000;
	tolerance() = 10000;
	hang_after() = 1;
	max_dead_cycles() = 25;
	escape_char() = '\\';
	end_line_char() = '\r';
	for (int k = 0; k < 256; k++)
		del_code(k) = -1;
	del_code('.') = 0;
	for (int k = dimen_base; k <= eqtb_size; k++)
		eqtb[k].int_ = 0;
	hashused = frozen_control_sequence;
	cscount = 0;
	eq_type(frozen_dont_expand) = dont_expand;
	text(frozen_dont_expand) = txt("notexpanded:");
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
	fonts[null_font].glue = nullptr;
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
	trienotready = true; 
	trie_root = 0;
	trieNode[0].c = 0;
	text(frozen_control_sequence) = txt("inaccessible");
	formatident = " (INITEX)";
	text(end_write) = txt("endwrite");
	eq_level(end_write) = 1;
	eq_type(end_write) = outer_call;
	equiv(end_write) = 0;
}

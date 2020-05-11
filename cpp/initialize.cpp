#include "initialize.h"

void Initialize(void)
{
	for (int i = 0; i < 32; i++)
		xchr[i] = ' ';
	for (int i = 32; i < 127; i++)
		xchr[i] = i;
	for (int i = 127; i < 256; i++)
		xchr[i] = ' ';
	for (int i = 0; i < 256; i++)
	    xord[char(i)] = 127;
	for (int i = 128; i < 256; i++)
		xord[xchr[i]] = i;
	for (int i = 0; i < 127; i++)
		xord[xchr[i]] = i;
	interaction = error_stop_mode;
	deletionsallowed = true;
	setboxallowed = true;
	errorcount = 0;
	helpptr = 0;
	useerrhelp = false;
	interrupt = 0;
	OKtointerrupt = true;
	nestptr = 0;
	maxneststack = 0;
	mode = vmode;
	head = contrib_head;
	tail = contrib_head;
	prev_depth = -0x1'00'00*1000;
	mode_line = 0;
	prev_graf = 0;
	shownmode = 0;
	pagecontents = 0;
	pagetail = page_head;
	link(page_head) = 0;
	lastglue = empty_flag;
	lastpenalty = 0;
	lastkern = 0;
	pagesofar[7] = 0;
	pagemaxdepth = 0;
	for (int k = int_base; k < 6107; k++)
    	xeqlevel[k] = 1;
	nonewcontrolsequence = true;
	hash[514].lh = 0;
	hash[514].rh = 0;
	for (int k = 515; k <2881; k++)
	    hash[k] = hash[514];
	saveptr = 0;
	curlevel = 1;
	curgroup = 0;
	curboundary = 0;
	maxsavestack = 0;
	magset = 0;
	curmark[0] = 0;
	curmark[1] = 0;
	curmark[2] = 0;
	curmark[3] = 0;
	curmark[4] = 0;
	curval = 0;
	curvallevel = 0;
	radix = 0;
	curorder = 0;
	for (int k = 0; k < 17; k++)
	    readopen[k] = 2;
	condptr = 0;
	iflimit = 0;
	curif = 0;
	ifline = 0;
	TEXformatdefault = "TeXformats:plain.fmt";
	for (int k = 0; k <= fontmax; k++)
		fontused[k] = false;
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
	adjusttail = 0;
	lastbadness = 0;
	packbeginline = 0;
	emptyfield.rh = 0;
	emptyfield.lh = 0;
	nulldelimiter.b0 = 0;
	nulldelimiter.b1 = 0;
	nulldelimiter.b2 = 0;
	nulldelimiter.b3 = 0;
	alignptr = 0;
	curalign = 0;
	curspan = 0;
	curloop = 0;
	curhead = 0;
	curtail = 0;
	for (int z = 0; z < 308; z++)
	{
		hyphword[z] = 0;
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
	aftertoken = 0;
	longhelpseen = false;
	formatident = 0;
	for (int k = 0; k < 18; k++)
		writeopen[k] = false;
	for (int k = 1; k < 20; k++)
		mem[k].int_ = 0;
	for (int k = 0; k <= lo_mem_stat_max; k += glue_spec_size)
	{
		glue_ref_count(k) = 1;
		stretch_order(k) = normal;
		shrink_order(k) = normal;
	}
	stretch(fil_glue) = unity;
	stretch_order(fil_glue) = fil;
	stretch(fill_glue) = unity;
	stretch_order(fill_glue) = fill;
	stretch(ss_glue) = unity;
	stretch_order(ss_glue) = fil;
	shrink(ss_glue) = unity;
	shrink_order(ss_glue) = fil;
	stretch(fil_neg_glue) = -unity;
	stretch_order(fil_neg_glue) = fil;
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
	info(omit_template) = frozen_end_template+cs_token_flag;
	link(end_span) = 256;
	info(end_span) = 0;
	type(active) = 1;
	info(29994) = empty_flag;
	subtype(active) = 0;
	subtype(page_ins_head) = 255;
	type(page_ins_head) = 1;
	link(page_ins_head) = page_ins_head;
	type(page_head) = 10;
	subtype(page_head) = 0;
	avail = 0;
	memend = mem_top;
	himemmin = hi_mem_stat_min;
	varused = 20;
	dynused = 14;
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
	link(zero_glue) += 530;
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
	equiv(cur_font_loc) = 0;
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
		math_code(k) = k+0x70'00;
	for (int k = 'A'; k <= 'Z'; k++)
	{
		cat_code(k) = letter;
		cat_code(k+'a'-'A') = letter;
		math_code(k) = k+0x71'00;
		math_code(k+'a'-'A') = k+0x71'00+'a'-'A';
		lc_code(k) = k+'a'-'A';
		lc_code(k+'a'-'A') = k+'a'-'A';
		uc_code(k) = k;
		uc_code(k+'a'-'A') = k;
		sf_code(k) = 999;
	}
	for (int k = int_base; k < del_code_base; k++)
		eqtb[k].int_ = 0;
	int_par(mag_code) = 1000;
	int_par(tolerance_code) = 10000;
	int_par(hang_after_code) = 1;
	int_par(max_dead_cycles_code) = 25;
	int_par(escape_char_code) = '\\';
	int_par(end_line_char_code) = '\r';
	for (int k = 0; k < 256; k++)
		del_code(k) = -1;
	del_code('.') = 0;
	for (int k = dimen_base; k <= eqtb_size; k++)
		eqtb[k].int_ = 0;
	hashused = frozen_control_sequence;
	cscount = 0;
	eq_type(frozen_dont_expand) = dont_expand;
	hash[frozen_dont_expand].rh = 502;
	fontptr = 0;
	fmemptr = 7;
	fontname[0] = 800;
	fontarea[0] = 338;
	hyphenchar[0] = 45;
	skewchar[0] = -1;
	bcharlabel[0] = 0;
	fontbchar[0] = 256;
	fontfalsebchar[0] = 256;
	fontbc[0] = 1;
	fontec[0] = 0;
	fontsize[0] = 0;
	fontdsize[0] = 0;
	charbase[0] = 0;
	widthbase[0] = 0;
	heightbase[0] = 0;
	depthbase[0] = 0;
	italicbase[0] = 0;
	ligkernbase[0] = 0;
	kernbase[0] = 0;
	extenbase[0] = 0;
	fontglue[0] = 0;
	fontparams[0] = 7;
	parambase[0] = -1;
	for (int k = 0; k < 7; k++)
		fontinfo[k].int_ = 0;
	for (int k = -trieopsize; k <= trieopsize; k++)
		trieophash[k] = 0;
	for (int k = 0; k < 256; k++)
		trieused[k] = 0;
	trieopptr = 0;
	trienotready = true;
	triel[0] = 0;
	triec[0] = 0;
	trieptr = 0;
	hash[frozen_control_sequence].rh = 1189;
	formatident = 1256;
	hash[end_write].rh = 1295;
	eq_level(end_write) = 1;
	eq_type(end_write) = outer_call;
	equiv(end_write) = 0;
}

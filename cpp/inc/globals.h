#ifndef GLOBALS_H
#define GLOBALS_H

#include <fstream>
#include <map>
#include <vector>

///////////////////////////////////////////////////////////////////////////////
// énumérations
///////////////////////////////////////////////////////////////////////////////
enum command_code
{
	number_code = 0, // //command code for \number
	roman_numeral_code = 1, //command code for \romannumeral
	string_code = 2, //command code for \string
	meaning_code = 3, //command code for \meaning
	font_name_code = 4, //command code for \fontname
	job_name_code = 5 //command code for \jobname
};

enum if_codes
{
	if_code = 1, //code for \if... being evaluated
	fi_code = 2, //code for \fi
	else_code = 3, //code for \else
	or_code = 4, //code for \or
};

enum selector
{
	no_print = 16, //!< \a selector setting that makes data disappear
	term_only = 17, //!<  printing is destined for the terminal only
	log_only = 18, //!<  printing is destined for the transcript file only
	term_and_log = 19 //!<  normal \a selector setting
//	pseudo = 20 //!<  special \a selector setting for \a show_context
//	new_string = 21 //!<  printing is deflected to the string pool
};

enum interactions
{
	batch_mode = 0, //!< omits all stops and omits terminal output
	nonstop_mode = 1, //!< omits all stops
	scroll_mode = 2, //!< omits error stops
	error_stop_mode = 3 //!< stops at every opportunity to interact
};

enum
{
	width_offset = 1, //!< position of \a width field in a box node
	depth_offset = 2, //!< position of \a depth field in a box node
	height_offset = 3, //!< position of \a height field in a box node
//	list_offset = 5, //!< position of \a list_ptr field in a box node
//	glue_offset = 6 //!< position of \a glue_set in a box node
};

enum
{
	normal = 0, //!< the most common case when several cases are named
	stretching = 1, //!< glue setting applies to the stretch components
	shrinking = 2 //!< glue setting applies to the shrink components
};

enum
{
	// math
	before = 0, //!< \a subtype for math node that introduces a formula
	after = 1, //!< \a subtype for math node that winds up a formula
	// kern
	explicit_ = 1, //!< \a subtype of kern nodes from \\kern and \\/
	acc_kern = 2, //!< \a subtype of kern nodes from accents
	// op_noad
	limits = 1, //!< \a subtype of \a op_noad whose scripts are to be above, below
	no_limits = 2, //!< \a subtype of \a op_noad whose scripts are to be normal
	// style
	display_style = 0, //!< \a subtype for \\displaystyle
	text_style = 2, //!< \a subtype for \\textstyle
	script_style = 4, //!< \a subtype for \\scriptstyle
	script_script_style = 6, //!< \a subtype for \\scriptscriptstyle
	// glue
	cond_math_glue = 98, //!< special \a subtype to suppress glue in the next node
	mu_glue = 99, //!< \a subtype for math glue
	// leaders
	a_leaders = 100, //!< \a subtype for aligned leaders
	c_leaders = 101, //!< \a subtype for centered leaders
	x_leaders = 102, //!< \a subtype for expanded leaders
	// whatsits
	open_node = 0, //!< \a subtype in whatsits that represent files to \\openout
	write_node = 1, //!< \a subtype in whatsits that represent things to \\write
	close_node = 2, //!< \a subtype in whatsits that represent streams to \\closeout
	special_node = 3, //!< \a subtype in whatsits that represent \\special things
	language_node = 4, //!< \a subtype in whatsits that change the current language
	immediate_code = 4, //!< command modifier for \\immediate
	set_language_code = 5, //!< command modifier for \\setlanguage
};

enum
{
	fil = 1, //!< first-order infinity
	fill = 2, //!< second-order infinity
	filll = 3 //!< third-order infinity
};

enum
{
	escape = 0, //!< escape delimiter (called \\ in The \\TeX book)
	relax = 0, //!< do nothing ( \\relax )
	left_brace = 1, //!< beginning of a group ( { )
	right_brace = 2, //!< ending of a group ( } )
	math_shift = 3, //!< mathematics shift character ( $ )
	tab_mark = 4, //!< alignment delimiter ( &, \\span )
	car_ret = 5, //!< end of line ( \a carriage_return, \\cr, \\crcr )
	out_param = 5, //!< output a macro parameter
	mac_param = 6, //!< macro parameter symbol ( # )
	sup_mark = 7, //!< superscript ( ^ )
	sub_mark = 8, //!< subscript ( _ )
	ignore = 9, //!< characters to ignore
	endv = 9, //!< end of \f$v_j\f$ list in alignment template
	spacer = 10, //!< characters equivalent to blank space
	letter = 11, //!< characters regarded as letters ( A..Z, a..z )
	other_char = 12, //!< none of the special character types
	active_char = 13, //!< characters that invoke macros ( ~ )
	par_end = 13, //!< end of paragraph ( \\par )
	match = 13, //!< match a macro parameter
	comment = 14, //!< characters that introduce comments ( % )
	end_match = 14, //!< end of parameters to macro
	stop = 14, //!< end of job ( \\end, \\dump )
	invalid_char = 15, //!< characters that shouldn't appear
	delim_num = 15, //!< specify delimiter numerically ( \\delimiter )
	max_char_code = 15, //!< largest catcode for individual characters
	char_num = 16, //!< character specified numerically ( \\char )
	math_char_num = 17, //!< explicit math code ( \\mathchar )
	mark = 18, //!< mark definition ( \\mark )
	xray = 19, //!< peek inside of \\TeX\\ ( \\show, \\showbox, etc. )
	make_box = 20, //!< make a box ( \\box, \\copy, \\hbox, etc. )
	hmove = 21, //!< horizontal motion ( \\moveleft, \\moveright )
	vmove = 22, //!< vertical motion ( \\raise, \\lower )
	un_hbox = 23, //!< unglue a box ( \\unhbox, \\unhcopy )
	un_vbox = 24, //!< unglue a box ( \\unvbox, \\unvcopy )
	remove_item = 25, //!< nullify last item ( \\unpenalty,
	hskip = 26, //!< horizontal glue ( \\hskip, \\hfil, etc. )
	vskip = 27, //!< vertical glue ( \\vskip, \\vfil, etc. )
	mskip = 28, //!< math glue ( \\mskip )
	kern = 29, //!< fixed space ( \\kern)
	mkern = 30, //!< math kern ( \\mkern )
	leader_ship = 31, //!< use a box ( \\shipout, \\leaders, etc. )
	halign = 32, //!< horizontal table alignment ( \\halign )
	valign = 33, //!< vertical table alignment ( \\valign )
	no_align = 34, //!< temporary escape from alignment ( \\noalign )
	vrule = 35, //!< vertical rule ( \\vrule )
	hrule = 36, //!< horizontal rule ( \\hrule )
	insert = 37, //!< vlist inserted in box ( \\insert )
	vadjust = 38, //!< vlist inserted in enclosing paragraph ( \\vadjust )
	ignore_spaces = 39, //!< gobble \a spacer tokens ( \\ignorespaces )
	after_assignment = 40, //!< save till assignment is done ( \\afterassignment )
	after_group = 41, //!< save till group is done ( \\aftergroup )
	break_penalty = 42, //!< additional badness ( \\penalty )
	start_par = 43, //!< begin paragraph ( \\indent, \\noindent )
	ital_corr = 44, //!< italic correction ( \\/ )
	accent = 45, //!< attach accent in text ( \\accent )
	math_accent = 46, //!< attach accent in math ( \\mathaccent )
	discretionary = 47, //!< discretionary texts ( \\-, \\discretionary )
	eq_no = 48, //!< equation number ( \\eqno, \\leqno )
	left_right = 49, //!< variable delimiter ( \\left, \\right )
	math_comp = 50, //!< component of formula ( \\mathbin, etc. )
	limit_switch = 51, //!< diddle limit conventions ( \\displaylimits, etc. )
	above = 52, //!< generalized fraction ( \\above, \\atop, etc. )
	math_style = 53, //!< style specification ( \\displaystyle, etc. )
	math_choice = 54, //!< choice specification ( \\mathchoice )
	non_script = 55, //!< conditional math glue ( \\nonscript )
	vcenter = 56, //!< vertically center a vbox ( \\vcenter )
	case_shift = 57, //!< force specific case ( \\lowercase, \\uppercase~)
	message = 58, //!< send to user ( \\message, \\errmessage )
	extension = 59, //!< extensions to \\TeX\\ ( \\write, \\special, etc. )
	in_stream = 60, //!< files for reading ( \\openin, \\closein )
	begin_group = 61, //!< begin local grouping ( \\begingroup )
	end_group = 62, //!< end local grouping ( \\endgroup )
	omit = 63, //!< omit alignment template ( \\omit )
	ex_space = 64, //!< explicit space ( \\\\  )
	no_boundary = 65, //!< suppress boundary ligatures ( \\noboundary )
	radical = 66, //!< square root and similar signs ( \\radical )
	end_cs_name = 67, //!< end control sequence ( \\endcsname )
	min_internal = 68, //!< the smallest code that can follow \\the
	char_given = 68, //!< character code defined by \\chardef
	math_given = 69, //!< math code defined by \\mathchardef
	last_item = 70, //!< most recent item ( \\lastpenalty,
	max_non_prefixed_command = 70, //!< largest command code that can't be \\global
	toks_register = 71, //!< token list register ( \\toks )
	assign_toks = 72, //!< special token list ( \\output, \\everypar, etc. )
	assign_int = 73, //!< user-defined integer ( \\tolerance, \\day, etc. )
	assign_dimen = 74, //!< user-defined length ( \\hsize, etc. )
	assign_glue = 75, //!< user-defined glue ( \\baselineskip, etc. )
	assign_mu_glue = 76, //!< user-defined muglue ( \\thinmuskip, etc. )
	assign_font_dimen = 77, //!< user-defined font dimension ( \\fontdimen )
	assign_font_int = 78, //!< user-defined font integer ( \\hyphenchar,
	set_aux = 79, //!< specify state info ( \\spacefactor, \\prevdepth )
	set_prev_graf = 80, //!< specify state info ( \\prevgraf )
	set_page_dimen = 81, //!< specify state info ( \\pagegoal, etc. )
	set_page_int = 82, //!< specify state info ( \\deadcycles,
	set_box_dimen = 83, //!< change dimension of box ( \\wd, \\ht, \\dp )
	set_shape = 84, //!< specify fancy paragraph shape ( \\parshape )
	def_code = 85, //!< define a character code ( \\catcode, etc. )
	def_family = 86, //!< declare math fonts ( \\textfont, etc. )
	set_font = 87, //!< set current font ( font identifiers )
	def_font = 88, //!< define a font file ( \\font )
	register_ = 89, //!< internal register ( \\count, \\dimen, etc. )
	max_internal = 89, //!< the largest code that can follow \\the
	advance = 90, //!< advance a register or parameter ( \\advance )
	multiply = 91, //!< multiply a register or parameter ( \\multiply )
	divide = 92, //!< divide a register or parameter ( \\divide )
	prefix = 93, //!< qualify a definition ( \\global, \\long, \\outer )
	let = 94, //!< assign a command code ( \\let, \\futurelet )
	shorthand_def = 95, //!< code definition ( \\chardef, \\countdef, etc. )
	read_to_cs = 96, //!< read into a control sequence ( \\read )
	def = 97, //!< macro definition ( \\def, \\gdef, \\xdef, \\edef )
	set_box = 98, //!< set a box ( \\setbox )
	hyph_data = 99, //!< hyphenation data ( \\hyphenation, \\patterns )
	set_interaction = 100, //!< define level of interaction ( \\batchmode, etc. )
	max_command = 100, //!< the largest command code seen at \a big_switch
		undefined_cs = 101, //!< =max_command+1 //!< initial state of most \a eq_type fields
		expand_after = 102, //!<  max_command+2 //!< special expansion ( \\expandafter )
		no_expand = 103, //!< max_command+3 //!< special nonexpansion ( \\noexpand )
		input = 104, //!< max_command+4 //!< input a source file ( \\input, \\endinput )
		if_test = 105, //!< max_command+5 //!< conditional text ( \\if, \\ifcase, etc. )
		fi_or_else = 106, //!< max_command+6 //!< delimiters for conditionals ( \\else, etc. )
		cs_name = 107, //!< max_command+7 //!< make a control sequence from tokens ( \\csname )
		convert = 108, //!<  max_command+8 //!< convert to text ( \\number, \\string, etc. )
		the = 109, //!<  max_command+9 //!< expand an internal quantity ( \\the )
		top_bot_mark = 110, //!< max_command+10 //!< inserted mark ( \\topmark, etc. )
		call = 111, //!< max_command+11 //!< non-long, non-outer control sequence
		long_call = 112, //!< max_command+12 //!< long, non-outer control sequence
		outer_call = 113, //!< max_command+13 //!< non-long, outer control sequence
		long_outer_call = 114, //!< max_command+14 //!< long, outer control sequence
		end_template = 115, //!< max_command+15 //!< end of an alignment template
		dont_expand = 116, //!< max_command+16 //!< the following token was marked by \\noexpand
		glue_ref = 117, //!< max_command+17 //!< the equivalent points to a glue specification
		shape_ref = 118, //!< max_command+18 //!< the equivalent points to a parshape specification
		box_ref = 119, //!< max_command+19 //!< the equivalent points to a box node, or is \a null
		data = 120 //!< max_command+20 //!< the equivalent is simply a halfword number
};

enum modes
{
	vmode = 1, //!< vertical mode
	hmode = vmode+max_command+1, //!< horizontal mode
	mmode = hmode+max_command+1 //!< math mode
};

enum groups
{
	bottom_level = 0, //!< group code for the outside world
	simple_group = 1, //!< group code for local structure only
	hbox_group = 2, //!< code for `\\hbox\\grp'
	adjusted_hbox_group = 3, //!< code for `\\hbox\\grp' in vertical mode
	vbox_group = 4, //!< code for `\\vbox\\grp'
	vtop_group = 5, //!< code for `\\vtop\\grp'
	align_group = 6, //!< code for `\\halign\\grp', `\\valign\\grp'
	no_align_group = 7, //!< code for `\\noalign\\grp'
	output_group = 8, //!< code for output routine
	math_group = 9, //!< code for, e.g., `^\\grp'
	disc_group = 10, //!< code for `\\discretionary\\grp\\grp\\grp'
	insert_group = 11, //!< code for `\\insert\\grp', `\\vadjust\\grp'
	vcenter_group = 12, //!< code for `\\vcenter\\grp'
	math_choice_group = 13, //!< code for `\\mathchoice\\grp\\grp\\grp\\grp'
	semi_simple_group = 14, //!< code for `\\begingroup...\\endgroup'
	math_shift_group = 15, //!<  //!< code for `$...$'
	math_left_group = 16 //!< code for `\\left...\\right'
};

enum levels
{
	level_zero = 0, //!< level for undefined quantities
	level_one = level_zero+1 //!< outermost level for defined quantities
};

enum special_token
{
	out_param_token = out_param<<8, //!< \f$2^8\cdot\textrm{out_param}\f$
	math_shift_token = math_shift<<8, //!< \f$2^8\cdot\textrm{math_shift}\f$
	tab_token = tab_mark<<8, //!< \f$2^8\cdot\textrm{tab_mark}\f$
	space_token = (spacer<<8)+' ', //!< \f$2^8\cdot\textrm{spacer}+\textrm{" "}\f$
	left_brace_token = left_brace<<8, //!< \f$2^8\cdot\textrm{left_brace}\f$
	right_brace_token = right_brace<<8, //!< \f$2^8\cdot\textrm{right_brace}\f$
	other_token = other_char<<8, //!< \f$2^8\cdot\textrm{other_char}\f$
		zero_token = other_token+'0', //!< zero, the smallest digit
		octal_token = other_token+'\'', //!< apostrophe, indicates an octal constant
		hex_token = other_token+'\"', //!< double quote, indicates a hex constant
		alpha_token = other_token+'`', //!< reverse apostrophe, precedes alpha constants
		point_token = other_token+'.', //!< decimal point
		continental_point_token = other_token+',', //!< decimal point, Eurostyle
		other_A_token = other_token+'A', //!< special hex digit of type \a other_char
	right_brace_limit = (right_brace+1)<<8, //!< \f$2^8\cdot(\textrm{right_brace}+1)\f$
	left_brace_limit = (left_brace+1)<<8,  //!< \f$2^8\cdot(\textrm{left_brace}+1)\f$
	match_token = match<<8, //!< \f$2^8\cdot\textrm{match}\f$
	end_match_token = end_match<<8, //!< \f$2^8\cdot\textrm{end_match}\f$
	letter_token = letter<<8, //!< \f$2^8\cdot\textrm{letter}\f$
		A_token = letter_token+'A' //!< the smallest special hex digit
};

enum state_code
{
	token_list = 0, //!< \a state code when scanning a token list
	mid_line = 1, //!< \a state code when scanning a line of characters
	skip_blanks = 2+max_char_code, //!< \a state code when ignoring blanks
	new_line = 3+2*max_char_code //!< \a state code at start of line
};


enum token_type
{
	parameter = 0, //!< \a token_type code for parameter
	u_template = 1, //!< \a token_type code for \f$<u_j>\f$ template
	v_template = 2, //!< \a token_type code for \f$<v_j>\f$ template
	backed_up = 3, //!< \a token_type code for text to be reread
	inserted = 4, //!< \a token_type code for inserted texts
	macro = 5, //!< \a token_type code for defined control sequences
	output_text = 6, //!< \a token_type code for output routines
	every_par_text = 7, //!< \a token_type code for \\everypar
	every_math_text = 8, //!< \a token_type code for \\everymath
	every_display_text = 9, //!< \a token_type code for \\everydisplay
	every_hbox_text = 10, //!< \a token_type code for \\everyhbox
	every_vbox_text = 11, //!< \a token_type code for \\everyvbox
	every_job_text = 12, //!< \a token_type code for \\everyjob
	every_cr_text = 13, //!< \a token_type code for \\everycr
	mark_text = 14, //!< \a token_type code for \\topmark, etc.
	write_text = 15 //!< \a token_type code for \\write
};

enum 
{
	int_val = 0, //!< integer values
	dimen_val = 1, //!< dimension values
	glue_val = 2, //!< glue specifications
	mu_val = 3, //!< math glue specifications
	ident_val = 4, //!< font identifier
	tok_val = 5 //!< token lists
};

enum
{
	if_char_code = 0, //!<  `\\if' 
	if_cat_code = 1, //!<  `\\ifcat' 
	if_int_code = 2, //!<  `\\ifnum' 
	if_dim_code = 3, //!<  `\\ifdim' 
	if_odd_code = 4, //!<  `\\ifodd' 
	if_vmode_code = 5, //!<  `\\ifvmode' 
	if_hmode_code = 6, //!<  `\\ifhmode' 
	if_mmode_code = 7, //!<  `\\ifmmode' 
	if_inner_code = 8, //!<  `\\ifinner' 
	if_void_code = 9, //!<  `\\ifvoid' 
	if_hbox_code = 10, //!<  `\\ifhbox' 
	if_vbox_code = 11, //!<  `\\ifvbox' 
	ifx_code = 12, //!<  `\\ifx' 
	if_eof_code = 13, //!<  `\\ifeof' 
	if_true_code = 14, //!<  `\\iftrue' 
	if_false_code = 15, //!<  `\\iffalse' 
	if_case_code = 16 //!<  `\\ifcase' 
};

enum
{
	no_tag = 0, //!< vanilla character
	lig_tag = 1, //!< character has a ligature/kerning program
	list_tag = 2, //!< character has a successor in a charlist
	ext_tag = 3 //!< character is extensible
};

enum
{
	slant_code = 1,
	space_code = 2,
	space_stretch_code = 3,
	space_shrink_code = 4,
	x_height_code = 5,
	quad_code = 6,
	extra_space_code = 7
};

enum box_dim
{
	exactly = 0, //!< a box dimension is pre-specified
	additional = 1 //!< a box dimension is increased from the natural one
};

enum math_type
{
	math_char = 1, //!< \a math_type when the attribute is simple
	sub_box = 2, //!< \a math_type when the attribute is a box
	sub_mlist = 3, //!< \a math_type when the attribute is a formula
	math_text_char=4 //!< \a math_type when italic correction is dubious
};

enum
{
	text_size = 0, //!< size code for the largest size in a family
	script_size = 16, //!< size code for the medium size in a family
	script_script_size = 32 //!< size code for the smallest size in a family
};

enum
{
	inserting = 0, //!< an insertion class that has not yet overflowed
	inserts_only = 1,
	box_there = 2 //!< \a page_contents when a box or rule has been contributed
};

enum
{
	empty_flag = (1<<16)-1, //!< the \a link of an empty variable-size node
	cs_token_flag = (1<<12)-1, //!< amount added to the \a eqtb location in a token that stands for a control sequence; is a multiple of 256, less 1
	no_expand_flag = 257, //!< this characterizes a special variant of \a relax
	stop_flag = 128, //!< value indicating `STOP' in a lig/kern program
	kern_flag = 128, //!< op code for a kern step
	null_flag = -(1<<30), //!< \f$-2^{30}\f$, signifies a missing item
	box_flag = 1<<30, //!< context code for `\\setbox0'
	ship_out_flag = box_flag+512, //!< context code for `\\shipout'
	leader_flag = box_flag+513 //!< context code for `\\leaders'
};

enum chr_code
{
	box_code = 0, //!< \a chr_code for `\\box'
	copy_code = 1, //!< \a chr_code for `\\copy'
	last_box_code = 2, //!< \a chr_code for `\\lastbox'
	vsplit_code = 3, //!< \a chr_code for `\\vsplit'
	vtop_code = 4 //!< \a chr_code for `\\vtop'
};

enum
{
	above_code = 0, //!<  `\\above' 
	over_code = 1, //!<  `\\over' 
	atop_code = 2, //!<  `\\atop' 
	delimited_code = 3 //!<  `\\abovewithdelims', etc.
};

enum shorthand_def
{
	char_def_code = 0, //!< \a shorthand_def for \\chardef
	math_char_def_code = 1, //!< \a shorthand_def for \\mathchardef
	count_def_code = 2, //!< \a shorthand_def for \\countdef
	dimen_def_code = 3, //!< \a shorthand_def for \\dimendef
	skip_def_code = 4, //!< \a shorthand_def for \\skipdef
	mu_skip_def_code = 5, //!< \a shorthand_def for \\muskipdef
	toks_def_code = 6 //!< \a shorthand_def for \\toksdef
};

enum
{
	show_code = 0, //!<  \\show 
	show_box_code = 1, //!<  \\showbox 
	show_the_code = 2, //!<  \\showthe 
	show_lists = 3 //!<  \\showlists
};

enum
{
	fil_code = 0, //!< identifies \\hfil and \\vfil
	fill_code = 1, //!< identifies \\hfill and \\vfill
	ss_code = 2, //!< identifies \\hss and \\vss
	fil_neg_code = 3, //!< identifies \\hfilneg and \\vfilneg
	skip_code = 4, //!< identifies \\hskip and \\vskip
	mskip_code = 5 //!< identifies \\mskip
};

enum
{
	top_mark_code = 0, //!< the mark in effect at the previous page break
	first_mark_code = 1, //!< the first mark between \a top_mark and \a bot_mark
	bot_mark_code = 2, //!< the mark in effect at the current page break
	split_first_mark_code = 3, //!< the first mark found by \\vsplit
	split_bot_mark_code = 4 //!< the last mark found by \\vsplit
};


enum
{
	pretolerance_code = 0, //!< badness tolerance before hyphenation
	tolerance_code = 1, //!< badness tolerance after hyphenation
	line_penalty_code = 2, //!< added to the badness of every line
	hyphen_penalty_code = 3, //!< penalty for break after discretionary hyphen
	ex_hyphen_penalty_code = 4, //!< penalty for break after explicit hyphen
	club_penalty_code = 5, //!< penalty for creating a club line
	widow_penalty_code = 6, //!< penalty for creating a widow line
	display_widow_penalty_code = 7, //!< ditto, just before a display
	broken_penalty_code = 8, //!< penalty for breaking a page at a broken line
	bin_op_penalty_code = 9, //!< penalty for breaking after a binary operation
	rel_penalty_code = 10, //!< penalty for breaking after a relation
	pre_display_penalty_code = 11,
	post_display_penalty_code = 12,
	inter_line_penalty_code = 13, //!< additional penalty between lines
	double_hyphen_demerits_code = 14, //!< demerits for double hyphen break
	final_hyphen_demerits_code = 15, //!< demerits for final hyphen break
	adj_demerits_code = 16, //!< demerits for adjacent incompatible lines
	mag_code = 17, //!< magnification ratio
	delimiter_factor_code = 18, //!< ratio for variable-size delimiters
	looseness_code = 19, //!< change in number of lines for a paragraph
	time_code = 20, //!< current time of day
	day_code = 21, //!< current day of the month
	month_code = 22, //!< current month of the year
	year_code = 23, //!< current year of our Lord
	show_box_breadth_code = 24, //!< nodes per level in |show_box|
	show_box_depth_code = 25, //!< maximum level in |show_box|
	hbadness_code = 26, //!< hboxes exceeding this badness will be shown by |hpack|
	vbadness_code = 27, //!< vboxes exceeding this badness will be shown by |vpack|
	pausing_code = 28, //!< pause after each line is read from a file
	tracing_online_code = 29, //!< show diagnostic output on terminal
	tracing_macros_code = 30, //!< show macros as they are being expanded
	tracing_stats_code = 31, //!< show memory usage if \TeX\ knows it
	tracing_paragraphs_code = 32, //!< show line-break calculations
	tracing_pages_code = 33, //!< show page-break calculations
	tracing_output_code = 34, //!< show boxes when they are shipped out
	tracing_lost_chars_code = 35, //!< show characters that aren't in the font
	tracing_commands_code = 36, //!< show command codes at |big_switch|
	tracing_restores_code = 37, //!< show equivalents when they are restored
	uc_hyph_code = 38, //!< hyphenate words beginning with a capital letter
	output_penalty_code = 39, //!< penalty found at current page break
	max_dead_cycles_code = 40, //!< bound on consecutive dead cycles of output
	hang_after_code = 41, //!< hanging indentation changes after this many lines
	floating_penalty_code = 42, //!< penalty for insertions heldover after a split
	global_defs_code = 43, //!< override \global specifications
	cur_fam_code = 44, //!< current family
	escape_char_code = 45, //!< escape character for token output
	default_hyphen_char_code = 46, //!< value of \hyphenchar when a font is loaded
	default_skew_char_code = 47, //!< value of \skewchar when a font is loaded
	end_line_char_code = 48, //!< character placed at the right end of the buffer
	new_line_char_code = 49, //!< character that prints as |print_ln|
	language_code = 50, //!< current hyphenation table
	left_hyphen_min_code = 51, //!< minimum left hyphenation fragment size
	right_hyphen_min_code = 52, //!< minimum right hyphenation fragment size
	holding_inserts_code = 53, //!< do not remove insertion nodes from \box255
	error_context_lines_code = 54 //!< maximum intermediate line pairs shown
};

enum
{
	line_skip_code = 0, //!< interline glue if |baseline_skip| is infeasible
	baseline_skip_code = 1, //!< desired glue between baselines
	par_skip_code = 2, //!< extra glue just above a paragraph
	above_display_skip_code = 3, //!< extra glue just above displayed math
	below_display_skip_code = 4, //!< extra glue just below displayed math
	above_display_short_skip_code = 5,
	below_display_short_skip_code = 6,
	left_skip_code = 7, //!< glue at left of justified lines
	right_skip_code = 8, //!< glue at right of justified lines
	top_skip_code = 9, //!< glue at top of main pages
	split_top_skip_code = 10, //!< glue at top of split pages
	tab_skip_code = 11, //!< glue between aligned entries*/
	space_skip_code = 12, //!< glue between words (if not |zero_glue|)
	xspace_skip_code = 13, //!< glue after sentences (if not |zero_glue|)
	par_fill_skip_code = 14, //!< glue on last line of paragraph
	thin_mu_skip_code = 15, //!< thin space in math formula
	med_mu_skip_code = 16, //!< medium space in math formula
	thick_mu_skip_code = 17 //!< thick space in math formula
};

enum
{
	par_indent_code = 0, //!< indentation of paragraphs
	math_surround_code = 1, //!< space around math in text
	line_skip_limit_code = 2, //!< threshold for |line_skip| instead of |baseline_skip|
	hsize_code = 3, //!< line width in horizontal mode
	vsize_code = 4, //!< page height in vertical mode
	max_depth_code = 5, //!< maximum depth of boxes on main pages
	split_max_depth_code = 6, //!< maximum depth of boxes on split pages
	box_max_depth_code = 7, //!< maximum depth of explicit vboxes
	hfuzz_code = 8, //!< tolerance for overfull hbox messages
	vfuzz_code = 9, //!< tolerance for overfull vbox messages
	delimiter_shortfall_code = 10, //!< maximum amount uncovered by variable delimiters
	null_delimiter_space_code = 11, //!< blank space in null delimiters
	script_space_code = 12, //!< extra space after subscript or superscript
	pre_display_size_code = 13, //!< length of text preceding a display
	display_width_code = 14, //!< length of line for displayed equation
	display_indent_code = 15, //!< indentation of line for displayed equation
	overfull_rule_code = 16, //!< width of rule that identifies overfull hboxes
	hang_indent_code = 17, //!< amount of hanging indentation
	h_offset_code = 18, //!< amount of horizontal offset when shipping pages out
	v_offset_code = 19, //!< amount of vertical offset when shipping pages out
	emergency_stretch_code = 20 //!< reduces badnesses on final pass of line-breaking
};

enum ligatures
{
	AB_C = 0, // symbole != ou LIG
	AB_CB = 1, //symbole =:| ou LIG/
	AB_cB = 5, //symbole =:|> ou LIG/>
	AB_AC = 2, //symbole |=: ou /LIG
	AB_aC = 6, //symbole |=:> ou /LIG>
	AB_ACB = 3, // symbole |=:| ou /LIG/
	AB_aCB = 7, //symbole |=:|> ou /LIG/>
	AB_acB = 11 //symbole |=:|>> ou /LIG/>>
};


///////////////////////////////////////////////////////////////////////////////
// constantes
///////////////////////////////////////////////////////////////////////////////
constexpr int memmax = 30000;
constexpr int memmin = 0;
constexpr int bufsize = 500;
constexpr int errorline = 72;
constexpr int halferrorline = 42;
constexpr int maxprintline = 79;
constexpr int stacksize = 200;
constexpr int maxinopen = 6;
constexpr int fontmax = 75;
constexpr int fontmemsize = 20000;
constexpr int paramsize = 60;
constexpr int nestsize = 40;
constexpr int maxstrings = 3000;
constexpr int poolsize = 32000;
constexpr int savesize = 600;
constexpr int triesize = 8000;
constexpr int trieopsize = 500;
constexpr int CHECKSUM = 117275187;
constexpr int mem_bot = 0; //!<  smallest index in the \a mem array dumped by INITEX
constexpr int mem_top = 30000; //!<  largest index in the \a mem array dumped by INITEX
constexpr int font_base = 0; //!<  smallest internal font number; must not be less
constexpr int hash_size = 2100; //!<  maximum number of control sequences; it should be at most about |(mem_max-mem_min)/10|}
constexpr int hash_prime = 1777; //!<  a prime number equal to about 85% of \a hash_size
constexpr char banner[] ="This is TeX, Version 3.14159265"; //!<  printed when \\TeX starts
constexpr int hi_mem_stat_usage = 14; //!< the number of one-word nodes always present
constexpr int glue_spec_size = 4; //!< number of words to allocate for a glue specification
constexpr int lo_mem_stat_max = mem_bot+5*glue_spec_size-1; //!< largest statically
constexpr int hi_mem_stat_min = mem_top-13; //!< smallest statically allocated word in
constexpr int int_pars = 55; //!< total number of integer parameters
constexpr int glue_pars = 18; //!< total number of glue parameters
constexpr int dimen_pars = 21; //!< total number of dimension parameters
constexpr int unity = 1<<16; //!< \f$2^{16}\f$, represents 1.00000
constexpr int two = 1<<17; //!< \f$2^{17}\f$, represents 2.00000
constexpr int inf_bad = 10000; //!< infinitely bad value
constexpr int deplorable = 100000; //!< more than \a inf_bad, but less than \a awful_bad
constexpr int awful_bad = (1<<30)-1; //!< more than a billion demerits
constexpr int inf_penalty = inf_bad; //!< ``infinite'' penalty value
constexpr int eject_penalty = -inf_penalty; //!< ``negatively infinite'' penalty value
constexpr int ignore_depth = -65536000; //!< \a prev_depth value that is ignored
constexpr int null_font = font_base;
constexpr int var_code = 28672;  //!< math code meaning ``use the current family''
constexpr int input_line_no_code = glue_val+1; //!< code for \\inputlineno
constexpr int badness_code = glue_val+2; //!< code for \\badness
constexpr int max_dimen = (1<<30)-1; //!< \f$2^{30}-1\f$
constexpr int infinity = (1l<<31)-1;//!< the largest positive value that \\TeX\\ knows
constexpr int non_char = 256; //!< a \a halfword code that can't match a real character
constexpr int non_address = 0; //!< a spurious \a bchar_label
constexpr int format_default_length = 20; //!< length of the \a TEX_format_default string
constexpr int format_area_length = 11; //!< length of its area part
constexpr int id_byte = 2; //!< identifies the kind of DVI files described here
constexpr int default_code = 1<<30; //!< denotes \a default_rule_thickness
constexpr int cramped = 1; //!< add this to an uncramped style if you want to cramp it
constexpr int span_code = 256; //!< distinct from any character
constexpr int cr_code = 257; //!< distinct from \a span_code and from any character
constexpr int cr_cr_code = cr_code+1; //!< this distinguishes \\crcr from \\cr
constexpr int delta_node = 2; //!< \a type field in a delta node
constexpr int split_up = 1; //!< an overflowed insertion class

///////////////////////////////////////////////////////////////////////////////
// types
///////////////////////////////////////////////////////////////////////////////
typedef std::uint8_t glueord; //0..3
typedef std::uint8_t groupcode; // 0..16
typedef std::uint8_t internalfontnumber; //0..fontmax
typedef std::uint8_t ASCIIcode; // 0..255
typedef std::uint8_t packedASCIIcode; // 0..255
typedef std::uint8_t eightbits; // 0..255
typedef std::uint8_t smallnumber; // 0..63
typedef std::uint8_t quarterword; // 0..255
typedef std::uint16_t halfword; // 0..0xFF'FF
typedef int poolpointer; // 0..poolsize
typedef int strnumber; // 0..maxstrings
typedef int scaled;
typedef int fontindex; // 0..fontmemsize
typedef int triepointer; // 0..triesize
typedef std::fstream alphafile; // file of char
typedef std::fstream bytefile; // file of eightbits
typedef std::fstream wordfile; // file of memoryword
typedef float glueratio;

class twohalves
{
	public:
		std::uint16_t rh;
		union
		{
			std::uint16_t lh;
			struct
			{
				std::uint8_t b0;
				std::uint8_t b1;
			};
		};
};

class fourquarters
{
	public:
		std::uint8_t b0;
		std::uint8_t b1;
		std::uint8_t b2;
		std::uint8_t b3;
};

typedef union
{
	std::int32_t int_;
	float gr;
	twohalves hh;
	fourquarters qqqq;
} memoryword;

class GlueSpec;

class Font
{
	public:
		static std::vector<memoryword> info; //!< the big collection of font data
		static fourquarters& infos(int);
		static quarterword skip_byte(int);
		static quarterword next_char(int);
		static quarterword op_byte(int);
		static quarterword rem_byte(int);
		int charbase; //!< base addresses for |char_info|
		int widthbase; //!< base addresses for widths
		int heightbase; //!< base addresses for heights
		int depthbase; //!< base addresses for depths
		int italicbase; //!< base addresses for italic corrections
		int ligkernbase; //!< base addresses for ligature/kerning programs
		int kernbase; //!< base addresses for kerns
		int extenbase; //!< base addresses for extensible recipes
		int parambase; //!< base addresses for font parameters
		std::string name; //!< name of the font
		std::string area; //!< area of the font
		fourquarters check; //!< check sum
		scaled size; //!< ``at'' size
		scaled dsize; //!< ``design'' size
		fontindex params; //!< how many font parameters are present
		eightbits bc; //!< beginning (smallest) character code
		eightbits ec; //!< ending (largest) character code
		GlueSpec *glue; //!< glue specification for interword space, |null| if not allocated
		bool used; //!< has a character from this font actually appeared in the output?
		int hyphenchar;//!< current \.{\\hyphenchar} values
		int skewchar; //!< current \.{\\skewchar} values
		fontindex bcharlabel; //!< start of |lig_kern| program for left boundary character, |non_address| if there is none
		int bchar; //!< right boundary character, |non_char| if there is none
		int falsebchar; //!< |font_bchar| if it doesn't exist in the font, otherwise |non_char|
		fourquarters char_info(smallnumber) const;
		int char_width(smallnumber) const;
		int char_height(smallnumber) const;
		int char_depth(smallnumber) const;
		int char_italic(smallnumber) const;
		int lig_kern_start(smallnumber) const; //!< beginning of lig/kern program
		int lig_kern_restart(int) const;
		int lig_kern_first(smallnumber) const;
		int char_kern(int) const;
		int& param(smallnumber) const;
		scaled heightplusdepth(quarterword) const;
		int& slant(void) const; //!< slant to the right, per unit distance upward
		int& extra_space(void) const; //!< additional space at end of sentence
		int& space(void) const; //!< normal space between words
		int& space_stretch(void) const; //!< stretch between words
		int& space_shrink(void) const; //!< shrink between words
		int& x_height(void) const; //!< one ex
		int& quad(void) const; //!< one em
		int char_tag(smallnumber);
		bool char_exists(smallnumber);
};

class LinkedNode;

class liststaterecord
{
	public:
		int modefield; // -203..203
		LinkedNode *headfield, *tailfield;
		int pgfield, mlfield;
		memoryword auxfield;
};

class instaterecord
{
	public:
		quarterword statefield, indexfield;
		halfword startfield;
		halfword locfield, limitfield;
		std::string namefield;
};

class Token
{
	public:
		eightbits cmd;
		halfword chr;
		halfword cs;
		halfword tok;
};

inline Token make_tok(Token t)
{
	t.tok = t.cs == 0 ? (t.cmd<<8)+t.chr : t.cs+cs_token_flag;
	return t;
}

inline Token make_tok(halfword tok)
{
	Token t;
	t.tok = tok;
	return t;
}

inline Token make_tok(eightbits cmd, halfword chr)
{
	Token t;
	t.cmd = cmd;
	t.chr = chr;
	return t;
}


class ArithException : public std::exception 
{
	public:
		const char * what () const throw () { return "arithmetic error"; }
};

///////////////////////////////////////////////////////////////////////////////
// variables globales
///////////////////////////////////////////////////////////////////////////////
inline liststaterecord curlist;
	inline auto &aux = curlist.auxfield; //!< auxiliary data about the current list
		inline int& prev_depth = aux.int_; //!< the name of \a aux in vertical mode
		inline halfword& space_factor = aux.hh.lh; //!< part of \a aux in horizontal mode
		inline halfword& clang = aux.hh.rh;  //!< the other part of \a aux in horizontal mode
	inline auto &head = curlist.headfield; //!< header node of current list
	inline auto &tail = curlist.tailfield; //!< final node on current list
	inline int& mode = curlist.modefield; //!< current mode
	inline int& prev_graf = curlist.pgfield; //!< number of paragraph lines accumulated
	inline int& mode_line = curlist.mlfield; //!< source file line number at beginning of list

inline std::map<ASCIIcode, char> xchr;
inline char interaction = error_stop_mode; // 0..3
inline std::vector<liststaterecord> nest(1);
inline groupcode curgroup = 0;
inline unsigned char baseptr; // 0..stacksize
inline char openparens = 0; // 0..maxinopen
inline halfword parloc;
inline halfword partoken;
inline bool outputactive = false;
inline halfword writeloc;

inline std::vector<instaterecord> inputstack(1);
inline instaterecord curinput;
	inline auto &start = curinput.startfield; //!< starting position in \a buffer
	inline auto &limit = curinput.limitfield; //!< end of current line in \a buffer
	inline auto &param_start = limit; //!< base of macro parameters in \a param_stack
	inline auto &loc = curinput.locfield; //!< location of first unread character in \a buffer
	inline auto &state = curinput.statefield; //!< current scanner state
	inline auto &index = curinput.indexfield; //!< reference for buffer information
	inline auto &token_type = index; //!< type of current token list
	inline auto &name = curinput.namefield; //!< name of the current file

///////////////////////////////////////////////////////////////////////////////
// fonctions inlines
///////////////////////////////////////////////////////////////////////////////
inline bool is_running(int d) { return d == null_flag; } //!< tests for a running dimension
inline bool terminal_input(const std::string &name) { return name == ""; } //!< are we reading from the terminal?

#endif

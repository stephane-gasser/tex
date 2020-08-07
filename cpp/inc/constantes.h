#ifndef CONSTANTES_H
#define CONSTANTES_H

#include "parametres.h"

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
	spotless = 0, //!< \a history value when nothing has been amiss yet
	warning_issued = 1, //!< \a history value when \a begin_diagnostic has been called
	error_message_issued = 2, //!< \a history value when \a error has been called
	fatal_error_stop = 3 //!< \a history value when termination was premature
};

enum
{
	if_node_size = 2, //!<  number of words in stack entry for conditionals
	box_node_size = 7, //!<  number of words to allocate for a box node
	rule_node_size = 4, //!<  number of words to allocate for a rule node
	ins_node_size = 5, //!<  number of words to allocate for an insertion
	small_node_size = 2, //!<  number of words to allocate for most node types
	movement_node_size = 3, //!<  number of words per entry in the down and right stacks
	style_node_size = 3, //!<  number of words in a style node
	align_stack_node_size = 5, //!<  number of \a mem words to save alignment states
	span_node_size = 2, //!<  number of \a mem words for a span node
	active_node_size = 3, //!<  number of words in active nodes
	passive_node_size = 2, //!<  number of words in passive nodes
	delta_node_size = 7, //!<  number of words in a delta node
	page_ins_node_size = 4, //!<  number of words for a page insertion node
	write_node_size = 2, //!< number of words in a write/whatsit node
	open_node_size = 3, //!< number of words in an open/whatsit node
	noad_size = 4, //!< number of words in a normal noad
	accent_noad_size = 5, //!< number of \a mem words in an accent noad
	radical_noad_size = 5, //!< number of \a mem words in a radical noad
	fraction_noad_size = 6, //!< number of \a mem words in a fraction noad
	glue_spec_size = 4 //!< number of words to allocate for a glue specification
};

enum
{
	width_offset = 1, //!< position of \a width field in a box node
	depth_offset = 2, //!< position of \a depth field in a box node
	height_offset = 3, //!< position of \a height field in a box node
	list_offset = 5, //!< position of \a list_ptr field in a box node
	glue_offset = 6 //!< position of \a glue_set in a box node
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
	// whatsits
	open_node = 0, //!< \a subtype in whatsits that represent files to \\openout
	write_node = 1, //!< \a subtype in whatsits that represent things to \\write
	close_node = 2, //!< \a subtype in whatsits that represent streams to \\closeout
	special_node = 3, //!< \a subtype in whatsits that represent \\special things
	language_node = 4, //!< \a subtype in whatsits that change the current language
	immediate_code = 4, //!< command modifier for \\immediate
	set_language_code = 5, //!< command modifier for \\setlanguage
	// leaders
	a_leaders = 100, //!< \a subtype for aligned leaders
	c_leaders = 101, //!< \a subtype for centered leaders
	x_leaders = 102, //!< \a subtype for expanded leaders
};

enum
{
	fil = 1, //!< first-order infinity
	fill = 2, //!< second-order infinity
	filll = 3 //!< third-order infinity
};

/*enum
{
	zero_glue = mem_bot, //!< specification for 0pt plus 0pt minus 0pt
	fil_glue = zero_glue+glue_spec_size, //!< 0pt plus 1fil minus 0pt
	fill_glue = fil_glue+glue_spec_size, //!< 0pt plus 1fill minus 0pt
	ss_glue = fill_glue+glue_spec_size, //!< 0pt plus 1fil minus 1fil
	fil_neg_glue = ss_glue+glue_spec_size //!< 0pt plus -1fil minus 0pt
};*/

inline std::vector<GlueSpec> glues(5);

inline auto	zero_glue = &glues[0]; //!< specification for 0pt plus 0pt minus 0pt
inline auto fil_glue = &glues[1]; //!< 0pt plus 1fil minus 0pt
inline auto fill_glue = &glues[2]; //!< 0pt plus 1fill minus 0pt
inline auto ss_glue = &glues[3]; //!< 0pt plus 1fil minus 1fil
inline auto fil_neg_glue = &glues[4]; //!< 0pt plus -1fil minus 0pt


constexpr int lo_mem_stat_max = mem_bot+5*glue_spec_size-1; //!< largest statically

enum
{
//	page_ins_head = mem_top, //!< list of insertion data for current page
//	contrib_head = mem_top-1, //!< vlist of items not yet on current page
//	page_head = mem_top-2, //!< vlist for current page
//	temp_head = mem_top-3, //!< head of a temporary list of some kind
//	hold_head = mem_top-4, //!< head of a temporary list of another kind
//	adjust_head = mem_top-5, //!< head of adjustment list returned by \a hpack
//	active = mem_top-7, //!< head of active list in \a line_break, needs two words
//	align_head = mem_top-8, //!< head of preamble list for alignments
//	end_span = mem_top-9, //!< tail of spanned-width lists
//	omit_template = mem_top-10, //!< a constant token list
//	null_list = mem_top-11, //!< permanently empty list
//	lig_trick = mem_top-12, //!< a ligature masquerading as a \a char_node
//	garbage = mem_top-12, //!< used for scrap information
//	backup_head = mem_top-13, //!< head of token list built by \a scan_keyword
	hi_mem_stat_min = mem_top-13 //!< smallest statically allocated word in
};

inline std::vector<AnyNode> heads;

inline PageInsNode *page_ins_head; //!< list of insertion data for current page
inline LinkedNode *contrib_head; //!< vlist of items not yet on current page
inline LinkedNode *page_head; //!< vlist for current page
inline TokenNode *temp_head; //!< head of a temporary list of some kind
inline LinkedNode *hold_head; //!< head of a temporary list of another kind
inline LinkedNode *adjust_head; //!< head of adjustment list returned by \a hpack
inline LinkedNode * const active = dynamic_cast<LinkedNode*>(&heads[7]); //!< head of active list in \a line_break, needs two words
inline LinkedNode * const align_head = dynamic_cast<LinkedNode*>(&heads[8]); //!< head of preamble list for alignments
inline SpanNode * const end_span = dynamic_cast<SpanNode*>(&heads[9]); //!< tail of spanned-width lists
inline TokenNode * omit_template; //!< a constant token list
inline LinkedNode *null_list; //!< permanently empty list
inline LinkedNode *lig_trick; //!< a ligature masquerading as a \a char_node
inline LinkedNode *garbage; //!< used for scrap information
inline LinkedNode *backup_head; //!< head of token list built by \a scan_keyword

constexpr int hi_mem_stat_usage = 14; //!< the number of one-word nodes always present

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

enum save_type
{
	restore_old_value = 0, //!< \a save_type when a value should be restored later
	restore_zero = 1, //!< \a save_type when an undefined entry should be restored
	insert_token = 2, //!< \a save_type when a token is being saved for later use
	level_boundary = 3 //!< \a save_type corresponding to beginning of group
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

enum memory
{
	active_base = 1, //!< beginning of region 1, for active character equivalents
	single_base = active_base+256, //!< equivalents of one-character control sequences
		null_cs = single_base+256, //!< equivalent of \\csname\\endcsname
	hash_base = null_cs+1, //!< beginning of region 2, for the hash table
		frozen_control_sequence = hash_base+hash_size, //!< for error recovery
		frozen_protection = frozen_control_sequence, //!< inaccessible but definable
		frozen_cr = frozen_control_sequence+1, //!< permanent `\\cr'
		frozen_end_group = frozen_control_sequence+2, //!< permanent `\\endgroup'
		frozen_right = frozen_control_sequence+3, //!< permanent `\\right'
		frozen_fi = frozen_control_sequence+4, //!< permanent `\\fi'
		frozen_end_template = frozen_control_sequence+5, //!< permanent `\\endtemplate'
		frozen_endv = frozen_control_sequence+6, //!< second permanent `\\endtemplate'
		frozen_relax = frozen_control_sequence+7, //!< permanent `\\relax'
		end_write = frozen_control_sequence+8, //!< permanent `\\endwrite'
		frozen_dont_expand = frozen_control_sequence+9,
		frozen_null_font = frozen_control_sequence+10,
	font_id_base = frozen_null_font-font_base,
		undefined_control_sequence = frozen_null_font+257, //!< dummy location
	glue_base = undefined_control_sequence+1, //!< beginning of region 3
	skip_base = glue_base+glue_pars, //!< table of 256 ``skip'' registers
	mu_skip_base = skip_base+256, //!< table of 256 ``muskip'' registers
	local_base = mu_skip_base+256, //!< beginning of region 4
		par_shape_loc = local_base, //!< specifies paragraph shape
		output_routine_loc = local_base+1, //!< points to token list for \\output
		every_par_loc = local_base+2, //!< points to token list for \\everypar
		every_math_loc = local_base+3, //!< points to token list for \\everymath
		every_display_loc = local_base+4, //!< points to token list for \\everydisplay
		every_hbox_loc = local_base+5, //!< points to token list for \\everyhbox
		every_vbox_loc = local_base+6, //!< points to token list for \\everyvbox
		every_job_loc = local_base+7, //!< points to token list for \\everyjob
		every_cr_loc = local_base+8, //!< points to token list for \\everycr
		err_help_loc = local_base+9, //!< points to token list for \\errhelp
	toks_base = local_base+10, //!< table of 256 token list registers
	box_base = toks_base+256, //!< table of 256 box registers
		cur_font_loc = box_base+256, //!< internal font number outside math mode
	math_font_base = cur_font_loc+1, //!< table of 48 math font numbers
	cat_code_base = math_font_base+48,
	lc_code_base = cat_code_base+256, //!< table of 256 lowercase mappings
	uc_code_base = lc_code_base+256, //!< table of 256 uppercase mappings
	sf_code_base = uc_code_base+256, //!< table of 256 spacefactor mappings
	math_code_base = sf_code_base+256, //!< table of 256 math mode mappings
	int_base = math_code_base+256, //!< beginning of region 5
	count_base = int_base+int_pars, //!< 256 user \\count registers
	del_code_base = count_base+256, //!< 256 delimiter code mappings
	dimen_base = del_code_base+256, //!< beginning of region 6
	scaled_base = dimen_base+dimen_pars,
	eqtb_size = scaled_base+255 //!< largest subscript of \a eqtb
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


enum scanner_status
{
	skipping = 1, //!< \a scanner_status when passing conditional text
	defining = 2, //!< \a scanner_status when reading a macro definition
	matching = 3, //!< \a scanner_status when reading macro arguments
	aligning = 4, //!< \a scanner_status when reading an alignment preamble
	absorbing = 5 //!< \a scanner_status when reading a balanced text
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
	just_open = 1, //!< newly opened, first line not yet read
	closed = 2 //!< not open, or at end of file
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

enum
{
	set1 = 128, //!< typeset a character and move right
	set_rule = 132, //!< typeset a rule and move right
	put_rule = 137, //!< typeset a rule
	bop = 139, //!< beginning of page
	eop = 140, //!< ending of page
	push = 141, //!< save the current positions
	pop = 142, //!< restore previous positions
	right1 = 143, //!< move right
	down1 = 157, //!< move down
	fnt_num_0 = 171, //!< set current font to 0
	fnt1 = 235, //!< set current font
	xxx1 = 239, //!< extension to DVI primitives
	xxx4 = 242, //!< potentially long extension to DVI primitives
	fnt_def1 = 243, //!< define the meaning of a font number
	pre = 247, //!< preamble
	post = 248, //!< postamble beginning
	post_post = 249 //!< postamble ending
};

enum info
{
	y_here = 1, //!< \a info when the movement entry points to a \a y command
	z_here = 2, //!< \a info when the movement entry points to a \a z command
	yz_OK = 3, //!< \a info corresponding to an unconstrained \a down command
	y_OK = 4, //!< \a info corresponding to a \a down that can't become a \a z
	z_OK = 5, //!< \a info corresponding to a \a down that can't become a \a y
	d_fixed = 6 //!< \a info corresponding to a \a down that can't change
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
constexpr int format_ext_length = 4; //!< length of its `.fmt' part
constexpr int id_byte = 2; //!< identifies the kind of DVI files described here
constexpr int default_code = 1<<30; //!< denotes \a default_rule_thickness
constexpr int cramped = 1; //!< add this to an uncramped style if you want to cramp it
constexpr int span_code = 256; //!< distinct from any character
constexpr int cr_code = 257; //!< distinct from \a span_code and from any character
constexpr int cr_cr_code = cr_code+1; //!< this distinguishes \\crcr from \\cr
constexpr int end_template_token = cs_token_flag+frozen_end_template;

enum
{
	very_loose_fit = 0, //!< fitness classification for lines stretching more than their stretchability
	loose_fit = 1, //!< fitness classification for lines stretching 0.5 to 1.0 of their stretchability
	decent_fit = 2, //!< fitness classification for all other lines
	tight_fit = 3 //!< fitness classification for lines shrinking 0.5 to 1.0 of their stretchability
};

enum
{
	unhyphenated = 0, //!< the \a type of a normal active break node
	hyphenated = 1 //!< the \a type of an active node that breaks at a \a disc_node
};

constexpr int delta_node = 2; //!< \a type field in a delta node
constexpr int split_up = 1; //!< an overflowed insertion class

inline LinkedNode *preamble = align_head->link; //!< the current preamble list

int length(halfword); //!< the number of characters
int cur_length(void); 
void append_char(ASCIIcode); //!< put \a ASCII_code # at the end of \a str_pool
void flush_char(void); //!< forget the last character in the pool
void flush_string(void); 
void tail_append(halfword); 
void tail_append(LinkedNode*);
halfword& node_size(halfword); //!< the size field in empty variable-size nodes
halfword& llink(halfword); //!< left link in doubly-linked list of empty nodes
halfword& rlink(halfword); //!< right link in doubly-linked list of empty nodes
halfword& link(halfword p); //!< the \a link field of a memory word
halfword& info(halfword p); //!< the \a info field of a memory word
quarterword& type(halfword p); //!< identifies what kind of node this is
quarterword& subtype(halfword p); //!< secondary identification in some cases
bool is_char_node(halfword);
quarterword& font(halfword); //!< the font code in a \a char_node
quarterword& character(halfword); //!< the character code in a \a char_node
int& width(halfword); //!< width of the box, in sp
int& depth(halfword); //!< depth of the box, in sp
int& height(halfword); //!< height of the box, in sp
//int& shift_amount(halfword); //!< repositioning distance, in sp
//halfword& list_ptr(halfword); //!< beginning of the list inside the box
quarterword& glue_order(halfword); //!< applicable order of infinity
quarterword& glue_sign(halfword); //!< stretching or shrinking
float &glue_set(halfword);
bool is_running(int); //!< tests for a running dimension
//int& float_cost(halfword); //!< the \a floating_penalty to be used
//halfword& ins_ptr(halfword); //!< the vertical list to be inserted
//halfword& split_top_ptr(halfword); //!< the \a split_top_skip to be used
//int& mark_ptr(halfword); //!< head of the token list for a mark
int& adjust_ptr(halfword); //!< vertical list to be moved out of horizontal list
halfword lig_char(halfword); //!< the word where the ligature is to be found
halfword& lig_ptr(halfword); //!< the list of characters
halfword& leader_ptr(halfword); //!< pointer to box or rule node for leaders
halfword& glue_ref_count(halfword); //!< reference count of a glue specification
int& stretch(halfword); //!< the stretchability of this glob of glue
int& shrink(halfword); //!< the shrinkability of this glob of glue
quarterword& stretch_order(halfword); //!< order of infinity for stretching
quarterword& shrink_order(halfword); //!< order of infinity for shrinking
int& penalty(halfword); //!< the added cost of breaking a list here
int& glue_stretch(halfword); //!< total stretch in an unset node
int& glue_shrink(halfword); //!< total shrink in an unset node
quarterword& span_count(halfword); //!< indicates the number of spanned columns
halfword& token_ref_count(halfword); //!< reference count preceding a token list
quarterword& eq_level(halfword);
quarterword& eq_type(halfword); //!< command code for equivalent
halfword& equiv(halfword); //!< equivalent value
//halfword& skip(halfword); //!< \a mem location of glue specification
halfword& par_shape_ptr(void); 
halfword& every_math(void); 
halfword& every_cr(void); 
halfword& err_help(void);
//halfword& box(halfword); 
halfword& cat_code(halfword);
halfword& lc_code(halfword p);
halfword& sf_code(halfword p);
halfword& math_code(halfword p);
int& del_code(halfword p);
int& count(halfword p);
int& dimen(halfword);
halfword& text(halfword); //!< string number for control sequence name
quarterword& save_type(halfword); //!< classifies a \a save_stack entry
quarterword& save_level(halfword);
halfword& save_index(halfword); 
int& saved(halfword); 
alphafile& cur_file(void); //!< the current \a alpha_file variable
int& if_line_field(halfword); 
void append_to_name(int&, char); 
int& location(halfword); //!< DVI byte number for a movement command
float vet_glue(float);
halfword nucleus(halfword); //!< the \a nucleus field of a noad
halfword supscr(halfword); //!< the \a supscr field of a noad
halfword subscr(halfword); //!< the \a subscr field of a noad
halfword& math_type(halfword); //!< a \a halfword in \a mem
quarterword& fam(halfword); //!< a \a quarterword in \a mem
halfword left_delimiter(halfword); //!< first delimiter field of a noad
halfword right_delimiter(halfword); //!< second delimiter field of a fraction noad
quarterword& small_fam(halfword); //!< \a fam for ``small'' delimiter
quarterword& small_char(halfword); //!< \a character for ``small'' delimiter
quarterword& large_fam(halfword); //!< \a fam for ``large'' delimiter
quarterword& large_char(halfword); //!< \a character for ``large'' delimiter
int& thickness(halfword); //!< \a thickness field in a fraction noad
halfword numerator(halfword); //!< \a numerator field in a fraction noad
halfword denominator(halfword); //!< \a denominator field in a fraction noad
halfword accent_chr(halfword); //!< the \a accent_chr field of an accent noad
halfword delimiter(halfword); //!< \a delimiter field in left and right noads
int default_rule_thickness(void); //!< thickness of \\over bars
int& new_hlist(halfword); //!< the translation of an mlist
int& u_part(halfword); //!< pointer to \f$<u_j\f$ token list
int&v_part(halfword); //!< pointer to \f$<v_j\f$ token list
halfword& extra_info(halfword); //!< info to remember during template
quarterword& fitness(halfword); //!< <em> very_loose_fit..tight_fit</em> on final line for this break
halfword& break_node(halfword); //!< pointer to the corresponding passive node
halfword& line_number(halfword); //!< line that begins at this breakpoint
int& total_demerits(halfword); //!< the quantity that \\TeX\\ minimizes
void set_cur_lang(void); 
halfword& broken_ins(halfword p); //!< this insertion might break at \a broken_ptr
halfword& last_ins_ptr(halfword p); //!< the most recent insertion for this \a subtype
halfword& best_ins_ptr(halfword); //!< the optimum most recent insertion
halfword& what_lang(halfword); //!< language number, in the range 0..255
quarterword& what_lhm(halfword); //!< minimum left fragment, in the range 1..63
quarterword& what_rhm(halfword); //!< minimum right fragment, in the range 1..63
halfword& write_tokens(halfword); //!< reference count of token list to write
halfword& write_stream(halfword); //!< stream number (0 to 17)
halfword& open_name(halfword); //!< string number of file name to open
halfword& open_area(halfword); //!< string number of file area for \a open_name
halfword& open_ext(halfword); //!< string number of file extension for \a open_name
halfword& every_vbox(void); 

inline auto start = curinput.startfield; //!< starting position in \a buffer
inline auto limit = curinput.limitfield; //!< end of current line in \a buffer
inline auto param_start = limit; //!< base of macro parameters in \a param_stack
inline auto loc = curinput.locfield; //!< location of first unread character in \a buffer
inline TokenNode *Start;
inline TokenNode *Loc;

extern quarterword &state; //!< current scanner state
extern quarterword &index; //!< reference for buffer information
extern std::string &name; //!< name of the current file
extern scaled &act_width; //!< length from first active node to current node
extern scaled &page_goal; //!< desired height of information on page being built
extern scaled &page_total; //!< height of the current page
extern scaled &page_shrink; //!< shrinkability of the current page
extern scaled &page_depth; //!< depth of the current page
//extern halfword &contrib_tail; //!< tail of the contribution list

inline bool precedes_break(halfword p) { return type(p) <math_node; }
inline void add_glue_ref(halfword p) { glue_ref_count(p)++; } //!< new reference to a glue spec
inline bool terminal_input(const std::string &name) { return name == ""; } //!< are we reading from the terminal?
inline quarterword &token_type = index; //!< type of current token list
inline bool end_line_char_inactive() { return end_line_char() < 0 || end_line_char() > 255; }
inline int cramped_style(int c) { return 2*(c/2)+cramped; } //!< cramp the style
inline int sub_style(int c) { return 2*(c/4)+script_style+cramped; } //!< smaller and cramped
inline int sup_style(int c) { return 2*(c/4)+script_style+c%2; } //!< smaller
inline void add_token_ref(halfword p) { token_ref_count(p)++; } //!< new reference to a token list


#endif

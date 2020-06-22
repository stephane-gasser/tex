#ifndef CONSTANTES_H
#define CONSTANTES_H

#include "tex.h"

constexpr int CHECKSUM = 117275187;
constexpr char banner[] ="This is TeX, Version 3.14159265"; //printed when \TeX\ starts
constexpr int mem_bot = 0; //smallest index in the |mem| array dumped by \.//INITEX;
constexpr int mem_top = 30000; //largest index in the |mem| array dumped by \.//INITEX;
constexpr int font_base = 0; //smallest internal font number; must not be less
constexpr int hash_size = 2100; //maximum number of control sequences; it should be at most
constexpr int hash_prime = 1777; //a prime number equal to about 85\pct! of |hash_size|
constexpr int hyph_size = 307; //another prime; the number of \hyphenation exceptions

extern halfword &loc; //loc==cur_input.loc_field //location of first unread character in |buffer|

int length(halfword); //length(#)==(str_start[#+1]-str_start[#]) //the number of characters
int cur_length(void); //cur_length == (pool_ptr - str_start[str_ptr])
void append_char(ASCIIcode); // append_char(#) == //put |ASCII_code| \# at the end of |str_pool| begin str_pool[pool_ptr]:=si(#); incr(pool_ptr);end
void flush_char(void); //flush_char == decr(pool_ptr) //forget the last character in the pool

void flush_string(void); //flush_string==begin decr(str_ptr); pool_ptr:=str_start[str_ptr];

enum
{
	no_print = 16, //|selector| setting that makes data disappear
	term_only = 17, //printing is destined for the terminal only
	log_only = 18, //printing is destined for the transcript file only
	term_and_log = 19, //normal |selector| setting
	pseudo = 20, //special |selector| setting for |show_context|
	new_string = 21 //printing is deflected to the string pool
};

enum
{
	batch_mode = 0, //omits all stops and omits terminal output
	nonstop_mode = 1, //omits all stops
	scroll_mode = 2, //omits error stops
	error_stop_mode = 3 //stops at every opportunity to interact
};

enum
{
	spotless = 0, //|history| value when nothing has been amiss yet
	warning_issued = 1, //|history| value when |begin_diagnostic| has been called
	error_message_issued = 2, //|history| value when |error| has been called
	fatal_error_stop = 3 //|history| value when termination was premature
};

constexpr int unity = 1<<16; //== @'200000 //$2^//16$, represents 1.00000
constexpr int two = 1<<17; //@'400000 //$2^//17$, represents 2.00000
constexpr int inf_bad = 10000; //infinitely bad value

extern memoryword& aux; //aux==cur_list.aux_field //auxiliary data about the current list
extern int& prev_depth; //prev_depth==aux.sc //the name of |aux| in vertical mode
extern halfword& space_factor; //space_factor==aux.hh.lh //part of |aux| in horizontal mode
extern halfword& clang; //clang==aux.hh.rh //the other part of |aux| in horizontal mode  
extern int& incompleat_noad; //incompleat_noad==aux.int //the name of |aux| in math mode*/
extern int& mode; //mode==cur_list.mode_field //current mode
extern halfword& head; //head==cur_list.head_field //header node of current list
extern halfword& tail; //tail==cur_list.tail_field //final node on current list
extern int& prev_graf; //prev_graf==cur_list.pg_field //number of paragraph lines accumulated
extern int& mode_line; //mode_line==cur_list.ml_field //source file line number at beginning of list
void tail_append(halfword); //tail_append(#)==begin link(tail):=#; tail:=link(tail);

constexpr int empty_flag = 65535; // == max_halfword //the |link| of an empty variable-size node
halfword& node_size(halfword); //node_size == info //the size field in empty variable-size nodes
halfword& llink(halfword); //llink(#) == info(#+1) //left link in doubly-linked list of empty nodes
halfword& rlink(halfword); //rlink(#) == link(#+1) //right link in doubly-linked list of empty nodes
halfword& link(halfword p); // link(#) == mem[#].hh.rh //the |link| field of a memory word
halfword& info(halfword p); // info(#) == mem[#].hh.lh //the |info| field of a memory word
quarterword& type(halfword p); //type(#) == mem[#].hh.b0 //identifies what kind of node this is
quarterword& subtype(halfword p); //subtype(#) == mem[#].hh.b1 //secondary identification in some cases

bool is_char_node(halfword); //is_char_node(#) == (#>=hi_mem_min)
quarterword& font(halfword); //font == type //the font code in a |char_node|
quarterword& character(halfword); // character == subtype //the character code in a |char_node|*/

enum
{
	if_node_size = 2, //number of words in stack entry for conditionals
	box_node_size = 7, //number of words to allocate for a box node
	rule_node_size = 4, //number of words to allocate for a rule node
	ins_node_size = 5, //number of words to allocate for an insertion
	small_node_size = 2, //number of words to allocate for most node types
	movement_node_size = 3, //number of words per entry in the down and right stacks
	style_node_size = 3, //number of words in a style node
	align_stack_node_size = 5, //number of |mem| words to save alignment states
	span_node_size = 2, //number of |mem| words for a span node
	active_node_size = 3, //number of words in active nodes
	passive_node_size = 2, //number of words in passive nodes
	delta_node_size = 7, //number of words in a delta node
	page_ins_node_size = 4, //number of words for a page insertion node
	write_node_size = 2, //number of words in a write/whatsit node
	open_node_size = 3, //number of words in an open/whatsit node
	noad_size = 4, //number of words in a normal noad
	accent_noad_size = 5, //number of |mem| words in an accent noad
	radical_noad_size = 5, //number of |mem| words in a radical noad
	fraction_noad_size = 6 //number of |mem| words in a fraction noad
};

enum
{
	hlist_node = 0, //|type| of hlist nodes
	vlist_node = 1, //|type| of vlist nodes
	rule_node = 2, //|type| of rule nodes
	ins_node = 3, //|type| of insertion nodes
	mark_node = 4, //|type| of a mark node
	adjust_node = 5, //|type| of an adjust node
	ligature_node = 6, //|type| of a ligature node
	disc_node = 7, //|type| of a discretionary node
	whatsit_node = 8, //|type| of special extension nodes
	math_node = 9, //|type| of a math node
	glue_node = 10, //|type| of node that points to a glue specification
	kern_node = 11, //|type| of a kern node
	penalty_node = 12, //|type| of a penalty node
	unset_node = 13, //|type| for an unset node
	style_node = 14, //unset_node+1 //|type| of a style node
	choice_node = 15 //unset_node+2 //|type| of a choice node
};

enum
{
	width_offset = 1, //position of |width| field in a box node
	depth_offset = 2, //position of |depth| field in a box node
	height_offset = 3, //position of |height| field in a box node
	list_offset = 5, //position of |list_ptr| field in a box node
	glue_offset = 6 //position of |glue_set| in a box node
};

int& width(halfword); //width(#) == mem[#+width_offset].sc //width of the box, in sp
int& depth(halfword); //depth(#) == mem[#+depth_offset].sc //depth of the box, in sp
int& height(halfword); //height(#) == mem[#+height_offset].sc //height of the box, in sp
int& shift_amount(halfword); //shift_amount(#) == mem[#+4].sc //repositioning distance, in sp
halfword& list_ptr(halfword); //list_ptr(#) == link(#+list_offset) //beginning of the list inside the box
quarterword& glue_order(halfword); //glue_order(#) == subtype(#+list_offset) //applicable order of infinity
quarterword& glue_sign(halfword); //glue_sign(#) == type(#+list_offset) //stretching or shrinking

enum
{
	normal = 0, //the most common case when several cases are named
	stretching = 1, //glue setting applies to the stretch components
	shrinking = 2 //glue setting applies to the shrink components
};

float &glue_set(halfword); //glue_set(#) == mem[#+glue_offset].gr

constexpr int null_flag = -1073741824; //==-@'10000000000 //$-2^//30$, signifies a missing item

bool is_running(int); /*is_running(#) == (#=null_flag) //tests for a running dimension*/

int& float_cost(halfword); //float_cost(#)==mem[#+1].int //the |floating_penalty| to be used
halfword& ins_ptr(halfword); //ins_ptr(#)==info(#+4) //the vertical list to be inserted
halfword& split_top_ptr(halfword);// split_top_ptr(#)==link(#+4) //the |split_top_skip| to be used
int& mark_ptr(halfword); //mark_ptr(#)==mem[#+1].int //head of the token list for a mark
int& adjust_ptr(halfword); //adjust_ptr==mark_ptr //vertical list to be moved out of horizontal list
halfword lig_char(halfword); //lig_char(#)==#+1 //the word where the ligature is to be found
halfword& lig_ptr(halfword); //lig_ptr(#)==link(lig_char(#)) //the list of characters
quarterword& replace_count(halfword); /*replace_count==subtype //how many subsequent nodes to replace*/
halfword& pre_break(halfword); //pre_break==llink //text that precedes a discretionary break
halfword& post_break(halfword); //post_break==rlink //text that follows a discretionary break

enum
{
	before = 0, //|subtype| for math node that introduces a formula
	after = 1 //|subtype| for math node that winds up a formula
};

inline bool precedes_break(halfword p) { return type(p) <math_node; } //precedes_break(#)==(type(#)<math_node)

constexpr int cond_math_glue = 98; //special |subtype| to suppress glue in the next node
constexpr int mu_glue = 99; //|subtype| for math glue

enum
{
	a_leaders = 100, //|subtype| for aligned leaders
	c_leaders = 101, //|subtype| for centered leaders
	x_leaders = 102, //|subtype| for expanded leaders
};

halfword& glue_ptr(halfword); //glue_ptr==llink //pointer to a glue specification
halfword& leader_ptr(halfword); //leader_ptr==rlink //pointer to box or rule node for leaders

constexpr int glue_spec_size = 4; //number of words to allocate for a glue specification*/

halfword& glue_ref_count(halfword); //glue_ref_count(#) == link(#) //reference count of a glue specification
int& stretch(halfword); //stretch(#) == mem[#+2].sc //the stretchability of this glob of glue
int& shrink(halfword); //shrink(#) == mem[#+3].sc //the shrinkability of this glob of glue
quarterword& stretch_order(halfword);//stretch_order == type //order of infinity for stretching
quarterword& shrink_order(halfword); //shrink_order == subtype //order of infinity for shrinking

constexpr int fil = 1; //first-order infinity
constexpr int fill = 2; //second-order infinity
constexpr int filll = 3; //third-order infinity
constexpr int explicit_ = 1; //|subtype| of kern nodes from \kern and \/
constexpr int acc_kern = 2; //|subtype| of kern nodes from accents
constexpr int inf_penalty = 10000; //inf_bad //``infinite'' penalty value
constexpr int eject_penalty = -10000; //-inf_penalty //``negatively infinite'' penalty value

int& penalty(halfword); // penalty(#) == mem[#+1].int //the added cost of breaking a list here
int& glue_stretch(halfword); //glue_stretch(#)==mem[#+glue_offset].sc //total stretch in an unset node
int& glue_shrink(halfword); //glue_shrink==shift_amount //total shrink in an unset node
quarterword& span_count(halfword); //span_count==subtype //indicates the number of spanned columns

enum
{
	zero_glue = 0, //mem_bot //specification for \.//0pt plus 0pt minus 0pt
	fil_glue = 4, //==zero_glue+glue_spec_size //\.//0pt plus 1fil minus 0pt
	fill_glue = 8, //==fil_glue+glue_spec_size //\.//0pt plus 1fill minus 0pt
	ss_glue = 12, //==fill_glue+glue_spec_size //\.//0pt plus 1fil minus 1fil
	fil_neg_glue = 16 //==ss_glue+glue_spec_size //\.//0pt plus -1fil minus 0pt
};

constexpr int lo_mem_stat_max = 19; //=fil_neg_glue+glue_spec_size-1 //largest statically
constexpr int page_ins_head = 30000; //mem_top //list of insertion data for current page
constexpr int contrib_head = 29999; //mem_top-1 //vlist of items not yet on current page
constexpr int page_head = 29998; //mem_top-2 //vlist for current page
constexpr int temp_head = 29997; //mem_top-3 //head of a temporary list of some kind
constexpr int hold_head = 29996; //mem_top-4 //head of a temporary list of another kind
constexpr int adjust_head = 29995; //mem_top-5 //head of adjustment list returned by |hpack|
constexpr int active = 29993; //mem_top-7 //head of active list in |line_break|, needs two words
constexpr int align_head = 29992; //mem_top-8 //head of preamble list for alignments
constexpr int end_span = 29991; //mem_top-9 //tail of spanned-width lists
constexpr int omit_template = 29990; //mem_top-10 //a constant token list
constexpr int null_list = 29989; //mem_top-11 //permanently empty list
constexpr int lig_trick = 29988; //mem_top-12 //a ligature masquerading as a |char_node|
constexpr int garbage = 29988; //mem_top-12 //used for scrap information
constexpr int backup_head = 29987; //mem_top-13 //head of token list built by |scan_keyword|
constexpr int hi_mem_stat_min = 29987; //mem_top-13 //smallest statically allocated word in
constexpr int hi_mem_stat_usage = 14; //the number of one-word nodes always present

halfword& token_ref_count(halfword); //token_ref_count(#) == info(#) //reference count preceding a token list
inline void add_glue_ref(halfword p) { glue_ref_count(p)++; } //new reference to a glue spec*/

constexpr int escape = 0; //escape delimiter (called \.\\ in //\sl The \TeX book\/)
constexpr int relax = 0; //do nothing ( \relax )
constexpr int left_brace = 1; //beginning of a group ( \.\// )
constexpr int right_brace = 2; //ending of a group ( \.\ )
constexpr int math_shift = 3; //mathematics shift character ( \.\$ )
constexpr int tab_mark = 4; //alignment delimiter ( \.\&, \span )
constexpr int car_ret = 5; //end of line ( |carriage_return|, \cr, \crcr )
constexpr int out_param = 5;  //output a macro parameter
constexpr int mac_param = 6; //macro parameter symbol ( \.\# )
constexpr int sup_mark = 7; //superscript ( \.//\char'136 )
constexpr int sub_mark = 8; //subscript ( \.//\char'137 )
constexpr int ignore = 9; //characters to ignore ( \.//\^\^@@ )
constexpr int endv = 9; //end of \<v_j> list in alignment template*/
constexpr int spacer = 10; //characters equivalent to blank space ( \.//\  )
constexpr int letter = 11; //characters regarded as letters ( \.//A..Z, \.//a..z )
constexpr int other_char = 12; //none of the special character types
constexpr int active_char = 13; //characters that invoke macros ( \.//\char`\~ )
constexpr int par_end = 13; //end of paragraph ( \par )
constexpr int match = 13; //match a macro parameter
constexpr int comment = 14; //characters that introduce comments ( \.\% )
constexpr int end_match = 14; //end of parameters to macro
constexpr int stop = 14; //end of job ( \end, \dump )*/
constexpr int invalid_char = 15; //characters that shouldn't appear ( \.//\^\^? )
constexpr int delim_num = 15; //specify delimiter numerically ( \delimiter )
constexpr int max_char_code = 15; //largest catcode for individual characters
constexpr int char_num = 16; //character specified numerically ( \char )
constexpr int math_char_num = 17; //explicit math code ( \mathchar )
constexpr int mark = 18; //mark definition ( \mark )
constexpr int xray = 19; //peek inside of \TeX\ ( \show, \showbox, etc.~)
constexpr int make_box = 20; //make a box ( \box, \copy, \hbox, etc.~)
constexpr int hmove = 21; //horizontal motion ( \moveleft, \moveright )
constexpr int vmove = 22; //vertical motion ( \raise, \lower )
constexpr int un_hbox = 23; //unglue a box ( \unhbox, \unhcopy )
constexpr int un_vbox = 24; //unglue a box ( \unvbox, \unvcopy )
constexpr int remove_item = 25; //nullify last item ( \unpenalty,
constexpr int hskip = 26; //horizontal glue ( \hskip, \hfil, etc.~)
constexpr int vskip = 27; //vertical glue ( \vskip, \vfil, etc.~)
constexpr int mskip = 28; //math glue ( \mskip )
constexpr int kern = 29; //fixed space ( \kern)*/
constexpr int mkern = 30; //math kern ( \mkern )
constexpr int leader_ship = 31; //use a box ( \shipout, \leaders, etc.~)
constexpr int halign = 32; //horizontal table alignment ( \halign )
constexpr int valign = 33; //vertical table alignment ( \valign )
constexpr int no_align = 34; //temporary escape from alignment ( \noalign )
constexpr int vrule = 35; //vertical rule ( \vrule )
constexpr int hrule = 36; //horizontal rule ( \hrule )
constexpr int insert = 37; //vlist inserted in box ( \insert )
constexpr int vadjust = 38; //vlist inserted in enclosing paragraph ( \vadjust )*/
constexpr int ignore_spaces = 39; //gobble |spacer| tokens ( \ignorespaces )
constexpr int after_assignment = 40; //save till assignment is done ( \afterassignment )
constexpr int after_group = 41; //save till group is done ( \aftergroup )
constexpr int break_penalty = 42; //additional badness ( \penalty )
constexpr int start_par = 43; //begin paragraph ( \indent, \noindent )
constexpr int ital_corr = 44; //italic correction ( \/ )
constexpr int accent = 45; //attach accent in text ( \accent )*/
constexpr int math_accent = 46; //attach accent in math ( \mathaccent )
constexpr int discretionary = 47; //discretionary texts ( \-, \discretionary )
constexpr int eq_no = 48; //equation number ( \eqno, \leqno )
constexpr int left_right = 49; //variable delimiter ( \left, \right )
constexpr int math_comp = 50; //component of formula ( \mathbin, etc.~)
constexpr int limit_switch = 51; //diddle limit conventions ( \displaylimits, etc.~)
constexpr int above = 52; //generalized fraction ( \above, \atop, etc.~)
constexpr int math_style = 53; //style specification ( \displaystyle, etc.~)
constexpr int math_choice = 54; //choice specification ( \mathchoice )
constexpr int non_script = 55; //conditional math glue ( \nonscript )
constexpr int vcenter = 56; //vertically center a vbox ( \vcenter )
constexpr int case_shift = 57; //force specific case ( \lowercase, \uppercase~)
constexpr int message = 58; //send to user ( \message, \errmessage )*/
constexpr int extension = 59; //extensions to \TeX\ ( \write, \special, etc.~)
constexpr int in_stream = 60; //files for reading ( \openin, \closein )
constexpr int begin_group = 61; //begin local grouping ( \begingroup )
constexpr int end_group = 62; //end local grouping ( \endgroup )
constexpr int omit = 63; //omit alignment template ( \omit )
constexpr int ex_space = 64; //explicit space ( \\  )
constexpr int no_boundary = 65; //suppress boundary ligatures ( \noboundary )
constexpr int radical = 66; //square root and similar signs ( \radical )
constexpr int end_cs_name = 67; //end control sequence ( \endcsname )
constexpr int min_internal = 68; //the smallest code that can follow \the*/
constexpr int char_given = 68; //character code defined by \chardef
constexpr int math_given = 69; //math code defined by \mathchardef
constexpr int last_item = 70; //most recent item ( \lastpenalty,
constexpr int max_non_prefixed_command = 70; //largest command code that can't be \global*/
constexpr int toks_register = 71; //token list register ( \toks )
constexpr int assign_toks = 72; //special token list ( \output, \everypar, etc.~)
constexpr int assign_int = 73; //user-defined integer ( \tolerance, \day, etc.~)
constexpr int assign_dimen = 74; //user-defined length ( \hsize, etc.~)
constexpr int assign_glue = 75; //user-defined glue ( \baselineskip, etc.~)
constexpr int assign_mu_glue = 76; //user-defined muglue ( \thinmuskip, etc.~)
constexpr int assign_font_dimen = 77; //user-defined font dimension ( \fontdimen )
constexpr int assign_font_int = 78; //user-defined font integer ( \hyphenchar,*/
constexpr int set_aux = 79; //specify state info ( \spacefactor, \prevdepth )
constexpr int set_prev_graf = 80; //specify state info ( \prevgraf )
constexpr int set_page_dimen = 81; //specify state info ( \pagegoal, etc.~)
constexpr int set_page_int = 82; //specify state info ( \deadcycles,
constexpr int set_box_dimen = 83; //change dimension of box ( \wd, \ht, \dp )
constexpr int set_shape = 84; //specify fancy paragraph shape ( \parshape )
constexpr int def_code = 85; //define a character code ( \catcode, etc.~)
constexpr int def_family = 86; //declare math fonts ( \textfont, etc.~)
constexpr int set_font = 87; //set current font ( font identifiers )
constexpr int def_font = 88; //define a font file ( \font )
constexpr int register_ = 89; //internal register ( \count, \dimen, etc.~)
constexpr int max_internal = 89; //the largest code that can follow \the
constexpr int advance = 90; //advance a register or parameter ( \advance )
constexpr int multiply = 91; //multiply a register or parameter ( \multiply )
constexpr int divide = 92; //divide a register or parameter ( \divide )
constexpr int prefix = 93; //qualify a definition ( \global, \long, \outer )
constexpr int let = 94; //assign a command code ( \let, \futurelet )
constexpr int shorthand_def = 95; //code definition ( \chardef, \countdef, etc.~)
constexpr int read_to_cs = 96; //read into a control sequence ( \read )
constexpr int def = 97; //macro definition ( \def, \gdef, \xdef, \edef )
constexpr int set_box = 98; //set a box ( \setbox )
constexpr int hyph_data = 99; //hyphenation data ( \hyphenation, \patterns )
constexpr int set_interaction = 100; //define level of interaction ( \batchmode, etc.~)*/
constexpr int max_command = 100; //the largest command code seen at |big_switch|
constexpr int undefined_cs = 101; //=max_command+1 //initial state of most |eq_type| fields
constexpr int expand_after = 102; // max_command+2 //special expansion ( \expandafter )
constexpr int no_expand = 103; //max_command+3 //special nonexpansion ( \noexpand )
constexpr int input = 104; //max_command+4 //input a source file ( \input, \endinput )
constexpr int if_test = 105; //max_command+5 //conditional text ( \if, \ifcase, etc.~)
constexpr int fi_or_else = 106; //max_command+6 //delimiters for conditionals ( \else, etc.~)
constexpr int cs_name = 107; //max_command+7 //make a control sequence from tokens ( \csname )
constexpr int convert = 108; // max_command+8 //convert to text ( \number, \string, etc.~)
constexpr int the = 109; // max_command+9 //expand an internal quantity ( \the )
constexpr int top_bot_mark = 110; //max_command+10 //inserted mark ( \topmark, etc.~)
constexpr int call = 111; //max_command+11 //non-long, non-outer control sequence
constexpr int long_call = 112; //max_command+12 //long, non-outer control sequence
constexpr int outer_call = 113; //max_command+13 //non-long, outer control sequence
constexpr int long_outer_call = 114; //max_command+14 //long, outer control sequence
constexpr int end_template = 115; //max_command+15 //end of an alignment template
constexpr int dont_expand = 116; //max_command+16 //the following token was marked by \noexpand
constexpr int glue_ref = 117; //max_command+17 //the equivalent points to a glue specification
constexpr int shape_ref = 118; //max_command+18 //the equivalent points to a parshape specification
constexpr int box_ref = 119; //max_command+19 //the equivalent points to a box node, or is |null|
constexpr int data = 120; //max_command+20 //the equivalent is simply a halfword number

enum
{
	vmode = 1, //vertical mode
	hmode = 102, //=vmode+max_command+1 //horizontal mode
	mmode = 203 //=hmode+max_command+1 //math mode
};

constexpr int ignore_depth = -65536000; //|prev_depth| value that is ignored

quarterword& eq_level(halfword); //eq_level_field(#)==#.hh.b1 
quarterword& eq_type(halfword); //eq_type(#)==eq_type_field(eqtb[#]) //command code for equivalent
halfword& equiv(halfword); //equiv(#)==equiv_field(eqtb[#]) //equivalent value

enum
{
	level_zero = 0, // min_quarterword //level for undefined quantities
	level_one = 1 // level_zero+1 //outermost level for defined quantities
};

enum
{
	active_base = 1, //beginning of region 1, for active character equivalents
	single_base = 257, //active_base+256 //equivalents of one-character control sequences
		null_cs = 513, // single_base+256 //equivalent of \csname\\endcsname
	hash_base = 514, //null_cs+1 //beginning of region 2, for the hash table
		frozen_control_sequence = 2614, //hash_base+hash_size //for error recovery
		frozen_protection = 2614, //frozen_control_sequence //inaccessible but definable
		frozen_cr = 2615, //frozen_control_sequence+1 //permanent `\cr'
		frozen_end_group = 2616, //=frozen_control_sequence+2 //permanent `\endgroup'
		frozen_right = 2617, //frozen_control_sequence+3 //permanent `\right'*/
		frozen_fi = 2618, //frozen_control_sequence+4 //permanent `\fi'
		frozen_end_template = 2619, //=frozen_control_sequence+5 //permanent `\endtemplate'*/
		frozen_endv = 2620, //frozen_control_sequence+6 //second permanent `\endtemplate'
		frozen_relax = 2621, //frozen_control_sequence+7 //permanent `\relax'*/
		end_write = 2622, //frozen_control_sequence+8 //permanent `\endwrite'
		frozen_dont_expand = 2623, //frozen_control_sequence+9
		frozen_null_font = 2624, //frozen_control_sequence+10
	font_id_base = 2624, //frozen_null_font-font_base
		undefined_control_sequence = 2881,// frozen_null_font+257 //dummy location
	glue_base = 2882, //undefined_control_sequence+1 //beginning of region 3
	skip_base = 2900, //glue_base+glue_pars //table of 256 ``skip'' registers
	mu_skip_base = 3156, //skip_base+256 //table of 256 ``muskip'' registers
	local_base = 3412, //mu_skip_base+256 //beginning of region 4
		par_shape_loc = 3412, //local_base //specifies paragraph shape
		output_routine_loc = 3413, //local_base+1 //points to token list for \output
		every_par_loc = 3414, //local_base+2 //points to token list for \everypar
		every_math_loc = 3415, //local_base+3 //points to token list for \everymath
		every_display_loc = 3416, //local_base+4 //points to token list for \everydisplay
		every_hbox_loc = 3417, //local_base+5 //points to token list for \everyhbox
		every_vbox_loc = 3418, //local_base+6 //points to token list for \everyvbox
		every_job_loc = 3419, //local_base+7 //points to token list for \everyjob
		every_cr_loc = 3420, //local_base+8 //points to token list for \everycr
		err_help_loc = 3421, //local_base+9 //points to token list for \errhelp*/
	toks_base = 3422, //local_base+10 //table of 256 token list registers
	box_base = 3678, //toks_base+256 //table of 256 box registers
		cur_font_loc = 3934, //box_base+256 //internal font number outside math mode
	math_font_base = 3935, //cur_font_loc+1 //table of 48 math font numbers
	cat_code_base = 3983, //math_font_base+48
	lc_code_base = 4239, //cat_code_base+256 //table of 256 lowercase mappings
	uc_code_base = 4495, //lc_code_base+256 //table of 256 uppercase mappings
	sf_code_base = 4751, // uc_code_base+256 //table of 256 spacefactor mappings
	math_code_base = 5007, //sf_code_base+256 //table of 256 math mode mappings
	int_base = 5263, //math_code_base+256 //beginning of region 5
	count_base = 5318, //int_base+int_pars //256 user \count registers
	del_code_base = 5574, //count_base+256 //256 delimiter code mappings
	dimen_base = 5830, //del_code_base+256 //beginning of region 6
};

enum
{
	line_skip_code = 0, //interline glue if |baseline_skip| is infeasible
	baseline_skip_code = 1, //desired glue between baselines
	par_skip_code = 2, //extra glue just above a paragraph
	above_display_skip_code = 3, //extra glue just above displayed math
	below_display_skip_code = 4, //extra glue just below displayed math
	above_display_short_skip_code = 5,
	below_display_short_skip_code = 6,
	left_skip_code = 7, //glue at left of justified lines
	right_skip_code = 8, //glue at right of justified lines
	top_skip_code = 9, //glue at top of main pages
	split_top_skip_code = 10, //glue at top of split pages
	tab_skip_code = 11, //glue between aligned entries*/
	space_skip_code = 12, //glue between words (if not |zero_glue|)
	xspace_skip_code = 13, //glue after sentences (if not |zero_glue|)
	par_fill_skip_code = 14, //glue on last line of paragraph
	thin_mu_skip_code = 15, //thin space in math formula
	med_mu_skip_code = 16, //medium space in math formula
	thick_mu_skip_code = 17 //thick space in math formula
};

constexpr int glue_pars = 18; //total number of glue parameters

halfword& skip(halfword); //skip(#)==equiv(skip_base+#) //|mem| location of glue specification
halfword& mu_skip(halfword); //mu_skip(#)==equiv(mu_skip_base+#) //|mem| location of math glue spec
halfword& glue_par(halfword); //glue_par(#)==equiv(glue_base+#) //|mem| location of glue specification
halfword& baseline_skip(void); //baseline_skip==glue_par(baseline_skip_code)
halfword& left_skip(void); //left_skip==glue_par(left_skip_code)
halfword& right_skip(void); //right_skip==glue_par(right_skip_code)
halfword& split_top_skip(void); //split_top_skip==glue_par(split_top_skip_code)
halfword& space_skip(void); //space_skip==glue_par(space_skip_code)
halfword& xspace_skip(void); //xspace_skip==glue_par(xspace_skip_code)
halfword& par_shape_ptr(void); //par_shape_ptr==equiv(par_shape_loc)
halfword& output_routine(void); //output_routine==equiv(output_routine_loc)
halfword& every_par(void); //every_par==equiv(every_par_loc)
halfword& every_math(void); //every_math==equiv(every_math_loc)
halfword& every_display(void); //every_display==equiv(every_display_loc)
halfword& every_hbox(void); //every_hbox==equiv(every_hbox_loc)
halfword& every_vbox(void); //every_vbox==equiv(every_vbox_loc)
halfword& every_job(void); //every_job==equiv(every_job_loc)
halfword& every_cr(void); //every_cr==equiv(every_cr_loc)
halfword& err_help(void); //err_help==equiv(err_help_loc)
halfword& box(halfword); //box(#)==equiv(box_base+#)
halfword& cur_font(void); //cur_font==equiv(cur_font_loc)
halfword& fam_fnt(halfword); //fam_fnt(#)==equiv(math_font_base+#)
halfword& cat_code(halfword); //cat_code(#)==equiv(cat_code_base+#)
halfword& lc_code(halfword p); //lc_code(#)==equiv(lc_code_base+#)
halfword& uc_code(halfword p); //uc_code(#)==equiv(uc_code_base+#)
halfword& sf_code(halfword p); //sf_code(#)==equiv(sf_code_base+#)
halfword& math_code(halfword p); //math_code(#)==equiv(math_code_base+#)

constexpr int null_font = 0; //font_base
constexpr int var_code = 28672; //=@'70000 //math code meaning ``use the current family''*/
constexpr int pretolerance_code = 0; //badness tolerance before hyphenation
constexpr int tolerance_code = 1; //badness tolerance after hyphenation
constexpr int line_penalty_code = 2; //added to the badness of every line
constexpr int hyphen_penalty_code = 3; //penalty for break after discretionary hyphen
constexpr int ex_hyphen_penalty_code = 4; //penalty for break after explicit hyphen
constexpr int club_penalty_code = 5; //penalty for creating a club line
constexpr int widow_penalty_code = 6; //penalty for creating a widow line
constexpr int display_widow_penalty_code = 7; //ditto, just before a display
constexpr int broken_penalty_code = 8; //penalty for breaking a page at a broken line
constexpr int bin_op_penalty_code = 9; //penalty for breaking after a binary operation
constexpr int rel_penalty_code = 10; //penalty for breaking after a relation
constexpr int pre_display_penalty_code = 11;
constexpr int post_display_penalty_code = 12;
constexpr int inter_line_penalty_code = 13; //additional penalty between lines
constexpr int double_hyphen_demerits_code = 14; //demerits for double hyphen break
constexpr int final_hyphen_demerits_code = 15; //demerits for final hyphen break
constexpr int adj_demerits_code = 16; //demerits for adjacent incompatible lines
constexpr int mag_code = 17; //magnification ratio
constexpr int delimiter_factor_code = 18; //ratio for variable-size delimiters
constexpr int looseness_code = 19; //change in number of lines for a paragraph
constexpr int time_code = 20; //current time of day
constexpr int day_code = 21; //current day of the month
constexpr int month_code = 22; //current month of the year
constexpr int year_code = 23; //current year of our Lord
constexpr int show_box_breadth_code = 24; //nodes per level in |show_box|
constexpr int show_box_depth_code = 25; //maximum level in |show_box|
constexpr int hbadness_code = 26; //hboxes exceeding this badness will be shown by |hpack|
constexpr int vbadness_code = 27; //vboxes exceeding this badness will be shown by |vpack|
constexpr int pausing_code = 28; //pause after each line is read from a file
constexpr int tracing_online_code = 29; //show diagnostic output on terminal
constexpr int tracing_macros_code = 30; //show macros as they are being expanded
constexpr int tracing_stats_code = 31; //show memory usage if \TeX\ knows it
constexpr int tracing_paragraphs_code = 32; //show line-break calculations
constexpr int tracing_pages_code = 33; //show page-break calculations
constexpr int tracing_output_code = 34; //show boxes when they are shipped out
constexpr int tracing_lost_chars_code = 35; //show characters that aren't in the font
constexpr int tracing_commands_code = 36; //show command codes at |big_switch|
constexpr int tracing_restores_code = 37; //show equivalents when they are restored
constexpr int uc_hyph_code = 38; //hyphenate words beginning with a capital letter
constexpr int output_penalty_code = 39; //penalty found at current page break
constexpr int max_dead_cycles_code = 40; //bound on consecutive dead cycles of output
constexpr int hang_after_code = 41; //hanging indentation changes after this many lines
constexpr int floating_penalty_code = 42; //penalty for insertions heldover after a split
constexpr int global_defs_code = 43; //override \global specifications
constexpr int cur_fam_code = 44; //current family
constexpr int escape_char_code = 45; //escape character for token output
constexpr int default_hyphen_char_code = 46; //value of \hyphenchar when a font is loaded
constexpr int default_skew_char_code = 47; //value of \skewchar when a font is loaded
constexpr int end_line_char_code = 48; //character placed at the right end of the buffer
constexpr int new_line_char_code = 49; //character that prints as |print_ln|
constexpr int language_code = 50; //current hyphenation table
constexpr int left_hyphen_min_code = 51; //minimum left hyphenation fragment size
constexpr int right_hyphen_min_code = 52; //minimum right hyphenation fragment size
constexpr int holding_inserts_code = 53; //do not remove insertion nodes from \box255
constexpr int error_context_lines_code = 54; //maximum intermediate line pairs shown
constexpr int int_pars = 55; //total number of integer parameters

int& del_code(halfword p); //del_code(#)==eqtb[del_code_base+#].int
int& count(halfword p); //count(#)==eqtb[count_base+#].int
int& int_par(halfword); //int_par(#)==eqtb[int_base+#].int //an integer parameter
int pretolerance(void); //pretolerance==int_par(pretolerance_code)
int& tolerance(void); //tolerance==int_par(tolerance_code)
int line_penalty(void); //line_penalty==int_par(line_penalty_code)
int hyphen_penalty(void); //hyphen_penalty==int_par(hyphen_penalty_code)
int ex_hyphen_penalty(void); //ex_hyphen_penalty==int_par(ex_hyphen_penalty_code)
int widow_penalty(void); //widow_penalty==int_par(widow_penalty_code)
int display_widow_penalty(void); //display_widow_penalty==int_par(display_widow_penalty_code)
int bin_op_penalty(void);//bin_op_penalty==int_par(bin_op_penalty_code)
int rel_penalty(void);//rel_penalty==int_par(rel_penalty_code)
int pre_display_penalty(void); //pre_display_penalty==int_par(pre_display_penalty_code)
int post_display_penalty(void); //post_display_penalty==int_par(post_display_penalty_code)
int broken_penalty(void); //broken_penalty==int_par(broken_penalty_code)
int club_penalty(void); //club_penalty==int_par(club_penalty_code)
int inter_line_penalty(void); //inter_line_penalty==int_par(inter_line_penalty_code)
int double_hyphen_demerits(void); //double_hyphen_demerits==int_par(double_hyphen_demerits_code)
int final_hyphen_demerits(void); //final_hyphen_demerits==int_par(final_hyphen_demerits_code)
int adj_demerits(void); //adj_demerits==int_par(adj_demerits_code)
int& mag(void); //mag==int_par(mag_code)
int delimiter_factor(void); //delimiter_factor==int_par(delimiter_factor_code)
int looseness(void); //looseness==int_par(looseness_code)
int& time(void); //time==int_par(time_code)
int& day(void); //day==int_par(day_code)
int& month(void); //month==int_par(month_code)
int& year(void); //year==int_par(year_code)
int show_box_breadth(void); //show_box_breadth==int_par(show_box_breadth_code)
int show_box_depth(void); //show_box_depth==int_par(show_box_depth_code)
int hbadness(void); //hbadness==int_par(hbadness_code)
int& vbadness(void); //vbadness==int_par(vbadness_code)
int pausing(void); //pausing==int_par(pausing_code)
int tracing_online(void); //tracing_online==int_par(tracing_online_code)
int tracing_macros(void); //tracing_macros==int_par(tracing_macros_code)
int tracing_commands(void); //tracing_commands==int_par(tracing_commands_code)
int tracing_lost_chars(void); //tracing_lost_chars==int_par(tracing_lost_chars_code)
int uc_hyph(void); //uc_hyph==int_par(uc_hyph_code)
int& max_dead_cycles(void); //max_dead_cycles==int_par(max_dead_cycles_code)
int& hang_after(void); //hang_after==int_par(hang_after_code)
int floating_penalty(void); //floating_penalty==int_par(floating_penalty_code)
int global_defs(void); //global_defs==int_par(global_defs_code)
int cur_fam(void); //cur_fam==int_par(cur_fam_code)
int& escape_char(void); //escape_char==int_par(escape_char_code)
int default_hyphen_char(void); //default_hyphen_char==int_par(default_hyphen_char_code)
int default_skew_char(void); //default_skew_char==int_par(default_skew_char_code)
int& end_line_char(void); //end_line_char==int_par(end_line_char_code)
int& new_line_char(void); //new_line_char==int_par(new_line_char_code)
int language(void); //language==int_par(language_code)
int left_hyphen_min(void); //left_hyphen_min==int_par(left_hyphen_min_code)
int right_hyphen_min(void); //right_hyphen_min==int_par(right_hyphen_min_code)
int error_context_lines(void); //error_context_lines==int_par(error_context_lines_code)
int holding_inserts(void); //holding_inserts==int_par(holding_inserts_code)
int& tracing_stats(void); //tracing_stats==int_par(tracing_stats_code)
int tracing_output(void); //tracing_output==int_par(tracing_output_code)

enum
{
	par_indent_code = 0, //indentation of paragraphs
	math_surround_code = 1, //space around math in text
	line_skip_limit_code = 2, //threshold for |line_skip| instead of |baseline_skip|
	hsize_code = 3, //line width in horizontal mode
	vsize_code = 4, //page height in vertical mode
	max_depth_code = 5, //maximum depth of boxes on main pages
	split_max_depth_code = 6, //maximum depth of boxes on split pages
	box_max_depth_code = 7, //maximum depth of explicit vboxes
	hfuzz_code = 8, //tolerance for overfull hbox messages
	vfuzz_code = 9, //tolerance for overfull vbox messages
	delimiter_shortfall_code = 10, //maximum amount uncovered by variable delimiters
	null_delimiter_space_code = 11, //blank space in null delimiters
	script_space_code = 12, //extra space after subscript or superscript
	pre_display_size_code = 13, //length of text preceding a display
	display_width_code = 14, //length of line for displayed equation
	display_indent_code = 15, //indentation of line for displayed equation
	overfull_rule_code = 16, //width of rule that identifies overfull hboxes
	hang_indent_code = 17, //amount of hanging indentation
	h_offset_code = 18, //amount of horizontal offset when shipping pages out
	v_offset_code = 19, //amount of vertical offset when shipping pages out
	emergency_stretch_code = 20 //reduces badnesses on final pass of line-breaking
};

constexpr int dimen_pars = 21; //total number of dimension parameters
constexpr int scaled_base = 5851; //dimen_base+dimen_pars;
constexpr int eqtb_size = 6106; // scaled_base+255; //largest subscript of |eqtb|

int& dimen(halfword); //dimen(#)==eqtb[scaled_base+#].sc
int& dimen_par(halfword); //dimen_par(#)==eqtb[dimen_base+#].sc //a scaled quantity
int par_indent(void); //par_indent==dimen_par(par_indent_code)
int math_surround(void); //math_surround==dimen_par(math_surround_code)
int line_skip_limit(void); //line_skip_limit==dimen_par(line_skip_limit_code)
int hsize(void); //hsize==dimen_par(hsize_code)
int vsize(void); //vsize==dimen_par(vsize_code)
int split_max_depth(void); //split_max_depth==dimen_par(split_max_depth_code)
int box_max_depth(void); //box_max_depth==dimen_par(box_max_depth_code)
int hfuzz(void); //hfuzz==dimen_par(hfuzz_code)
int& vfuzz(void); //vfuzz==dimen_par(vfuzz_code)
int delimiter_shortfall(void); //delimiter_shortfall==dimen_par(delimiter_shortfall_code)
int null_delimiter_space(void); //null_delimiter_space==dimen_par(null_delimiter_space_code)
int script_space(void); //script_space==dimen_par(script_space_code)
int pre_display_size(void); //pre_display_size==dimen_par(pre_display_size_code)
int display_width(void); //display_width==dimen_par(display_width_code)
int display_indent(void); //display_indent==dimen_par(display_indent_code)
int& overfull_rule(void); //overfull_rule==dimen_par(overfull_rule_code)
int hang_indent(void); //hang_indent==dimen_par(hang_indent_code)
int h_offset(void); //h_offset==dimen_par(h_offset_code)
int v_offset(void); //v_offset==dimen_par(v_offset_code)
int emergency_stretch(void); //emergency_stretch==dimen_par(emergency_stretch_code)
halfword& next(halfword); //next(#) == hash[#].lh //link for coalesced lists
halfword& text(halfword); //text(#) == hash[#].rh //string number for control sequence name
bool hash_is_full(void); //hash_is_full == (hash_used=hash_base) //test if all positions are occupied
halfword& font_id_text(halfword); //font_id_text(#) == text(font_id_base+#) //a frozen font identifier's name
quarterword& save_type(halfword); //save_type(#)==save_stack[#].hh.b0 //classifies a |save_stack| entry
quarterword& save_level(halfword); //save_level(#)==save_stack[#].hh.b1
halfword& save_index(halfword); //save_index(#)==save_stack[#].hh.rh

enum
{
	restore_old_value = 0, //|save_type| when a value should be restored later
	restore_zero = 1, //|save_type| when an undefined entry should be restored
	insert_token = 2, //|save_type| when a token is being saved for later use
	level_boundary=3 //|save_type| corresponding to beginning of group*/
};

enum
{
	bottom_level = 0, //group code for the outside world
	simple_group = 1, //group code for local structure only
	hbox_group = 2, //code for `\hbox\grp'
	adjusted_hbox_group = 3, //code for `\hbox\grp' in vertical mode
	vbox_group = 4, //code for `\vbox\grp'
	vtop_group = 5, //code for `\vtop\grp'
	align_group = 6, //code for `\halign\grp', `\valign\grp'
	no_align_group = 7, //code for `\noalign\grp'
	output_group = 8, //code for output routine
	math_group = 9, //code for, e.g., `\.//\char'136\grp'
	disc_group = 10, //code for `\discretionary\grp\grp\grp'
	insert_group = 11, //code for `\insert\grp', `\vadjust\grp'
	vcenter_group = 12, //code for `\vcenter\grp'
	math_choice_group = 13, //code for `\mathchoice\grp\grp\grp\grp'
	semi_simple_group = 14, //code for `\begingroup...\\endgroup'*/
	math_shift_group = 15, // //code for `\.//\$...\$'
	math_left_group = 16 //code for `\left...\\right'
};

int& saved(halfword); //saved(#)==save_stack[save_ptr+#].int

constexpr int cs_token_flag = 4095; //==@'7777 //amount added to the |eqtb| location in a

enum
{
	out_param_token = 0x100*out_param, //@'2400 //$2^8\cdot|out_param|$
	math_shift_token = 0x100*math_shift, //@'1400 //$2^8\cdot|math_shift|$
	tab_token = 0x100*tab_mark, //@'2000 //$2^8\cdot|tab_mark|$
	space_token = 0x100*spacer+' ', // @'5040 //$2^8\cdot|spacer|+|" "|$
	left_brace_token = 0x100*left_brace, //@'0400 //$2^8\cdot|left_brace|$
	right_brace_token = 0x100*right_brace, //@'1000 //$2^8\cdot|right_brace|$
	other_token = 0x100*other_char, //@'6000 //$2^8\cdot|other_char|$
	zero_token = other_token+'0',//other_token+"0" //zero, the smallest digit
	right_brace_limit = 0x100*(right_brace+1), //@'1400 //$2^8\cdot(|right_brace|+1)$
	left_brace_limit = 0x100*(left_brace+1), //@'1000 //$2^8\cdot(|left_brace|+1)$
	match_token = 0x100*match,//@'6400 //$2^8\cdot|match|$
	end_match_token = 0x100*end_match, // @'7000 //$2^8\cdot|end_match|$
	octal_token = other_token+'\'', //apostrophe, indicates an octal constant
	hex_token = other_token+'\"', //double quote, indicates a hex constant
	alpha_token = other_token+'`', //reverse apostrophe, precedes alpha constants
	point_token = other_token+'.', //decimal point
	continental_point_token = other_token+',', //decimal point, Eurostyle
	letter_token = 0x100*letter, //@'5400 //$2^8\cdot|letter|$
	A_token = letter_token+'A', //the smallest special hex digit
	other_A_token = other_token+'A' //special hex digit of type |other_char|
};

extern quarterword &state; //==cur_input.state_field //current scanner state
extern quarterword &index; //==cur_input.index_field //reference for buffer information
extern halfword &start; //==cur_input.start_field //starting position in |buffer|
extern halfword &limit; //==cur_input.limit_field //end of current line in |buffer|
extern std::string &name; //==cur_input.name_field //name of the current file

enum
{
	token_list = 0, //|state| code when scanning a token list
	mid_line = 1, //|state| code when scanning a line of characters
	skip_blanks = 17, //2+max_char_code //|state| code when ignoring blanks
	new_line = 33 //3+max_char_code+max_char_code //|state| code at start of line
};

inline bool terminal_input(const std::string &name) { return name == ""; } //terminal_input==(name=0) //are we reading from the terminal?
alphafile& cur_file(void); //cur_file==input_file[index] //the current |alpha_file| variable

enum
{
	skipping = 1, //|scanner_status| when passing conditional text
	defining = 2, //|scanner_status| when reading a macro definition
	matching = 3, //|scanner_status| when reading macro arguments
	aligning = 4, //|scanner_status| when reading an alignment preamble
	absorbing = 5 //|scanner_status| when reading a balanced text
};

inline quarterword &token_type = index; //token_type==index //type of current token list
inline halfword &param_start = limit; //param_start==limit //base of macro parameters in |param_stack|

enum
{
	parameter = 0, //|token_type| code for parameter
	u_template = 1, //|token_type| code for \<u_j> template
	v_template = 2, //|token_type| code for \<v_j> template
	backed_up = 3, //|token_type| code for text to be reread
	inserted = 4, //|token_type| code for inserted texts
	macro = 5, //|token_type| code for defined control sequences
	output_text = 6, //|token_type| code for output routines
	every_par_text = 7, //|token_type| code for \everypar
	every_math_text = 8, //|token_type| code for \everymath
	every_display_text = 9, //|token_type| code for \everydisplay
	every_hbox_text = 10, //|token_type| code for \everyhbox
	every_vbox_text = 11, //|token_type| code for \everyvbox
	every_job_text = 12, //|token_type| code for \everyjob
	every_cr_text = 13, //|token_type| code for \everycr
	mark_text = 14, //|token_type| code for \topmark, etc.
	write_text = 15 //|token_type| code for \write
};

constexpr int no_expand_flag = 257; //this characterizes a special variant of |relax|
inline bool end_line_char_inactive() { return end_line_char() < 0 || end_line_char() > 255; }

enum
{
	top_mark_code = 0, //the mark in effect at the previous page break
	first_mark_code = 1, //the first mark between |top_mark| and |bot_mark|
	bot_mark_code = 2, //the mark in effect at the current page break
	split_first_mark_code = 3, //the first mark found by \vsplit
	split_bot_mark_code = 4 //the last mark found by \vsplit
};

extern halfword &top_mark; //==cur_mark[top_mark_code]
extern halfword &first_mark; //==cur_mark[first_mark_code]
extern halfword &bot_mark; //==cur_mark[bot_mark_code]
extern halfword &split_first_mark; //==cur_mark[split_first_mark_code]
extern halfword &split_bot_mark; //==cur_mark[split_bot_mark_code]

enum 
{
	int_val = 0, //integer values
	dimen_val = 1, //dimension values
	glue_val = 2, //glue specifications
	mu_val = 3, //math glue specifications
	ident_val = 4, //font identifier
	tok_val = 5 //token lists
};

void scanned_result(int, char); //scanned_result_end(#)==cur_val_level:=#;@+end scanned_result(#)==@+begin cur_val:=#;scanned_result_end

constexpr int input_line_no_code = 3; //glue_val+1 //code for \inputlineno
constexpr int badness_code = 4; //glue_val+2 //code for \badness
constexpr int max_dimen = 1073741823; //=@'7777777777 //$2^//30-1$
constexpr int infinity = 2147483647; //==@'17777777777 //the largest positive value that \TeX\ knows
constexpr int default_rule = 26214; //0.4\thinspace pt
constexpr int number_code = 0; // //command code for \number
constexpr int roman_numeral_code = 1; //command code for \romannumeral
constexpr int string_code = 2; //command code for \string
constexpr int meaning_code = 3; //command code for \meaning
constexpr int font_name_code = 4; //command code for \fontname
constexpr int job_name_code = 5; //command code for \jobname

enum
{
	just_open = 1, //newly opened, first line not yet read
	closed = 2 //not open, or at end of file
};

constexpr int if_char_code = 0; // `\if' 
constexpr int if_cat_code = 1; // `\ifcat' 
constexpr int if_int_code = 2; // `\ifnum' 
constexpr int if_dim_code = 3; // `\ifdim' 
constexpr int if_odd_code = 4; // `\ifodd' 
constexpr int if_vmode_code = 5; // `\ifvmode' 
constexpr int if_hmode_code = 6; // `\ifhmode' 
constexpr int if_mmode_code = 7; // `\ifmmode' 
constexpr int if_inner_code = 8; // `\ifinner' 
constexpr int if_void_code = 9; // `\ifvoid' 
constexpr int if_hbox_code = 10; // `\ifhbox' 
constexpr int if_vbox_code = 11; // `\ifvbox' 
constexpr int ifx_code = 12; // `\ifx' 
constexpr int if_eof_code = 13; // `\ifeof' 
constexpr int if_true_code = 14; // `\iftrue' 
constexpr int if_false_code = 15; // `\iffalse' 
constexpr int if_case_code = 16; // `\ifcase' 
int& if_line_field(halfword); //if_line_field(#)==mem[#+1].int
constexpr int if_code = 1; //code for \if... being evaluated
constexpr int fi_code = 2; //code for \fi
constexpr int else_code = 3; //code for \else
constexpr int or_code = 4; //code for \or
const std::string TEX_area = "TeXinputs:";
const std::string TEX_font_area = "TeXfonts:";

void append_to_name(int&, char); //append_to_name(#)==begin c:=#; incr(k);
constexpr int format_default_length = 20; //length of the |TEX_format_default| string
constexpr int format_area_length = 11; //length of its area part
constexpr int format_ext_length = 4; //length of its `\.//.fmt' part
const std::string format_extension = ".fmt"; //the extension, as a \.//WEB constant

enum
{
	no_tag = 0, //vanilla character
	lig_tag = 1, //character has a ligature/kerning program
	list_tag = 2, //character has a successor in a charlist
	ext_tag = 3 //character is extensible
};

constexpr int stop_flag = 128; //==qi(128) //value indicating `\.//STOP' in a lig/kern program
constexpr int kern_flag = 128; //==qi(128) //op code for a kern step
quarterword skip_byte(fourquarters); // skip_byte(#)==#.b0
quarterword next_char(fourquarters); //next_char(#)==#.b1
quarterword op_byte(fourquarters); //op_byte(#)==#.b2
quarterword rem_byte(fourquarters); //rem_byte(#)==#.b3
quarterword ext_top(fourquarters); //ext_top(#)==#.b0 //|top| piece in a recipe
quarterword ext_mid(fourquarters); //ext_mid(#)==#.b1 //|mid| pie1ce in a recipe
quarterword ext_bot(fourquarters); //ext_bot(#)==#.b2 //|bot| piece in a recipe
quarterword ext_rep(fourquarters); //ext_rep(#)==#.b3 //|rep| piece in a recipe
constexpr int slant_code = 1;
constexpr int space_code = 2;
constexpr int space_stretch_code = 3;
constexpr int space_shrink_code = 4;
constexpr int x_height_code = 5;
constexpr int quad_code = 6;
constexpr int extra_space_code = 7;
constexpr int non_char = 256; //==qi(256) //a |halfword| code that can't match a real character
constexpr int non_address = 0; //a spurious |bchar_label|

fourquarters char_info(internalfontnumber, smallnumber); //char_info(#)==font_info[char_base[#]+char_info_end //char_info_end(#)==#].qqqq
int char_width(internalfontnumber, fourquarters); //char_width(#)==font_info[width_base[#]+char_width_end //char_width_end(#)==#.b0].sc
bool char_exists(fourquarters); //char_exists(#)==(#.b0>min_quarterword)
int char_italic(internalfontnumber, fourquarters); //char_italic(#)==font_info[italic_base[#]+char_italic_end //char_italic_end(#)==(qo(#.b2)) div 4].sc
int char_height(internalfontnumber, fourquarters); //char_height(#)==font_info[height_base[#]+char_height_end //char_height_end(#)==(#) div 16].sc
int char_depth(internalfontnumber, fourquarters); //char_depth(#)==font_info[depth_base[#]+char_depth_end //char_depth_end(#)==(#) mod 16].sc
int char_tag(fourquarters);//char_tag(#)==((qo(#.b2)) mod 4)
int char_kern(internalfontnumber, fourquarters); //char_kern(#)==font_info[kern_base[#]+char_kern_end //char_kern_end(#)==256*op_byte(#)+rem_byte(#)].sc
int lig_kern_start(internalfontnumber, fourquarters); //lig_kern_start(#)==lig_kern_base[#]+rem_byte //beginning of lig/kern program
int lig_kern_restart(internalfontnumber, fourquarters); //lig_kern_restart(#)==lig_kern_base[#]+lig_kern_restart_end //lig_kern_restart_end(#)==256*op_byte(#)+rem_byte(#)+0x80'00-kern_base_offset
int& param(smallnumber, internalfontnumber); //param(#)==font_info[#+param_end //param_end(#)==param_base[#]].sc
int& slant(internalfontnumber); //slant==param(slant_code) //slant to the right, per unit distance upward
int& space(internalfontnumber); //space==param(space_code) //normal space between words
int& space_stretch(internalfontnumber); //space_stretch==param(space_stretch_code) //stretch between words
int& space_shrink(internalfontnumber); //space_shrink==param(space_shrink_code) //shrink between words
int& x_height(internalfontnumber); //x_height==param(x_height_code) //one ex
int& quad(internalfontnumber); //quad==param(quad_code) //one em
int& extra_space(internalfontnumber); //extra_space==param(extra_space_code) //additional space at end of sentence

enum
{
	set1 = 128, //typeset a character and move right
	set_rule = 132, //typeset a rule and move right
	put_rule = 137, //typeset a rule
	bop = 139, //beginning of page
	eop = 140, //ending of page
	push = 141, //save the current positions
	pop = 142, //restore previous positions
	right1 = 143, //move right
	down1 = 157, //move down
	fnt_num_0 = 171, //set current font to 0
	fnt1 = 235, //set current font
	xxx1 = 239, //extension to \.//DVI primitives
	xxx4 = 242, //potentially long extension to \.//DVI primitives
	fnt_def1 = 243, //define the meaning of a font number
	pre = 247, //preamble
	post = 248, //postamble beginning
	post_post = 249 //postamble ending
};

constexpr int id_byte = 2; //identifies the kind of \.//DVI files described here

int& location(halfword); //location(#)==mem[#+2].int //\.//DVI byte number for a movement command

enum
{
	y_here = 1, //|info| when the movement entry points to a |y| command
	z_here = 2, //|info| when the movement entry points to a |z| command
	yz_OK = 3, //|info| corresponding to an unconstrained \\//down command
	y_OK = 4, //|info| corresponding to a \\//down that can't become a |z|
	z_OK = 5, //|info| corresponding to a \\//down that can't become a |y|
	d_fixed = 6 //|info| corresponding to a \\//down that can't change*/
};

enum
{
	none_seen = 0, //no |y_here| or |z_here| nodes have been encountered yet
	y_seen = 6, //we have seen |y_here| but not |z_here|
	z_seen = 12 //we have seen |z_here| but not |y_here|
};

float vet_glue(float);/*@ billion==float_constant(1000000000) vet_glue(#)== glue_temp:=#;*/

enum
{
	exactly = 0, //a box dimension is pre-specified
	additional = 1 //a box dimension is increased from the natural one
};

halfword nucleus(halfword); //nucleus(#)==#+1 //the |nucleus| field of a noad
halfword supscr(halfword); //supscr(#)==#+2 //the |supscr| field of a noad
halfword subscr(halfword); //subscr(#)==#+3 //the |subscr| field of a noad
halfword& math_type(halfword); //math_type==link //a |halfword| in |mem|
quarterword& fam(halfword); //fam==font //a |quarterword| in |mem|
enum
{
	math_char = 1, //|math_type| when the attribute is simple
	sub_box = 2, //|math_type| when the attribute is a box
	sub_mlist = 3, //|math_type| when the attribute is a formula
	math_text_char=4 //|math_type| when italic correction is dubious
};

constexpr int ord_noad = 16; //unset_node+3 //|type| of a noad classified Ord
constexpr int op_noad = 17; //ord_noad+1 //|type| of a noad classified Op
constexpr int bin_noad = 18; //ord_noad+2 //|type| of a noad classified Bin
constexpr int rel_noad = 19;//ord_noad+3 //|type| of a noad classified Rel
constexpr int open_noad = 20; //ord_noad+4 //|type| of a noad classified Ope
constexpr int close_noad = 21; //ord_noad+5 //|type| of a noad classified Clo
constexpr int punct_noad = 22; //ord_noad+6 //|type| of a noad classified Pun
constexpr int inner_noad = 23; //ord_noad+7 //|type| of a noad classified Inn
constexpr int limits = 1; //|subtype| of |op_noad| whose scripts are to be above, below
constexpr int no_limits = 2; //|subtype| of |op_noad| whose scripts are to be normal
halfword left_delimiter(halfword); //left_delimiter(#)==#+4 //first delimiter field of a noad
halfword right_delimiter(halfword); //right_delimiter(#)==#+5 //second delimiter field of a fraction noad
constexpr int radical_noad = 24; //inner_noad+1 //|type| of a noad for square roots
constexpr int fraction_noad = 25; //radical_noad+1 //|type| of a noad for generalized fractions
quarterword& small_fam(halfword); //small_fam(#)==mem[#].qqqq.b0 //|fam| for ``small'' delimiter
quarterword& small_char(halfword);//small_char(#)==mem[#].qqqq.b1 //|character| for ``small'' delimiter
quarterword& large_fam(halfword); //large_fam(#)==mem[#].qqqq.b2 //|fam| for ``large'' delimiter
quarterword& large_char(halfword); //large_char(#)==mem[#].qqqq.b3 //|character| for ``large'' delimiter
int& thickness(halfword); //thickness==width //|thickness| field in a fraction noad
constexpr int default_code = 1073741824;//==@'10000000000 //denotes |default_rule_thickness|
halfword numerator(halfword); //numerator==supscr //|numerator| field in a fraction noad
halfword denominator(halfword); //denominator==subscr //|denominator| field in a fraction noad
constexpr int under_noad = 26; //fraction_noad+1 //|type| of a noad for underlining
constexpr int over_noad = 27; // under_noad+1 //|type| of a noad for overlining
constexpr int accent_noad = 28; //over_noad+1 //|type| of a noad for accented subformulas
halfword accent_chr(halfword); //accent_chr(#)==#+4 //the |accent_chr| field of an accent noad
constexpr int vcenter_noad = 29; //accent_noad+1 //|type| of a noad for \vcenter
constexpr int left_noad = 30; //vcenter_noad+1 //|type| of a noad for \left
constexpr int right_noad = 31; //left_noad+1 //|type| of a noad for \right
halfword delimiter(halfword); //delimiter==nucleus //|delimiter| field in left and right noads

enum
{
	display_style = 0, //|subtype| for \displaystyle
	text_style = 2, //|subtype| for \textstyle
	script_style = 4, //|subtype| for \scriptstyle
	script_script_style = 6 //|subtype| for \scriptscriptstyle
};

halfword& display_mlist(halfword); //display_mlist(#)==info(#+1) //mlist to be used in display style
halfword& text_mlist(halfword); //text_mlist(#)==link(#+1) //mlist to be used in text style
halfword& script_mlist(halfword); //script_mlist(#)==info(#+2) //mlist to be used in script style
halfword& script_script_mlist(halfword); //script_script_mlist(#)==link(#+2) //mlist to be used in scriptscript style

enum
{
	text_size = 0, //size code for the largest size in a family
	script_size = 16, //size code for the medium size in a family
	script_script_size = 32 //size code for the smallest size in a family
};

int mathsy(smallnumber, smallnumber); //mathsy(#)==font_info[#+param_base[mathsy_end //mathsy_end(#)==fam_fnt(2+#)]].sc
int math_x_height(smallnumber); //math_x_height==mathsy(5) //height of `\.x'
int math_quad(smallnumber); //math_quad==mathsy(6) //\.//18mu
int num1(smallnumber); //num1==mathsy(8) //numerator shift-up in display styles
int num2(smallnumber); //num2==mathsy(9) //numerator shift-up in non-display, non-\atop
int num3(smallnumber); //num3==mathsy(10) //numerator shift-up in non-display \atop
int denom1(smallnumber); //denom1==mathsy(11) //denominator shift-down in display styles
int denom2(smallnumber); //denom2==mathsy(12) //denominator shift-down in non-display styles
int sup1(smallnumber); //sup1==mathsy(13) //superscript shift-up in uncramped display style
int sup2(smallnumber);//sup2==mathsy(14) //superscript shift-up in uncramped non-display
int sup3(smallnumber);//sup3==mathsy(15) //superscript shift-up in cramped styles
int sub1(smallnumber);//sub1==mathsy(16) //subscript shift-down if superscript is absent
int sub2(smallnumber);//sub2==mathsy(17) //subscript shift-down if superscript is present
int sup_drop(smallnumber); //sup_drop==mathsy(18) //superscript baseline below top of large box
int sub_drop(smallnumber); //sub_drop==mathsy(19) //subscript baseline below bottom of large box
int delim1(smallnumber); //delim1==mathsy(20) //size of \atopwithdelims delimiters
int delim2(smallnumber); //delim2==mathsy(21) //size of \atopwithdelims delimiters in non-displays
int axis_height(smallnumber); //axis_height==mathsy(22) //height of fraction lines above the baseline

constexpr int total_mathsy_params = 22;
constexpr int total_mathex_params = 13;

int mathex(smallnumber); //mathex(#)==font_info[#+param_base[fam_fnt(3+cur_size)]].sc
int default_rule_thickness(void); //default_rule_thickness==mathex(8) //thickness of \over bars
int big_op_spacing1(void); //big_op_spacing1==mathex(9) //minimum clearance above a displayed op
int big_op_spacing2(void); //big_op_spacing2==mathex(10) //minimum clearance below a displayed op
int big_op_spacing3(void); //big_op_spacing3==mathex(11) //minimum baselineskip above displayed op
int big_op_spacing4(void); //big_op_spacing4==mathex(12) //minimum baselineskip below displayed op
int big_op_spacing5(void); //big_op_spacing5==mathex(13) //padding above and below displayed limits

constexpr int cramped = 1; //add this to an uncramped style if you want to cramp it

inline int cramped_style(int c) { return 2*(c/2)+cramped; } //cramp the style
inline int sub_style(int c) { return 2*(c/4)+script_style+cramped; } //smaller and cramped
inline int sup_style(int c) { return 2*(c/4)+script_style+c%2; } //smaller
inline int num_style(int c) { return c+2-2*(c/6); } //smaller unless already script-script
inline int denom_style(int c) { return 2*(c/2)+cramped+2-2*(c/6); } //smaller, cramped

int& new_hlist(halfword); //new_hlist(#)==mem[nucleus(#)].int //the translation of an mlist

const std::string math_spacing = "0234000122*4000133**3**344*0400400*000000234000111*1111112341011";

int& u_part(halfword); //u_part(#)==mem[#+height_offset].int //pointer to \<u_j> token list
int&v_part(halfword); //v_part(#)==mem[#+depth_offset].int //pointer to \<v_j> token list
halfword& extra_info(halfword); //extra_info(#)==info(#+list_offset) //info to remember during template
halfword& preamble(void); //preamble==link(align_head) //the current preamble list

constexpr int span_code = 256; //distinct from any character
constexpr int cr_code = 257; //distinct from |span_code| and from any character
constexpr int cr_cr_code = 258; //cr_code+1 //this distinguishes \crcr from \cr
constexpr int end_template_token = cs_token_flag+frozen_end_template;
constexpr int tight_fit = 3; //fitness classification for lines shrinking 0.5 to 1.0 of their
constexpr int loose_fit = 1; //fitness classification for lines stretching 0.5 to 1.0 of their
constexpr int very_loose_fit = 0; //fitness classification for lines stretching more than
constexpr int decent_fit = 2; //fitness classification for all other lines

quarterword& fitness(halfword); //fitness==subtype //|very_loose_fit..tight_fit| on final line for this break
halfword& break_node(halfword); //break_node==rlink //pointer to the corresponding passive node
halfword& line_number(halfword); //line_number==llink //line that begins at this breakpoint
int& total_demerits(halfword); //total_demerits(#)==mem[#+2].int //the quantity that \TeX\ minimizes

constexpr int unhyphenated = 0; //the |type| of a normal active break node
constexpr int hyphenated = 1; //the |type| of an active node that breaks at a |disc_node|
constexpr int delta_node = 2; //|type| field in a delta node

void copy_to_cur_active(void); //copy_to_cur_active(#)==cur_active_width[#]:=active_width[#]
void update_width(halfword); //update_width(#)==cur_active_width[#]:=cur_active_width[#]+mem[r+#].sc

constexpr int awful_bad = 1073741823; //=@'7777777777 //more than a billion demerits
constexpr int deplorable = 100000; //more than |inf_bad|, but less than |awful_bad|

void set_break_width_to_background(void); //set_break_width_to_background(#)==break_width[#]:=background[#]
void convert_to_break_width(halfword prev_r); // convert_to_break_width(#)==@|mem[prev_r+#].sc:=mem[prev_r+#].sc  -cur_active_width[#]+break_width[#]
void store_break_width(void); // store_break_width(#)==active_width[#]:=break_width[#]
void new_delta_to_break_width(halfword); //new_delta_to_break_width(#)==@|mem[q+#].sc:=break_width[#]-cur_active_width[#]
void new_delta_from_break_width(halfword); //new_delta_from_break_width(#)==@|mem[q+#].sc:= cur_active_width[#]-break_width[#]
void combine_two_deltas(halfword, halfword); //combine_two_deltas(#)==@|mem[prev_r+#].sc:=mem[prev_r+#].sc+mem[r+#].sc
void downdate_width(halfword); //downdate_width(#)==@|cur_active_width[#]:=cur_active_width[#]-mem[prev_r+#].sc
void update_active(halfword); //update_active(#)==active_width[#]:=active_width[#]+mem[r+#].sc
void store_background(void); //store_background(#)==active_width[#]:=background[#]

extern scaled &act_width; //act_width==active_width[1] //length from first active node to current node

halfword& trie_link(halfword); //@ trie_link(#)==trie[#].rh //``downward'' link in a trie
halfword& trie_back(halfword); //trie_back(#)==trie[#].lh //backward links in |trie| holes
quarterword& trie_char(halfword); //trie_char(#)==trie[#].b1 //character matched at this trie location
quarterword& trie_op(halfword); //trie_op(#)==trie[#].b0 //program for hyphenation at this trie location

void set_cur_lang(void); //set_cur_lang==if language<=0 then cur_lang:=0

extern triepointer &trie_root; //trie_root==trie_l[0] //root of the linked trie
extern triepointer *trie_ref; //trie_ref==trie_hash //where linked trie families go into |trie|

enum
{
	inserting = 0, //an insertion class that has not yet overflowed
	inserts_only = 1,
	box_there = 2 //|page_contents| when a box or rule has been contributed
};

constexpr int split_up = 1; //an overflowed insertion class

halfword& broken_ptr(halfword);//broken_ptr(#)==link(#+1)
halfword& broken_ins(halfword p); //broken_ins(#)==info(#+1) //this insertion might break at |broken_ptr|
halfword& last_ins_ptr(halfword p); //last_ins_ptr(#)==link(#+2) //the most recent insertion for this |subtype|
halfword& best_ins_ptr(halfword); //best_ins_ptr(#)==info(#+2) //the optimum most recent insertion

extern scaled &page_goal; //desired height of information on page being built
extern scaled &page_total; //height of the current page
extern scaled &page_shrink; //shrinkability of the current page
extern scaled &page_depth; //depth of the current page
extern halfword &contrib_tail; //contrib_tail==nest[0].tail_field //tail of the contribution list

enum
{
	fil_code = 0, //identifies \hfil and \vfil
	fill_code = 1, //identifies \hfill and \vfill
	ss_code = 2, //identifies \hss and \vss
	fil_neg_code = 3, //identifies \hfilneg and \vfilneg
	skip_code = 4, //identifies \hskip and \vskip
	mskip_code = 5 //identifies \mskip
};

enum
{
	box_flag = 1073741824, //@'10000000000 //context code for `\setbox0'
	ship_out_flag = 1073742336, //=box_flag+512 //context code for `\shipout'
	leader_flag = 1073742337//=box_flag+513 //context code for `\leaders'*/
};

enum
{
	box_code = 0, //|chr_code| for `\box'
	copy_code = 1, //|chr_code| for `\copy'
	last_box_code = 2, //|chr_code| for `\lastbox'
	vsplit_code = 3, //|chr_code| for `\vsplit'
	vtop_code = 4 //|chr_code| for `\vtop'
};

bool fam_in_range(void); //fam_in_range==((cur_fam>=0)and(cur_fam<16))

enum
{
	above_code = 0, // `\above' 
	over_code = 1, // `\over' 
	atop_code = 2, // `\atop' 
	delimited_code = 3 // `\abovewithdelims', etc.
};

enum
{
	char_def_code = 0, //|shorthand_def| for \chardef
	math_char_def_code = 1, //|shorthand_def| for \mathchardef
	count_def_code = 2, //|shorthand_def| for \countdef
	dimen_def_code = 3, //|shorthand_def| for \dimendef
	skip_def_code = 4, //|shorthand_def| for \skipdef
	mu_skip_def_code = 5, //|shorthand_def| for \muskipdef
	toks_def_code = 6 //|shorthand_def| for \toksdef
};

enum
{
	show_code = 0, // \show 
	show_box_code = 1, // \showbox 
	show_the_code = 2, // \showthe 
	show_lists = 3 // \showlists
};
 
enum
{
	open_node = 0, //|subtype| in whatsits that represent files to \openout
	write_node = 1, //|subtype| in whatsits that represent things to \write
	close_node = 2, //|subtype| in whatsits that represent streams to \closeout
	special_node = 3, //|subtype| in whatsits that represent \special things
	language_node = 4, //|subtype| in whatsits that change the current language
	immediate_code = 4, //command modifier for \immediate
	set_language_code = 5 //command modifier for \setlanguage
};

halfword& what_lang(halfword); //what_lang(#)==link(#+1) //language number, in the range |0..255|
quarterword& what_lhm(halfword); //what_lhm(#)==type(#+1) //minimum left fragment, in the range |1..63|
quarterword& what_rhm(halfword); //what_rhm(#)==subtype(#+1) //minimum right fragment, in the range |1..63|*/
halfword& write_tokens(halfword); //write_tokens(#) == link(#+1) //reference count of token list to write
halfword& write_stream(halfword); //write_stream(#) == info(#+1) //stream number (0 to 17)
halfword& open_name(halfword); //open_name(#) == link(#+1) //string number of file name to open
halfword& open_area(halfword); //open_area(#) == info(#+2) //string number of file area for |open_name|
halfword& open_ext(halfword); //open_ext(#) == link(#+2) //string number of file extension for |open_name|

///// ailleurs


//str_room(#) == //make sure that the pool hasn't overflowed //begin if pool_ptr+# > pool_size then  overflow("pool size",pool_size-init_pool_ptr);@:TeX capacity exceeded pool size}{\quad pool size@>  end => overflow.cpp
/*check_interrupt==begin if interrupt<>0 then pause_for_instructions; => pauseforinstruction.cpp*/
//read_sixteen(#)==begin #:=fbyte; if #>127 then abort;  fget; #:=#*256+fbyte;  end  => readfontinfo.cpp
/*free_avail(#)== //single-word node liberation begin link(#):=avail; avail:=#;  end => getavail.cpp
fast_get_avail(#)==@t@>@;@/*/
//adjust_space_factor==@t@>@;@/ => maincontrol.cpp
/*mu_mult(#)==nx_plus_y(n,#,xn_over_d(#,f,@'200000)) => multandadd.cpp
nx_plus_y(#)==mult_and_add(#,@'7777777777)
mult_integers(#)==mult_and_add(#,0,@'17777777777)*/
//add_token_ref(#)==incr(token_ref_count(#)) //new reference to a token list => copynodelist.cpp
/*global==(a>=4)
define(#)==if global then geq_define(#)@+else eq_define(#) => eqdefine.cpp
word_define(#)==if global then geq_word_define(#)@+else eq_word_define(#) => eqworddefine.cpp*/
/*@ print_plus_end(#)==print(#);@+end => printtotals.cpp
print_plus(#)==if page_so_far[#]<>0 then*/
/*node_list_display(#)==begin append_char('.'); show_node_list(#); flush_char;  => shownodelist.cpp
  end {|str_room| need not be checked; see |show_box| below} */
/*check_full_save_stack==if save_ptr>max_save_stack then begin max_save_stack:=save_ptr;  if max_save_stack>save_size-6 then overflow('save size',save_size); end  => overflow.cpp */
//begin_pseudoprint==begin l:=tally; tally:=0; selector:=pseudo;  trick_count:=1000000;   end => showcontext.cpp
//set_trick_count==begin first_count:=tally;   trick_count:=tally+1+error_line-half_error_line;   if trick_count<error_line then trick_count:=error_line;   end  => showcontext.cpp
//push_input==@t@> //enter a new input level, save the old => pushinput.cpp
//pop_input==@t@> //leave an input level, re-enter the old => popinput.h
/*back_list(#)==begin_token_list(#,backed_up) //backs up a simple token list => begintokenlist.cpp
ins_list(#)==begin_token_list(#,inserted) //inserts a simple token list*/
//any_state_plus(#) == mid_line+#,skip_blanks+#,new_line+# => getnext.cpp
//add_delims_to(#)==#+math_shift,#+tab_mark,#+mac_param, => getnext.cpp
//is_hex(#)==(((#>="0")and(#<="9"))or((#>="a")and(#<="f"))) => getnext.cpp
/*hex_to_cur_chr== .. => remplacé dans getnext.cpp */
//store_new_token(#)==begin q:=get_avail; link(p):=q; info(q):=#; => getavail.cpp
//fast_store_new_token(#)==begin fast_get_avail(q); link(p):=q; info(q):=#; => getavail.cpp
//scan_normal_dimen==scan_dimen(false,false,false) => scandimen.cpp
/*set_conversion_end(#)== denom:=#; end
set_conversion(#)==@+begin num:=#; set_conversion_end => scandimen*/
// get_x_token_or_active_char==@t@>@; => conditional.cpp
//pack_cur_name==pack_file_name(cur_name,cur_area,cur_ext) => packfilename.cpp
//ensure_dvi_open==if output_file_name=0 then => shipout.cpp
//start_font_error_message==print_err("Font "); sprint_cs(u); => readfontinfo.cpp
//store_four_quarters(#)==begin fget; a:=fbyte; qw.b0:=qi(a); => readfontinfo.cpp
// check_byte_range(#)==begin if (#<bc)or(#>ec) then abort@+end => readfontinfo.cpp
// current_character_being_worked_on==k+bc-fmem_ptr => readfontinfo.cpp
// store_scaled(#)==begin fget; a:=fbyte; fget; b:=fbyte; => readfontinfo.cpp
// check_existence(#)==@t@>@;@/  => readfontinfo.cpp
//dvi_out(#)==@+begin dvi_buf[dvi_ptr]:=#; incr(dvi_ptr); if dvi_ptr=dvi_limit then dvi_swap;  end => dviswap.cpp
/* synch_h==if cur_h<>dvi_h then  => movement.cpp
synch_v==if cur_v<>dvi_v then*/
//vpack(#)==vpackage(#,max_dimen) //special case of unconstrained depth => vpackage.cpp
/*scripts_allowed(#)==(type(#)>=ord_noad)and(type(#)<left_noad) => subsup.cpp */
// choose_mlist(#)==begin p:=#(q); #(q):=null;@+end => mlisttohlist.cpp
//check_shrinkage(#)==if (shrink_order(#)<>normal)and(shrink(#)<>0) then => linebreak.cpp
//kern_break==begin if not is_char_node(link(cur_p)) and auto_breaking then => linebreak.cpp
//set_cur_r==begin if j<n then cur_r:=qi(hu[j+1])@+else cur_r:=bchar; => reconstitute.cpp
//@ wrap_lig(#)==if ligature_present then => reconstitute.cpp
//pop_lig_stack==begin if lig_ptr(lig_stack)>null then => reconstitute.cpp
//advance_major_tail==begin major_tail:=link(major_tail); incr(r_count); => hyphenate.cpp
/*dump_wd(#)==begin fmt_file^:=#; put(fmt_file);@+end => storefmtfile.cpp
dump_int(#)==begin fmt_file^.int:=#; put(fmt_file);@+end
dump_hh(#)==begin fmt_file^.hh:=#; put(fmt_file);@+end
@ dump_four_ASCII==
dump_qqqq(#)==begin fmt_file^.qqqq:=#; put(fmt_file);@+end*/
/*undump_wd(#)==begin get(fmt_file); #:=fmt_file^;@+end => loadfmtfile.cpp
undump_int(#)==begin get(fmt_file); #:=fmt_file^.int;@+end
undump_hh(#)==begin get(fmt_file); #:=fmt_file^.hh;@+end
undump_end_end(#)==#:=x;@+end
undump_end(#)==(x>#) then goto bad_fmt@+else undump_end_end
undump(#)==begin undump_int(x); if (x<#) or undump_end
undump_size_end_end(#)==too_small(#)@+else undump_end_end
undump_size_end(#)==if x># then undump_size_end_end
undump_size(#)==begin undump_int(x);
@ undump_four_ASCII==
undump_qqqq(#)==begin get(fmt_file); #:=fmt_file^.qqqq;@+end*/
//active_height==active_width //new name for the six distance variables => vertbreak.cpp
//set_height_zero(#)==active_height[#]:=0 //initialize the height to zero  => vertbreak.cpp
//cur_height==active_height[1] //the natural height => vertbreak.cpp
/*pack_lig(#)== //the parameter is either |rt_hit| or |false| => maincontrol.cpp
wrapup(#)==if cur_l<non_char then*/
//set_page_so_far_zero(#)==page_so_far[#]:=0 => freezepagespecs.cpp
/*any_mode(#)==vmode+#,hmode+#,mmode+# //for mode-independent commands => maincontrol.cpp
non_math(#)==vmode+#,hmode+#*/
/*end_write_token==cs_token_flag+end_write => writeout.cpp */

#endif

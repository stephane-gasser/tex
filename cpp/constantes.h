#ifndef CONSTANTES_H
#define CONSTANTES_H

#include "tex.h"

constexpr char banner[] ="This is TeX, Version 3.14159265"; //printed when \TeX\ starts
/*mtype==t@&y@&p@&e //this is a \.//WEB coding trick:
start_of_TEX=1 //go here when \TeX's variables are initialized
end_of_TEX=9998 //go here to close files and terminate gracefully
final_end=9999 //this label marks the ending of the program
debug==@// //change this to `$\\//debug\equiv\null$' when debugging
gubed==@t@>@ //change this to `$\\//gubed\equiv\null$' when debugging
stat==@// //change this to `$\\//stat\equiv\null$' when gathering
tats==@t@>@ //change this to `$\\//tats\equiv\null$' when gathering
init== //change this to `$\\//init\equiv\.//@@\//$' in the production version
tini== //change this to `$\\//tini\equiv\.//@@\$' in the production version
othercases == others: //default for cases not listed explicitly
endcases == @+end //follows the default case in an extended |case| statement
mem_bot=0 //smallest index in the |mem| array dumped by \.//INITEX;*/
constexpr int mem_top = 30000; //largest index in the |mem| array dumped by \.//INITEX;
/*font_base=0 //smallest internal font number; must not be less*/
constexpr int hash_size=2100; //maximum number of control sequences; it should be at most
/*hash_prime=1777 //a prime number equal to about 85\pct! of |hash_size|
hyph_size=307 //another prime; the number of \.//\\hyphenation exceptions
exit=10 //go here to leave a procedure
restart=20 //go here to start a procedure again
reswitch=21 //go here to start a case statement again
continue=22 //go here to resume a loop
done=30 //go here to exit a loop
done1=31 //like |done|, when there is more than one loop
done2=32 //for exiting the second loop in a long block
done3=33 //for exiting the third loop in a very long block
done4=34 //for exiting the fourth loop in an extremely long block
done5=35 //for exiting the fifth loop in an immense block
done6=36 //for exiting the sixth loop in a block
found=40 //go here when you've found it
found1=41 //like |found|, when there's more than one per routine
found2=42 //like |found|, when there's more than two per routine
not_found=45 //go here when you've found nothing
common_ending=50 //go here when you want to merge with another branch
incr(#) == #:=#+1 //increase a variable by unity
decr(#) == #:=#-1 //decrease a variable by unity
negate(#) == #:=-# //change the sign of a variable
loop == @+ while true do@+ //repeat over and over until a |goto| happens
do_nothing == //empty statement
return == goto exit //terminate a procedure call
empty=0 //symbolic name for a null constant
text_char == char //the data type of characters in text files
first_text_char=0 //ordinal number of the smallest element of |text_char|
last_text_char=255 //ordinal number of the largest element of |text_char|
null_code=@'0 //ASCII code that might disappear
carriage_return=@'15 //ASCII code used at end of line
invalid_code=@'177 //ASCII code that many systems prohibit in text files
reset_OK(#)==erstat(#)=0
rewrite_OK(#)==erstat(#)=0
t_open_in==reset(term_in,'TTY:','/O/I') //open the terminal for text input
t_open_out==rewrite(term_out,'TTY:','/O') //open the terminal for text output
update_terminal == break(term_out) //empty the terminal output buffer
clear_terminal == break_in(term_in,true) //clear the terminal input buffer
wake_up_terminal == do_nothing //cancel the user's cancellation of output
loc==cur_input.loc_field //location of first unread character in |buffer|
si(#) == # //convert from |ASCII_code| to |packed_ASCII_code|
so(#) == # //convert from |packed_ASCII_code| to |ASCII_code|
length(#)==(str_start[#+1]-str_start[#]) //the number of characters
cur_length == (pool_ptr - str_start[str_ptr])
append_char(#) == //put |ASCII_code| \# at the end of |str_pool|
flush_char == decr(pool_ptr) //forget the last character in the pool
str_room(#) == //make sure that the pool hasn't overflowed
flush_string==begin decr(str_ptr); pool_ptr:=str_start[str_ptr];
@ app_lc_hex(#)==l:=#;
@ bad_pool(#)==begin wake_up_terminal; write_ln(term_out,#);
no_print=16 //|selector| setting that makes data disappear
term_only=17 //printing is destined for the terminal only
log_only=18 //printing is destined for the transcript file only
term_and_log=19 //normal |selector| setting
pseudo=20 //special |selector| setting for |show_context|
new_string=21 //printing is deflected to the string pool
max_selector=21 //highest selector setting
wterm(#)==write(term_out,#)
wterm_ln(#)==write_ln(term_out,#)
wterm_cr==write_ln(term_out)
wlog(#)==write(log_file,#)
wlog_ln(#)==write_ln(log_file,#)
wlog_cr==write_ln(log_file)
print_ASCII == print
prompt_input(#)==begin wake_up_terminal; print(#); term_input;
batch_mode=0 //omits all stops and omits terminal output
nonstop_mode=1 //omits all stops
scroll_mode=2 //omits error stops
error_stop_mode=3 //stops at every opportunity to interact
print_err(#)==begin if interaction=error_stop_mode then wake_up_terminal;
spotless=0 //|history| value when nothing has been amiss yet
warning_issued=1 //|history| value when |begin_diagnostic| has been called
error_message_issued=2 //|history| value when |error| has been called
fatal_error_stop=3 //|history| value when termination was premature
hlp1(#)==help_line[0]:=#;@+end
hlp2(#)==help_line[1]:=#; hlp1
hlp3(#)==help_line[2]:=#; hlp2
hlp4(#)==help_line[3]:=#; hlp3
hlp5(#)==help_line[4]:=#; hlp4
hlp6(#)==help_line[5]:=#; hlp5
help0==help_ptr:=0 //sometimes there might be no help
help1==@+begin help_ptr:=1; hlp1 //use this with one help line
help2==@+begin help_ptr:=2; hlp2 //use this with two help lines
help3==@+begin help_ptr:=3; hlp3 //use this with three help lines
help4==@+begin help_ptr:=4; hlp4 //use this with four help lines
help5==@+begin help_ptr:=5; hlp5 //use this with five help lines
help6==@+begin help_ptr:=6; hlp6 //use this with six help lines
succumb==begin if interaction=error_stop_mode then
check_interrupt==begin if interrupt<>0 then pause_for_instructions;
unity == @'200000 //$2^//16$, represents 1.00000
two == @'400000 //$2^//17$, represents 2.00000
nx_plus_y(#)==mult_and_add(#,@'7777777777)
mult_integers(#)==mult_and_add(#,0,@'17777777777)
inf_bad = 10000 //infinitely bad value
set_glue_ratio_zero(#) == #:=0.0 //store the representation of zero ratio
set_glue_ratio_one(#) == #:=1.0 //store the representation of unit ratio
float(#) == # //convert from |glue_ratio| to type |real|
unfloat(#) == # //convert from |real| to type |glue_ratio|
float_constant(#) == #.0 //convert |integer| constant to |real|
min_quarterword=0 //smallest allowable value in a |quarterword|
max_quarterword=255 //largest allowable value in a |quarterword|
min_halfword==0 //smallest allowable value in a |halfword|
max_halfword==65535 //largest allowable value in a |halfword|
qi(#)==#+min_quarterword
qo(#)==#-min_quarterword
hi(#)==#+min_halfword
ho(#)==#-min_halfword
sc==int //|scaled| data is equivalent to |integer|
pointer==halfword //a flag or a location in |mem| or |eqtb|
null==min_halfword //the null pointer*/
/*free_avail(#)== //single-word node liberation
fast_get_avail(#)==@t@>@;@/
empty_flag == max_halfword //the |link| of an empty variable-size node
is_empty(#) == (link(#)=empty_flag) //tests for empty node
node_size == info //the size field in empty variable-size nodes
llink(#) == info(#+1) //left link in doubly-linked list of empty nodes
rlink(#) == link(#+1) //right link in doubly-linked list of empty nodes*/

// link(#) == mem[#].hh.rh //the |link| field of a memory word
halfword& link(halfword p);
// info(#) == mem[#].hh.lh //the |info| field of a memory word
halfword& info(halfword p);
//type(#) == mem[#].hh.b0 //identifies what kind of node this is
quarterword& type(halfword p);
//subtype(#) == mem[#].hh.b1 //secondary identification in some cases
quarterword& subtype(halfword p);

/*is_char_node(#) == (#>=hi_mem_min)
font == type //the font code in a |char_node|
character == subtype //the character code in a |char_node|*/
constexpr int hlist_node = 0; //|type| of hlist nodes
/*box_node_size=7 //number of words to allocate for a box node
width_offset=1 //position of |width| field in a box node
depth_offset=2 //position of |depth| field in a box node
height_offset=3 //position of |height| field in a box node
width(#) == mem[#+width_offset].sc //width of the box, in sp
depth(#) == mem[#+depth_offset].sc //depth of the box, in sp
height(#) == mem[#+height_offset].sc //height of the box, in sp
shift_amount(#) == mem[#+4].sc //repositioning distance, in sp
list_offset=5 //position of |list_ptr| field in a box node
list_ptr(#) == link(#+list_offset) //beginning of the list inside the box
glue_order(#) == subtype(#+list_offset) //applicable order of infinity
glue_sign(#) == type(#+list_offset) //stretching or shrinking
normal=0 //the most common case when several cases are named
stretching = 1 //glue setting applies to the stretch components
shrinking = 2 //glue setting applies to the shrink components
glue_offset = 6 //position of |glue_set| in a box node
glue_set(#) == mem[#+glue_offset].gr*/
constexpr int vlist_node = 1; //|type| of vlist nodes
constexpr int rule_node = 2; //|type| of rule nodes
/*rule_node_size=4 //number of words to allocate for a rule node
null_flag==-@'10000000000 //$-2^//30$, signifies a missing item
is_running(#) == (#=null_flag) //tests for a running dimension*/
constexpr int ins_node = 3; //|type| of insertion nodes
/*ins_node_size=5 //number of words to allocate for an insertion
float_cost(#)==mem[#+1].int //the |floating_penalty| to be used
ins_ptr(#)==info(#+4) //the vertical list to be inserted
split_top_ptr(#)==link(#+4) //the |split_top_skip| to be used*/
constexpr int mark_node = 4; //|type| of a mark node
/*small_node_size=2 //number of words to allocate for most node types
mark_ptr(#)==mem[#+1].int //head of the token list for a mark*/
constexpr int adjust_node = 5; //|type| of an adjust node
/*adjust_ptr==mark_ptr //vertical list to be moved out of horizontal list*/
constexpr int ligature_node = 6; //|type| of a ligature node
/*lig_char(#)==#+1 //the word where the ligature is to be found
lig_ptr(#)==link(lig_char(#)) //the list of characters*/
constexpr int disc_node = 7; //|type| of a discretionary node
/*replace_count==subtype //how many subsequent nodes to replace
pre_break==llink //text that precedes a discretionary break
post_break==rlink //text that follows a discretionary break*/
constexpr int whatsit_node = 8; //|type| of special extension nodes
constexpr int math_node = 9; //|type| of a math node
/*before=0 //|subtype| for math node that introduces a formula
after=1 //|subtype| for math node that winds up a formula
precedes_break(#)==(type(#)<math_node)
non_discardable(#)==(type(#)<math_node)*/
constexpr int glue_node = 10; //|type| of node that points to a glue specification
/*cond_math_glue=98 //special |subtype| to suppress glue in the next node
mu_glue=99 //|subtype| for math glue
a_leaders=100 //|subtype| for aligned leaders
c_leaders=101 //|subtype| for centered leaders
x_leaders=102 //|subtype| for expanded leaders
glue_ptr==llink //pointer to a glue specification
leader_ptr==rlink //pointer to box or rule node for leaders
glue_spec_size=4 //number of words to allocate for a glue specification
glue_ref_count(#) == link(#) //reference count of a glue specification
stretch(#) == mem[#+2].sc //the stretchability of this glob of glue
shrink(#) == mem[#+3].sc //the shrinkability of this glob of glue
stretch_order == type //order of infinity for stretching
shrink_order == subtype //order of infinity for shrinking
fil=1 //first-order infinity
fill=2 //second-order infinity
filll=3 //third-order infinity*/
constexpr int kern_node = 11; //|type| of a kern node
/*explicit=1 //|subtype| of kern nodes from \.//\\kern and \.//\\/
acc_kern=2 //|subtype| of kern nodes from accents*/
constexpr int penalty_node = 12; //|type| of a penalty node
/*inf_penalty=inf_bad //``infinite'' penalty value
eject_penalty=-inf_penalty //``negatively infinite'' penalty value
penalty(#) == mem[#+1].int //the added cost of breaking a list here
unset_node=13 //|type| for an unset node
glue_stretch(#)==mem[#+glue_offset].sc //total stretch in an unset node
glue_shrink==shift_amount //total shrink in an unset node
span_count==subtype //indicates the number of spanned columns
zero_glue==mem_bot //specification for \.//0pt plus 0pt minus 0pt
fil_glue==zero_glue+glue_spec_size //\.//0pt plus 1fil minus 0pt
fill_glue==fil_glue+glue_spec_size //\.//0pt plus 1fill minus 0pt
ss_glue==fill_glue+glue_spec_size //\.//0pt plus 1fil minus 1fil
fil_neg_glue==ss_glue+glue_spec_size //\.//0pt plus -1fil minus 0pt
lo_mem_stat_max==fil_neg_glue+glue_spec_size-1 //largest statically*/

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

/*hi_mem_stat_usage=14 //the number of one-word nodes always present
node_list_display(#)==
token_ref_count(#) == info(#) //reference count preceding a token list
fast_delete_glue_ref(#)==@t@>@;@/
add_token_ref(#)==incr(token_ref_count(#)) //new reference to a token list
add_glue_ref(#)==incr(glue_ref_count(#)) //new reference to a glue spec*/
constexpr int escape = 0; //escape delimiter (called \.\\ in //\sl The \TeX book\/)
/*relax=0 //do nothing ( \.//\\relax )*/
constexpr int left_brace = 1; //beginning of a group ( \.\// )
constexpr int right_brace = 2; //ending of a group ( \.\ )
constexpr int math_shift = 3; //mathematics shift character ( \.\$ )
constexpr int tab_mark = 4; //alignment delimiter ( \.\&, \.//\\span )
constexpr int car_ret = 5; //end of line ( |carriage_return|, \.//\\cr, \.//\\crcr )
/*out_param=5 //output a macro parameter*/
constexpr int mac_param = 6; //macro parameter symbol ( \.\# )
constexpr int sup_mark = 7; //superscript ( \.//\char'136 )
constexpr int sub_mark = 8; //subscript ( \.//\char'137 )
constexpr int ignore = 9; //characters to ignore ( \.//\^\^@@ )
/*endv=9 //end of \<v_j> list in alignment template*/
constexpr int spacer = 10; //characters equivalent to blank space ( \.//\  )
constexpr int letter = 11; //characters regarded as letters ( \.//A..Z, \.//a..z )
constexpr int other_char = 12; //none of the special character types
constexpr int active_char = 13; //characters that invoke macros ( \.//\char`\~ )
/*par_end=13 //end of paragraph ( \.//\\par )
match=13 //match a macro parameter*/
constexpr int comment = 14; //characters that introduce comments ( \.\% )
/*end_match=14 //end of parameters to macro
stop=14 //end of job ( \.//\\end, \.//\\dump )*/
constexpr int invalid_char = 15; //characters that shouldn't appear ( \.//\^\^? )
/*delim_num=15 //specify delimiter numerically ( \.//\\delimiter )
max_char_code=15 //largest catcode for individual characters
char_num=16 //character specified numerically ( \.//\\char )
math_char_num=17 //explicit math code ( \.//\\mathchar )
mark=18 //mark definition ( \.//\\mark )
xray=19 //peek inside of \TeX\ ( \.//\\show, \.//\\showbox, etc.~)
make_box=20 //make a box ( \.//\\box, \.//\\copy, \.//\\hbox, etc.~)
hmove=21 //horizontal motion ( \.//\\moveleft, \.//\\moveright )
vmove=22 //vertical motion ( \.//\\raise, \.//\\lower )
un_hbox=23 //unglue a box ( \.//\\unhbox, \.//\\unhcopy )
un_vbox=24 //unglue a box ( \.//\\unvbox, \.//\\unvcopy )
remove_item=25 //nullify last item ( \.//\\unpenalty,
hskip=26 //horizontal glue ( \.//\\hskip, \.//\\hfil, etc.~)
vskip=27 //vertical glue ( \.//\\vskip, \.//\\vfil, etc.~)
mskip=28 //math glue ( \.//\\mskip )
kern=29 //fixed space ( \.//\\kern)
mkern=30 //math kern ( \.//\\mkern )
leader_ship=31 //use a box ( \.//\\shipout, \.//\\leaders, etc.~)
halign=32 //horizontal table alignment ( \.//\\halign )
valign=33 //vertical table alignment ( \.//\\valign )
no_align=34 //temporary escape from alignment ( \.//\\noalign )
vrule=35 //vertical rule ( \.//\\vrule )
hrule=36 //horizontal rule ( \.//\\hrule )
insert=37 //vlist inserted in box ( \.//\\insert )
vadjust=38 //vlist inserted in enclosing paragraph ( \.//\\vadjust )
ignore_spaces=39 //gobble |spacer| tokens ( \.//\\ignorespaces )
after_assignment=40 //save till assignment is done ( \.//\\afterassignment )
after_group=41 //save till group is done ( \.//\\aftergroup )
break_penalty=42 //additional badness ( \.//\\penalty )
start_par=43 //begin paragraph ( \.//\\indent, \.//\\noindent )
ital_corr=44 //italic correction ( \.//\\/ )
accent=45 //attach accent in text ( \.//\\accent )
math_accent=46 //attach accent in math ( \.//\\mathaccent )
discretionary=47 //discretionary texts ( \.//\\-, \.//\\discretionary )
eq_no=48 //equation number ( \.//\\eqno, \.//\\leqno )
left_right=49 //variable delimiter ( \.//\\left, \.//\\right )
math_comp=50 //component of formula ( \.//\\mathbin, etc.~)
limit_switch=51 //diddle limit conventions ( \.//\\displaylimits, etc.~)
above=52 //generalized fraction ( \.//\\above, \.//\\atop, etc.~)
math_style=53 //style specification ( \.//\\displaystyle, etc.~)
math_choice=54 //choice specification ( \.//\\mathchoice )
non_script=55 //conditional math glue ( \.//\\nonscript )
vcenter=56 //vertically center a vbox ( \.//\\vcenter )
case_shift=57 //force specific case ( \.//\\lowercase, \.//\\uppercase~)
message=58 //send to user ( \.//\\message, \.//\\errmessage )
extension=59 //extensions to \TeX\ ( \.//\\write, \.//\\special, etc.~)
in_stream=60 //files for reading ( \.//\\openin, \.//\\closein )
begin_group=61 //begin local grouping ( \.//\\begingroup )
end_group=62 //end local grouping ( \.//\\endgroup )
omit=63 //omit alignment template ( \.//\\omit )
ex_space=64 //explicit space ( \.//\\\  )
no_boundary=65 //suppress boundary ligatures ( \.//\\noboundary )
radical=66 //square root and similar signs ( \.//\\radical )
end_cs_name=67 //end control sequence ( \.//\\endcsname )
min_internal=68 //the smallest code that can follow \.//\\the
char_given=68 //character code defined by \.//\\chardef
math_given=69 //math code defined by \.//\\mathchardef
last_item=70 //most recent item ( \.//\\lastpenalty,
max_non_prefixed_command=70 //largest command code that can't be \.//\\global
toks_register=71 //token list register ( \.//\\toks )
assign_toks=72 //special token list ( \.//\\output, \.//\\everypar, etc.~)
assign_int=73 //user-defined integer ( \.//\\tolerance, \.//\\day, etc.~)
assign_dimen=74 //user-defined length ( \.//\\hsize, etc.~)
assign_glue=75 //user-defined glue ( \.//\\baselineskip, etc.~)
assign_mu_glue=76 //user-defined muglue ( \.//\\thinmuskip, etc.~)
assign_font_dimen=77 //user-defined font dimension ( \.//\\fontdimen )
assign_font_int=78 //user-defined font integer ( \.//\\hyphenchar,
set_aux=79 //specify state info ( \.//\\spacefactor, \.//\\prevdepth )
set_prev_graf=80 //specify state info ( \.//\\prevgraf )
set_page_dimen=81 //specify state info ( \.//\\pagegoal, etc.~)
set_page_int=82 //specify state info ( \.//\\deadcycles,
set_box_dimen=83 //change dimension of box ( \.//\\wd, \.//\\ht, \.//\\dp )
set_shape=84 //specify fancy paragraph shape ( \.//\\parshape )
def_code=85 //define a character code ( \.//\\catcode, etc.~)
def_family=86 //declare math fonts ( \.//\\textfont, etc.~)
set_font=87 //set current font ( font identifiers )
def_font=88 //define a font file ( \.//\\font )
register=89 //internal register ( \.//\\count, \.//\\dimen, etc.~)
max_internal=89 //the largest code that can follow \.//\\the
advance=90 //advance a register or parameter ( \.//\\advance )
multiply=91 //multiply a register or parameter ( \.//\\multiply )
divide=92 //divide a register or parameter ( \.//\\divide )
prefix=93 //qualify a definition ( \.//\\global, \.//\\long, \.//\\outer )
let=94 //assign a command code ( \.//\\let, \.//\\futurelet )
shorthand_def=95 //code definition ( \.//\\chardef, \.//\\countdef, etc.~)
read_to_cs=96 //read into a control sequence ( \.//\\read )
def=97 //macro definition ( \.//\\def, \.//\\gdef, \.//\\xdef, \.//\\edef )
set_box=98 //set a box ( \.//\\setbox )
hyph_data=99 //hyphenation data ( \.//\\hyphenation, \.//\\patterns )
set_interaction=100 //define level of interaction ( \.//\\batchmode, etc.~)
max_command=100 //the largest command code seen at |big_switch|
undefined_cs=max_command+1 //initial state of most |eq_type| fields
expand_after=max_command+2 //special expansion ( \.//\\expandafter )
no_expand=max_command+3 //special nonexpansion ( \.//\\noexpand )
input=max_command+4 //input a source file ( \.//\\input, \.//\\endinput )
if_test=max_command+5 //conditional text ( \.//\\if, \.//\\ifcase, etc.~)
fi_or_else=max_command+6 //delimiters for conditionals ( \.//\\else, etc.~)
cs_name=max_command+7 //make a control sequence from tokens ( \.//\\csname )
convert=max_command+8 //convert to text ( \.//\\number, \.//\\string, etc.~)
the=max_command+9 //expand an internal quantity ( \.//\\the )
top_bot_mark=max_command+10 //inserted mark ( \.//\\topmark, etc.~)
call=max_command+11 //non-long, non-outer control sequence
long_call=max_command+12 //long, non-outer control sequence
outer_call=max_command+13 //non-long, outer control sequence
long_outer_call=max_command+14 //long, outer control sequence
end_template=max_command+15 //end of an alignment template
dont_expand=max_command+16 //the following token was marked by \.//\\noexpand
glue_ref=max_command+17 //the equivalent points to a glue specification
shape_ref=max_command+18 //the equivalent points to a parshape specification
box_ref=max_command+19 //the equivalent points to a box node, or is |null|
data=max_command+20 //the equivalent is simply a halfword number
vmode=1 //vertical mode
hmode=vmode+max_command+1 //horizontal mode
mmode=hmode+max_command+1 //math mode
ignore_depth==-65536000 //|prev_depth| value that is ignored
@ mode==cur_list.mode_field //current mode
head==cur_list.head_field //header node of current list
tail==cur_list.tail_field //final node on current list
prev_graf==cur_list.pg_field //number of paragraph lines accumulated
aux==cur_list.aux_field //auxiliary data about the current list
prev_depth==aux.sc //the name of |aux| in vertical mode
space_factor==aux.hh.lh //part of |aux| in horizontal mode
clang==aux.hh.rh //the other part of |aux| in horizontal mode
incompleat_noad==aux.int //the name of |aux| in math mode
mode_line==cur_list.ml_field //source file line number at beginning of list
tail_append(#)==begin link(tail):=#; tail:=link(tail);*/

//eq_level_field(#)==#.hh.b1
quarterword& eq_level(halfword);

//eq_type_field(#)==#.hh.b0
//eq_type(#)==eq_type_field(eqtb[#]) //command code for equivalent
quarterword& eq_type(halfword);

//equiv_field(#)==#.hh.rh
//equiv(#)==equiv_field(eqtb[#]) //equivalent value
halfword& equiv(halfword);

/*level_zero=min_quarterword //level for undefined quantities
level_one=level_zero+1 //outermost level for defined quantities*/
constexpr int active_base = 1; //beginning of region 1, for active character equivalents
constexpr int single_base = 257; //active_base+256 //equivalents of one-character control sequences
constexpr int null_cs = 513; // single_base+256 //equivalent of \.//\\csname\\endcsname
constexpr int hash_base = 514; //null_cs+1 //beginning of region 2, for the hash table
constexpr int frozen_control_sequence = 2614; //hash_base+hash_size //for error recovery
/*frozen_protection=frozen_control_sequence //inaccessible but definable
frozen_cr=frozen_control_sequence+1 //permanent `\.//\\cr'
frozen_end_group=frozen_control_sequence+2 //permanent `\.//\\endgroup'
frozen_right=frozen_control_sequence+3 //permanent `\.//\\right'
frozen_fi=frozen_control_sequence+4 //permanent `\.//\\fi'
frozen_end_template=frozen_control_sequence+5 //permanent `\.//\\endtemplate'
frozen_endv=frozen_control_sequence+6 //second permanent `\.//\\endtemplate'
frozen_relax=frozen_control_sequence+7 //permanent `\.//\\relax'*/
constexpr int end_write = 2622; //frozen_control_sequence+8 //permanent `\.//\\endwrite'
constexpr int frozen_dont_expand = 2623; //frozen_control_sequence+9
constexpr int frozen_null_font = 2624; //frozen_control_sequence+10
/*font_id_base=frozen_null_font-font_base*/
constexpr int undefined_control_sequence = 2881;// frozen_null_font+257 //dummy location
constexpr int glue_base = 2882; //undefined_control_sequence+1 //beginning of region 3
/*line_skip_code=0 //interline glue if |baseline_skip| is infeasible*/
constexpr int baseline_skip_code = 1; //desired glue between baselines
/*par_skip_code=2 //extra glue just above a paragraph
above_display_skip_code=3 //extra glue just above displayed math
below_display_skip_code=4 //extra glue just below displayed math
above_display_short_skip_code=5
below_display_short_skip_code=6*/
constexpr int left_skip_code = 7; //glue at left of justified lines
constexpr int right_skip_code = 8; //glue at right of justified lines
/*top_skip_code=9 //glue at top of main pages*/
constexpr int split_top_skip_code = 10; //glue at top of split pages
/*tab_skip_code=11 //glue between aligned entries*/
constexpr int space_skip_code = 12; //glue between words (if not |zero_glue|)
constexpr int xspace_skip_code = 13; //glue after sentences (if not |zero_glue|)
/*par_fill_skip_code=14 //glue on last line of paragraph
thin_mu_skip_code=15 //thin space in math formula
med_mu_skip_code=16 //medium space in math formula
thick_mu_skip_code=17 //thick space in math formula*/
constexpr int glue_pars = 18; //total number of glue parameters
constexpr int skip_base = 2900; //glue_base+glue_pars //table of 256 ``skip'' registers
constexpr int mu_skip_base = 3156; //skip_base+256 //table of 256 ``muskip'' registers
constexpr int local_base = 3412; //mu_skip_base+256 //beginning of region 4

//skip(#)==equiv(skip_base+#) //|mem| location of glue specification
halfword& skip(halfword);

//mu_skip(#)==equiv(mu_skip_base+#) //|mem| location of math glue spec
halfword& mu_skip(halfword);

//glue_par(#)==equiv(glue_base+#) //|mem| location of glue specification
halfword& glue_par(halfword);

/*line_skip==glue_par(line_skip_code)*/

//baseline_skip==glue_par(baseline_skip_code)
halfword& baseline_skip(void);

/*par_skip==glue_par(par_skip_code)
above_display_skip==glue_par(above_display_skip_code)
below_display_skip==glue_par(below_display_skip_code)
above_display_short_skip==glue_par(above_display_short_skip_code)
below_display_short_skip==glue_par(below_display_short_skip_code)*/

//left_skip==glue_par(left_skip_code)
halfword& left_skip(void);

//right_skip==glue_par(right_skip_code)
halfword& right_skip(void);

/*top_skip==glue_par(top_skip_code)*/

//split_top_skip==glue_par(split_top_skip_code)
halfword& split_top_skip(void);

/*tab_skip==glue_par(tab_skip_code)*/

//space_skip==glue_par(space_skip_code)
halfword& space_skip(void);

//xspace_skip==glue_par(xspace_skip_code)
halfword& xspace_skip(void);

/*par_fill_skip==glue_par(par_fill_skip_code)
thin_mu_skip==glue_par(thin_mu_skip_code)
med_mu_skip==glue_par(med_mu_skip_code)
thick_mu_skip==glue_par(thick_mu_skip_code)
*/
constexpr int par_shape_loc = 3412; //local_base //specifies paragraph shape
constexpr int output_routine_loc = 3413; //local_base+1 //points to token list for \.//\\output
constexpr int every_par_loc = 3414; //local_base+2 //points to token list for \.//\\everypar
constexpr int every_math_loc = 3415; //local_base+3 //points to token list for \.//\\everymath
constexpr int every_display_loc = 3416; //local_base+4 //points to token list for \.//\\everydisplay
constexpr int every_hbox_loc = 3417; //local_base+5 //points to token list for \.//\\everyhbox
constexpr int every_vbox_loc = 3418; //local_base+6 //points to token list for \.//\\everyvbox
constexpr int every_job_loc = 3419; //local_base+7 //points to token list for \.//\\everyjob
constexpr int every_cr_loc = 3420; //local_base+8 //points to token list for \.//\\everycr
constexpr int err_help_loc = 3421; //local_base+9 //points to token list for \.//\\errhelp*/
constexpr int toks_base = 3422;//local_base+10 //table of 256 token list registers
constexpr int box_base = 3678; //toks_base+256 //table of 256 box registers
constexpr int cur_font_loc = 3934;//box_base+256 //internal font number outside math mode
constexpr int math_font_base = 3935; //cur_font_loc+1 //table of 48 math font numbers
constexpr int cat_code_base = 3983; //math_font_base+48
constexpr int lc_code_base = 4239; //cat_code_base+256 //table of 256 lowercase mappings
constexpr int uc_code_base = 4495; //lc_code_base+256 //table of 256 uppercase mappings
constexpr int sf_code_base = 4751; // uc_code_base+256 //table of 256 spacefactor mappings
constexpr int math_code_base = 5007; //sf_code_base+256 //table of 256 math mode mappings
constexpr int int_base = 5263;//math_code_base+256 //beginning of region 5

//par_shape_ptr==equiv(par_shape_loc)
halfword& par_shape_ptr(void);

//output_routine==equiv(output_routine_loc)
halfword& output_routine(void);

//every_par==equiv(every_par_loc)
halfword& every_par(void);

//every_math==equiv(every_math_loc)
halfword& every_math(void);

//every_display==equiv(every_display_loc)
halfword& every_display(void);

//every_hbox==equiv(every_hbox_loc)
halfword& every_hbox(void);

//every_vbox==equiv(every_vbox_loc)
halfword& every_vbox(void);

//every_job==equiv(every_job_loc)
halfword& every_job(void);

//every_cr==equiv(every_cr_loc)
halfword& every_cr(void);

//err_help==equiv(err_help_loc)
halfword& err_help(void);

/*toks(#)==equiv(toks_base+#)*/

//box(#)==equiv(box_base+#)
halfword& box(halfword);

//cur_font==equiv(cur_font_loc)
halfword& cur_font(void);

//fam_fnt(#)==equiv(math_font_base+#)
halfword& fam_fnt(halfword);

//cat_code(#)==equiv(cat_code_base+#)
halfword& cat_code(halfword);

//lc_code(#)==equiv(lc_code_base+#)
halfword& lc_code(halfword p);

//uc_code(#)==equiv(uc_code_base+#)
halfword& uc_code(halfword p);

//sf_code(#)==equiv(sf_code_base+#)
halfword& sf_code(halfword p);

//math_code(#)==equiv(math_code_base+#)
halfword& math_code(halfword p);

/*null_font==font_base
var_code==@'70000 //math code meaning ``use the current family''*/
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
/*tracing_paragraphs_code=32 //show line-break calculations
tracing_pages_code=33 //show page-break calculations*/
constexpr int tracing_output_code = 34; //show boxes when they are shipped out
constexpr int tracing_lost_chars_code = 35; //show characters that aren't in the font
constexpr int tracing_commands_code = 36; //show command codes at |big_switch|
/*tracing_restores_code=37 //show equivalents when they are restored*/
constexpr int uc_hyph_code = 38; //hyphenate words beginning with a capital letter
/*output_penalty_code=39 //penalty found at current page break*/
constexpr int max_dead_cycles_code = 40; //bound on consecutive dead cycles of output
constexpr int hang_after_code = 41; //hanging indentation changes after this many lines
constexpr int floating_penalty_code = 42; //penalty for insertions heldover after a split
constexpr int global_defs_code = 43; //override \.//\\global specifications
constexpr int cur_fam_code = 44; //current family
constexpr int escape_char_code = 45; //escape character for token output
constexpr int default_hyphen_char_code = 46; //value of \.//\\hyphenchar when a font is loaded
constexpr int default_skew_char_code = 47; //value of \.//\\skewchar when a font is loaded
constexpr int end_line_char_code = 48; //character placed at the right end of the buffer
constexpr int new_line_char_code = 49; //character that prints as |print_ln|
constexpr int language_code = 50; //current hyphenation table
constexpr int left_hyphen_min_code = 51; //minimum left hyphenation fragment size
constexpr int right_hyphen_min_code = 52; //minimum right hyphenation fragment size
constexpr int holding_inserts_code = 53; //do not remove insertion nodes from \.//\\box255
constexpr int error_context_lines_code = 54; //maximum intermediate line pairs shown
constexpr int int_pars = 55; //total number of integer parameters
constexpr int count_base = 5318; //int_base+int_pars //256 user \.//\\count registers
constexpr int del_code_base = 5574; //count_base+256 //256 delimiter code mappings
constexpr int dimen_base = 5830; //del_code_base+256 //beginning of region 6

//del_code(#)==eqtb[del_code_base+#].int
int& del_code(halfword p);

//count(#)==eqtb[count_base+#].int
int& count(halfword p);

//int_par(#)==eqtb[int_base+#].int //an integer parameter
int& int_par(halfword);

/*pretolerance==int_par(pretolerance_code)
tolerance==int_par(tolerance_code)
line_penalty==int_par(line_penalty_code)
hyphen_penalty==int_par(hyphen_penalty_code)
ex_hyphen_penalty==int_par(ex_hyphen_penalty_code)
club_penalty==int_par(club_penalty_code)
widow_penalty==int_par(widow_penalty_code)
display_widow_penalty==int_par(display_widow_penalty_code)
broken_penalty==int_par(broken_penalty_code)
bin_op_penalty==int_par(bin_op_penalty_code)
rel_penalty==int_par(rel_penalty_code)
pre_display_penalty==int_par(pre_display_penalty_code)
post_display_penalty==int_par(post_display_penalty_code)
inter_line_penalty==int_par(inter_line_penalty_code)
double_hyphen_demerits==int_par(double_hyphen_demerits_code)
final_hyphen_demerits==int_par(final_hyphen_demerits_code)
adj_demerits==int_par(adj_demerits_code)
mag==int_par(mag_code)
delimiter_factor==int_par(delimiter_factor_code)
looseness==int_par(looseness_code)
time==int_par(time_code)
day==int_par(day_code)
month==int_par(month_code)
year==int_par(year_code)
show_box_breadth==int_par(show_box_breadth_code)
show_box_depth==int_par(show_box_depth_code)
hbadness==int_par(hbadness_code)
vbadness==int_par(vbadness_code)
pausing==int_par(pausing_code)
tracing_online==int_par(tracing_online_code)
tracing_macros==int_par(tracing_macros_code)
tracing_stats==int_par(tracing_stats_code)
tracing_paragraphs==int_par(tracing_paragraphs_code)
tracing_pages==int_par(tracing_pages_code)
tracing_output==int_par(tracing_output_code)
tracing_lost_chars==int_par(tracing_lost_chars_code)
tracing_commands==int_par(tracing_commands_code)
tracing_restores==int_par(tracing_restores_code)
uc_hyph==int_par(uc_hyph_code)
output_penalty==int_par(output_penalty_code)
max_dead_cycles==int_par(max_dead_cycles_code)
hang_after==int_par(hang_after_code)
floating_penalty==int_par(floating_penalty_code)
global_defs==int_par(global_defs_code)
cur_fam==int_par(cur_fam_code)
escape_char==int_par(escape_char_code)
default_hyphen_char==int_par(default_hyphen_char_code)
default_skew_char==int_par(default_skew_char_code)
end_line_char==int_par(end_line_char_code)
new_line_char==int_par(new_line_char_code)
language==int_par(language_code)
left_hyphen_min==int_par(left_hyphen_min_code)
right_hyphen_min==int_par(right_hyphen_min_code)
holding_inserts==int_par(holding_inserts_code)
error_context_lines==int_par(error_context_lines_code)*/
constexpr int par_indent_code = 0; //indentation of paragraphs
constexpr int math_surround_code = 1; //space around math in text
constexpr int line_skip_limit_code = 2; //threshold for |line_skip| instead of |baseline_skip|
constexpr int hsize_code = 3; //line width in horizontal mode
constexpr int vsize_code = 4; //page height in vertical mode
/*max_depth_code=5 //maximum depth of boxes on main pages*/
constexpr int split_max_depth_code = 6; //maximum depth of boxes on split pages
constexpr int box_max_depth_code = 7; //maximum depth of explicit vboxes
constexpr int hfuzz_code = 8; //tolerance for overfull hbox messages
constexpr int vfuzz_code = 9; //tolerance for overfull vbox messages
constexpr int delimiter_shortfall_code = 10; //maximum amount uncovered by variable delimiters
constexpr int null_delimiter_space_code = 11; //blank space in null delimiters
constexpr int script_space_code = 12; //extra space after subscript or superscript
constexpr int pre_display_size_code = 13; //length of text preceding a display
constexpr int display_width_code = 14; //length of line for displayed equation
constexpr int display_indent_code = 15; //indentation of line for displayed equation
constexpr int overfull_rule_code = 16; //width of rule that identifies overfull hboxes
constexpr int hang_indent_code = 17; //amount of hanging indentation
constexpr int h_offset_code = 18; //amount of horizontal offset when shipping pages out
constexpr int v_offset_code = 19; //amount of vertical offset when shipping pages out
constexpr int emergency_stretch_code = 20; //reduces badnesses on final pass of line-breaking
constexpr int dimen_pars = 21; //total number of dimension parameters
constexpr int scaled_base = 5851; //dimen_base+dimen_pars;
constexpr int eqtb_size = 6106; // scaled_base+255; //largest subscript of |eqtb|

//dimen(#)==eqtb[scaled_base+#].sc
int& dimen(halfword);

//dimen_par(#)==eqtb[dimen_base+#].sc //a scaled quantity
int& dimen_par(halfword p);

/*par_indent==dimen_par(par_indent_code)
math_surround==dimen_par(math_surround_code)
line_skip_limit==dimen_par(line_skip_limit_code)
hsize==dimen_par(hsize_code)
vsize==dimen_par(vsize_code)
max_depth==dimen_par(max_depth_code)
split_max_depth==dimen_par(split_max_depth_code)
box_max_depth==dimen_par(box_max_depth_code)
hfuzz==dimen_par(hfuzz_code)
vfuzz==dimen_par(vfuzz_code)
delimiter_shortfall==dimen_par(delimiter_shortfall_code)
null_delimiter_space==dimen_par(null_delimiter_space_code)
script_space==dimen_par(script_space_code)
pre_display_size==dimen_par(pre_display_size_code)
display_width==dimen_par(display_width_code)
display_indent==dimen_par(display_indent_code)
overfull_rule==dimen_par(overfull_rule_code)
hang_indent==dimen_par(hang_indent_code)
h_offset==dimen_par(h_offset_code)
v_offset==dimen_par(v_offset_code)
emergency_stretch==dimen_par(emergency_stretch_code)
next(#) == hash[#].lh //link for coalesced lists
text(#) == hash[#].rh //string number for control sequence name
hash_is_full == (hash_used=hash_base) //test if all positions are occupied
font_id_text(#) == text(font_id_base+#) //a frozen font identifier's name*/

//save_type(#)==save_stack[#].hh.b0 //classifies a |save_stack| entry
quarterword& save_type(halfword p);

//save_level(#)==save_stack[#].hh.b1
quarterword& save_level(halfword);

//save_index(#)==save_stack[#].hh.rh
halfword& save_index(halfword);

/*restore_old_value=0 //|save_type| when a value should be restored later
restore_zero=1 //|save_type| when an undefined entry should be restored
insert_token=2 //|save_type| when a token is being saved for later use
level_boundary=3 //|save_type| corresponding to beginning of group
bottom_level=0 //group code for the outside world
simple_group=1 //group code for local structure only
hbox_group=2 //code for `\.//\\hbox\grp'
adjusted_hbox_group=3 //code for `\.//\\hbox\grp' in vertical mode
vbox_group=4 //code for `\.//\\vbox\grp'
vtop_group=5 //code for `\.//\\vtop\grp'
align_group=6 //code for `\.//\\halign\grp', `\.//\\valign\grp'
no_align_group=7 //code for `\.//\\noalign\grp'
output_group=8 //code for output routine
math_group=9 //code for, e.g., `\.//\char'136\grp'
disc_group=10 //code for `\.//\\discretionary\grp\grp\grp'
insert_group=11 //code for `\.//\\insert\grp', `\.//\\vadjust\grp'
vcenter_group=12 //code for `\.//\\vcenter\grp'
math_choice_group=13 //code for `\.//\\mathchoice\grp\grp\grp\grp'
semi_simple_group=14 //code for `\.//\\begingroup...\\endgroup'
math_shift_group=15 //code for `\.//\$...\$'
math_left_group=16 //code for `\.//\\left...\\right'
max_group_code=16
check_full_save_stack==if save_ptr>max_save_stack then
saved(#)==save_stack[save_ptr+#].int
cs_token_flag==@'7777 //amount added to the |eqtb| location in a
left_brace_token=@'0400 //$2^8\cdot|left_brace|$
left_brace_limit=@'1000 //$2^8\cdot(|left_brace|+1)$
right_brace_token=@'1000 //$2^8\cdot|right_brace|$
right_brace_limit=@'1400 //$2^8\cdot(|right_brace|+1)$
math_shift_token=@'1400 //$2^8\cdot|math_shift|$
tab_token=@'2000 //$2^8\cdot|tab_mark|$
out_param_token=@'2400 //$2^8\cdot|out_param|$
space_token=@'5040 //$2^8\cdot|spacer|+|" "|$
letter_token=@'5400 //$2^8\cdot|letter|$
other_token=@'6000 //$2^8\cdot|other_char|$
match_token=@'6400 //$2^8\cdot|match|$
end_match_token=@'7000 //$2^8\cdot|end_match|$
chr_cmd(#)==begin print(#); print_ASCII(chr_code);
state==cur_input.state_field //current scanner state
index==cur_input.index_field //reference for buffer information
start==cur_input.start_field //starting position in |buffer|
limit==cur_input.limit_field //end of current line in |buffer|
name==cur_input.name_field //name of the current file
mid_line=1 //|state| code when scanning a line of characters
skip_blanks=2+max_char_code //|state| code when ignoring blanks
new_line=3+max_char_code+max_char_code //|state| code at start of line
terminal_input==(name=0) //are we reading from the terminal?
cur_file==input_file[index] //the current |alpha_file| variable
skipping=1 //|scanner_status| when passing conditional text
defining=2 //|scanner_status| when reading a macro definition
matching=3 //|scanner_status| when reading macro arguments
aligning=4 //|scanner_status| when reading an alignment preamble
absorbing=5 //|scanner_status| when reading a balanced text
token_list=0 //|state| code when scanning a token list
token_type==index //type of current token list
param_start==limit //base of macro parameters in |param_stack|
parameter=0 //|token_type| code for parameter
u_template=1 //|token_type| code for \<u_j> template
v_template=2 //|token_type| code for \<v_j> template
backed_up=3 //|token_type| code for text to be reread
inserted=4 //|token_type| code for inserted texts
macro=5 //|token_type| code for defined control sequences
output_text=6 //|token_type| code for output routines
every_par_text=7 //|token_type| code for \.//\\everypar
every_math_text=8 //|token_type| code for \.//\\everymath
every_display_text=9 //|token_type| code for \.//\\everydisplay
every_hbox_text=10 //|token_type| code for \.//\\everyhbox
every_vbox_text=11 //|token_type| code for \.//\\everyvbox
every_job_text=12 //|token_type| code for \.//\\everyjob
every_cr_text=13 //|token_type| code for \.//\\everycr
mark_text=14 //|token_type| code for \.//\\topmark, etc.
write_text=15 //|token_type| code for \.//\\write
begin_pseudoprint==
set_trick_count==
push_input==@t@> //enter a new input level, save the old
pop_input==@t@> //leave an input level, re-enter the old
back_list(#)==begin_token_list(#,backed_up) //backs up a simple token list
ins_list(#)==begin_token_list(#,inserted) //inserts a simple token list
switch=25 //a label in |get_next|
start_cs=26 //another
any_state_plus(#) == mid_line+#,skip_blanks+#,new_line+#
@ add_delims_to(#)==#+math_shift,#+tab_mark,#+mac_param,
is_hex(#)==(((#>="0")and(#<="9"))or((#>="a")and(#<="f")))
hex_to_cur_chr==
no_expand_flag=257 //this characterizes a special variant of |relax|
end_line_char_inactive == (end_line_char<0)or(end_line_char>255)
store_new_token(#)==begin q:=get_avail; link(p):=q; info(q):=#;
fast_store_new_token(#)==begin fast_get_avail(q); link(p):=q; info(q):=#;
top_mark_code=0 //the mark in effect at the previous page break
first_mark_code=1 //the first mark between |top_mark| and |bot_mark|
bot_mark_code=2 //the mark in effect at the current page break
split_first_mark_code=3 //the first mark found by \.//\\vsplit
split_bot_mark_code=4 //the last mark found by \.//\\vsplit
top_mark==cur_mark[top_mark_code]
first_mark==cur_mark[first_mark_code]
bot_mark==cur_mark[bot_mark_code]
split_first_mark==cur_mark[split_first_mark_code]
split_bot_mark==cur_mark[split_bot_mark_code]
int_val=0 //integer values
dimen_val=1 //dimension values
glue_val=2 //glue specifications
mu_val=3 //math glue specifications
ident_val=4 //font identifier
tok_val=5 //token lists
scanned_result_end(#)==cur_val_level:=#;@+end
scanned_result(#)==@+begin cur_val:=#;scanned_result_end
input_line_no_code=glue_val+1 //code for \.//\\inputlineno
badness_code=glue_val+2 //code for \.//\\badness
max_dimen==@'7777777777 //$2^//30-1$
octal_token=other_token+"'" //apostrophe, indicates an octal constant
hex_token=other_token+"""" //double quote, indicates a hex constant
alpha_token=other_token+"`" //reverse apostrophe, precedes alpha constants
point_token=other_token+"." //decimal point
continental_point_token=other_token+"," //decimal point, Eurostyle
@ infinity==@'17777777777 //the largest positive value that \TeX\ knows
zero_token=other_token+"0" //zero, the smallest digit
A_token=letter_token+"A" //the smallest special hex digit
other_A_token=other_token+"A" //special hex digit of type |other_char|
attach_fraction=88 //go here to pack |cur_val| and |f| into |cur_val|
attach_sign=89 //go here when |cur_val| is correct except perhaps for sign
scan_normal_dimen==scan_dimen(false,false,false)
set_conversion_end(#)== denom:=#; end
set_conversion(#)==@+begin num:=#; set_conversion_end
default_rule=26214 //0.4\thinspace pt
number_code=0 //command code for \.//\\number
roman_numeral_code=1 //command code for \.//\\romannumeral
string_code=2 //command code for \.//\\string
meaning_code=3 //command code for \.//\\meaning
font_name_code=4 //command code for \.//\\fontname
job_name_code=5 //command code for \.//\\jobname
closed=2 //not open, or at end of file
just_open=1 //newly opened, first line not yet read
if_char_code=0 // `\.//\\if' 
if_cat_code=1 // `\.//\\ifcat' 
if_int_code=2 // `\.//\\ifnum' 
if_dim_code=3 // `\.//\\ifdim' 
if_odd_code=4 // `\.//\\ifodd' 
if_vmode_code=5 // `\.//\\ifvmode' 
if_hmode_code=6 // `\.//\\ifhmode' 
if_mmode_code=7 // `\.//\\ifmmode' 
if_inner_code=8 // `\.//\\ifinner' 
if_void_code=9 // `\.//\\ifvoid' 
if_hbox_code=10 // `\.//\\ifhbox' 
if_vbox_code=11 // `\.//\\ifvbox' 
ifx_code=12 // `\.//\\ifx' 
if_eof_code=13 // `\.//\\ifeof' 
if_true_code=14 // `\.//\\iftrue' 
if_false_code=15 // `\.//\\iffalse' 
if_case_code=16 // `\.//\\ifcase' 
if_node_size=2 //number of words in stack entry for conditionals
if_line_field(#)==mem[#+1].int
if_code=1 //code for \.//\\if... being evaluated
fi_code=2 //code for \.//\\fi
else_code=3 //code for \.//\\else
or_code=4 //code for \.//\\or
get_x_token_or_active_char==@t@>@;
TEX_area=="TeXinputs:"
TEX_font_area=="TeXfonts:"
append_to_name(#)==begin c:=#; incr(k);
format_default_length=20 //length of the |TEX_format_default| string
format_area_length=11 //length of its area part
format_ext_length=4 //length of its `\.//.fmt' part
format_extension=".fmt" //the extension, as a \.//WEB constant
pack_cur_name==pack_file_name(cur_name,cur_area,cur_ext)
ensure_dvi_open==if output_file_name=0 then
no_tag=0 //vanilla character
lig_tag=1 //character has a ligature/kerning program
list_tag=2 //character has a successor in a charlist
ext_tag=3 //character is extensible
stop_flag==qi(128) //value indicating `\.//STOP' in a lig/kern program
kern_flag==qi(128) //op code for a kern step
skip_byte(#)==#.b0
next_char(#)==#.b1
op_byte(#)==#.b2
rem_byte(#)==#.b3
ext_top(#)==#.b0 //|top| piece in a recipe
ext_mid(#)==#.b1 //|mid| piece in a recipe
ext_bot(#)==#.b2 //|bot| piece in a recipe
ext_rep(#)==#.b3 //|rep| piece in a recipe
slant_code=1
space_code=2
space_stretch_code=3
space_shrink_code=4
x_height_code=5
quad_code=6
extra_space_code=7
non_char==qi(256) //a |halfword| code that can't match a real character
non_address=0 //a spurious |bchar_label|
char_info_end(#)==#].qqqq
char_info(#)==font_info[char_base[#]+char_info_end
char_width_end(#)==#.b0].sc
char_width(#)==font_info[width_base[#]+char_width_end
char_exists(#)==(#.b0>min_quarterword)
char_italic_end(#)==(qo(#.b2)) div 4].sc
char_italic(#)==font_info[italic_base[#]+char_italic_end
height_depth(#)==qo(#.b1)
char_height_end(#)==(#) div 16].sc
char_height(#)==font_info[height_base[#]+char_height_end
char_depth_end(#)==(#) mod 16].sc
char_depth(#)==font_info[depth_base[#]+char_depth_end
char_tag(#)==((qo(#.b2)) mod 4)
char_kern_end(#)==256*op_byte(#)+rem_byte(#)].sc
char_kern(#)==font_info[kern_base[#]+char_kern_end
kern_base_offset==256*(128+min_quarterword)
lig_kern_start(#)==lig_kern_base[#]+rem_byte //beginning of lig/kern program
lig_kern_restart_end(#)==256*op_byte(#)+rem_byte(#)+32768-kern_base_offset
lig_kern_restart(#)==lig_kern_base[#]+lig_kern_restart_end
param_end(#)==param_base[#]].sc
param(#)==font_info[#+param_end
slant==param(slant_code) //slant to the right, per unit distance upward
space==param(space_code) //normal space between words
space_stretch==param(space_stretch_code) //stretch between words
space_shrink==param(space_shrink_code) //shrink between words
x_height==param(x_height_code) //one ex
quad==param(quad_code) //one em
extra_space==param(extra_space_code) //additional space at end of sentence
bad_tfm=11 //label for |read_font_info|
abort==goto bad_tfm //do this when the \.//TFM data is wrong
start_font_error_message==print_err("Font "); sprint_cs(u);
fget==get(tfm_file)
fbyte==tfm_file^
read_sixteen(#)==begin #:=fbyte;
store_four_quarters(#)==begin fget; a:=fbyte; qw.b0:=qi(a);
check_byte_range(#)==begin if (#<bc)or(#>ec) then abort@+end
current_character_being_worked_on==k+bc-fmem_ptr
store_scaled(#)==begin fget; a:=fbyte; fget; b:=fbyte;
@ check_existence(#)==@t@>@;@/
adjust(#)==#[f]:=qo(#[f])
@ set_char_0=0 //typeset character 0 and move right*/
constexpr int set1 = 128; //typeset a character and move right
constexpr int set_rule = 132; //typeset a rule and move right
constexpr int put_rule = 137; //typeset a rule
/*nop=138 //no operation*/
constexpr int bop = 139; //beginning of page
constexpr int eop = 140; //ending of page
constexpr int push = 141; //save the current positions
constexpr int pop = 142; //restore previous positions
/*right1=143 //move right
w0=147 //move right by |w|
w1=148 //move right and set |w|
x0=152 //move right by |x|
x1=153 //move right and set |x|
down1=157 //move down
y0=161 //move down by |y|
y1=162 //move down and set |y|
z0=166 //move down by |z|
z1=167 //move down and set |z|
fnt_num_0=171 //set current font to 0
fnt1=235 //set current font*/
constexpr int xxx1 = 239; //extension to \.//DVI primitives
constexpr int xxx4 = 242; //potentially long extension to \.//DVI primitives
constexpr int fnt_def1 = 243; //define the meaning of a font number
constexpr int pre = 247; //preamble
constexpr int post = 248; //postamble beginning
constexpr int post_post = 249; //postamble ending
constexpr int id_byte = 2; //identifies the kind of \.//DVI files described here
/*dvi_out(#)==@+begin dvi_buf[dvi_ptr]:=#; incr(dvi_ptr);
movement_node_size=3 //number of words per entry in the down and right stacks
location(#)==mem[#+2].int //\.//DVI byte number for a movement command
y_here=1 //|info| when the movement entry points to a |y| command
z_here=2 //|info| when the movement entry points to a |z| command
yz_OK=3 //|info| corresponding to an unconstrained \\//down command
y_OK=4 //|info| corresponding to a \\//down that can't become a |z|
z_OK=5 //|info| corresponding to a \\//down that can't become a |y|
d_fixed=6 //|info| corresponding to a \\//down that can't change
none_seen=0 //no |y_here| or |z_here| nodes have been encountered yet
y_seen=6 //we have seen |y_here| but not |z_here|
z_seen=12 //we have seen |z_here| but not |y_here|
synch_h==if cur_h<>dvi_h then
synch_v==if cur_v<>dvi_v then
move_past=13 //go to this label when advancing past glue or a rule
fin_rule=14 //go to this label to finish processing a rule
next_p=15 //go to this label when finished with node |p|
@ billion==float_constant(1000000000)
vet_glue(#)== glue_temp:=#;
exactly=0 //a box dimension is pre-specified
additional=1 //a box dimension is increased from the natural one
natural==0,additional //shorthand for parameters to |hpack| and |vpack|
vpack(#)==vpackage(#,max_dimen) //special case of unconstrained depth
noad_size=4 //number of words in a normal noad
nucleus(#)==#+1 //the |nucleus| field of a noad
supscr(#)==#+2 //the |supscr| field of a noad
subscr(#)==#+3 //the |subscr| field of a noad
math_type==link //a |halfword| in |mem|
fam==font //a |quarterword| in |mem|
math_char=1 //|math_type| when the attribute is simple
sub_box=2 //|math_type| when the attribute is a box
sub_mlist=3 //|math_type| when the attribute is a formula
math_text_char=4 //|math_type| when italic correction is dubious
ord_noad=unset_node+3 //|type| of a noad classified Ord
op_noad=ord_noad+1 //|type| of a noad classified Op
bin_noad=ord_noad+2 //|type| of a noad classified Bin
rel_noad=ord_noad+3 //|type| of a noad classified Rel
open_noad=ord_noad+4 //|type| of a noad classified Ope
close_noad=ord_noad+5 //|type| of a noad classified Clo
punct_noad=ord_noad+6 //|type| of a noad classified Pun
inner_noad=ord_noad+7 //|type| of a noad classified Inn
limits=1 //|subtype| of |op_noad| whose scripts are to be above, below
no_limits=2 //|subtype| of |op_noad| whose scripts are to be normal
left_delimiter(#)==#+4 //first delimiter field of a noad
right_delimiter(#)==#+5 //second delimiter field of a fraction noad
radical_noad=inner_noad+1 //|type| of a noad for square roots
radical_noad_size=5 //number of |mem| words in a radical noad
fraction_noad=radical_noad+1 //|type| of a noad for generalized fractions
fraction_noad_size=6 //number of |mem| words in a fraction noad
small_fam(#)==mem[#].qqqq.b0 //|fam| for ``small'' delimiter
small_char(#)==mem[#].qqqq.b1 //|character| for ``small'' delimiter
large_fam(#)==mem[#].qqqq.b2 //|fam| for ``large'' delimiter
large_char(#)==mem[#].qqqq.b3 //|character| for ``large'' delimiter
thickness==width //|thickness| field in a fraction noad
default_code==@'10000000000 //denotes |default_rule_thickness|
numerator==supscr //|numerator| field in a fraction noad
denominator==subscr //|denominator| field in a fraction noad
under_noad=fraction_noad+1 //|type| of a noad for underlining
over_noad=under_noad+1 //|type| of a noad for overlining
accent_noad=over_noad+1 //|type| of a noad for accented subformulas
accent_noad_size=5 //number of |mem| words in an accent noad
accent_chr(#)==#+4 //the |accent_chr| field of an accent noad
vcenter_noad=accent_noad+1 //|type| of a noad for \.//\\vcenter
left_noad=vcenter_noad+1 //|type| of a noad for \.//\\left
right_noad=left_noad+1 //|type| of a noad for \.//\\right
delimiter==nucleus //|delimiter| field in left and right noads
scripts_allowed(#)==(type(#)>=ord_noad)and(type(#)<left_noad)*/
constexpr int style_node = 14; //unset_node+1 //|type| of a style node
/*style_node_size=3 //number of words in a style node
display_style=0 //|subtype| for \.//\\displaystyle
text_style=2 //|subtype| for \.//\\textstyle
script_style=4 //|subtype| for \.//\\scriptstyle
script_script_style=6 //|subtype| for \.//\\scriptscriptstyle
cramped=1 //add this to an uncramped style if you want to cramp it*/
constexpr int choice_node = 15; //unset_node+2 //|type| of a choice node
/*display_mlist(#)==info(#+1) //mlist to be used in display style
text_mlist(#)==link(#+1) //mlist to be used in text style
script_mlist(#)==info(#+2) //mlist to be used in script style
script_script_mlist(#)==link(#+2) //mlist to be used in scriptscript style
text_size=0 //size code for the largest size in a family
script_size=16 //size code for the medium size in a family
script_script_size=32 //size code for the smallest size in a family
mathsy_end(#)==fam_fnt(2+#)]].sc
mathsy(#)==font_info[#+param_base[mathsy_end
math_x_height==mathsy(5) //height of `\.x'
math_quad==mathsy(6) //\.//18mu
num1==mathsy(8) //numerator shift-up in display styles
num2==mathsy(9) //numerator shift-up in non-display, non-\.//\\atop
num3==mathsy(10) //numerator shift-up in non-display \.//\\atop
denom1==mathsy(11) //denominator shift-down in display styles
denom2==mathsy(12) //denominator shift-down in non-display styles
sup1==mathsy(13) //superscript shift-up in uncramped display style
sup2==mathsy(14) //superscript shift-up in uncramped non-display
sup3==mathsy(15) //superscript shift-up in cramped styles
sub1==mathsy(16) //subscript shift-down if superscript is absent
sub2==mathsy(17) //subscript shift-down if superscript is present
sup_drop==mathsy(18) //superscript baseline below top of large box
sub_drop==mathsy(19) //subscript baseline below bottom of large box
delim1==mathsy(20) //size of \.//\\atopwithdelims delimiters
delim2==mathsy(21) //size of \.//\\atopwithdelims delimiters in non-displays
axis_height==mathsy(22) //height of fraction lines above the baseline
total_mathsy_params=22
mathex(#)==font_info[#+param_base[fam_fnt(3+cur_size)]].sc
default_rule_thickness==mathex(8) //thickness of \.//\\over bars
big_op_spacing1==mathex(9) //minimum clearance above a displayed op
big_op_spacing2==mathex(10) //minimum clearance below a displayed op
big_op_spacing3==mathex(11) //minimum baselineskip above displayed op
big_op_spacing4==mathex(12) //minimum baselineskip below displayed op
big_op_spacing5==mathex(13) //padding above and below displayed limits
total_mathex_params=13
cramped_style(#)==2*(# div 2)+cramped //cramp the style
sub_style(#)==2*(# div 4)+script_style+cramped //smaller and cramped
sup_style(#)==2*(# div 4)+script_style+(# mod 2) //smaller
num_style(#)==#+2-2*(# div 6) //smaller unless already script-script
denom_style(#)==2*(# div 2)+cramped+2-2*(# div 6) //smaller, cramped
mu_mult(#)==nx_plus_y(n,#,xn_over_d(#,f,@'200000))
new_hlist(#)==mem[nucleus(#)].int //the translation of an mlist
done_with_noad=80 //go here when a noad has been fully translated
done_with_node=81 //go here when a node has been fully converted
check_dimensions=82 //go here to update |max_h| and |max_d|
delete_q=83 //go here to delete |q| and move to the next node
@ choose_mlist(#)==begin p:=#(q); #(q):=null;@+end
math_spacing=@;@/
u_part(#)==mem[#+height_offset].int //pointer to \<u_j> token list
v_part(#)==mem[#+depth_offset].int //pointer to \<v_j> token list
extra_info(#)==info(#+list_offset) //info to remember during template
preamble==link(align_head) //the current preamble list
align_stack_node_size=5 //number of |mem| words to save alignment states
span_code=256 //distinct from any character
cr_code=257 //distinct from |span_code| and from any character
cr_cr_code=cr_code+1 //this distinguishes \.//\\crcr from \.//\\cr
end_template_token==cs_token_flag+frozen_end_template
span_node_size=2 //number of |mem| words for a span node
tight_fit=3 //fitness classification for lines shrinking 0.5 to 1.0 of their
loose_fit=1 //fitness classification for lines stretching 0.5 to 1.0 of their
very_loose_fit=0 //fitness classification for lines stretching more than
decent_fit=2 //fitness classification for all other lines
active_node_size=3 //number of words in active nodes
fitness==subtype //|very_loose_fit..tight_fit| on final line for this break
break_node==rlink //pointer to the corresponding passive node
line_number==llink //line that begins at this breakpoint
total_demerits(#)==mem[#+2].int //the quantity that \TeX\ minimizes
unhyphenated=0 //the |type| of a normal active break node
hyphenated=1 //the |type| of an active node that breaks at a |disc_node|
last_active==active //the active list ends where it begins
passive_node_size=2 //number of words in passive nodes
cur_break==rlink //in passive node, points to position of this breakpoint
prev_break==llink //points to passive node that should precede this one
serial==info //serial number for symbolic identification
delta_node_size=7 //number of words in a delta node
delta_node=2 //|type| field in a delta node
do_all_six(#)==#(1);#(2);#(3);#(4);#(5);#(6)
check_shrinkage(#)==if (shrink_order(#)<>normal)and(shrink(#)<>0) then
copy_to_cur_active(#)==cur_active_width[#]:=active_width[#]
deactivate=60 //go here when node |r| should be deactivated
update_width(#)==@|
awful_bad==@'7777777777 //more than a billion demerits
set_break_width_to_background(#)==break_width[#]:=background[#]
convert_to_break_width(#)==@|
store_break_width(#)==active_width[#]:=break_width[#]
new_delta_to_break_width(#)==@|
new_delta_from_break_width(#)==@|mem[q+#].sc:=
combine_two_deltas(#)==@|mem[prev_r+#].sc:=mem[prev_r+#].sc+mem[r+#].sc
downdate_width(#)==@|cur_active_width[#]:=cur_active_width[#]-
update_active(#)==active_width[#]:=active_width[#]+mem[r+#].sc
store_background(#)==active_width[#]:=background[#]
act_width==active_width[1] //length from first active node to current node
kern_break==begin if not is_char_node(link(cur_p)) and auto_breaking then
next_break==prev_break //new name for |prev_break| after links are reversed
@ append_charnode_to_t(#)== begin link(t):=get_avail; t:=link(t);
set_cur_r==begin if j<n then cur_r:=qi(hu[j+1])@+else cur_r:=bchar;
@ wrap_lig(#)==if ligature_present then
pop_lig_stack==begin if lig_ptr(lig_stack)>null then
advance_major_tail==begin major_tail:=link(major_tail); incr(r_count);
@ trie_link(#)==trie[#].rh //``downward'' link in a trie
trie_char(#)==trie[#].b1 //character matched at this trie location
trie_op(#)==trie[#].b0 //program for hyphenation at this trie location
set_cur_lang==if language<=0 then cur_lang:=0
trie_root==trie_l[0] //root of the linked trie
trie_ref==trie_hash //where linked trie families go into |trie|
trie_back(#)==trie[#].lh //backward links in |trie| holes
active_height==active_width //new name for the six distance variables
cur_height==active_height[1] //the natural height
set_height_zero(#)==active_height[#]:=0 //initialize the height to zero
update_heights=90 //go here to record glue in the |active_height| table
@ deplorable==100000 //more than |inf_bad|, but less than |awful_bad|
inserts_only=1
box_there=2 //|page_contents| when a box or rule has been contributed
page_ins_node_size=4 //number of words for a page insertion node
inserting=0 //an insertion class that has not yet overflowed
split_up=1 //an overflowed insertion class
broken_ptr(#)==link(#+1)
broken_ins(#)==info(#+1) //this insertion might break at |broken_ptr|
last_ins_ptr(#)==link(#+2) //the most recent insertion for this |subtype|
best_ins_ptr(#)==info(#+2) //the optimum most recent insertion
page_goal==page_so_far[0] //desired height of information on page being built
page_total==page_so_far[1] //height of the current page
page_shrink==page_so_far[6] //shrinkability of the current page
page_depth==page_so_far[7] //depth of the current page
@ print_plus_end(#)==print(#);@+end
print_plus(#)==if page_so_far[#]<>0 then
set_page_so_far_zero(#)==page_so_far[#]:=0
contribute=80 //go here to link a node into the current page
@ contrib_tail==nest[0].tail_field //tail of the contribution list
big_switch=60 //go here to branch on the next token of input
main_loop=70 //go here to typeset a string of consecutive characters
main_loop_wrapup=80 //go here to finish a character or ligature
main_loop_move=90 //go here to advance the ligature cursor
main_loop_move_lig=95 //same, when advancing past a generated ligature
main_loop_lookahead=100 //go here to bring in another character, if any
main_lig_loop=110 //go here to check for ligatures or kerning
append_normal_space=120 //go here to append a normal space between words
adjust_space_factor==@t@>@;@/
pack_lig(#)== //the parameter is either |rt_hit| or |false|
wrapup(#)==if cur_l<non_char then
any_mode(#)==vmode+#,hmode+#,mmode+# //for mode-independent commands
non_math(#)==vmode+#,hmode+#
fil_code=0 //identifies \.//\\hfil and \.//\\vfil
fill_code=1 //identifies \.//\\hfill and \.//\\vfill
ss_code=2 //identifies \.//\\hss and \.//\\vss
fil_neg_code=3 //identifies \.//\\hfilneg and \.//\\vfilneg
skip_code=4 //identifies \.//\\hskip and \.//\\vskip
mskip_code=5 //identifies \.//\\mskip
box_flag==@'10000000000 //context code for `\.//\\setbox0'
ship_out_flag==box_flag+512 //context code for `\.//\\shipout'
leader_flag==box_flag+513 //context code for `\.//\\leaders'
box_code=0 //|chr_code| for `\.//\\box'
copy_code=1 //|chr_code| for `\.//\\copy'
last_box_code=2 //|chr_code| for `\.//\\lastbox'
vsplit_code=3 //|chr_code| for `\.//\\vsplit'
vtop_code=4 //|chr_code| for `\.//\\vtop'
fam_in_range==((cur_fam>=0)and(cur_fam<16))
above_code=0 // `\.//\\above' 
over_code=1 // `\.//\\over' 
atop_code=2 // `\.//\\atop' 
delimited_code=3 // `\.//\\abovewithdelims', etc.
global==(a>=4)
define(#)==if global then geq_define(#)@+else eq_define(#)
word_define(#)==if global then geq_word_define(#)@+else eq_word_define(#)
char_def_code=0 //|shorthand_def| for \.//\\chardef
math_char_def_code=1 //|shorthand_def| for \.//\\mathchardef
count_def_code=2 //|shorthand_def| for \.//\\countdef
dimen_def_code=3 //|shorthand_def| for \.//\\dimendef
skip_def_code=4 //|shorthand_def| for \.//\\skipdef
mu_skip_def_code=5 //|shorthand_def| for \.//\\muskipdef
toks_def_code=6 //|shorthand_def| for \.//\\toksdef
@ show_code=0 // \.//\\show 
show_box_code=1 // \.//\\showbox 
show_the_code=2 // \.//\\showthe 
show_lists=3 // \.//\\showlists 
bad_fmt=6666 //go here if the format file is unacceptable
too_small(#)==begin wake_up_terminal;
dump_wd(#)==begin fmt_file^:=#; put(fmt_file);@+end
dump_int(#)==begin fmt_file^.int:=#; put(fmt_file);@+end
dump_hh(#)==begin fmt_file^.hh:=#; put(fmt_file);@+end
dump_qqqq(#)==begin fmt_file^.qqqq:=#; put(fmt_file);@+end
undump_wd(#)==begin get(fmt_file); #:=fmt_file^;@+end
undump_int(#)==begin get(fmt_file); #:=fmt_file^.int;@+end
undump_hh(#)==begin get(fmt_file); #:=fmt_file^.hh;@+end
undump_qqqq(#)==begin get(fmt_file); #:=fmt_file^.qqqq;@+end
undump_end_end(#)==#:=x;@+end
undump_end(#)==(x>#) then goto bad_fmt@+else undump_end_end
undump(#)==begin undump_int(x); if (x<#) or undump_end
undump_size_end_end(#)==too_small(#)@+else undump_end_end
undump_size_end(#)==if x># then undump_size_end_end
undump_size(#)==begin undump_int(x);
@ dump_four_ASCII==
@ undump_four_ASCII==
breakpoint=888 //place where a breakpoint is desirable
write_node_size=2 //number of words in a write/whatsit node
open_node_size=3 //number of words in an open/whatsit node
open_node=0 //|subtype| in whatsits that represent files to \.//\\openout
write_node=1 //|subtype| in whatsits that represent things to \.//\\write
close_node=2 //|subtype| in whatsits that represent streams to \.//\\closeout
special_node=3 //|subtype| in whatsits that represent \.//\\special things
language_node=4 //|subtype| in whatsits that change the current language
what_lang(#)==link(#+1) //language number, in the range |0..255|
what_lhm(#)==type(#+1) //minimum left fragment, in the range |1..63|
what_rhm(#)==subtype(#+1) //minimum right fragment, in the range |1..63|
write_tokens(#) == link(#+1) //reference count of token list to write
write_stream(#) == info(#+1) //stream number (0 to 17)
open_name(#) == link(#+1) //string number of file name to open
open_area(#) == info(#+2) //string number of file area for |open_name|
open_ext(#) == link(#+2) //string number of file extension for |open_name|
immediate_code=4 //command modifier for \.//\\immediate
set_language_code=5 //command modifier for \.//\\setlanguage
@ adv_past(#)==@+if subtype(#)=language_node then
end_write_token==cs_token_flag+end_write*/

#endif

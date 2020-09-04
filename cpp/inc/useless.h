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
return == goto exit //terminate a procedure call*/
/*empty=0 //symbolic name for a null constant
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
wake_up_terminal == do_nothing //cancel the user's cancellation of output*/
/*si(#) == # //convert from |ASCII_code| to |packed_ASCII_code|
so(#) == # //convert from |packed_ASCII_code| to |ASCII_code|*/
/*wterm(#)==write(term_out,#)
wterm_ln(#)==write_ln(term_out,#)
wterm_cr==write_ln(term_out)
wlog(#)==write(log_file,#)
wlog_ln(#)==write_ln(log_file,#)
wlog_cr==write_ln(log_file)
print_ASCII == print
prompt_input(#)==begin wake_up_terminal; print(#); term_input;*/
/*print_err(#)==begin if interaction=error_stop_mode then wake_up_terminal;*/
/*hlp1(#)==help_line[0]:=#;@+end
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
succumb==begin if interaction=error_stop_mode then*/
/*set_glue_ratio_zero(#) == #:=0.0 //store the representation of zero ratio
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
//do_all_six(#)==#(1);#(2);#(3);#(4);#(5);#(6)
//kern_base_offset==256*(128+min_quarterword)*/
//@ bad_pool(#)==begin wake_up_terminal; write_ln(term_out,#);
/*@ app_lc_hex(#)==l:=#; if l<10 then append_char(l+'0')else append_char(l-10+'a') */
/*is_empty(#) == (link(#)=empty_flag) //tests for empty node*/
//constexpr int max_selector = 21; //highest selector setting
/*non_discardable(#)==(type(#)<math_node)*/
//@ append_charnode_to_t(#)== begin link(t):=get_avail; t:=link(t);font(t):=hf; character(t):=#; end 
//fast_delete_glue_ref(#)==@t@>@;@/
//eq_type_field(#)==#.hh.b0
//equiv_field(#)==#.hh.rh
/*line_skip==glue_par(line_skip_code)*/
/*par_skip==glue_par(par_skip_code)
above_display_skip==glue_par(above_display_skip_code)
below_display_skip==glue_par(below_display_skip_code)
above_display_short_skip==glue_par(above_display_short_skip_code)
below_display_short_skip==glue_par(below_display_short_skip_code)*/
/*top_skip==glue_par(top_skip_code)*/
/*tab_skip==glue_par(tab_skip_code)*/
/*par_fill_skip==glue_par(par_fill_skip_code)
thin_mu_skip==glue_par(thin_mu_skip_code)
med_mu_skip==glue_par(med_mu_skip_code)
thick_mu_skip==glue_par(thick_mu_skip_code)*/
/*toks(#)==equiv(toks_base+#)*/
/*output_penalty==int_par(output_penalty_code)
tracing_stats==int_par(tracing_stats_code)
tracing_paragraphs==int_par(tracing_paragraphs_code)
tracing_pages==int_par(tracing_pages_code)
tracing_lost_chars==int_par(tracing_lost_chars_code)
tracing_restores==int_par(tracing_restores_code)*/
/*max_depth==dimen_par(max_depth_code)*/
/*max_group_code=16*/
/*chr_cmd(#)==begin print(#); print_ASCII(chr_code);*/
//switch=25 //a label in |get_next|
//start_cs=26 //another
/*attach_fraction=88 //go here to pack |cur_val| and |f| into |cur_val|
attach_sign=89 //go here when |cur_val| is correct except perhaps for sign*/
/*height_depth(#)==qo(#.b1)*/
/*bad_tfm=11 //label for |read_font_info|
abort==goto bad_tfm //do this when the \.//TFM data is wrong
/*fget==get(tfm_file)
fbyte==tfm_file^*/
//adjust(#)==#[f]:=qo(#[f])
/*@ set_char_0=0 //typeset character 0 and move right*/
/*nop=138 //no operation*/
/*w0=147 //move right by |w|
w1=148 //move right and set |w|
x0=152 //move right by |x|
x1=153 //move right and set |x|*/
/*y0=161 //move down by |y|
y1=162 //move down and set |y|
z0=166 //move down by |z|
z1=167 //move down and set |z|
move_past=13 //go to this label when advancing past glue or a rule
fin_rule=14 //go to this label to finish processing a rule
next_p=15 //go to this label when finished with node |p|*/
/*natural==0,additional //shorthand for parameters to |hpack| and |vpack|
/*done_with_noad=80 //go here when a noad has been fully translated
done_with_node=81 //go here when a node has been fully converted
check_dimensions=82 //go here to update |max_h| and |max_d|
delete_q=83 //go here to delete |q| and move to the next node
/*last_active==active //the active list ends where it begins
cur_break==rlink //in passive node, points to position of this breakpoint
prev_break==llink //points to passive node that should precede this one*/
/*serial==info //serial number for symbolic identification*/
//deactivate=60 //go here when node |r| should be deactivated
//next_break==prev_break //new name for |prev_break| after links are reversed
/*big_switch=60 //go here to branch on the next token of input
main_loop=70 //go here to typeset a string of consecutive characters
main_loop_wrapup=80 //go here to finish a character or ligature
main_loop_move=90 //go here to advance the ligature cursor
main_loop_move_lig=95 //same, when advancing past a generated ligature
main_loop_lookahead=100 //go here to bring in another character, if any
main_lig_loop=110 //go here to check for ligatures or kerning
append_normal_space=120 //go here to append a normal space between words
bad_fmt=6666 //go here if the format file is unacceptable*/
//update_heights=90 //go here to record glue in the |active_height| table
//contribute=80 //go here to link a node into the current page
/*too_small(#)==begin wake_up_terminal;
breakpoint=888 //place where a breakpoint is desirable*/
//@ adv_past(#)==@+if subtype(#)=language_node then
//typedef unsigned int nonnegativeinteger; //0..2147483647

//halfword& node_size(halfword); //!< the size field in empty variable-size nodes
//halfword& llink(halfword); //!< left link in doubly-linked list of empty nodes
//halfword& rlink(halfword); //!< right link in doubly-linked list of empty nodes
//halfword& link(halfword p); //!< the \a link field of a memory word
//halfword& info(halfword p); //!< the \a info field of a memory word
//int length(halfword); //!< the number of characters
//quarterword& type(halfword p); //!< identifies what kind of node this is
//quarterword& subtype(halfword p); //!< secondary identification in some cases
//bool is_char_node(halfword);
//quarterword& font(halfword); //!< the font code in a \a char_node
//quarterword& character(halfword); //!< the character code in a \a char_node
//int& width(halfword); //!< width of the box, in sp
//int& depth(halfword); //!< depth of the box, in sp
//int& height(halfword); //!< height of the box, in sp
//int& shift_amount(halfword); //!< repositioning distance, in sp
//halfword& list_ptr(halfword); //!< beginning of the list inside the box
//quarterword& glue_order(halfword); //!< applicable order of infinity
//quarterword& glue_sign(halfword); //!< stretching or shrinking
//float &glue_set(halfword);
//int& float_cost(halfword); //!< the \a floating_penalty to be used
//halfword& ins_ptr(halfword); //!< the vertical list to be inserted
//halfword& split_top_ptr(halfword); //!< the \a split_top_skip to be used
//int& mark_ptr(halfword); //!< head of the token list for a mark
//int& adjust_ptr(halfword); //!< vertical list to be moved out of horizontal list
//halfword lig_char(halfword); //!< the word where the ligature is to be found
//halfword& lig_ptr(halfword); //!< the list of characters
//halfword& leader_ptr(halfword); //!< pointer to box or rule node for leaders
//halfword& glue_ref_count(halfword); //!< reference count of a glue specification
//int& stretch(halfword); //!< the stretchability of this glob of glue
//int& shrink(halfword); //!< the shrinkability of this glob of glue
//quarterword& stretch_order(halfword); //!< order of infinity for stretching
//quarterword& shrink_order(halfword); //!< order of infinity for shrinking
//int& penalty(halfword); //!< the added cost of breaking a list here
//int& glue_stretch(halfword); //!< total stretch in an unset node
//int& glue_shrink(halfword); //!< total shrink in an unset node
//quarterword& span_count(halfword); //!< indicates the number of spanned columns
//halfword& token_ref_count(halfword); //!< reference count preceding a token list
//halfword& skip(halfword); //!< \a mem location of glue specification
//halfword& box(halfword); 
//halfword& text(halfword); //!< string number for control sequence name
//quarterword& save_type(halfword); //!< classifies a \a save_stack entry
//quarterword& save_level(halfword);
//halfword& save_index(halfword); 
//int& saved(halfword); 
//int& if_line_field(halfword); 
//int& location(halfword); //!< DVI byte number for a movement command
//halfword nucleus(halfword); //!< the \a nucleus field of a noad
//halfword supscr(halfword); //!< the \a supscr field of a noad
//halfword subscr(halfword); //!< the \a subscr field of a noad
//halfword& math_type(halfword); //!< a \a halfword in \a mem
//quarterword& fam(halfword); //!< a \a quarterword in \a mem
//halfword left_delimiter(halfword); //!< first delimiter field of a noad
//halfword right_delimiter(halfword); //!< second delimiter field of a fraction noad
//quarterword& small_fam(halfword); //!< \a fam for ``small'' delimiter
//quarterword& small_char(halfword); //!< \a character for ``small'' delimiter
//quarterword& large_fam(halfword); //!< \a fam for ``large'' delimiter
//quarterword& large_char(halfword); //!< \a character for ``large'' delimiter
//int& thickness(halfword); //!< \a thickness field in a fraction noad
//halfword numerator(halfword); //!< \a numerator field in a fraction noad
//halfword denominator(halfword); //!< \a denominator field in a fraction noad
//halfword accent_chr(halfword); //!< the \a accent_chr field of an accent noad
//halfword delimiter(halfword); //!< \a delimiter field in left and right noads
//int& u_part(halfword); //!< pointer to \f$<u_j\f$ token list
//int&v_part(halfword); //!< pointer to \f$<v_j\f$ token list
//halfword& extra_info(halfword); //!< info to remember during template
//quarterword& fitness(halfword); //!< <em> very_loose_fit..tight_fit</em> on final line for this break
//halfword& break_node(halfword); //!< pointer to the corresponding passive node
//halfword& line_number(halfword); //!< line that begins at this breakpoint
//int& total_demerits(halfword); //!< the quantity that \\TeX\\ minimizes
//halfword& broken_ins(halfword p); //!< this insertion might break at \a broken_ptr
//halfword& last_ins_ptr(halfword p); //!< the most recent insertion for this \a subtype
//halfword& best_ins_ptr(halfword); //!< the optimum most recent insertion
//halfword& what_lang(halfword); //!< language number, in the range 0..255
//quarterword& what_lhm(halfword); //!< minimum left fragment, in the range 1..63
//quarterword& what_rhm(halfword); //!< minimum right fragment, in the range 1..63
//halfword& write_tokens(halfword); //!< reference count of token list to write
//halfword& write_stream(halfword); //!< stream number (0 to 17)
//halfword& open_name(halfword); //!< string number of file name to open
//halfword& open_area(halfword); //!< string number of file area for \a open_name
//halfword& open_ext(halfword); //!< string number of file extension for \a open_name
//inline void add_glue_ref(halfword p) { glue_ref_count(p)++; } //!< new reference to a glue spec
//inline void add_token_ref(halfword p) { token_ref_count(p)++; } //!< new reference to a token list
//extern halfword &contrib_tail; //!< tail of the contribution list
//inline void flush_char(void) { currentString.pop_back(); } //!< forget the last character in the pool
/*enum
{
	zero_glue = mem_bot, //!< specification for 0pt plus 0pt minus 0pt
	fil_glue = zero_glue+glue_spec_size, //!< 0pt plus 1fil minus 0pt
	fill_glue = fil_glue+glue_spec_size, //!< 0pt plus 1fill minus 0pt
	ss_glue = fill_glue+glue_spec_size, //!< 0pt plus 1fil minus 1fil
	fil_neg_glue = ss_glue+glue_spec_size //!< 0pt plus -1fil minus 0pt
};*/

/*enum
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
};*/
/*enum
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
};*/





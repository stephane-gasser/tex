#ifndef PARAMETRES_H
#define PARAMETRES_H

constexpr int int_pars = 55; //!< total number of integer parameters
constexpr int glue_pars = 18; //!< total number of glue parameters
constexpr int dimen_pars = 21; //!< total number of dimension parameters

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

int& int_par(halfword); //!< an integer parameter
inline int ex_hyphen_penalty(void) { return int_par(ex_hyphen_penalty_code); }
inline int& tolerance(void) { return int_par(tolerance_code); }
inline int pre_display_penalty(void) { return int_par(pre_display_penalty_code); }
inline int post_display_penalty(void) { return int_par(post_display_penalty_code); }
inline int& mag(void) { return int_par(mag_code); }
inline int looseness(void) { return int_par(looseness_code); }
inline int& time(void) { return int_par(time_code); }
inline int& day(void) { return int_par(day_code); }
inline int& month(void) { return int_par(month_code); }
inline int& year(void) { return int_par(year_code); }
inline int& vbadness(void) { return int_par(vbadness_code); }
inline int tracing_commands(void) { return int_par(tracing_commands_code); }
inline int tracing_online(void) { return int_par(tracing_online_code); }
inline int tracing_macros(void) { return int_par(tracing_macros_code); }
inline int& max_dead_cycles(void) { return int_par(max_dead_cycles_code); }
inline int left_hyphen_min(void) { return int_par(left_hyphen_min_code); }
inline int right_hyphen_min(void) { return int_par(right_hyphen_min_code); }
inline int language(void) { return int_par(language_code); }
inline int& end_line_char(void) { return int_par(end_line_char_code); }
inline int global_defs(void) { return int_par(global_defs_code); }
inline int& hang_after(void) { return int_par(hang_after_code); }
inline int& escape_char(void) { return int_par(escape_char_code); }
inline int cur_fam(void) { return int_par(cur_fam_code); }
inline int& new_line_char(void) { return int_par(new_line_char_code); }
inline int default_hyphen_char(void) { return int_par(default_hyphen_char_code); }

halfword& glue_par(halfword);//!< |mem| location of glue specification
inline halfword& left_skip(void) { return glue_par(left_skip_code); }
inline halfword& right_skip(void) { return glue_par(right_skip_code); }
inline halfword& split_top_skip(void) { return glue_par(split_top_skip_code); }
inline halfword& space_skip(void) { return glue_par(space_skip_code); }

int& dimen_par(halfword); //! a scaled quantity
inline int display_indent(void) { return dimen_par(display_indent_code); }
inline int& overfull_rule(void) { return dimen_par(overfull_rule_code); }
inline int& vfuzz(void) { return dimen_par(vfuzz_code); }
inline int hsize(void) { return dimen_par(hsize_code); }
inline int split_max_depth(void) { return dimen_par(split_max_depth_code); }
inline int hang_indent(void) { return dimen_par(hang_indent_code); }
inline int par_indent(void) { return dimen_par(par_indent_code); }

#endif

#include "initprim.h"
#include "primitive.h"
#include "texte.h"

void initprim(void)
{
	nonewcontrolsequence = false;
	primitive("lineskip", assign_glue, glue_base+line_skip_code);
	primitive("baselineskip", assign_glue, glue_base+baseline_skip_code); 
	primitive("parskip", assign_glue, glue_base+par_skip_code); 
	primitive("abovedisplayskip", assign_glue, glue_base+above_display_skip_code);
	primitive("belowdisplayskip", assign_glue, glue_base+below_display_skip_code);
	primitive("abovedisplayshortskip", assign_glue, glue_base+above_display_short_skip_code);
	primitive("belowdisplayshortskip", assign_glue, glue_base+below_display_short_skip_code);
	primitive("leftskip", assign_glue, glue_base+left_skip_code); 
	primitive("rightskip", assign_glue, glue_base+right_skip_code); 
	primitive("topskip", assign_glue, glue_base+top_skip_code); 
	primitive("splittopskip", assign_glue, glue_base+split_top_skip_code);
	primitive("tabskip", assign_glue, glue_base+tab_skip_code); 
	primitive("spaceskip", assign_glue, glue_base+space_skip_code); 
	primitive("xspaceskip", assign_glue, glue_base+xspace_skip_code); 
	primitive("parfillskip", assign_glue, glue_base+par_fill_skip_code); 
	primitive("thinmuskip", assign_mu_glue, glue_base+thin_mu_skip_code);
	primitive("medmuskip", assign_mu_glue, glue_base+med_mu_skip_code);
	primitive("thickmuskip", assign_mu_glue, glue_base+thick_mu_skip_code);
	primitive("output", assign_toks, output_routine_loc);
	primitive("everypar", assign_toks, every_par_loc);
	primitive("everymath", assign_toks, every_math_loc);
	primitive("everydisplay", assign_toks, every_display_loc);
	primitive("everyhbox", assign_toks, every_hbox_loc);
	primitive("everyvbox", assign_toks, every_vbox_loc);
	primitive("everyjob", assign_toks, every_job_loc);
	primitive("everycr", assign_toks, every_cr_loc);
	primitive("errhelp", assign_toks, err_help_loc);
	primitive("pretolerance", assign_int, int_base+pretolerance_code); 
	primitive("tolerance", assign_int, int_base+tolerance_code); 
	primitive("linepenalty", assign_int, int_base+line_penalty_code); 
	primitive("hyphenpenalty", assign_int, int_base+hyphen_penalty_code); 
	primitive("exhyphenpenalty", assign_int, int_base+ex_hyphen_penalty_code); 
	primitive("clubpenalty", assign_int, int_base+club_penalty_code); 
	primitive("widowpenalty", assign_int, int_base+widow_penalty_code); 
	primitive("displaywidowpenalty", assign_int, int_base+display_widow_penalty_code); 
	primitive("brokenpenalty", assign_int, int_base+broken_penalty_code); 
	primitive("binoppenalty", assign_int, int_base+bin_op_penalty_code); 
	primitive("relpenalty", assign_int, int_base+rel_penalty_code); 
	primitive("predisplaypenalty", assign_int, int_base+pre_display_penalty_code); 
	primitive("postdisplaypenalty", assign_int, int_base+post_display_penalty_code); 
	primitive("interlinepenalty", assign_int, int_base+inter_line_penalty_code); 
	primitive("doublehyphendemerits", assign_int, int_base+double_hyphen_demerits_code); 
	primitive("finalhyphendemerits", assign_int, int_base+final_hyphen_demerits_code); 
	primitive("adjdemerits", assign_int, int_base+adj_demerits_code); 
	primitive("mag", assign_int, int_base+mag_code); 
	primitive("delimiterfactor", assign_int, int_base+delimiter_factor_code); 
	primitive("looseness", assign_int, int_base+looseness_code); 
	primitive("time", assign_int, int_base+time_code); 
	primitive("day", assign_int, int_base+day_code); 
	primitive("month", assign_int, int_base+month_code); 
	primitive("year", assign_int, int_base+year_code); 
	primitive("showboxbreadth", assign_int, int_base+show_box_breadth_code); 
	primitive("showboxdepth", assign_int, int_base+show_box_depth_code); 
	primitive("hbadness", assign_int, int_base+hbadness_code); 
	primitive("vbadness", assign_int, int_base+vbadness_code); 
	primitive("pausing", assign_int, int_base+pausing_code); 
	primitive("tracingonline", assign_int, int_base+tracing_online_code); 
	primitive("tracingmacros", assign_int, int_base+tracing_macros_code); 
	primitive("tracingstats", assign_int, int_base+tracing_stats_code); 
	primitive("tracingparagraphs", assign_int, int_base+tracing_paragraphs_code); 
	primitive("tracingpages", assign_int, int_base+tracing_pages_code); 
	primitive("tracingoutput", assign_int, int_base+tracing_output_code); 
	primitive("tracinglostchars", assign_int, int_base+tracing_lost_chars_code); 
	primitive("tracingcommands", assign_int, int_base+tracing_commands_code); 
	primitive("tracingrestores", assign_int, int_base+tracing_restores_code); 
	primitive("uchyph", assign_int, int_base+uc_hyph_code); 
	primitive("outputpenalty", assign_int, int_base+output_penalty_code); 
	primitive("maxdeadcycles", assign_int, int_base+max_dead_cycles_code); 
	primitive("hangafter", assign_int, int_base+hang_after_code); 
	primitive("floatingpenalty", assign_int, int_base+floating_penalty_code); 
	primitive("globaldefs", assign_int, int_base+global_defs_code); 
	primitive("fam", assign_int, int_base+cur_fam_code); 
	primitive("escapechar", assign_int, int_base+escape_char_code); 
	primitive("defaulthyphenchar", assign_int, int_base+default_hyphen_char_code); 
	primitive("defaultskewchar", assign_int, int_base+default_skew_char_code); 
	primitive("endlinechar", assign_int, int_base+end_line_char_code); 
	primitive("newlinechar", assign_int, int_base+new_line_char_code); 
	primitive("language", assign_int, int_base+language_code); 
	primitive("lefthyphenmin", assign_int, int_base+left_hyphen_min_code); 
	primitive("righthyphenmin", assign_int, int_base+right_hyphen_min_code); 
	primitive("holdinginserts", assign_int, int_base+holding_inserts_code); 
	primitive("errorcontextlines", assign_int, int_base+error_context_lines_code); 
	primitive("parindent", assign_dimen, dimen_base+par_indent_code); 
	primitive("mathsurround", assign_dimen, dimen_base+math_surround_code); 
	primitive("lineskiplimit", assign_dimen, dimen_base+line_skip_limit_code); 
	primitive("hsize", assign_dimen, dimen_base+hsize_code); 
	primitive("vsize", assign_dimen, dimen_base+vsize_code); 
	primitive("maxdepth", assign_dimen, dimen_base+max_depth_code); 
	primitive("splitmaxdepth", assign_dimen, dimen_base+split_max_depth_code); 
	primitive("boxmaxdepth", assign_dimen, dimen_base+box_max_depth_code); 
	primitive("hfuzz", assign_dimen, dimen_base+hfuzz_code); 
	primitive("vfuzz", assign_dimen, dimen_base+vfuzz_code); 
	primitive("delimitershortfall", assign_dimen, dimen_base+delimiter_shortfall_code); 
	primitive("nulldelimiterspace", assign_dimen, dimen_base+null_delimiter_space_code); 
	primitive("scriptspace", assign_dimen, dimen_base+script_space_code); 
	primitive("predisplaysize", assign_dimen, dimen_base+pre_display_size_code); 
	primitive("displaywidth", assign_dimen, dimen_base+display_width_code); 
	primitive("displayindent", assign_dimen, dimen_base+display_indent_code); 
	primitive("overfullrule", assign_dimen, dimen_base+overfull_rule_code); 
	primitive("hangindent", assign_dimen, dimen_base+hang_indent_code); 
	primitive("hoffset", assign_dimen, dimen_base+h_offset_code); 
	primitive("voffset", assign_dimen, dimen_base+v_offset_code); 
	primitive("emergencystretch", assign_dimen, dimen_base+emergency_stretch_code); 
	primitive(' ', ex_space, 0);
	primitive('/', ital_corr, 0);
	primitive("accent", accent, 0); 
	primitive("advance", advance, 0); 
	primitive("afterassignment", after_assignment, 0); 
	primitive("aftergroup", after_group, 0); 
	primitive("begingroup", begin_group, 0); 
	primitive("char", char_num, 0); 
	primitive("csname", cs_name, 0); 
	primitive("delimiter", delim_num, 0); 
	primitive("divide", divide, 0); 
	primitive("endcsname", end_cs_name, 0); 
	primitive("endgroup", end_group, 0); 
	text(frozen_end_group) = txt("endgroup");
	eqtb[frozen_end_group] = eqtb[curval];
	primitive("expandafter", expand_after, 0); 
	primitive("font", def_font, 0); 
	primitive("fontdimen", assign_font_dimen, 0); 
	primitive("halign", halign, 0); 
	primitive("hrule", hrule, 0); 
	primitive("ignorespaces", ignore_spaces, 0); 
	primitive("insert", insert, 0); 
	primitive("mark", mark, 0); 
	primitive("mathaccent", math_accent, 0); 
	primitive("mathchar", math_char_num, 0); 
	primitive("mathchoice", math_choice, 0); 
	primitive("multiply", multiply, 0); 
	primitive("noalign", no_align, 0); 
	primitive("noboundary", no_boundary, 0); 
	primitive("noexpand", no_expand, 0); 
	primitive("nonscript", non_script, 0); 
	primitive("omit", omit, 0); 
	primitive("parshape", set_shape, 0); 
	primitive("penalty", break_penalty, 0); 
	primitive("prevgraf", set_prev_graf, 0); 
	primitive("radical", radical, 0); 
	primitive("read", read_to_cs, 0); 
	primitive("relax", relax, 256); 
	text(frozen_relax) = txt("relax"); 
	eqtb[frozen_relax] = eqtb[curval];
	primitive("setbox", set_box, 0); 
	primitive("the", the, 0); 
	primitive("toks", toks_register, 0); 
	primitive("vadjust", vadjust, 0); 
	primitive("valign", valign, 0); 
	primitive("vcenter", vcenter, 0); 
	primitive("vrule", vrule, 0); 
	primitive("par", par_end, 256); 
	parloc = curval;
	partoken = cs_token_flag+parloc;
	primitive("input", input, 0); 
	primitive("endinput", input, 1); 
	primitive("topmark", top_bot_mark, top_mark_code); 
	primitive("firstmark", top_bot_mark, first_mark_code); 
	primitive("botmark", top_bot_mark, bot_mark_code); 
	primitive("splitfirstmark", top_bot_mark, split_first_mark_code); 
	primitive("splitbotmark", top_bot_mark, split_bot_mark_code); 
	primitive("count", register_, int_val); 
	primitive("dimen", register_, dimen_val); 
	primitive("skip", register_, glue_val); 
	primitive("muskip", register_, mu_val); 
	primitive("spacefactor", set_aux, hmode); 
	primitive("prevdepth", set_aux, vmode); 
	primitive("deadcycles", set_page_int, 0); 
	primitive("insertpenalties", set_page_int, 1); 
	primitive("wd", set_box_dimen, width_offset); 
	primitive("ht", set_box_dimen, height_offset); 
	primitive("dp", set_box_dimen, depth_offset); 
	primitive("lastpenalty", last_item, int_val); 
	primitive("lastkern", last_item, dimen_val); 
	primitive("lastskip", last_item, glue_val); 
	primitive("inputlineno", last_item, input_line_no_code); 
	primitive("badness", last_item, badness_code); 
	primitive("number", convert, number_code); 
	primitive("romannumeral", convert, roman_numeral_code); 
	primitive("string", convert, string_code); 
	primitive("meaning", convert, meaning_code); 
	primitive("fontname", convert, font_name_code); 
	primitive("jobname", convert, job_name_code); 
	primitive("if", if_test, if_char_code); 
	primitive("ifcat", if_test, if_cat_code); 
	primitive("ifnum", if_test, if_int_code); 
	primitive("ifdim", if_test, if_dim_code); 
	primitive("ifodd", if_test, if_odd_code); 
	primitive("ifvmode", if_test, if_vmode_code); 
	primitive("ifhmode", if_test, if_hmode_code); 
	primitive("ifmmode", if_test, if_mmode_code); 
	primitive("ifinner", if_test, if_inner_code); 
	primitive("ifvoid", if_test, if_void_code); 
	primitive("ifhbox", if_test, if_hbox_code); 
	primitive("ifvbox", if_test, if_vbox_code); 
	primitive("ifx", if_test, ifx_code); 
	primitive("ifeof", if_test, if_eof_code); 
	primitive("iftrue", if_test, if_true_code); 
	primitive("iffalse", if_test, if_false_code); 
	primitive("ifcase", if_test, if_case_code); 
	primitive("fi", fi_or_else, fi_code); 
	text(frozen_fi) = txt("fi");
	eqtb[frozen_fi] = eqtb[curval];
	primitive("or", fi_or_else, or_code); 
	primitive("else", fi_or_else, else_code); 
	primitive("nullfont", set_font, null_font); 
	text(frozen_null_font) = txt("nullfont");
	eqtb[frozen_null_font] = eqtb[curval]; 
	primitive("span", tab_mark, span_code); 
	primitive("cr", car_ret, cr_code); 
	text(frozen_cr) = txt("cr");
	eqtb[frozen_cr] = eqtb[curval];
	primitive("crcr", car_ret, cr_cr_code); 
	text(frozen_end_template) = txt("endtemplate");
	text(frozen_endv) = txt("endtemplate");
	eq_type(frozen_endv) = endv;
	equiv(frozen_endv) = null_list;
	eq_level(frozen_endv) = 1;
	eqtb[frozen_end_template] = eqtb[frozen_endv];
	eq_type(frozen_end_template) = end_template;
	primitive("pagegoal", set_page_dimen, 0); 
	primitive("pagetotal", set_page_dimen, 1); 
	primitive("pagestretch", set_page_dimen, 2); 
	primitive("pagefilstretch", set_page_dimen, 3); 
	primitive("pagefillstretch", set_page_dimen, 4); 
	primitive("pagefilllstretch", set_page_dimen, 5); 
	primitive("pageshrink", set_page_dimen, 6); 
	primitive("pagedepth", set_page_dimen, 7); 
	primitive("end", stop, 0); 
	primitive("dump", stop, 1); 
	primitive("hskip", hskip, skip_code); 
	primitive("hfil", hskip, fil_code); 
	primitive("hfill", hskip, fill_code); 
	primitive("hss", hskip, ss_code); 
	primitive("hfilneg", hskip, fil_neg_code); 
	primitive("vskip", vskip, skip_code); 
	primitive("vfil", vskip, fil_code); 
	primitive("vfill", vskip, fill_code); 
	primitive("vss", vskip, ss_code); 
	primitive("vfilneg", vskip, fil_neg_code); 
	primitive("mskip", mskip, mskip_code); 
	primitive("kern", kern, explicit_); 
	primitive("mkern", mkern, mu_glue); 
	primitive("moveleft", hmove, 1); 
	primitive("moveright", hmove, 0); 
	primitive("raise", vmove, 1); 
	primitive("lower", vmove, 0); 
	primitive("box", make_box, box_code); 
	primitive("copy", make_box, copy_code); 
	primitive("lastbox", make_box, last_box_code); 
	primitive("vsplit", make_box, vsplit_code); 
	primitive("vtop", make_box, vtop_code); 
	primitive("vbox", make_box, vtop_code+vmode); 
	primitive("hbox", make_box, vtop_code+hmode); 
	primitive("shipout", leader_ship, a_leaders-1); 
	primitive("leaders", leader_ship, a_leaders); 
	primitive("cleaders", leader_ship, c_leaders); 
	primitive("xleaders", leader_ship, x_leaders); 
	primitive("indent", start_par, 1); 
	primitive("noindent", start_par, 0); 
	primitive("unpenalty", remove_item, penalty_node); 
	primitive("unkern", remove_item, kern_node); 
	primitive("unskip", remove_item, glue_node); 
	primitive("unhbox", un_hbox, box_code); 
	primitive("unhcopy", un_hbox, copy_code); 
	primitive("unvbox", un_vbox, box_code); 
	primitive("unvcopy", un_vbox, copy_code); 
	primitive('-', discretionary, 1);
	primitive("discretionary", discretionary, 0); 
	primitive("eqno", eq_no, 0); 
	primitive("leqno", eq_no, 1); 
	primitive("mathord", math_comp, ord_noad); 
	primitive("mathop", math_comp, op_noad); 
	primitive("mathbin", math_comp, bin_noad); 
	primitive("mathrel", math_comp, rel_noad); 
	primitive("mathopen", math_comp, open_noad); 
	primitive("mathclose", math_comp, close_noad); 
	primitive("mathpunct", math_comp, punct_noad); 
	primitive("mathinner", math_comp, inner_noad); 
	primitive("underline", math_comp, under_noad); 
	primitive("overline", math_comp, over_noad); 
	primitive("displaylimits", limit_switch, normal); 
	primitive("limits", limit_switch, limits); 
	primitive("nolimits", limit_switch, no_limits); 
	primitive("displaystyle", math_style, display_style); 
	primitive("textstyle", math_style, text_style); 
	primitive("scriptstyle", math_style, script_style); 
	primitive("scriptscriptstyle", math_style, script_script_style); 
	primitive("above", above, above_code); 
	primitive("over", above, over_code); 
	primitive("atop", above, atop_code); 
	primitive("abovewithdelims", above, delimited_code+above_code); 
	primitive("overwithdelims", above, delimited_code+over_code); 
	primitive("atopwithdelims", above, delimited_code+atop_code); 
	primitive("left", left_right, left_noad); 
	primitive("right", left_right, right_noad); 
	text(frozen_right) = txt("right");
	eqtb[frozen_right] = eqtb[curval];
	primitive("long", prefix, 1); 
	primitive("outer", prefix, 2); 
	primitive("global", prefix, 4); 
	primitive("def", def, 0); 
	primitive("gdef", def, 1); 
	primitive("edef", def, 2); 
	primitive("xdef", def, 3); 
	primitive("let", let, normal); 
	primitive("futurelet", let, normal+1); 
	primitive("chardef", shorthand_def, char_def_code); 
	primitive("mathchardef", shorthand_def, math_char_def_code); 
	primitive("countdef", shorthand_def, count_def_code); 
	primitive("dimendef", shorthand_def, dimen_def_code); 
	primitive("skipdef", shorthand_def, skip_def_code); 
	primitive("muskipdef", shorthand_def, mu_skip_def_code); 
	primitive("toksdef", shorthand_def, toks_def_code); 
	primitive("catcode", def_code, cat_code_base); 
	primitive("mathcode", def_code, math_code_base); 
	primitive("lccode", def_code, lc_code_base); 
	primitive("uccode", def_code, uc_code_base); 
	primitive("sfcode", def_code, sf_code_base); 
	primitive("delcode", def_code, del_code_base); 
	primitive("textfont", def_family, math_font_base); 
	primitive("scriptfont", def_family, math_font_base+script_size); 
	primitive("scriptscriptfont", def_family, math_font_base+script_script_size); 
	primitive("hyphenation", hyph_data, 0); 
	primitive("patterns", hyph_data, 1); 
	primitive("hyphenchar", assign_font_int, 0); 
	primitive("skewchar", assign_font_int, 1); 
	primitive("batchmode", set_interaction, batch_mode); 
	primitive("nonstopmode", set_interaction, nonstop_mode); 
	primitive("scrollmode", set_interaction, scroll_mode); 
	primitive("errorstopmode", set_interaction, error_stop_mode); 
	primitive("openin", in_stream, 1); 
	primitive("closein", in_stream, 0); 
	primitive("message", message, 0); 
	primitive("errmessage", message, 1); 
	primitive("lowercase", case_shift, lc_code_base); 
	primitive("uppercase", case_shift, uc_code_base); 
	primitive("show", xray, show_code); 
	primitive("showbox", xray, show_box_code); 
	primitive("showthe", xray, show_the_code); 
	primitive("showlists", xray, show_lists); 
	primitive("openout", extension, open_node); 
	primitive("write", extension, write_node); 
	writeloc = curval; 
	primitive("closeout", extension, close_node); 
	primitive("special", extension, special_node); 
	primitive("immediate", extension, immediate_code); 
	primitive("setlanguage", extension, set_language_code);
	nonewcontrolsequence = true;
}

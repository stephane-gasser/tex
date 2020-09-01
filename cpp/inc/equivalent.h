#ifndef EQUIVALENT_H
#define EQUIVALENT_H

#include "globals.h"
#include "parametres.h"

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
			frozen_dont_expand = frozen_control_sequence+9, //!< permanent `\\notexpanded'
			frozen_null_font = frozen_control_sequence+10, //!< permanent `\\nullfont'
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
		cat_code_base = math_font_base+48, //!< table of 256 command codes (the ``catcodes'')
		lc_code_base = cat_code_base+256, //!< table of 256 lowercase mappings
		uc_code_base = lc_code_base+256, //!< table of 256 uppercase mappings
		sf_code_base = uc_code_base+256, //!< table of 256 spacefactor mappings
		math_code_base = sf_code_base+256, //!< table of 256 math mode mappings
	int_base = math_code_base+256, //!< beginning of region 5
		count_base = int_base+int_pars, //!< 256 user \\count registers
		del_code_base = count_base+256, //!< 256 delimiter code mappings
	dimen_base = del_code_base+256, //!< beginning of region 6
		scaled_base = dimen_base+dimen_pars, //!< table of 256 user-defined \\dimen registers
	eqtb_size = scaled_base+255 //!< largest subscript of \a eqtb
};

constexpr int end_template_token = cs_token_flag+frozen_end_template;

class MemoryNode : public AnyNode
{
	public:
		quarterword type; //!< command code for equivalent
		quarterword level; //!< level of definition
		AnyNode *index; //!< equivalent value
		int int_; //!< equivalent value
		MemoryNode(quarterword t = 0, quarterword l = 0, AnyNode *i = nullptr) : type(t), level(l), index(i) {}
		bool operator == (const MemoryNode &m) { return std::tuple(type, level, index, int_) == std::tuple(m.type, m.level, m.index, m.int_); }
		bool operator != (const MemoryNode &m) { return std::tuple(type, level, index, int_) != std::tuple(m.type, m.level, m.index, m.int_); }
};

inline std::vector<MemoryNode> eqtb(6107); // débute à 1

// control sequences
inline std::vector<MemoryNode> eqtb_active(hash_base-active_base); //  holds the current equivalents of single-character control sequences.
	// 256 active characters
	// 256 single letter control sequences
	// 1 null control sequence
inline std::vector<MemoryNode> eqtb_cs(glue_base-hash_base); // holds the current equivalents of multiletter control sequences.
	// 2100 (hash_size) control sequences
	// 11 frozen control sequences
	// 256 fonts
	// 1 undefined control sequence
// glues
inline std::vector<MemoryNode> eqtb_glue(local_base-glue_base); // holds the current equivalents of glue parameters like the current baselineskip.
	// 18 glue parameters
	inline GlueSpec* glue_par(halfword p) { return dynamic_cast<GlueSpec*>(eqtb_glue[p].index); } //!< |mem| location of glue specification
		inline GlueSpec *left_skip(void) { return glue_par(left_skip_code); }
		inline void setLeftSkip(GlueSpec *g) { eqtb_glue[left_skip_code].index = g; }
		inline GlueSpec *right_skip(void) { return glue_par(right_skip_code);  }
		inline void setRightSkip(GlueSpec *g) { eqtb_glue[right_skip_code].index = g; }
		inline GlueSpec *split_top_skip(void) { return glue_par(split_top_skip_code); }
		inline void setSplitTopSkip(GlueSpec *g) { eqtb_glue[split_top_skip_code].index = g; }
		inline GlueSpec *space_skip(void) { return glue_par(space_skip_code); }
		inline GlueSpec *xspace_skip(void) { return glue_par(xspace_skip_code); }
		inline GlueSpec *baseline_skip(void) { return glue_par(baseline_skip_code); }
		inline GlueSpec *line_skip(void) { return glue_par(line_skip_code); }
	// 256 text glues
	inline GlueSpec* skip(halfword p) { return dynamic_cast<GlueSpec*>(eqtb_glue[p+skip_base-glue_base].index); } //! location of glue spec
	// 256 math glues
	inline GlueSpec* mu_skip(halfword p) { return dynamic_cast<GlueSpec*>(eqtb_glue[p+mu_skip_base-glue_base].index); } //! location of math glue spec
// local
inline std::vector<MemoryNode> eqtb_local(int_base-local_base); // holds the current equivalents of local halfword quantities like the current box registers, the current ``catcodes,'' the current font, and a pointer to the current paragraph shape.
	// 1 paragraph shape
	inline ShapeNode* par_shape_ptr(void) { return dynamic_cast<ShapeNode*>(eqtb_local[par_shape_loc-local_base].index); }
	// 9 tokens lists
	inline TokenNode* output_routine(void) { return dynamic_cast<TokenNode*>(eqtb_local[output_routine_loc-local_base].index); }
	inline TokenNode* every_par(void) { return dynamic_cast<TokenNode*>(eqtb_local[every_par_loc-local_base].index); } //!< points to token list for \\everypar
	inline TokenNode* every_math(void) { return dynamic_cast<TokenNode*>(eqtb_local[every_math_loc-local_base].index); }
	inline TokenNode *every_display(void) { return dynamic_cast<TokenNode*>(eqtb_local[every_display_loc-local_base].index); }
	inline TokenNode* every_hbox(void) { return dynamic_cast<TokenNode*>(eqtb_local[every_hbox_loc-local_base].index); }
	inline TokenNode* every_vbox(void) { return dynamic_cast<TokenNode*>(eqtb_local[every_vbox_loc-local_base].index); } //!< points to token list for \\everyvbox
	inline TokenNode* every_job(void) { return dynamic_cast<TokenNode*>(eqtb_local[every_job_loc-local_base].index); }
	inline TokenNode* every_cr(void) { return dynamic_cast<TokenNode*>(eqtb_local[every_cr_loc-local_base].index); } //!< points to token list for \\everyvbox
	inline TokenNode* err_help(void) { return dynamic_cast<TokenNode*>(eqtb_local[err_help_loc-local_base].index); }
	// 256 token list registers
	// 256 box registers
	inline BoxNode* box(halfword p) { return dynamic_cast<BoxNode*>(eqtb_local[p+box_base-local_base].index); }
	inline void setBox(halfword p, BoxNode *b) { eqtb_local[p+box_base-local_base].index = b; }
	// 1 current math font number
	// 48 math font number
	inline int& math_code(halfword p) { return eqtb_local[p+math_code_base-local_base].int_; }
	// 256 cat_codes
	inline int& cat_code(halfword p) { return eqtb_local[p+cat_code_base-local_base].int_; }
	// 256 lowercase mappings
	inline int& lc_code(halfword p) { return eqtb_local[p+lc_code_base-local_base].int_; }
	// 256 uppercase mappings
	inline int& uc_code(halfword p) { return eqtb_local[p+uc_code_base-local_base].int_; }
	// 256 spacefactor mappings
	inline int& sf_code(halfword p) { return eqtb_local[p+sf_code_base-local_base].int_; }
	// 256 math mode mappings
// integer
inline std::vector<MemoryNode> eqtb_int(dimen_base-int_base); // holds the current equivalents of fullword integer parameters like the current hyphenation penalty.
	// 55 integer parameters
	inline int& int_par(halfword p) { return eqtb_int[p].int_; } //!< an integer parameter
		inline int delimiter_factor(void) { return int_par(delimiter_factor_code); }
		inline int bin_op_penalty(void) { return int_par(bin_op_penalty_code); }
		inline int rel_penalty(void) { return int_par(rel_penalty_code); }
		inline int hbadness(void) { return int_par(hbadness_code); }
		inline int tracing_lost_chars(void) { return int_par(tracing_lost_chars_code); }
		inline int widow_penalty(void) { return int_par(widow_penalty_code); }
		inline int holding_inserts(void) { return int_par(holding_inserts_code); }
		inline int pausing(void) { return int_par(pausing_code); }
		inline int floating_penalty(void) { return int_par(floating_penalty_code); }
		inline int adj_demerits(void) { return int_par(adj_demerits_code); }
		inline int double_hyphen_demerits(void) { return int_par(double_hyphen_demerits_code); }
		inline int final_hyphen_demerits(void) { return int_par(final_hyphen_demerits_code); }
		inline int line_penalty(void) { return int_par(line_penalty_code); }
		inline int& tracing_stats(void) { return int_par(tracing_stats_code); }
		inline int tracing_output(void) { return int_par(tracing_output_code); }
		inline int broken_penalty(void) { return int_par(broken_penalty_code); }
		inline int club_penalty(void) { return int_par(club_penalty_code); }
		inline int inter_line_penalty(void) { return int_par(inter_line_penalty_code); }
		inline int default_skew_char(void) { return int_par(default_skew_char_code); }
		inline int hyphen_penalty(void) { return int_par(hyphen_penalty_code); }
		inline int pretolerance(void) { return int_par(pretolerance_code); }
		inline int uc_hyph(void) { return int_par(uc_hyph_code); }
		inline int display_widow_penalty(void) { return int_par(display_widow_penalty_code); } 
		inline int show_box_breadth(void) { return int_par(show_box_breadth_code); }
		inline int show_box_depth(void) { return int_par(show_box_depth_code); }
		inline int error_context_lines(void) { return int_par(error_context_lines_code); }
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
			inline bool end_line_char_inactive() { return end_line_char() < 0 || end_line_char() > 255; }
		inline int global_defs(void) { return int_par(global_defs_code); }
		inline int& hang_after(void) { return int_par(hang_after_code); }
		inline int& escape_char(void) { return int_par(escape_char_code); }
		inline int cur_fam(void) { return int_par(cur_fam_code); }
		inline bool fam_in_range(void) { return cur_fam() >= 0 && cur_fam() < 16; }
		inline int& new_line_char(void) { return int_par(new_line_char_code); }
		inline int default_hyphen_char(void) { return int_par(default_hyphen_char_code); }
	// 256 count registers
	inline int& count(halfword p) { return eqtb_int[p+count_base-int_base].int_; }
	// 256 delimiter code mappings
	inline int& del_code(halfword p) { return eqtb_int[p+del_code_base-int_base].int_; }
// dimensions
inline std::vector<MemoryNode> eqtb_dimen(eqtb_size-dimen_base); // holds the current equivalents of fullword dimension parameters like the current hsize or amount of hanging indentation.
	// 21 dimension parameters
	inline int& dimen_par(halfword p) { return eqtb_dimen[p].int_; } //! a scaled quantity
		inline int display_indent(void) { return dimen_par(display_indent_code); }
		inline int& overfull_rule(void) { return dimen_par(overfull_rule_code); }
		inline int& vfuzz(void) { return dimen_par(vfuzz_code); }
		inline int hsize(void) { return dimen_par(hsize_code); }
		inline int split_max_depth(void) { return dimen_par(split_max_depth_code); }
		inline int hang_indent(void) { return dimen_par(hang_indent_code); }
		inline int par_indent(void) { return dimen_par(par_indent_code); }
		inline int display_width(void) { return dimen_par(display_width_code); }
		inline int math_surround(void) { return dimen_par(math_surround_code); }
		inline int pre_display_size(void) { return dimen_par(pre_display_size_code); }
		inline int hfuzz(void) { return dimen_par(hfuzz_code); }
		inline int box_max_depth(void) { return dimen_par(box_max_depth_code); }
		inline int script_space(void) { return dimen_par(script_space_code); }
		inline int delimiter_shortfall(void) { return dimen_par(delimiter_shortfall_code); }
		inline int vsize(void) { return dimen_par(vsize_code); }
		inline int emergency_stretch(void) { return dimen_par(emergency_stretch_code); }
		inline int line_skip_limit(void) { return dimen_par(line_skip_limit_code); }
		inline int h_offset(void) { return dimen_par(h_offset_code); }
		inline int v_offset(void) { return dimen_par(v_offset_code); }
		inline int null_delimiter_space(void) { return dimen_par(null_delimiter_space_code); }
	// 256 dimen registers
	inline int& dimen(halfword p) { return eqtb_dimen[p+scaled_base-dimen_base].int_; } 

inline quarterword xeqlevel[6107]; // débute à 5263
inline std::vector<MemoryNode*> savestack;

void eqworddefine(MemoryNode*, int);
void word_define(int, MemoryNode*, int);
void geqworddefine(MemoryNode*, int);
void define(int a, MemoryNode*, quarterword, halfword);
void define_(int a, MemoryNode*, quarterword, AnyNode*);
void eqdefine(MemoryNode*, quarterword, halfword);
void geqdefine(MemoryNode*, quarterword, halfword);
void eqdefine_(MemoryNode*, quarterword, AnyNode*);
void geqdefine_(MemoryNode*, quarterword, AnyNode*);
void eqdestroy(MemoryNode*);

#endif

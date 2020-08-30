#ifndef EQUIVALENT_H
#define EQUIVALENT_H

#include "globals.h"

class MemoryNode : public AnyNode
{
	public:
		quarterword type;
		quarterword level;
		AnyNode *index;
		int int_;
		MemoryNode(quarterword t = 0, quarterword l = 0, AnyNode *i = nullptr) : type(t), level(l), index(i) {}
		bool operator == (const MemoryNode &m) { return std::tuple(type, level, index, int_) == std::tuple(m.type, m.level, m.index, m.int_); }
		bool operator != (const MemoryNode &m) { return std::tuple(type, level, index, int_) != std::tuple(m.type, m.level, m.index, m.int_); }
};

void eqworddefine(MemoryNode*, int);
void word_define(int, MemoryNode*, int);
void geqworddefine(MemoryNode*, int);
void define(int a, MemoryNode*, quarterword, halfword);
void eqdefine(MemoryNode*, quarterword, halfword);
void geqdefine(MemoryNode*, quarterword, halfword);
void eqdestroy(MemoryNode*);
quarterword& eq_level(halfword);
quarterword& eq_type(halfword); //!< command code for equivalent
halfword& equiv(halfword); //!< equivalent value
int& del_code(halfword);
int& count(halfword);
int& dimen(halfword);
inline std::vector<GlueSpec*> skip(256);
//! |mem| location of math glue spec
//static halfword& mu_skip(halfword p) { return equiv(mu_skip_base+p); }
inline std::vector<GlueSpec*> mu_skip(256);
int& cat_code(halfword);
int& lc_code(halfword);
int& sf_code(halfword);
int& math_code(halfword);
ShapeNode *par_shape_ptr(void);

inline std::vector<MemoryNode> eqtb(6107); // débute à 1
inline std::vector<MemoryNode> eqtb_active(hash_base-active_base); // |eqtb[active_base..(hash_base-1)]| holds the current equivalents of single-character control sequences.
inline std::vector<MemoryNode> eqtb_cs(glue_base-hash_base); // |eqtb[hash_base..(glue_base-1)]| holds the current equivalents of multiletter control sequences.
inline std::vector<MemoryNode> eqtb_glue(local_base-glue_base); // |eqtb[glue_base..(local_base-1)]| holds the current equivalents of glue parameters like the current baselineskip.
inline std::vector<MemoryNode> eqtb_local(int_base-local_base); // |eqtb[local_base..(int_base-1)]| holds the current equivalents of local halfword quantities like the current box registers, the current ``catcodes,'' the current font, and a pointer to the current paragraph shape.
inline std::vector<MemoryNode> eqtb_int(dimen_base-int_base); // |eqtb[int_base..(dimen_base-1)]| holds the current equivalents of fullword integer parameters like the current hyphenation penalty.
inline std::vector<MemoryNode> eqtb_dimen(eqtb_size-dimen_base); // |eqtb[dimen_base..eqtb_size]| holds the current equivalents of fullword dimension parameters like the current hsize or amount of hanging indentation.
inline quarterword xeqlevel[6107]; // débute à 5263
inline std::vector<MemoryNode*> savestack;

#endif

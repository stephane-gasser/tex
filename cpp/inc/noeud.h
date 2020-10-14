#ifndef NOEUD_H
#define NOEUD_H

#include "globals.h"
#include "token.h"
#include "police.h"
#include <tuple>

enum
{
	hlist_node = 0, //!< \a type of hlist nodes
	vlist_node = 1, //!< \a type of vlist nodes
	rule_node = 2, //!< \a type of rule nodes
	ins_node = 3, //!< \a type of insertion nodes
	mark_node = 4, //!< \a type of a mark node
	adjust_node = 5, //!< \a type of an adjust node
	ligature_node = 6, //!< \a type of a ligature node
	disc_node = 7, //!< \a type of a discretionary node
	whatsit_node = 8, //!< \a type of special extension nodes
	math_node = 9, //!< \a type of a math node
	glue_node = 10, //!< \a type of node that points to a glue specification
	kern_node = 11, //!< \a type of a kern node
	penalty_node = 12, //!< \a type of a penalty node
	unset_node = 13, //!< \a type for an unset node
	style_node = unset_node+1, //!< \a type of a style node
	choice_node = unset_node+2, //!< \a type of a choice node
	ord_noad = unset_node+3, //!< \a type of a noad classified Ord
	op_noad = ord_noad+1, //!< \a type of a noad classified Op
	bin_noad = ord_noad+2, //!< \a type of a noad classified Bin
	rel_noad = ord_noad+3, //!< \a type of a noad classified Rel
	open_noad = ord_noad+4, //!< \a type of a noad classified Ope
	close_noad = ord_noad+5, //!< \a type of a noad classified Clo
	punct_noad = ord_noad+6, //!< \a type of a noad classified Pun
	inner_noad = ord_noad+7, //!< \a type of a noad classified Inn
	radical_noad = inner_noad+1, //!< \a type of a noad for square roots
	fraction_noad = radical_noad+1, //!< \a type of a noad for generalized fractions
	under_noad = fraction_noad+1, //!< \a type of a noad for underlining
	over_noad = under_noad+1, //!< \a type of a noad for overlining
	accent_noad = over_noad+1, //!< \a type of a noad for accented subformulas
	vcenter_noad = accent_noad+1, //!< \a type of a noad for \\vcenter
	left_noad = vcenter_noad+1, //!< \a type of a noad for \\left
	right_noad = left_noad+1, //!< \a type of a noad for \\right
	char_node = 255
};

class PassiveNode;

class LinkedNode : public AnyNode
{
	public:
		LinkedNode *link = nullptr;
		~LinkedNode(void);
		virtual LinkedNode *copy(void);
		virtual std::string shortDisplay(void) { return ""; }
		virtual std::string showNode(const std::string &) { return "Unknown node type!"; }
		virtual quarterword getSubtype(void) { return 0; }
		virtual void vlist(scaled) {}
		virtual void hlist(scaled, scaled, scaled) {}
		virtual scaled getHeight(void) { return 0; }
		virtual scaled getDepth(void) { return 0; }
		virtual scaled getWidth(void) { return 0; }
		virtual int getPenalty(void) { return 0; }
		virtual void update_width(void) {}
		virtual void convert_to_break_width(void) {}
		virtual void downdate_width(void) {}
		virtual void update_active(void) {}
		virtual halfword getLineNumber(void) { return 0; }
		virtual quarterword getFitness(void) { return 0; }
		virtual int getTotalDemerits(void) { return 0; }
		virtual PassiveNode *getBreak(void) { return nullptr; }
		virtual void setWidth(scaled) {}
		virtual LinkedNode *curBreak(void) { return nullptr; }
		virtual LinkedNode *prevBreak(void) { return nullptr; }
		virtual LinkedNode *nextBreak(void) { return nullptr; }
		virtual void mToH(void) {}
		virtual void mToH(scaled&, scaled&) {}
		virtual void mToH(LinkedNode*&) {}
		virtual bool mToH(scaled&, scaled&, scaled&) { return false; }
		virtual void mToH2(scaled&, scaled&, scaled&) {}
		virtual void out(void) {}
};

class ShapeNode : public LinkedNode
{
	public:
		std::vector<int> values; // info = .size()/2
		ShapeNode(int);
};

class CharNode : public LinkedNode
{
	public:
		internalfontnumber font; //type
		quarterword character; //subtype
		CharNode(internalfontnumber f, quarterword c) : font(f), character(c) { type = char_node; }
		virtual CharNode* copy(void) { return new CharNode(font, character); }
		int width(void);
		int depth(void);
		int height(void);
		int italic(void);
		virtual scaled getWidth(void) { return width(); }
		virtual std::string shortDisplay(void);
		virtual std::string showNode(const std::string &);
		virtual void vlist(scaled);
		virtual void hlist(scaled, scaled, scaled);
};

extern std::vector<Font> fonts;

class LigatureNode : public CharNode
{
	public:
		CharNode *lig_ptr;
		quarterword subtype; // 0: AB, 1: A_ 2: _B 3: __
		LigatureNode(internalfontnumber f, quarterword c, CharNode *q) : subtype(0), CharNode(f, c), lig_ptr(q) { type = ligature_node; }
		LigatureNode(quarterword c) : subtype(0), CharNode(null_font, c), lig_ptr(nullptr) { type = ligature_node; } //newligitem
		~LigatureNode(void);
		virtual LigatureNode* copy(void);
		virtual std::string shortDisplay(void);
		std::string showNode(const std::string &);
		virtual void hlist(scaled, scaled, scaled);
};


class ChoiceNode : public LinkedNode
{
	public:
		LinkedNode *display_mlist = nullptr; //!< mlist to be used in display style
		LinkedNode *text_mlist = nullptr; //!< mlist to be used in text style
		LinkedNode *script_mlist = nullptr; //!< mlist to be used in script style
		LinkedNode *script_script_mlist = nullptr; //!< mlist to be used in scriptscript style
		ChoiceNode(void) { type = choice_node; }
		~ChoiceNode(void);
		std::string showNode(const std::string &);
		virtual void mToH(LinkedNode*&);
};

class DiscNode : public LinkedNode
{
	public:
		quarterword replace_count = 0; //!< how many subsequent nodes to replace
		LinkedNode *pre_break = nullptr; //!< text that precedes a discretionary break
		LinkedNode *post_break = nullptr; //!< text that follows a discretionary break
		DiscNode(void) { type = disc_node; }
		~DiscNode(void);
		DiscNode *copy(void);
		virtual std::string shortDisplay(void);
		std::string showNode(const std::string &);
};

class KernNode : public LinkedNode
{
	public:
		quarterword subtype; // normal/explicit_/acc_kern/mu_glue
		scaled width; //(normally negative) amount of spacing
		KernNode(scaled w, quarterword s = 0) : width(w), subtype(s) { type = kern_node; }
		virtual KernNode *copy(void) { return new KernNode(width, subtype); }
		void mathkern(scaled);
		std::string showNode(const std::string &);
		virtual quarterword getSubtype(void) { return subtype; }
		virtual void vlist(scaled);
		virtual void hlist(scaled, scaled, scaled);
		virtual scaled getWidth(void) { return width; }
		virtual void setWidth(scaled w) { width = w; }
		virtual void mToH(void);
};

class GlueSpec : public AnyNode
{
	public:
		halfword glue_ref_count = 1;
		scaled width = 0, stretch = 0, shrink = 0;
		glueord stretch_order = 0, shrink_order = 0; // normal/fil/fill/filll
		GlueSpec(void) {}
		GlueSpec(GlueSpec *p) 
		{ 
			width = p->width; 
			stretch = p->stretch; 
			shrink = p->shrink; 
			stretch_order = p->stretch_order; 
			shrink_order = p->shrink_order; 
			glue_ref_count = 0; 
		}
		std::string print(const std::string & = "");
};

class InsNode : public LinkedNode
{
	public:
		quarterword subtype; //corresponding box number
		scaled height; //natural height plus depth of the vertical list being inserted
		scaled depth; //|split_max_depth| to be used in case this insertion is split
		GlueSpec *split_top_ptr; //the |split_top_skip| to be used
		int float_cost; //the |floating_penalty| to be used
		LinkedNode *ins_ptr; //the vertical list to be inserted
		InsNode(void) { type = ins_node; }
		~InsNode(void);
		virtual InsNode *copy(void);
		virtual std::string shortDisplay(void) { return "[]"; }
		virtual std::string showNode(const std::string &);
};

class MarkNode : public LinkedNode
{
	public:
		TokenList *mark_ptr = &defRef;
		MarkNode(void) { type = mark_node; }
		~MarkNode(void) { mark_ptr->deleteTokenRef(); }
		virtual MarkNode *copy(void) { auto m = new MarkNode; m->mark_ptr = mark_ptr; mark_ptr->token_ref_count++; return m; }
		virtual std::string shortDisplay(void) { return "[]"; }
		std::string showNode(const std::string &);
};

class AdjustNode : public LinkedNode
{
	public:
		LinkedNode *adjust_ptr;
		AdjustNode(void) { type = adjust_node; }
		~AdjustNode(void);
		virtual AdjustNode *copy(void);
		virtual std::string shortDisplay(void) { return "[]"; }
		std::string showNode(const std::string &);
};

class PageInsNode : public LinkedNode
{
	public:
		quarterword subtype; 
		scaled height;
		LinkedNode *broken_ptr; // an insertion for this class will break here if anywhere
		LinkedNode* broken_ins; // this insertion might break at |broken_ptr|
		LinkedNode *last_ins_ptr; // the most recent insertion for this |subtype|
		LinkedNode* best_ins_ptr;// the optimum most recent insertion
		PageInsNode(void) {}
};

GlueSpec *glue_par(halfword);

class GlueNode : public LinkedNode
{
	public:
		quarterword subtype;
		LinkedNode *leader_ptr = nullptr; //!< pointer to box or rule node for leaders
		GlueSpec *glue_ptr; //!< pointer to a glue specification
		GlueNode(GlueSpec *g) : subtype(0), glue_ptr(g) { type = glue_node; g->glue_ref_count++; }
		GlueNode(smallnumber n) : subtype(n+1) { type = glue_node; glue_ptr = glue_par(n); glue_ptr->glue_ref_count++; }
		~GlueNode(void);
		virtual GlueNode *copy(void);
		virtual std::string shortDisplay(void);
		std::string showNode(const std::string &);
		virtual void mToH(scaled&, scaled&);
};

class PenaltyNode : public LinkedNode
{
	public:
		int penalty;
		PenaltyNode(int p = 0) : penalty(p) { type = penalty_node; } 
		virtual PenaltyNode *copy(void) { return new PenaltyNode(penalty); }
		std::string showNode(const std::string &);
		virtual int getPenalty(void) { return penalty; }
};

class RuleNode : public LinkedNode
{
	public:
		quarterword subtype = 0;
		int width = -(1<<30); //null_flag
		int depth = -(1<<30); //null_flag
		int height = -(1<<30); //null_flag
		RuleNode(void) { type = rule_node; }
		RuleNode(scaled t) : depth(0), height(t) { type = rule_node; }
		virtual RuleNode *copy(void) { auto r = new RuleNode; r->width = width; r->depth = depth; r->height = height; return r; }
		virtual std::string shortDisplay(void) { return "|"; }
		virtual std::string showNode(const std::string &);
		virtual void vlist(scaled);
		virtual void hlist(scaled, scaled, scaled);
		virtual scaled getHeight(void) { return height; }
		virtual scaled getWidth(void) { return width; }
		virtual scaled getDepth(void) { return depth; }
		virtual void mToH(scaled&, scaled&);
		virtual void setShift(scaled s) {}
};

class BoxNode : public RuleNode
{
	public:
		scaled shift_amount = 0; //!< repositioning distance, in sp
		LinkedNode *list_ptr = nullptr; //!< beginning of the list inside the box
		quarterword glue_sign = 0; //normal  //!< stretching or shrinking
		quarterword glue_order = 0; //normal //!< applicable order of infinity
		float glue_set = 0.0;
		BoxNode(void) { type = hlist_node; subtype = 0; width = depth = height = 0; } 
		~BoxNode(void);
		virtual BoxNode *copy(void);
		virtual std::string shortDisplay(void) { return "[]"; }
		virtual std::string showNode(const std::string &);
		virtual void vlist(scaled);
		virtual void hlist(scaled, scaled, scaled);
		virtual void setShift(scaled s) { shift_amount = s; }
};

class UnsetNode : public BoxNode
{
	public:
		quarterword &span_count = BoxNode::subtype;
		// pas de glue_set ni de shift_amount
		scaled glue_shrink;
		scaled glue_stretch;
		UnsetNode(void) : BoxNode() { type = unset_node; span_count = 0; } 
		virtual UnsetNode *copy(void);
		virtual std::string showNode(const std::string &);
		virtual void setShift(scaled s) {}
};

class StyleNode : public LinkedNode
{
	public:
		quarterword subtype;
		StyleNode(smallnumber s) : subtype(s) { type = style_node; }
		std::string showNode(const std::string &);
		virtual quarterword getSubtype(void) { return subtype; }
};

inline BoxNode *justbox;

class MathNode : public LinkedNode
{
	public:
		quarterword subtype;
		int width;
		MathNode(scaled w, smallnumber s) : subtype(s), width(w) { type = math_node; }
		virtual MathNode *copy(void) { return new MathNode(width, subtype); }
		virtual std::string shortDisplay(void) { return "$"; }
		std::string showNode(const std::string &);
		virtual void hlist(scaled, scaled, scaled);
		virtual scaled getWidth(void) { return width; }
		virtual void setWidth(scaled w) { width = w; }
		virtual quarterword getSubtype(void) { return subtype; }
};

class WhatsitNode : public LinkedNode
{
	public:
		quarterword subtype;
		WhatsitNode(smallnumber s) : subtype(s) { type = whatsit_node; }
		~WhatsitNode(void);
		virtual WhatsitNode *copy(void);
		virtual std::string shortDisplay(void) { return "[]"; }
		virtual std::string showNode(const std::string &);
		virtual void vlist(scaled);
		virtual void hlist(scaled, scaled, scaled);
		virtual quarterword getSubtype(void) { return subtype; }
};

class WriteWhatsitNode : public WhatsitNode
{
	public:
		halfword write_stream; //!< stream number (0 to 17)
		WriteWhatsitNode(smallnumber s) : WhatsitNode(s) {}
		virtual std::string showNode(const std::string &);
};

class OpenWriteWhatsitNode : public WriteWhatsitNode
{
	public:
		std::string open_name; //!< string number of file name to open
		std::string open_area; //!< string number of file area for \a open_name
		std::string open_ext; //!< string number of file extension for \a open_name
		OpenWriteWhatsitNode(int s) : WriteWhatsitNode(open_node) { write_stream = s; }
		virtual OpenWriteWhatsitNode *copy(void) { auto w = new OpenWriteWhatsitNode(write_stream); w->open_name = open_name; w->open_area = open_area; w->open_ext = open_ext; return w; }
		virtual std::string showNode(const std::string &);
		virtual void out(void);
};

class NotOpenWriteWhatsitNode : public WriteWhatsitNode
{
	public:
		TokenList *write_tokens; //!< reference count of token list to write
		NotOpenWriteWhatsitNode(smallnumber s, int val) : WriteWhatsitNode(s)
		{
			val = std::min(val, 16);
			if (val < 0)
				val = 17;
			write_stream = val;
		}
		~NotOpenWriteWhatsitNode(void) { if (write_tokens) write_tokens->deleteTokenRef(); }
		virtual NotOpenWriteWhatsitNode *copy(void) 
		{ 
			auto w = new NotOpenWriteWhatsitNode(subtype, write_stream); 
			w->write_tokens = write_tokens;
			w->write_stream = write_stream; 
			write_tokens->token_ref_count++; 
			return w; 
		}
		virtual std::string showNode(const std::string &);
		virtual void out(void);
};

class LanguageWhatsitNode : public WhatsitNode
{
	public:
		halfword what_lang; //!< language number, in the range 0..255
		quarterword what_lhm; //!< minimum left fragment, in the range 1..63
		quarterword what_rhm; //!< minimum right fragment, in the range 1..63
		LanguageWhatsitNode(ASCIIcode);
		virtual LanguageWhatsitNode *copy(void) { auto l = new LanguageWhatsitNode(what_lang); l->what_lhm = what_lhm; l->what_rhm = what_rhm; return l; }
		virtual std::string showNode(const std::string &);
};

class NoadContent : public AnyNode
{
	public:
		halfword math_type = 0;
		LinkedNode *info = nullptr;
		quarterword character = 0;
		quarterword fam = 0;
		~NoadContent(void);
		bool operator == (const NoadContent &n) { return std::tuple(math_type, info, character, fam) == std::tuple(n.math_type, n.info, n.character, n.fam); }
		std::string subsidiarydata(char c, const std::string &symbol);
		std::string famandchar(void);
		void scan(char);
};

class Noad : public LinkedNode
{
	public:
		quarterword subtype;
		NoadContent nucleus;
		NoadContent subscr;
		NoadContent supscr;
		Noad(void) : subtype(normal) { type = ord_noad; }
		Noad(quarterword t) : subtype(normal) { type = t; }
		Noad(quarterword ch, quarterword fam, quarterword tp) : subtype(normal) 
		{
			nucleus.math_type = math_char;
			nucleus.character = ch;
			nucleus.fam = fam;
			tp += ord_noad;
			switch (tp)
			{	
				case op_noad:
				case bin_noad:
				case rel_noad:
				case open_noad:
				case close_noad:
				case punct_noad:
					type = tp;
					break;
				default:
					type = ord_noad;
			}
		}
		virtual std::string showNode(const std::string &);
		virtual void mToH(scaled&, scaled&);
		virtual bool mToH(scaled&, scaled&, scaled&);
		virtual void mToH2(scaled&, scaled&, scaled&);
};

class Delimiter
{
	public:
		quarterword small_fam; //|fam| for ``small'' delimiter
		quarterword small_char; //|character| for ``small'' delimiter
		quarterword large_fam; //|fam| for ``large'' delimiter
		quarterword large_char; //|character| for ``large'' delimiter
		std::string print(void);
		void scan(char, bool, Token);
};

class RadicalNoad : public Noad
{
	public:
		Delimiter left_delimiter;
		RadicalNoad(Token);
		virtual std::string showNode(const std::string &);
		virtual void mToH(void);
};

class FractionNoad : public Noad
{
	public:
		Delimiter left_delimiter = Delimiter{0, 0, 0, 0};
		Delimiter right_delimiter = Delimiter{0, 0, 0, 0};
		NoadContent &numerator = supscr; // |numerator| field in a fraction noad
		NoadContent &denominator = subscr; // |denominator| field in a fraction noad
		scaled thickness; //!< \a thickness field in a fraction noad
		FractionNoad(halfword, Token);
		virtual std::string showNode(const std::string &);
		virtual void mToH(scaled&, scaled&);
};

class LeftRightNoad : public Noad
{
	public:
		Delimiter delimiter; //!< \a delimiter field in left and right noads
		LeftRightNoad(Token);
		virtual std::string showNode(const std::string &);
};

class AccentNoad : public Noad
{
	public:
		NoadContent accent_chr; //!< the \a accent_chr field of an accent noad
		AccentNoad(void);
		virtual std::string showNode(const std::string &);
		virtual void mToH();
};

//inline int &incompleat_noad = aux.int_; //!< the name of \a aux in math mode
inline FractionNoad *incompleat_noad; //!< the name of \a aux in math mode
inline std::vector<TokenList*> curmark(5, nullptr);
inline TokenList *top_mark = curmark[top_mark_code];
inline TokenList *first_mark = curmark[first_mark_code];
inline TokenList *bot_mark = curmark[bot_mark_code];
inline TokenList *split_first_mark = curmark[split_first_mark_code];
inline TokenList *split_bot_mark = curmark[split_bot_mark_code];
inline std::vector<AnyNode> heads;
inline PageInsNode *page_ins_head = nullptr; //!< list of insertion data for current page
inline LinkedNode *contrib_head = nullptr; //!< vlist of items not yet on current page
inline LinkedNode *page_head = nullptr; //!< vlist for current page
inline LinkedNode *temp_head = nullptr; //!< head of a temporary list of some kind
inline LinkedNode *adjust_head = nullptr; //!< head of adjustment list returned by \a hpack
inline LinkedNode * const align_head = dynamic_cast<LinkedNode*>(&heads[8]); //!< head of preamble list for alignments
inline TokenList omit_template; //!< a constant token list
inline LinkedNode *null_list = nullptr; //!< permanently empty list
inline CharNode *lig_trick = nullptr; //!< a ligature masquerading as a \a char_node
//inline LinkedNode *garbage = nullptr; //!< used for scrap information
//inline LinkedNode *backup_head = nullptr; //!< head of token list built by \a scan_keyword
inline Noad *curmlist;
inline LinkedNode *bestpagebreak;
inline GlueSpec *lastglue = nullptr;
inline LinkedNode *adjusttail = nullptr;
inline LinkedNode *pagetail;
inline std::vector<GlueSpec> glues(5);
inline auto	zero_glue = &glues[0]; //!< specification for 0pt plus 0pt minus 0pt
inline auto fil_glue = &glues[1]; //!< 0pt plus 1fil minus 0pt
inline auto fill_glue = &glues[2]; //!< 0pt plus 1fill minus 0pt
inline auto ss_glue = &glues[3]; //!< 0pt plus 1fil minus 1fil
inline auto fil_neg_glue = &glues[4]; //!< 0pt plus -1fil minus 0pt

CharNode* newcharacter(internalfontnumber, eightbits);
void newfont(smallnumber);
void newgraf(bool);
void newinteraction(Token);
GlueNode* newskipparam(smallnumber);
void appendchoices(void);
void appenddiscretionary(halfword);
GlueNode *glueToAppend(halfword);
void appenditaliccorrection(void);
void appendtovlist(BoxNode*);
void followUntilBeforeTarget(LinkedNode*, LinkedNode*&, LinkedNode*);
void flushnodelist(LinkedNode*);
LinkedNode* copynodelist(LinkedNode*);
void deleteglueref(GlueSpec *);
GlueSpec *trapzeroglue(GlueSpec *);

inline bool precedes_break(LinkedNode *p) { return p->type < math_node; }
inline LinkedNode *new_hlist(Noad *p) { return p->nucleus.info; } //!< the translation of an mlist
template<class T> void next(T* &p) { p = dynamic_cast<T*>(p->link); }
template<class T> void putAfter(T* &p, LinkedNode *q) { p = dynamic_cast<T*>(q->link); }


template<class T> void appendAtEnd(T* &p, LinkedNode *q)
{
	p->link = q;
	next(p);
}

template<class T> void appendAtStart(T* &p, LinkedNode *q)
{
	q->link = p;
	p = dynamic_cast<T*>(q);
}

inline void followUntilEnd(LinkedNode *s, LinkedNode* &p) { followUntilBeforeTarget(s, p, nullptr); }

inline void insertNodeAfter(LinkedNode *p, LinkedNode *q)
{
	q->link = p->link;
	p->link = q;
}

template<class T> void replaceNode(T* &p, LinkedNode *q)
{
	auto r = p;
	p = dynamic_cast<T*>(q);
	delete r;
}

template<class T> void removeNodeAtStart(T* &q)
{
	auto p = q;
	next(q);
	delete p;
}

inline void removeNodeAfter(LinkedNode *prev)
{
	auto p = prev->link; // prev -> p -> q
	prev->link = p->link; // prev -> q
	delete p;
}

inline bool is_running(int d) { return d == null_flag; } //!< tests for a running dimension

#endif

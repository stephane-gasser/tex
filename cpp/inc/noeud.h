#ifndef NOEUD_H
#define NOEUD_H

#include "globals.h"

void confusion(const std::string &);

class AnyNode
{
	public:
		halfword num = 0; // bidon
		quarterword type = 0;
		virtual bool is_char_node(void) { return false; }
		virtual ~AnyNode(void) {}
};

class SpanNode : public AnyNode
{
	public:
		halfword link;
		SpanNode *info;
		scaled width;
		SpanNode(void) {}
		~SpanNode(void) { if (info) delete info; }
};

void flushnodelist(LinkedNode*);
LinkedNode* copynodelist(LinkedNode*);

class LinkedNode : public AnyNode
{
	public:
		LinkedNode *link = nullptr;
		~LinkedNode(void) { if (!is_char_node() && type > right_noad) confusion("flushing"); flushnodelist(link); }
		virtual LinkedNode *copy(void) { confusion("copying"); return new LinkedNode; }
};

class CharNode : public LinkedNode
{
	public:
		Font font; //type
		quarterword character; //subtype
		virtual bool is_char_node(void) { return true; }
		CharNode(const Font &f, quarterword c) : font(f), character(c) {}
		virtual CharNode* copy(void) { return new CharNode(font, character); }
};

class TokenNode : public LinkedNode
{
	public:
		TokenNode(halfword t = 0) : token(t) {}
		halfword token; // info
		halfword &token_ref_count = token; // info
		virtual bool is_char_node(void) { return true; }
		virtual TokenNode* copy(void) { return new TokenNode(token); }
};

class LigatureNode : public LinkedNode
{
	public:
		CharNode lig_char;
		LinkedNode *lig_ptr;
		quarterword subtype;
		LigatureNode(const Font &f, quarterword c, LinkedNode*q) : subtype(0), lig_char(f, c), lig_ptr(q) { type = ligature_node; }
		//newligitem
		LigatureNode(quarterword c) : subtype(0), lig_char(fonts[0], c), lig_ptr(nullptr) { type = ligature_node; }
		~LigatureNode(void) { flushnodelist(lig_ptr); /*if (lig_ptr) delete lig_ptr;*/ }
		virtual LigatureNode* copy(void) { return new LigatureNode(lig_char.font, lig_char.character, copynodelist(lig_ptr)); }
};


class ChoiceNode : public LinkedNode
{
	public:
		LinkedNode *display_mlist = nullptr; //!< mlist to be used in display style
		LinkedNode *text_mlist = nullptr; //!< mlist to be used in text style
		LinkedNode *script_mlist = nullptr; //!< mlist to be used in script style
		LinkedNode *script_script_mlist = nullptr; //!< mlist to be used in scriptscript style
		ChoiceNode(void) { type = choice_node; }
		~ChoiceNode(void) { flushnodelist(display_mlist); flushnodelist(text_mlist); flushnodelist(script_mlist); flushnodelist(script_script_mlist);/*if (display_mlist) delete display_mlist; if(text_mlist) delete text_mlist; if (script_mlist) delete script_mlist; if (script_script_mlist) delete script_script_mlist;*/ }
};

class DiscNode : public LinkedNode
{
	public:
		quarterword replace_count = 0; //!< how many subsequent nodes to replace
		LinkedNode *pre_break = nullptr; //!< text that precedes a discretionary break
		LinkedNode *post_break = nullptr; //!< text that follows a discretionary break
		DiscNode(void) { type = disc_node; }
		~DiscNode(void) { flushnodelist(pre_break); flushnodelist(post_break); }
		DiscNode *copy(void) { auto d = new DiscNode; d->pre_break = copynodelist(pre_break);  d->post_break = copynodelist(post_break); return d; }
};

class KernNode : public LinkedNode
{
	public:
		quarterword subtype; // normal/explicit_/acc_kern/mu_glue
		scaled width; //(normally negative) amount of spacing
		KernNode(scaled w, quarterword s = 0) : width(w), subtype(s) { type = kern_node; }
		virtual KernNode *copy(void) { return new KernNode(width, subtype); }
};

void deleteglueref(GlueSpec *);
halfword& glue_ref_count(halfword);
int& width(halfword); //!< width of the box, in sp
int& stretch(halfword); //!< the stretchability of this glob of glue
int& shrink(halfword); //!< the shrinkability of this glob of glue
quarterword& stretch_order(halfword); //!< order of infinity for stretching
quarterword& shrink_order(halfword); //!< order of infinity for shrinking

class GlueSpec : public AnyNode
{
	public:
		halfword glue_ref_count = 1;
		scaled width = 0, stretch = 0, shrink = 0;
		glueord stretch_order = 0, shrink_order = 0; // normal/fil/fill/filll
		GlueSpec(void) {}
		GlueSpec(GlueSpec *p) { width = p->width; stretch = p->stretch; shrink = p->shrink; stretch_order = p->stretch_order; shrink_order = p->shrink_order; glue_ref_count = 0; }
		GlueSpec(halfword v) { glue_ref_count = ::glue_ref_count(v); width = ::width(v); stretch = ::stretch(v); shrink = ::shrink(v); stretch_order = ::stretch_order(v); shrink_order = ::shrink_order(v); }
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
		~InsNode(void) { flushnodelist(ins_ptr); deleteglueref(split_top_ptr); }
		virtual InsNode *copy(void) { auto i = new InsNode; i->height = height; i->depth = depth; i->split_top_ptr = split_top_ptr; i->float_cost = float_cost; split_top_ptr->glue_ref_count++; i->ins_ptr = copynodelist(ins_ptr); return i; }
};

extern TokenNode *defref;

void deletetokenref(TokenNode*);

class MarkNode : public LinkedNode
{
	public:
		TokenNode *mark_ptr = defref;
		MarkNode(void) { type = mark_node; }
		~MarkNode(void) { deletetokenref(mark_ptr); }
		virtual MarkNode *copy(void) { auto m = new MarkNode; m->mark_ptr = mark_ptr; mark_ptr->token_ref_count++; return m; }
};

class AdjustNode : public LinkedNode
{
	public:
		TokenNode *adjust_ptr;
		AdjustNode(void) { type = adjust_node; }
		~AdjustNode(void) { flushnodelist(adjust_ptr); }
		virtual AdjustNode *copy(void) { auto a = new AdjustNode; a->adjust_ptr = dynamic_cast<TokenNode*>(copynodelist(adjust_ptr)); return a; }
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

halfword& glue_par(halfword);

class GlueNode : public LinkedNode
{
	public:
		quarterword subtype;
		LinkedNode *leader_ptr = nullptr; //!< pointer to box or rule node for leaders
		GlueSpec *glue_ptr; //!< pointer to a glue specification
		GlueNode(GlueSpec *g) : subtype(0), glue_ptr(g) { type = glue_node; g->glue_ref_count++; }
		GlueNode(smallnumber n) : subtype(n+1) { type = glue_node; glue_ptr->num = glue_par(n); glue_ptr->glue_ref_count++; }
		~GlueNode(void) { deleteglueref(glue_ptr); flushnodelist(leader_ptr); }
		virtual GlueNode *copy(void) { auto g = new GlueNode(glue_ptr); g->leader_ptr = copynodelist(leader_ptr); return g; }
};

inline std::vector<GlueSpec*> skip(256);
inline std::vector<GlueSpec*> mu_skip(256);

class PenaltyNode : public LinkedNode
{
	public:
		int penalty;
		PenaltyNode(int p = 0) : penalty(p) { type = penalty_node; } 
		virtual PenaltyNode *copy(void) { return new PenaltyNode(penalty); }
};

class RuleNode : public LinkedNode
{
	public:
		quarterword subtype = 0;
		int width = -(1<<30); //null_flag
		int depth = -(1<<30); //null_flag
		int height = -(1<<30); //null_flag
		RuleNode(void) { type = rule_node; } 
		virtual RuleNode *copy(void) { auto r = new RuleNode; r->width = width; r->depth = depth; r->height = height; return r; }
};

class BoxNode : public RuleNode
{
	public:
		int shift_amount = 0; //!< repositioning distance, in sp
		LinkedNode *list_ptr = nullptr; //!< beginning of the list inside the box
		quarterword glue_sign = 0; //normal  //!< stretching or shrinking
		quarterword glue_order = 0; //normal //!< applicable order of infinity
		float glue_set = 0.0;
		BoxNode(void) { type = hlist_node; subtype = 0; width = depth = height = 0; } 
		~BoxNode(void) { flushnodelist(list_ptr); }
		virtual BoxNode *copy(void) { auto r = new BoxNode; r->width = width; r->depth = depth; r->height = height; r->glue_set = glue_set; r->glue_sign = glue_sign; r->glue_order = glue_order; r->list_ptr = copynodelist(list_ptr); r->shift_amount = shift_amount; return r; }
};

class UnsetNode : public BoxNode
{
	public:
		quarterword &span_count = BoxNode::subtype;
		// pas de glue_set ni de shift_amount
		scaled glue_shrink;
		scaled glue_stretch;
		UnsetNode(void) : BoxNode() { type = unset_node; span_count = 0; } 
		virtual UnsetNode *copy(void) { auto r = new UnsetNode; r->width = width; r->depth = depth; r->height = height; r->glue_shrink = glue_shrink; r->glue_sign = glue_sign; r->glue_order = glue_order; r->list_ptr = copynodelist(list_ptr); r->glue_stretch = glue_stretch; return r; }
};

class StyleNode : public LinkedNode
{
	public:
		quarterword subtype;
		StyleNode(smallnumber s) : subtype(s) { type = style_node; }
};

inline std::vector<BoxNode*> box(256);
inline BoxNode *justbox;
inline BoxNode *curbox;

class MathNode : public LinkedNode
{
	public:
		quarterword subtype;
		int width;
		MathNode(scaled w, smallnumber s) : subtype(s), width(w) { type = math_node; }
		virtual MathNode *copy(void) { return new MathNode(width, subtype); }
};

class WhatsitNode : public LinkedNode
{
	public:
		quarterword subtype;
		WhatsitNode(smallnumber s) : subtype(s) { type = whatsit_node; }
		~WhatsitNode(void) { if (subtype > language_node) confusion("ext3"); }
		virtual WhatsitNode *copy(void) { confusion("ext2"); return nullptr; }
};

class WriteWhatsitNode : public WhatsitNode
{
	public:
		halfword write_stream; //!< stream number (0 to 17)
		WriteWhatsitNode(smallnumber s) : WhatsitNode(s) {}
};

class OpenWriteWhatsitNode : public WriteWhatsitNode
{
	public:
		std::string open_name; //!< string number of file name to open
		std::string open_area; //!< string number of file area for \a open_name
		std::string open_ext; //!< string number of file extension for \a open_name
		OpenWriteWhatsitNode(void) : WriteWhatsitNode(/*open_node*/0) {}
		virtual OpenWriteWhatsitNode *copy(void) { auto w = new OpenWriteWhatsitNode; w->write_stream = write_stream; w->open_name = open_name; w->open_area = open_area; w->open_ext = open_ext; return w; }
};

class NotOpenWriteWhatsitNode : public WriteWhatsitNode
{
	public:
		TokenNode *write_tokens; //!< reference count of token list to write
		NotOpenWriteWhatsitNode(smallnumber s) : WriteWhatsitNode(s) {}
		~NotOpenWriteWhatsitNode(void) { deletetokenref(write_tokens); }
		virtual NotOpenWriteWhatsitNode *copy(void) { auto w = new NotOpenWriteWhatsitNode(subtype); w->write_stream = write_stream; w->write_tokens = write_tokens; write_tokens->token_ref_count++; return w; }
};

class LanguageWhatsitNode : public WhatsitNode
{
	public:
		halfword what_lang; //!< language number, in the range 0..255
		quarterword what_lhm; //!< minimum left fragment, in the range 1..63
		quarterword what_rhm; //!< minimum right fragment, in the range 1..63
		LanguageWhatsitNode(ASCIIcode l) : WhatsitNode(/*language_node*/4), what_lang(l) {}
		virtual LanguageWhatsitNode *copy(void) { auto l = new LanguageWhatsitNode(what_lang); l->what_lhm = what_lhm; l->what_rhm = what_rhm; return l; }
};

class NoadContent : public AnyNode
{
	public:
		halfword math_type = 0;
		LinkedNode *info = nullptr;
		quarterword character = 0;
		quarterword fam = 0;
		~NoadContent(void) { if (math_type >= /*sub_box*/2) flushnodelist(info); }
};

class Noad : public LinkedNode
{
	public:
		quarterword subtype;
		NoadContent nucleus;
		NoadContent subscr;
		NoadContent supscr;
		Noad(void) : subtype(0/*normal*/) { type = ord_noad; }
};

class Delimiter
{
	public:
		quarterword small_fam; //|fam| for ``small'' delimiter
		quarterword small_char; //|character| for ``small'' delimiter
		quarterword large_fam; //|fam| for ``large'' delimiter
		quarterword large_char; //|character| for ``large'' delimiter
};

class RadicalNoad : public Noad
{
	public:
		Delimiter left_delimiter;
		RadicalNoad(void) { type = radical_noad; subtype = 0/*normal*/; }
};

class FractionNoad : public RadicalNoad
{
	public:
		Delimiter right_delimiter;
		NoadContent &numerator = supscr; // |numerator| field in a fraction noad
		NoadContent &denominator = subscr; // |denominator| field in a fraction noad
		scaled thickness; //!< \a thickness field in a fraction noad
		FractionNoad(void) { type = fraction_noad; subtype = 0/*normal*/; }
};

class LeftRightNoad : public Noad
{
	public:
		Delimiter delimiter; //!< \a delimiter field in left and right noads
		LeftRightNoad(quarterword t) { type = t; }
};

class AccentNoad : public Noad
{
	public:
		NoadContent accent_chr; //!< the \a accent_chr field of an accent noad
		AccentNoad(void) { type = accent_noad; subtype = 0/*normal*/; accent_chr.math_type = 1/*math_char*/; }
};

//inline int &incompleat_noad = aux.int_; //!< the name of \a aux in math mode
inline FractionNoad *incompleat_noad; //!< the name of \a aux in math mode
inline TokenNode *pstack[9];
inline TokenNode *paramstack[paramsize+1];
inline std::vector<TokenNode*> curmark(5, nullptr);
inline TokenNode *top_mark = curmark[top_mark_code];
inline TokenNode *first_mark = curmark[first_mark_code];
inline TokenNode *bot_mark = curmark[bot_mark_code];
inline TokenNode *split_first_mark = curmark[split_first_mark_code];
inline TokenNode *split_bot_mark = curmark[split_bot_mark_code];
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
inline CharNode *lig_trick; //!< a ligature masquerading as a \a char_node
inline LinkedNode *garbage; //!< used for scrap information
inline LinkedNode *backup_head; //!< head of token list built by \a scan_keyword
inline LinkedNode *preamble = align_head->link; //!< the current preamble list
inline TokenNode *Start;
inline TokenNode *Loc;

CharNode* newcharacter(internalfontnumber, eightbits);
void newfont(smallnumber);
void newgraf(bool);
void newhyphexceptions(void);
void newinteraction(Token);
void newsavelevel(groupcode);
GlueNode* newskipparam(smallnumber);
void freenode(halfword, halfword);
halfword getnode(int);
void appendchoices(void);
void appenddiscretionary(halfword);
void appendglue(halfword);
void appenditaliccorrection(void);
void appendkern(halfword);
void appendpenalty(void);
void appendtovlist(halfword);
void appspace(halfword &, fontindex &);

#endif

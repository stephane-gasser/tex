#ifndef GLOBALS_H
#define GLOBALS_H

#include <fstream>
#include <map>
#include <vector>

///////////////////////////////////////////////////////////////////////////////
// constantes
///////////////////////////////////////////////////////////////////////////////
constexpr int memmax = 30000;
constexpr int memmin = 0;
constexpr int bufsize = 500;
constexpr int errorline = 72;
constexpr int halferrorline = 42;
constexpr int maxprintline = 79;
constexpr int stacksize = 200;
constexpr int maxinopen = 6;
constexpr int fontmax = 75;
constexpr int fontmemsize = 20000;
constexpr int paramsize = 60;
constexpr int nestsize = 40;
constexpr int maxstrings = 3000;
constexpr int poolsize = 32000;
constexpr int savesize = 600;
constexpr int triesize = 8000;
constexpr int trieopsize = 500;
constexpr int filenamesize = 40;
constexpr int CHECKSUM = 117275187;
constexpr int mem_bot = 0; //!<  smallest index in the \a mem array dumped by INITEX
constexpr int mem_top = 30000; //!<  largest index in the \a mem array dumped by INITEX
constexpr int font_base = 0; //!<  smallest internal font number; must not be less
constexpr int hash_size = 2100; //!<  maximum number of control sequences; it should be at most
constexpr int hash_prime = 1777; //!<  a prime number equal to about 85% of \a hash_size
constexpr int hyph_size = 307; //!<  another prime; the number of \\hyphenation exceptions
constexpr char banner[] ="This is TeX, Version 3.14159265"; //!<  printed when \\TeX starts

///////////////////////////////////////////////////////////////////////////////
// types
///////////////////////////////////////////////////////////////////////////////
typedef std::uint8_t ASCIIcode; // 0..255
typedef std::uint8_t eightbits; // 0..255
typedef std::fstream alphafile; // file of char
typedef std::fstream bytefile; // file of eightbits
typedef std::fstream wordfile; // file of memoryword
typedef int poolpointer; // 0..poolsize
typedef int strnumber; // 0..maxstrings
typedef std::uint8_t packedASCIIcode; // 0..255
typedef int scaled;
typedef std::uint8_t smallnumber; // 0..63
typedef float glueratio;
typedef std::uint8_t quarterword; // 0..255
typedef std::uint16_t halfword; // 0..0xFF'FF
typedef char internalfontnumber; //0..fontmax
typedef int fontindex; // 0..fontmemsize
typedef int dviindex; // 0..dvibufsize
typedef int triepointer; // 0..triesize
typedef int hyphpointer; //0..307

typedef struct
{
    std::uint16_t rh;
    union
    {
    	std::uint16_t lh;
    	struct
    	{
    		std::uint8_t b0;
    		std::uint8_t b1;
    	};
    };
} twohalves;

typedef struct
{
	std::uint8_t b0;
	std::uint8_t b1;
	std::uint8_t b2;
	std::uint8_t b3;
} fourquarters;

typedef union
{
	std::int32_t int_;
	float gr;
	twohalves hh;
	fourquarters qqqq;
} memoryword;

typedef char glueord; //0..3
typedef char groupcode; // 0..16

class GlueSpec;

class Font
{
	public:
		static std::vector<memoryword> info;
		int charbase; //!< base addresses for |char_info|
		int widthbase; //!< base addresses for widths
		int heightbase; //!< base addresses for heights
		int depthbase; //!< base addresses for depths
		int italicbase; //!< base addresses for italic corrections
		int ligkernbase; //!< base addresses for ligature/kerning programs
		int kernbase; //!< base addresses for kerns
		int extenbase; //!< base addresses for extensible recipes
		int parambase; //!< base addresses for font parameters
		std::string name; //!< name of the font
		std::string area; //!< area of the font
		fourquarters check; //!< check sum
		scaled size; //!< ``at'' size
		scaled dsize; //!< ``design'' size
		fontindex params; //!< how many font parameters are present
		eightbits bc; //!< beginning (smallest) character code
		eightbits ec; //!< ending (largest) character code
		GlueSpec *glue; //!< glue specification for interword space, |null| if not allocated
		bool used; //!< has a character from this font actually appeared in the output?
		int hyphenchar;//!< current \.{\\hyphenchar} values
		int skewchar; //!< current \.{\\skewchar} values
		fontindex bcharlabel; //!< start of |lig_kern| program for left boundary character, |non_address| if there is none
		int bchar; //!< right boundary character, |non_char| if there is none
		int falsebchar; //!< |font_bchar| if it doesn't exist in the font, otherwise |non_char|
		static fourquarters& infos(int);
		static quarterword skip_byte(int);
		static quarterword next_char(int);
		static quarterword op_byte(int);
		static quarterword rem_byte(int);
		fourquarters char_info(smallnumber) const;
		int char_width(smallnumber) const;
		int char_height(smallnumber) const;
		int char_depth(smallnumber) const;
		int char_italic(smallnumber) const;
		int lig_kern_start(fourquarters) const; //!< beginning of lig/kern program
		int lig_kern_restart(fourquarters) const;
		int char_kern(fourquarters) const;
		int& param(smallnumber) const;
		scaled heightplusdepth(quarterword) const;
		int& slant(void) const; //!< slant to the right, per unit distance upward
		int& extra_space(void) const; //!< additional space at end of sentence
		int& space(void) const; //!< normal space between words
		int& space_stretch(void) const; //!< stretch between words
		int& space_shrink(void) const; //!< shrink between words
		int& x_height(void) const; //!< one ex
		int& quad(void) const; //!< one em
		int char_tag(smallnumber);
		bool char_exists(smallnumber);
		bool operator != (const Font &f) { return this != &f; } 
};

inline std::vector<memoryword> Font::info(7);
inline std::vector<Font> fonts(1);

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
	right_noad = left_noad+1 //!< \a type of a noad for \\right
};

class LinkedNode;

typedef struct
{
    int modefield; // -203..203
    LinkedNode *headfield, *tailfield;
    int pgfield, mlfield;
    memoryword auxfield;
} liststaterecord;

inline liststaterecord curlist;
inline auto &aux = curlist.auxfield; //!< auxiliary data about the current list
inline auto &head = curlist.headfield; //!< header node of current list
inline auto &tail = curlist.tailfield; //!< final node on current list
inline int& prev_depth = aux.int_; //!< the name of \a aux in vertical mode
inline halfword& space_factor = aux.hh.lh; //!< part of \a aux in horizontal mode
inline halfword& clang = aux.hh.rh;  //!< the other part of \a aux in horizontal mode
inline int& mode = curlist.modefield; //!< current mode
inline int& prev_graf = curlist.pgfield; //!< number of paragraph lines accumulated
inline int& mode_line = curlist.mlfield; //!< source file line number at beginning of list

inline LinkedNode *curhead, *curtail;

typedef struct
{
    quarterword statefield, indexfield;
    halfword startfield;
    halfword locfield, limitfield;
    std::string namefield;
} instaterecord;

inline instaterecord curinput;

inline std::string hyphword[308];
inline std::string helpline;
inline std::vector<std::string> strings;
inline std::string currentString;
inline std::string curname;
inline std::string curarea;
inline std::string curext;
inline std::string jobname;
inline std::string outputfilename;
inline std::string logname;
inline std::string formatident;

class Token
{
	public:
		eightbits cmd;
		halfword chr;
		halfword cs;
		halfword tok;
		void make_tok(void)
		{
			if (cs == 0)
				tok = (cmd<<8)+chr;
			else
				tok = cs+/*cs_token_flag*/(1<<12)-1;
		}
};

inline Token aftertoken;
inline Font fontinshortdisplay;
inline GlueSpec *lastglue;

inline LinkedNode *adjusttail;
inline LinkedNode *pagetail;

inline LinkedNode *curp;

inline int bad;
inline int tally;
inline int trickcount;
inline int firstcount;
inline int varused, dynused;
inline int depththreshold;
inline int breadthmax;
inline int cscount;
inline int magset;
inline int line;
inline int maxparamstack;
inline int alignstate;
inline int ifline;
inline int skipline;
inline int totalpages;
inline int maxpush;
inline int lastbop;
inline int deadcycles;
inline int lq, lr;
inline int dvioffset;
inline int curs;
inline int lastbadness;
inline int packbeginline;
inline int fewestdemerits;
inline int actuallooseness;
inline int linediff;
inline int hyfchar;
inline int lhyf, rhyf, initlhyf, initrhyf;
inline int leastpagecost;
inline int lastpenalty;
inline int insertpenalties;
inline int readyalready;
inline int threshold;
inline int minimumdemerits;
inline std::map<char, ASCIIcode> xord;
inline std::map<ASCIIcode, char> xchr;
inline std::string nameoffile;// char[filenamesize+1]; // débute à 1
inline char namelength; //0..filenamesize;
inline ASCIIcode buffer[bufsize+1]; // débute à 0
inline int First;// 0..bufsize
inline int last; // 0..bufsize
inline int maxbufstack; // 0..bufsize
inline alphafile poolfile;
inline alphafile logfile;
inline char selector; //0..21
inline char dig[23]; // of 0..15
inline char termoffset; // 0..maxprintline
inline char fileoffset; // 0..maxprintline
inline ASCIIcode trickbuf[errorline+1];
inline char interaction; // 0..3
//extern bool deletionsallowed;
inline char history; // 0..3
inline char errorcount; // -1..100
inline bool useerrhelp;
inline bool aritherror;
inline scaled remainder_;
inline halfword tempptr;
inline memoryword mem[memmax+1];
inline halfword lomemmax;
inline halfword himemmin;
inline halfword avail;
inline halfword memend;
inline halfword rover;
inline liststaterecord nest[nestsize+1];

inline LinkedNode *contrib_tail = nest[0].tailfield;

inline char nestptr; //0..nestsize
inline char maxneststack; // 0..nestsize
inline int shownmode; //-203..203
inline char oldsetting; // 0..21
inline memoryword eqtb[6107]; // débute à 1
inline quarterword xeqlevel[6107]; // débute à 5263
inline twohalves hash[2881]; // débute à 514
inline halfword hashused;
inline bool nonewcontrolsequence;
inline std::vector<memoryword> savestack;
inline quarterword curlevel;
inline groupcode curgroup;
inline int curboundary; // 0..savesize
inline instaterecord inputstack[stacksize+1];
inline unsigned char inputptr; // 0..stacksize
inline unsigned char maxinstack; // 0..stacksize
inline char inopen; // 0..maxinopen
inline char openparens; // 0..maxinopen
inline alphafile inputfile[maxinopen+1]; // commence à 1
inline int linestack[maxinopen+1]; // commence à 1
inline char scannerstatus; // 0..5
inline halfword warningindex;
inline char paramptr; // 0..paramsize
inline unsigned char baseptr; // 0..stacksize
inline halfword parloc;
inline halfword partoken;
inline bool forceeof;

enum
{
	top_mark_code = 0, //!< the mark in effect at the previous page break
	first_mark_code = 1, //!< the first mark between \a top_mark and \a bot_mark
	bot_mark_code = 2, //!< the mark in effect at the current page break
	split_first_mark_code = 3, //!< the first mark found by \\vsplit
	split_bot_mark_code = 4 //!< the last mark found by \\vsplit
};

inline char longstate; // 111..114
inline smallnumber radix;
inline glueord curorder;
inline alphafile readfile[16];
inline char readopen[17]; // of 0..2
inline halfword condptr;
inline char iflimit; // 0..4
inline smallnumber curif;
inline poolpointer areadelimiter;
inline poolpointer extdelimiter;
inline std::string TEXformatdefault; // commence à 1
inline bool nameinprogress;
inline bool logopened;
inline bytefile dvifile;
inline bytefile tfmfile;
inline fourquarters nullcharacter;
inline scaled maxv;
inline scaled maxh;
inline bool doingleaders;
inline quarterword c, f; // ????????????????
inline scaled ruleht, ruledp, rulewd;
inline halfword g; // ??????????????
inline dviindex dviptr;
inline scaled dvih, dviv;
inline scaled curh, curv;
inline internalfontnumber dvif;
inline scaled totalstretch[4], totalshrink[4];
inline halfword curmlist;
inline smallnumber curstyle;
inline smallnumber cursize;
inline scaled curmu;
inline bool mlistpenalties;
inline halfword curalign;
inline halfword curspan;
inline halfword alignptr;
inline halfword passive;
inline halfword printednode;
inline halfword passnumber;
inline scaled activewidth[7]; // commence à 1
inline scaled curactivewidth[7]; // commence à 1
inline scaled background[7]; // commence à 1 
inline scaled breakwidth[7]; // commence à 1
inline bool noshrinkerroryet;
inline bool secondpass;
inline bool finalpass;
inline int minimaldemerits[4];
inline halfword bestplace[4];
inline halfword bestplline[4];
inline scaled discwidth;
inline halfword easyline;
inline halfword lastspecialline;
inline scaled firstwidth;
inline scaled secondwidth;
inline scaled firstindent;
inline scaled secondindent;
inline halfword bestbet;
inline halfword bestline;
inline ASCIIcode curlang, initcurlang;
inline halfword hyfbchar;
inline char hyf[65]; // of 0..9
inline smallnumber hyphenpassed;
inline halfword curl, curr;
inline bool ligaturepresent;
inline bool lfthit, rthit;
inline std::map<ASCIIcode, int> opstart; //of 0..trieopsize
inline halfword hyphlist[308];
inline hyphpointer hyphcount;
inline std::map<ASCIIcode, quarterword> trieused;
inline bool trienotready;
inline scaled bestheightplusdepth;
inline char pagecontents; // 0..2
inline scaled pagemaxdepth;
inline halfword bestpagebreak;
inline scaled bestsize;
inline scaled pagesofar[8];
inline scaled lastkern;
inline bool outputactive;
inline halfword bchar;
inline halfword falsebchar;
inline bool cancelboundary;
inline bool insdisc;
inline bool longhelpseen;
inline wordfile fmtfile;
inline alphafile writefile[16];
inline bool writeopen[18];
inline halfword writeloc;

#include "constantes.h"
#include "noeud.h"

#endif

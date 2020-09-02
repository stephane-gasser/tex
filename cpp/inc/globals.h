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
constexpr int CHECKSUM = 117275187;
constexpr int mem_bot = 0; //!<  smallest index in the \a mem array dumped by INITEX
constexpr int mem_top = 30000; //!<  largest index in the \a mem array dumped by INITEX
constexpr int font_base = 0; //!<  smallest internal font number; must not be less
constexpr int hash_size = 2100; //!<  maximum number of control sequences; it should be at most about |(mem_max-mem_min)/10|}
constexpr int hash_prime = 1777; //!<  a prime number equal to about 85% of \a hash_size
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
typedef int triepointer; // 0..triesize

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
		inline int& prev_depth = aux.int_; //!< the name of \a aux in vertical mode
		inline halfword& space_factor = aux.hh.lh; //!< part of \a aux in horizontal mode
		inline halfword& clang = aux.hh.rh;  //!< the other part of \a aux in horizontal mode
	inline auto &head = curlist.headfield; //!< header node of current list
	inline auto &tail = curlist.tailfield; //!< final node on current list
	inline int& mode = curlist.modefield; //!< current mode
	inline int& prev_graf = curlist.pgfield; //!< number of paragraph lines accumulated
	inline int& mode_line = curlist.mlfield; //!< source file line number at beginning of list

typedef struct
{
    quarterword statefield, indexfield;
    halfword startfield;
    halfword locfield, limitfield;
    std::string namefield;
} instaterecord;

inline instaterecord curinput;

inline std::string helpline;
inline std::vector<std::string> strings;
inline std::string currentString;
inline std::string curname;
inline std::string curarea;
inline std::string curext;
inline std::string jobname = "";
inline std::string outputfilename = "";
inline std::string logname;
inline std::string formatident = " (INITEX)";

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
inline GlueSpec *lastglue = nullptr;
inline LinkedNode *adjusttail = nullptr;
inline LinkedNode *pagetail;

inline int trickcount;
inline int firstcount;
inline int varused = 20, dynused = 14/**hi_mem_stat_usage*/;
inline int depththreshold;
inline int breadthmax;
inline int cscount = 0;
inline int line = 0;
inline int alignstate = 1000000;
inline int ifline = 0;
inline int skipline;
inline int totalpages = 0;
inline int maxpush = 0;
inline int deadcycles = 0;
inline int lq, lr;
inline int curs = -1;
inline int packbeginline = 0;
inline int actuallooseness;
inline int linediff;
inline int leastpagecost;
inline int lastpenalty = 0;
inline int insertpenalties = 0;
inline int readyalready;
inline int threshold;
inline int minimumdemerits;
inline std::map<char, ASCIIcode> xord;
inline std::map<ASCIIcode, char> xchr;
inline std::string nameoffile;// char[filenamesize+1]; // débute à 1
inline ASCIIcode buffer[bufsize+1]; // débute à 0
inline int First = 1;// 0..bufsize
inline int last; // 0..bufsize
inline int maxbufstack = 0; // 0..bufsize
inline alphafile logfile;
inline char selector; //0..21
inline char termoffset = 0; // 0..maxprintline
inline char fileoffset = 0; // 0..maxprintline
inline ASCIIcode trickbuf[errorline+1];
inline char interaction = /*error_stop_mode*/3; // 0..3
inline char errorcount = 0; // -1..100
inline bool aritherror;
inline scaled remainder_;
inline memoryword mem[memmax+1];
inline halfword himemmin = (mem_top-13)/*hi_mem_stat_min*/;
inline halfword avail = 0;
inline halfword memend = mem_top;
inline halfword rover = /*lo_mem_stat_max*/19+1;
inline halfword lomemmax = /*rover*/20+1000;
inline std::vector<liststaterecord> nest(1);
inline LinkedNode *contrib_tail = nest[0].tailfield;
inline int shownmode = 0; //-203..203
inline unsigned char baseptr; // 0..stacksize
inline char oldsetting; // 0..21
inline groupcode curgroup = 0;
inline std::vector<instaterecord> inputstack(1);
inline unsigned char inputptr = 0; // 0..stacksize
inline char inopen = 0; // 0..maxinopen
inline char openparens = 0; // 0..maxinopen
inline alphafile inputfile[maxinopen+1]; // commence à 1
inline int linestack[maxinopen+1]; // commence à 1
inline halfword parloc;
inline halfword partoken;

enum
{
	top_mark_code = 0, //!< the mark in effect at the previous page break
	first_mark_code = 1, //!< the first mark between \a top_mark and \a bot_mark
	bot_mark_code = 2, //!< the mark in effect at the current page break
	split_first_mark_code = 3, //!< the first mark found by \\vsplit
	split_bot_mark_code = 4 //!< the last mark found by \\vsplit
};

inline alphafile readfile[16];
inline std::vector<char> readopen(17, 2/*closed*/); // of 0..2
inline char iflimit = 0; // 0..4
inline smallnumber curif = 0;
inline bool logopened = false;
inline bytefile tfmfile;
inline scaled maxv = 0;
inline scaled maxh = 0;
inline bool doingleaders = false;
inline scaled ruleht, ruledp, rulewd;
inline scaled totalstretch[4], totalshrink[4];
inline smallnumber curstyle;
inline smallnumber cursize;
inline scaled curmu;
inline bool mlistpenalties;
inline halfword passnumber;
inline bool noshrinkerroryet;
inline bool secondpass;
inline bool finalpass;
inline halfword bestplline[4];
inline scaled discwidth;
inline halfword easyline;
inline halfword lastspecialline;
inline scaled firstwidth;
inline scaled secondwidth;
inline scaled firstindent;
inline scaled secondindent;
inline halfword bestline;
inline ASCIIcode curlang, initcurlang;
inline halfword curl, curr;
inline bool lfthit = false, rthit = false;
inline bool trienotready = true;
inline scaled bestheightplusdepth;
inline char pagecontents = 0; // 0..2
inline scaled pagemaxdepth = 0;
inline scaled bestsize;
inline scaled pagesofar[8];
inline scaled lastkern = 0;
inline bool outputactive = false;
inline halfword bchar;
inline halfword falsebchar;
inline bool cancelboundary = false;
inline bool insdisc = false;
inline bool longhelpseen = false;
inline alphafile writefile[16];
inline std::vector<bool> writeopen(18, false);
inline halfword writeloc;

#include "constantes.h"
#include "noeud.h"

class ArithException : public std::exception 
{
	public:
		const char * what () const throw () { return "arithmetic error"; }
};

#endif

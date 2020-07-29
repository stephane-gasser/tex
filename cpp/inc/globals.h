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
constexpr int dvibufsize = 800;
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

typedef struct
{
    int modefield; // -203..203
    halfword headfield, tailfield;
    int pgfield, mlfield;
    memoryword auxfield;
} liststaterecord;

typedef char groupcode; // 0..16

typedef struct
{
    quarterword statefield, indexfield;
    halfword startfield, locfield, limitfield;
    std::string namefield;
} instaterecord;

typedef char internalfontnumber; //0..fontmax
typedef int fontindex; // 0..fontmemsize
typedef int dviindex; // 0..dvibufsize
typedef int triepointer; // 0..triesize
typedef int hyphpointer; //0..307

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
		void make_tok(void);		
};

inline Token aftertoken;

extern int bad;
extern int tally;
extern int trickcount;
extern int firstcount;
extern int varused, dynused;
extern int fontinshortdisplay;
extern int depththreshold;
extern int breadthmax;
extern int cscount;
extern int magset;
extern int line;
extern int maxparamstack;
extern int alignstate;
extern int ifline;
extern int skipline;
extern int totalpages;
extern int maxpush;
extern int lastbop;
extern int deadcycles;
extern int lq, lr;
extern int dvioffset;
extern int dvigone;
extern int curs;
extern int lastbadness;
extern int packbeginline;
extern int fewestdemerits;
extern int actuallooseness;
extern int linediff;
extern int hyfchar;
extern int lhyf, rhyf, initlhyf, initrhyf;
extern int leastpagecost;
extern int lastpenalty;
extern int insertpenalties;
extern int readyalready;
extern int threshold;
extern int minimumdemerits;
extern std::map<char, ASCIIcode> xord;
extern std::map<ASCIIcode, char> xchr;
extern std::string nameoffile;// char[filenamesize+1]; // débute à 1
extern char namelength; //0..filenamesize;
extern ASCIIcode buffer[bufsize+1]; // débute à 0
extern int First;// 0..bufsize
extern int last; // 0..bufsize
extern int maxbufstack; // 0..bufsize
extern alphafile poolfile;
extern alphafile logfile;
extern char selector; //0..21
extern char dig[23]; // of 0..15
extern char termoffset; // 0..maxprintline
extern char fileoffset; // 0..maxprintline
extern ASCIIcode trickbuf[errorline+1];
extern char interaction; // 0..3
extern bool deletionsallowed;
extern char history; // 0..3
extern char errorcount; // -1..100
extern bool useerrhelp;
extern bool aritherror;
extern scaled remainder_;
extern halfword tempptr;
extern memoryword mem[memmax+1];
extern halfword lomemmax;
extern halfword himemmin;
extern halfword avail;
extern halfword memend;
extern halfword rover;
extern liststaterecord nest[nestsize+1];
extern char nestptr; //0..nestsize
extern char maxneststack; // 0..nestsize
extern liststaterecord curlist;
extern int shownmode; //-203..203
extern char oldsetting; // 0..21
extern memoryword eqtb[6107]; // débute à 1
extern quarterword xeqlevel[6107]; // débute à 5263
extern twohalves hash[2881]; // débute à 514
extern halfword hashused;
extern bool nonewcontrolsequence;
extern memoryword savestack[savesize+1];
extern int saveptr; //0..savesize
extern int maxsavestack; // 0..savesize
extern quarterword curlevel;
extern groupcode curgroup;
extern int curboundary; // 0..savesize
extern instaterecord inputstack[stacksize+1];
extern unsigned char inputptr; // 0..stacksize
extern unsigned char maxinstack; // 0..stacksize
extern instaterecord curinput;
extern char inopen; // 0..maxinopen
extern char openparens; // 0..maxinopen
extern alphafile inputfile[maxinopen+1]; // commence à 1
extern int linestack[maxinopen+1]; // commence à 1
extern char scannerstatus; // 0..5
extern halfword warningindex;
extern halfword paramstack[paramsize+1];
extern char paramptr; // 0..paramsize
extern unsigned char baseptr; // 0..stacksize
extern halfword parloc;
extern halfword partoken;
extern bool forceeof;
extern halfword curmark[5];
extern char longstate; // 111..114
extern halfword pstack[9];
extern smallnumber radix;
extern glueord curorder;
extern alphafile readfile[16];
extern char readopen[17]; // of 0..2
extern halfword condptr;
extern char iflimit; // 0..4
extern smallnumber curif;
extern poolpointer areadelimiter;
extern poolpointer extdelimiter;
extern std::string TEXformatdefault; // commence à 1
extern bool nameinprogress;
extern bool logopened;
extern bytefile dvifile;
extern bytefile tfmfile;
extern fourquarters nullcharacter;
extern scaled maxv;
extern scaled maxh;
extern bool doingleaders;
extern quarterword c, f;
extern scaled ruleht, ruledp, rulewd;
extern halfword g;
extern eightbits dvibuf[dvibufsize+1];
extern dviindex halfbuf;
extern dviindex dvilimit;
extern dviindex dviptr;
extern halfword downptr, rightptr;
extern scaled dvih, dviv;
extern scaled curh, curv;
extern internalfontnumber dvif;
extern scaled totalstretch[4], totalshrink[4];
extern halfword adjusttail;
extern halfword curmlist;
extern smallnumber curstyle;
extern smallnumber cursize;
extern scaled curmu;
extern bool mlistpenalties;
extern halfword curalign;
extern halfword curspan;
extern halfword alignptr;
extern halfword curhead, curtail;
extern halfword justbox;
extern halfword passive;
extern halfword printednode;
extern halfword passnumber;
extern scaled activewidth[7]; // commence à 1
extern scaled curactivewidth[7]; // commence à 1
extern scaled background[7]; // commence à 1 
extern scaled breakwidth[7]; // commence à 1
extern bool noshrinkerroryet;
extern halfword curp;
extern bool secondpass;
extern bool finalpass;
extern int minimaldemerits[4];
extern halfword bestplace[4];
extern halfword bestplline[4];
extern scaled discwidth;
extern halfword easyline;
extern halfword lastspecialline;
extern scaled firstwidth;
extern scaled secondwidth;
extern scaled firstindent;
extern scaled secondindent;
extern halfword bestbet;
extern halfword bestline;
extern int hc[66]; // of 0..256
extern smallnumber hn;
extern halfword ha, hb;
extern internalfontnumber hf;
extern int hu[64]; // of 0..256
extern ASCIIcode curlang, initcurlang;
extern halfword hyfbchar;
extern char hyf[65]; // of 0..9
extern smallnumber hyphenpassed;
extern halfword curl, curr;
extern bool ligaturepresent;
extern bool lfthit, rthit;
extern std::map<ASCIIcode, int> opstart; //of 0..trieopsize
extern halfword hyphlist[308];
extern hyphpointer hyphcount;
extern std::map<ASCIIcode, quarterword> trieused;
extern bool trienotready;
extern scaled bestheightplusdepth;
extern halfword pagetail;
extern char pagecontents; // 0..2
extern scaled pagemaxdepth;
extern halfword bestpagebreak;
extern scaled bestsize;
extern scaled pagesofar[8];
extern halfword lastglue;
extern scaled lastkern;
extern bool outputactive;
extern halfword bchar;
extern halfword falsebchar;
extern bool cancelboundary;
extern bool insdisc;
extern halfword curbox;
extern bool longhelpseen;
extern wordfile fmtfile;
extern alphafile writefile[16];
extern bool writeopen[18];
extern halfword writeloc;

#include "constantes.h"

#endif

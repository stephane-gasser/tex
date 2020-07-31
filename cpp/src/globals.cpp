#include "globals.h"

int bad;
int tally;
int trickcount;
int firstcount;
int varused, dynused;
int fontinshortdisplay;
int depththreshold;
int breadthmax;
int cscount;
int magset;
int line;
int maxparamstack;
int alignstate;
int ifline;
int skipline;
int totalpages;
int maxpush;
int lastbop;
int deadcycles;
int lq, lr;
int dvioffset;
int dvigone;
int curs;
int lastbadness;
int packbeginline;
int fewestdemerits;
int actuallooseness;
int linediff;
int hyfchar;
int lhyf, rhyf, initlhyf, initrhyf;
int leastpagecost;
int lastpenalty;
int insertpenalties;
int readyalready;
int threshold;
int minimumdemerits;
std::map<char, ASCIIcode> xord;
std::map<ASCIIcode, char> xchr;
std::string nameoffile;// char[filenamesize+1]; // débute à 1
char namelength; //0..filenamesize;
ASCIIcode buffer[bufsize+1]; // débute à 0
int First;// 0..bufsize
int last; // 0..bufsize
int maxbufstack; // 0..bufsize
packedASCIIcode strpool[poolsize+1]; // débute à 0
poolpointer strstart[maxstrings+1]; // débute à 1
poolpointer poolptr;
strnumber strptr;
poolpointer initpoolptr;
strnumber initstrptr;
alphafile poolfile;
alphafile logfile;
char selector; //0..21
char dig[23]; // of 0..15
char termoffset; // 0..maxprintline
char fileoffset; // 0..maxprintline
ASCIIcode trickbuf[errorline+1];
char interaction; // 0..3
char history; // 0..3
char errorcount; // -1..100
bool useerrhelp;
bool aritherror;
scaled remainder_;
halfword tempptr;
memoryword mem[memmax+1];
halfword lomemmax;
halfword himemmin;
halfword avail;
halfword memend;
halfword rover;
liststaterecord nest[nestsize+1];
char nestptr; //0..nestsize
char maxneststack; // 0..nestsize
int shownmode; //-203..203
char oldsetting; // 0..21
memoryword eqtb[6107]; // débute à 1
quarterword xeqlevel[6107]; // débute à 5263
twohalves hash[2881]; // débute à 514
halfword hashused;
bool nonewcontrolsequence;
memoryword savestack[savesize+1];
int saveptr; //0..savesize
int maxsavestack; // 0..savesize
quarterword curlevel;
groupcode curgroup;
int curboundary; // 0..savesize
instaterecord inputstack[stacksize+1];
unsigned char inputptr; // 0..stacksize
unsigned char maxinstack; // 0..stacksize
char inopen; // 0..maxinopen
char openparens; // 0..maxinopen
alphafile inputfile[maxinopen+1]; // commence à 1
int linestack[maxinopen+1]; // commence à 1
char scannerstatus; // 0..5
halfword warningindex;
char paramptr; // 0..paramsize
unsigned char baseptr; // 0..stacksize
halfword parloc;
halfword partoken;
bool forceeof;
halfword curmark[5];
char longstate; // 111..114
smallnumber radix;
glueord curorder;
alphafile readfile[16];
char readopen[17]; // of 0..2
halfword condptr;
char iflimit; // 0..4
smallnumber curif;
poolpointer areadelimiter;
poolpointer extdelimiter;
std::string TEXformatdefault; // commence à 1
bool nameinprogress;
bool logopened;
bytefile dvifile;
bytefile tfmfile;
internalfontnumber dvif;
fourquarters nullcharacter;
scaled maxv;
scaled maxh;
bool doingleaders;
quarterword c, f;
scaled ruleht, ruledp, rulewd;
halfword g;
eightbits dvibuf[dvibufsize+1];
dviindex halfbuf;
dviindex dvilimit;
dviindex dviptr;
halfword downptr, rightptr;
scaled dvih, dviv;
scaled curh, curv;
scaled totalstretch[4], totalshrink[4];
halfword adjusttail;
halfword curmlist;
smallnumber curstyle;
smallnumber cursize;
scaled curmu;
bool mlistpenalties;
halfword curalign;
halfword curspan;
halfword alignptr;
halfword justbox;
halfword passive;
halfword printednode;
halfword passnumber;
scaled activewidth[7]; // commence à 1
scaled curactivewidth[7]; // commence à 1
scaled background[7]; // commence à 1 
scaled breakwidth[7]; // commence à 1
bool noshrinkerroryet;
halfword curp;
bool secondpass;
bool finalpass;
int minimaldemerits[4];
halfword bestplace[4];
halfword bestplline[4];
scaled discwidth;
halfword easyline;
halfword lastspecialline;
scaled firstwidth;
scaled secondwidth;
scaled firstindent;
scaled secondindent;
halfword bestbet;
halfword bestline;
int hc[66]; // of 0..256
smallnumber hn;
halfword ha, hb;
internalfontnumber hf;
int hu[64]; // of 0..256
ASCIIcode curlang, initcurlang;
halfword hyfbchar;
char hyf[65]; // of 0..9
smallnumber hyphenpassed;
halfword curl, curr;
bool ligaturepresent;
bool lfthit, rthit;
std::map<ASCIIcode, int> opstart; //of 0..trieopsize
halfword hyphlist[308];
hyphpointer hyphcount;
std::map<ASCIIcode, quarterword> trieused;
bool trienotready;
scaled bestheightplusdepth;
halfword pagetail;
char pagecontents; // 0..2
scaled pagemaxdepth;
halfword bestpagebreak;
scaled bestsize;
scaled pagesofar[8];
halfword lastglue;
scaled lastkern;
bool outputactive;
halfword bchar;
halfword falsebchar;
bool cancelboundary;
bool insdisc;
halfword curbox;
bool longhelpseen;
wordfile fmtfile;
alphafile writefile[16];
bool writeopen[18];
halfword writeloc;

void Token::make_tok(void)
{
	if (cs == 0)
		tok = (cmd<<8)+chr;
	else
		tok = cs_token_flag+cs;
}



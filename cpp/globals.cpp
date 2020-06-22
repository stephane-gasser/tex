#include "globals.h"

using std::map;

int bad;
int tally;
int trickcount;
int firstcount;
int interrupt;
int varused, dynused;
int fontinshortdisplay;
int depththreshold;
int breadthmax;
int cscount;
int magset;
int line;
int maxparamstack;
int alignstate;
int curval;
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
map<char, ASCIIcode> xord;
map<ASCIIcode, char> xchr;
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
bool deletionsallowed;
bool setboxallowed;
char history; // 0..3
char errorcount; // -1..100
char helpptr; // 0..6
bool useerrhelp;
bool OKtointerrupt;
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
liststaterecord curlist;
memoryword& aux = curlist.auxfield;
int& prev_depth = aux.int_;
halfword& space_factor = aux.hh.lh;
halfword& clang = aux.hh.rh;
int &incompleat_noad = aux.int_;
int& mode = curlist.modefield;
halfword& head = curlist.headfield;
halfword& tail = curlist.tailfield;
int& prev_graf = curlist.pgfield;
int& mode_line = curlist.mlfield;
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
eightbits curcmd;
halfword curchr;
halfword curcs;
halfword curtok;
instaterecord inputstack[stacksize+1];
unsigned char inputptr; // 0..stacksize
unsigned char maxinstack; // 0..stacksize
instaterecord curinput;
char inopen; // 0..maxinopen
char openparens; // 0..maxinopen
alphafile inputfile[maxinopen+1]; // commence à 1
int linestack[maxinopen+1]; // commence à 1
char scannerstatus; // 0..5
halfword warningindex;
halfword defref;
halfword paramstack[paramsize+1];
char paramptr; // 0..paramsize
unsigned char baseptr; // 0..stacksize
halfword parloc;
halfword partoken;
bool forceeof;
halfword curmark[5];
char longstate; // 111..114
halfword pstack[9];
char curvallevel; // 0..5
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
memoryword fontinfo[fontmemsize+1];
fontindex fmemptr;
internalfontnumber fontptr;
fourquarters fontcheck[fontmax+1];
scaled fontsize[fontmax+1];
scaled fontdsize[fontmax+1]; 
fontindex fontparams[fontmax+1];
eightbits fontbc[fontmax+1];
eightbits fontec[fontmax+1];
halfword fontglue[fontmax+1];
bool fontused[fontmax+1];
int hyphenchar[fontmax+1];
int skewchar[fontmax+1];
fontindex bcharlabel[fontmax+1];
int fontbchar[fontmax+1]; // of 0..256
int fontfalsebchar[fontmax+1]; // of 0..256
int charbase[fontmax+1];
int widthbase[fontmax+1];
int heightbase[fontmax+1];
int depthbase[fontmax+1];
int italicbase[fontmax+1];
int ligkernbase[fontmax+1];
int kernbase[fontmax+1];
int extenbase[fontmax+1];
int parambase[fontmax+1];
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
internalfontnumber dvif;
scaled totalstretch[4], totalshrink[4];
halfword adjusttail;
twohalves emptyfield;
fourquarters nulldelimiter;
halfword curmlist;
smallnumber curstyle;
smallnumber cursize;
scaled curmu;
bool mlistpenalties;
internalfontnumber curf;
quarterword curc;
fourquarters curi;
halfword curalign;
halfword curspan;
halfword curloop;
halfword alignptr;
halfword curhead, curtail;
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
halfword initlist;
bool initlig;
bool initlft;
smallnumber hyphenpassed;
halfword curl, curr;
halfword curq;
halfword ligstack;
bool ligaturepresent;
bool lfthit, rthit;
twohalves trie[triesize+1];
smallnumber hyfdistance[trieopsize+1]; // commence à 1
smallnumber hyfnum[trieopsize+1]; // commence à 1
quarterword hyfnext[trieopsize+1]; // commence à 
map<ASCIIcode, int> opstart; //of 0..trieopsize
halfword hyphlist[308];
hyphpointer hyphcount;
map<int, int> trieophash; // [-trieopsize..trieopsize] of 0..trieopsize
map<ASCIIcode, quarterword> trieused;
ASCIIcode trieoplang[trieopsize+1]; // commence à 1
quarterword trieopval[trieopsize+1]; // commence à 1
int trieopptr; // 0..trieopsize
packedASCIIcode triec[triesize+1];
quarterword trieo[triesize+1];
triepointer triel[triesize+1];
triepointer trier[triesize+1];
triepointer trieptr;
triepointer triehash[triesize+1];
bool trietaken[triesize+1]; // commence à 1
map<ASCIIcode, triepointer> triemin;
triepointer triemax;
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
halfword aftertoken;
bool longhelpseen;
wordfile fmtfile;
alphafile writefile[16];
bool writeopen[18];
halfword writeloc;

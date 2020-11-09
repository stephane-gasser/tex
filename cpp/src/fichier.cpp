#include "fichier.h"
#include "erreur.h"
#include "impression.h"
#include "lecture.h"
#include "chaine.h"
#include "etat.h"
#include "tampon.h"
#include "getnext.h"
#include <iostream>
#include <algorithm>

int inputln(std::istream& f, bool bypasseoln, int first)
{
	if (bypasseoln && !f.eof())
		f.get();
	if (f.eof())
		return -1;
	std::string line;
	getline(f, line);
	int lst = first+find_if(line.begin(), line.end(), [](char c) { return c == ' '; })-line.begin();
	setBufChangeBadChar(line, first);
	return lst;
}

int terminput(int first)
{
	std::cout << std::flush;
	int lst = inputln(std::cin, true, first);
	if (lst < 0)
		fatalerror("End of file on the terminal!");
	termoffset = 0;
	selector--;
	print(readBuf(first, lst-1)+"\n");
	selector++;
	return lst;
}

int firmuptheline(void)
{
	print("\n"+readAllBuf()+"=>");
	int lst = terminput(curinput.limit);
	if (lst > curinput.limit)
	{
		shiftBuf(curinput.limit, lst, curinput.start);
		setBufSize(lst-curinput.limit+1);
	}
	return lst;
}

int initterminal(int first)
{
	while (true)
	{
		std::cout << "**" << std::flush;
		std::cin.clear();
		int lst = inputln(std::cin, false, first);
		if (lst < 0)
		{
			std::cout << std::endl;
			std::cout << "! End of file on the terminal... why?'";
			throw std::string();
		}
		if (first < lst)
			return lst;
		std::cout << "Please type the name of your input file.\n";
	}
}

void openlogfile(int first)
{
	auto oldsetting = selector;
	if (jobname == "") 
		jobname = "texput";
	while (!aopenout(logfile, logname = packjobname(".log")))
	{
		selector = term_only;
		promptfilename(" transcript file name", ".log", first);
	}
	selector = log_only;
	logopened = true;
	logfile << banner;
	print(formatident+"  "+std::to_string(day())+" ");
	constexpr char months[] = "JANFEBMARAPRMAYJUNJULAUGSEPOCTNOVDEC";
	for (int k = 3*month()-2; k <= 3*month(); k++)
		logfile << months[k];
	print(" "+std::to_string(year())+" "+twoDigits(time()/60)+":"+twoDigits(time()%60));
	inputstack.back() = curinput;
	print("\r**");
	int l = inputstack[0].limit;
	if (getBuf(l) == end_line_char())
		l--;
	print(readBuf(1, l)+"\n");
	selector = oldsetting+2;
}

void openorclosein(char status, halfword c)
{
	auto n = scanner.getUInt4(status);
	if (readopen[n] != closed)
	{
		aclose(readfile[n]);
		readopen[n] = closed;
	}
	if (c)
	{
		scanner.optionalEquals(status);
		scanfilename(status);
		if (curext == "") 
			curext = ".tex";
		if (aopenin(readfile[n], pack_cur_name()))
			readopen[n] = just_open;
	}
}
static alphafile inputfile[maxinopen+1]; // commence à 1

alphafile& cur_file(void) { return inputfile[index]; } //!< the current \a alpha_file variable

static int linestack[maxinopen+1]; // commence à 1

void endfilereading(void)
{
	line = linestack[index];
	if (name.size() != 1 || name[0] > 17)
		aclose(cur_file());
	pop_input();
	inopen--;
}

//! The \a begin_file_reading procedure starts a new level of input for lines
//! of characters to be read from a file, or as an insertion from the
//! terminal. It does not take care of opening the file, nor does it set \a loc
//! or \a limit or \a line.
void beginfilereading(void)
{
	if (inopen == maxinopen)
		overflow("text input levels", maxinopen); 
	inopen++;
	push_input();
	index = inopen;
	linestack[index] = line;
	state = mid_line;
	name = "";
	// \a terminal_input is now \a true
}

static poolpointer areadelimiter;
static poolpointer extdelimiter;

static void beginname(void)
{
	areadelimiter = 0;
	extdelimiter = 0;
}

static std::string currentString;
int cur_length(void) { return currentString.size(); }
static void append_char(ASCIIcode c) { currentString += c; } //!< put \a ASCII_code # at the end of \a str_pool

static void morename(ASCIIcode c)
{
	append_char(c);
	switch (c)
	{
		case '>':
		case ':':
			areadelimiter = cur_length();
			extdelimiter = 0;
			break;
		case '.':
			if (extdelimiter == 0)
				extdelimiter = cur_length();
	}
}

static void endname(void)
{
	curarea = currentString.substr(0, areadelimiter);
	if (areadelimiter)
		strings.push_back(curarea);
	if (extdelimiter == 0)
	{
		curext = "";
		curname = currentString.substr(areadelimiter);
	}
	else
	{
		curext = currentString.substr(extdelimiter-1);
		curname = currentString.substr(areadelimiter, extdelimiter-1);
	}
	strings.push_back(curname);
	if (extdelimiter)
		strings.push_back(curext);
}


std::string promptfilename(const std::string &s, const std::string &e, int first)
{
	if (interaction == scroll_mode)
		print_err(s == "input file name" ? "I can't find file `" : "I can't write on file `"+asFilename(curname, curarea, curext)+"'.");
	if (e == ".tex")
		print(showcontext());
	print("\rPlease type another "+s);
	if (interaction < scroll_mode)
		fatalerror("*** (job aborted, file error in nonstop mode)");
	std::cin.clear();
	print(": ");
	int lst = terminput(first);
	beginname();
	for (int k = first; k < lst; k++)
		morename(getBuf(k));
	endname();
	if (curext == "")
		curext = e;
	nameoffile = pack_cur_name();
	return nameoffile;
}

void scanfilename(char status)
{
	nameinprogress = true;
	beginname();
	for (auto t = scanner.getXSkipSpace(status); true; t = scanner.getX(status))
	{
		if (t.cmd > other_char || t.chr > 255)
		{
			backinput(t);
			break;
		}
		if (t.chr == ' ')
			break;
		morename(t.chr);
	}
	endname();
	nameinprogress = false;
}

constexpr char TEXAreaDefault[] = "TeXformats:";
constexpr char TEXNameDefault[] = "plain";
constexpr char TEXExtDefault[] = ".fmt";

std::string packbufferedname(smallnumber n, const std::string &name)
{
	nameoffile = "";
	switch(n)
	{
		case area:
			nameoffile = TEXAreaDefault;
			break;
		case area_name:
			nameoffile = TEXAreaDefault;
			nameoffile += TEXNameDefault;
	}
	for (auto c: name)
		nameoffile += xchr[c];
	nameoffile = nameoffile.substr(0, filenamesize-format_ext_length);
	nameoffile += TEXExtDefault;
	return nameoffile;
}

std::string packfilename(const std::string &n, const std::string &a, const std::string &e)
{
	nameoffile = "";
	for (auto c: a+n+e)
		nameoffile += xchr[c];
	nameoffile = nameoffile.substr(0, filenamesize);
	return nameoffile;
}

std::string pack_cur_name(void) { return packfilename(curname, curarea, curext); }

std::string packjobname(const std::string &s)
{
	curarea = "";
	curext = s;
	curname = jobname;
	pack_cur_name();
	return nameoffile;
}

void aclose(alphafile& f) { f.close(); } //! Close a text file.
void bclose(bytefile& f) { f.close(); } //! Close a binary file.
void wclose(wordfile& f) { f.close(); } //! Close a word file.

static bool openin(std::fstream &f, const std::string &n)
{
	f.open(n, std::ios_base::in);
	return f.is_open();
}

static bool openout(std::fstream &f, const std::string &n)
{
	f.open(n, std::ios_base::out);
	return f.is_open();
}

bool aopenin(alphafile& f, const std::string &n) { return openin(f, n); } //! Open a text file for input.
bool bopenin(bytefile& f, const std::string &n) { return openin(f, n); } //! Open a binary file for input.
bool wopenin(wordfile& f, const std::string &n) { return openin(f, n); } //! Open a word file for input.
bool aopenout(alphafile& f, const std::string &n) { return openout(f, n); } //! Open a text file for output.
bool bopenout(bytefile& f, const std::string &n) { return openout(f, n); } //! Open a binary file for output.
bool wopenout(wordfile& f, const std::string &n) { return openout(f, n); } //! Open a word file for output.


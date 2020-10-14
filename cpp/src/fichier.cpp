#include "fichier.h"
#include "erreur.h"
#include "impression.h"
#include "lecture.h"
#include "chaine.h"
#include "etat.h"
#include <iostream>
#include "getnext.h"

void firmuptheline(void)
{
	limit = last;
	if (pausing() > 0 && interaction > nonstop_mode)
	{
		print("\n"+std::string(buffer+start, buffer+limit)+"=>");
		First = limit;
		terminput();
		if (last > First)
		{
			for (int k = First; k < last; k++)
				buffer[k+start-First] = buffer[k];
			limit = start+last-First;
		}
	}
}

void initterminal(void)
{
	while (true)
	{
		std::cout << "**" << std::flush;
		std::cin.clear();
		if (!inputln(std::cin, false))
		{
			std::cout << std::endl;
			std::cout << "! End of file on the terminal... why?'";
			throw std::string();
		}
		for (loc = First; loc < last && buffer[loc] == ' '; loc++); // trim à droite
		if (loc < last)
			return;
		std::cout << "Please type the name of your input file.\n";
	}
}

bool inputln(std::istream& f, bool bypasseoln)
{
	if (bypasseoln && !f.eof())
		f.get();
	last = First;
	if (f.eof())
		return false;
	std::string line;
	getline(f, line);
	int lastnonblank = First;
	for (char c: line)
	{
		if (last >= maxbufstack)
		{
			maxbufstack = last+1;
			if (maxbufstack == bufsize)
				if (formatident == "")
				{
					std::cout << "Buffer size exceeded!\n";
					throw std::string();
				}
				else
				{
					loc = First;
					limit = last-1;
					overflow("buffer size", bufsize); 
				}
		}
		buffer[last++] = 32 <= c && c < 127 ? c : 127;
		if (buffer[last-1] != ' ')
			lastnonblank = last;
	}
	last = lastnonblank;
	return true;
}

void terminput(void)
{
	std::cout << std::flush;
	if (!inputln(std::cin, true))
		fatalerror("End of file on the terminal!");
	termoffset = 0;
	selector--;
	print(std::string(buffer+First, buffer+last)+"\n");
	selector++;
}

void openlogfile(void)
{
	auto oldsetting = selector;
	if (jobname == "") 
		jobname = "texput";
	while (!aopenout(logfile, logname = packjobname(".log")))
	{
		selector = term_only;
		promptfilename(" transcript file name", ".log");
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
	int l = inputstack[0].limitfield;
	if (buffer[l] == end_line_char())
		l--;
	print(std::string(buffer+1, buffer+l+1)+"\n");
	selector = oldsetting+2;
}

void openorclosein(halfword c)
{
	auto n = scanfourbitint(scannerstatus);
	if (readopen[n] != closed)
	{
		aclose(readfile[n]);
		readopen[n] = closed;
	}
	if (c)
	{
		scanoptionalequals();
		scanfilename();
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
	First = start;
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
	if (First == bufsize)
		overflow("buffer size", bufsize);
	inopen++;
	push_input();
	index = inopen;
	linestack[index] = line;
	start = First;
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


std::string promptfilename(const std::string &s, const std::string &e)
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
	terminput();
	beginname();
	// trim gauche
	int k;
	for (k = First; buffer[k] == ' '  && k < last; k++);
	// trim droite
	for (; buffer[k] != ' ' && k < last; k++)
		morename(buffer[k]);
	endname();
	if (curext == "")
		curext = e;
	nameoffile = pack_cur_name();
	return nameoffile;
}

void scanfilename(void)
{
	nameinprogress = true;
	beginname();
	for (auto t = getXTokenSkipSpace(); true; t = getxtoken())
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


#include "fichier.h"
#include "erreur.h"
#include "impression.h"
#include "terminput.h"
#include "lecture.h"
#include "backinput.h"
#include "chaine.h"
#include "popinput.h"
#include "pushinput.h"
#include "texte.h"
#include <iostream>

void openorclosein(halfword c)
{
	auto n = scanfourbitint();
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

void endfilereading(void)
{
	First = start;
	line = linestack[index];
	if (txt(name) > 17)
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
	printnl("Please type another "+s);
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

static bool openin(std::fstream &f, const std::string &name)
{
	f.open(name, std::ios_base::in);
	return f.is_open();
}

static bool openout(std::fstream &f, const std::string &name)
{
	f.open(name, std::ios_base::out);
	return f.is_open();
}

bool aopenin(alphafile& f, const std::string &name) { return openin(f, name); } //! Open a text file for input.
bool bopenin(bytefile& f, const std::string &name) { return openin(f, name); } //! Open a binary file for input.
bool wopenin(wordfile& f, const std::string &name) { return openin(f, name); } //! Open a word file for input.
bool aopenout(alphafile& f, const std::string &name) { return openout(f, name); } //! Open a text file for output.
bool bopenout(bytefile& f, const std::string &name) { return openout(f, name); } //! Open a binary file for output.
bool wopenout(wordfile& f, const std::string &name) { return openout(f, name); } //! Open a word file for output.


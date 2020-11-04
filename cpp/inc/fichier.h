#ifndef FICHIER_H
#define FICHIER_H

#include "globals.h"

enum
{
	none = 0,
	area = 1,
	area_name = 2
};

enum
{
	opened = 0,
	just_open = 1, //!< newly opened, first line not yet read
	closed = 2 //!< not open, or at end of file
};

constexpr int format_ext_length = 4; //!< length of its `.fmt' part
constexpr int filenamesize = 40;

inline char selector; //0..21
inline bool nameinprogress;
inline std::string curname;
inline std::string curarea;
inline std::string curext;
inline std::string jobname = "";
inline std::string outputfilename = "";
inline std::string logname;
inline alphafile logfile;
inline alphafile readfile[16];
inline std::vector<char> readopen(17, closed); // of 0..2
inline alphafile writefile[16];
inline std::vector<bool> writeopen(18, false);
inline bool logopened = false;
inline char inopen = 0; // 0..maxinopen
inline std::string nameoffile;// char[filenamesize+1]; // débute à 1
inline std::string buffer;
inline int First = 1;// 0..bufsize
inline int last; // 0..bufsize
inline int line = 0;
inline std::string formatident = " (INITEX)";

void scanfilename(char);
std::string packfilename(const std::string &, const std::string &, const std::string &);
std::string pack_cur_name(void);
std::string packjobname(const std::string &);
std::string packbufferedname(smallnumber, const std::string&);
void aclose(alphafile& f);
void bclose(bytefile& f);
void wclose(wordfile& f);
bool aopenin(alphafile& f, const std::string&);
bool aopenout(alphafile& f, const std::string&);
bool bopenin(bytefile& f, const std::string&);
bool bopenout(bytefile& f, const std::string&);
bool wopenin(wordfile& f, const std::string&);
bool wopenout(wordfile& f, const std::string&);
std::string promptfilename(const std::string &, const std::string &);
void beginfilereading(void);
void endfilereading(void);
alphafile& cur_file(void);
void openorclosein(char, halfword);
void openlogfile(void);
void terminput(void);
bool inputln(std::istream& f, bool bypasseoln);
void initterminal(void);
void firmuptheline(void);

inline bool terminal_input(const std::string &name) { return name == ""; } //!< are we reading from the terminal?

#endif

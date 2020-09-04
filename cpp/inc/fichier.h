#ifndef FICHIER_H
#define FICHIER_H

#include "globals.h"

enum
{
	none = 0,
	area = 1,
	area_name = 2
};

constexpr int format_ext_length = 4; //!< length of its `.fmt' part
constexpr int filenamesize = 40;

inline bool nameinprogress;

void scanfilename(void);
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
void openorclosein(halfword);

#endif

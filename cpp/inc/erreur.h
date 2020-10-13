#ifndef ERREUR_H
#define ERREUR_H

#include "globals.h"
#include "token.h"
#include "police.h"
#include <string>

enum
{
	spotless = 0, //!< \a history value when nothing has been amiss yet
	warning_issued = 1, //!< \a history value when \a begin_diagnostic has been called
	error_message_issued = 2, //!< \a history value when \a error has been called
	fatal_error_stop = 3 //!< \a history value when termination was premature
};

inline char history; // 0..3
inline bool useerrhelp = false;
inline char errorcount = 0; // -1..100

void error(const std::string &, const std::string &, bool = true);
void inserror(Token, const std::string &, const std::string &, bool = true);
void backerror(Token, const std::string &, const std::string &);
void boxerror(eightbits, const std::string &, const std::string &);
void fatal(const std::string &, const std::string &);
void fatalerror(const std::string &);
void interror(int, const std::string &, const std::string &);
void overflow(const std::string &, int);
void reportillegalcase(Token);
bool privileged(Token);
void confusion(const std::string &);
void charwarning(const Font &, eightbits);

#endif

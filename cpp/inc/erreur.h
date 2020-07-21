#ifndef ERREUR_H
#define ERREUR_H

#include "globals.h"
#include <string>

void error(const std::string &, const std::string &, bool = true);
void inserror(Token, const std::string &, const std::string &, bool = true);
void backerror(Token, const std::string &, const std::string &);
void boxerror(eightbits, const std::string &, const std::string &);
void fatal(const std::string &, const std::string &);
void fatalerror(const std::string &);
void interror(int, const std::string &, const std::string &);
void overflow(const std::string &, int);
void check_full_save_stack(void);
void reportillegalcase(Token);
bool privileged(Token);
void confusion(const std::string &);

#endif

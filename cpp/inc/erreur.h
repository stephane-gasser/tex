#ifndef ERREUR_H
#define ERREUR_H

#include "globals.h"
#include <string>

void error(const std::string &, const std::string &, bool = true);
void inserror(halfword, const std::string &, const std::string &, bool = true);
void backerror(halfword, const std::string &, const std::string &);
void boxerror(eightbits, const std::string &, const std::string &);
void clearforerrorprompt(void);
void fatal(const std::string &, const std::string &);
void fatalerror(const std::string &);
void interror(int, const std::string &, const std::string &);
void overflow(const std::string &, int);
//void str_room(int);
void check_full_save_stack(void);
void reportillegalcase(eightbits, halfword);
bool privileged(eightbits, halfword);
void confusion(const std::string &);

#endif

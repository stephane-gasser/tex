#ifndef ERREUR_H
#define ERREUR_H

#include "globals.h"
#include <string>

void error(const std::string &, const std::string &, halfword, bool = true);
void inserror(halfword, const std::string &, const std::string &, halfword, bool = true);
void backerror(halfword, const std::string &, const std::string &, halfword);
void boxerror(eightbits, const std::string &, const std::string &, halfword);
void clearforerrorprompt(void);
void fatal(const std::string &, const std::string &, halfword);
void fatalerror(const std::string &, halfword);
void interror(int, const std::string &, const std::string &, halfword);
void overflow(const std::string &, int, halfword);
//void str_room(int);
void check_full_save_stack(halfword);
void reportillegalcase(eightbits, halfword, halfword);
bool privileged(eightbits, halfword);
void confusion(const std::string &, halfword);

#endif

#ifndef ERREUR_H
#define ERREUR_H

#include "globals.h"
#include <string>

void error(void);
void inserror(void);
void alignerror(void);
void backerror(void);
void cserror(void);
void boxerror(eightbits n);
void clearforerrorprompt(void);
void fatalerror(const std::string &);
void interror(int n);
void muerror(void);
void noalignerror(void);
void omiterror(void);
void overflow(const std::string &, int);
void str_room(int);
void check_full_save_stack(void);
void reportillegalcase(void);
void youcant(void);
void giveerrhelp(void);
bool privileged(void);
void confusion(const std::string &);

#endif

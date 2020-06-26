#ifndef FICHIER_H
#define FICHIER_H

#include "globals.h"

void aclose(alphafile& f);
void bclose(bytefile& f);
void wclose(wordfile& f);
bool aopenin(alphafile& f);
bool aopenout(alphafile& f);
bool bopenin(bytefile& f);
bool bopenout(bytefile& f);
bool wopenin(wordfile& f);
bool wopenout(wordfile& f);

#endif

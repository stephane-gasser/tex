#include "tampon.h"
#include "fichier.h"
#include "etat.h"
#include "equivalent.h"
#include <algorithm>

char currentBuf(void) { return buffer[curinput.loc]; }
char &lastBuf(void) { return buffer[curinput.limit]; }
int posBuf(void) { return curinput.loc-curinput.start; }
int sizeBuf(void) { return curinput.limit-curinput.start+1; }
void bufBegin(void) { curinput.loc = curinput.start; }
void bufEnd(void) { curinput.loc = curinput.limit+1; }
void bufNext(void) { curinput.loc++; }
void setBufSize(int size) { curinput.limit = curinput.start+size-1; }
bool isBufFull(void) { return curinput.loc > curinput.limit; }
bool atLeastTwoInBuf(void) { return curinput.loc < curinput.limit; }
std::string readBuf(int beg, int end) { return buffer.substr(beg, end-beg+1); };
std::string readBufUpTo(int end) { return buffer.substr(curinput.loc, end-curinput.loc+1); };
std::string readAllBuf(void) { return buffer.substr(curinput.start, curinput.limit-curinput.start); }
void setBufChangeBadChar(const std::string &line, int first) { std::transform(line.begin(), line.end(), buffer.begin()+first, [](char c) {return between(' ', c,  '~') ? c : '\x7f'; }); }
char &getBuf(int pos) { return buffer[pos]; }
void shiftBuf(int first, int lst, int newPos) { std::copy(buffer.begin()+first, buffer.begin()+lst, buffer.begin()+newPos); }

void removeLastBuf(void)
{
	if (end_line_char_inactive())
		curinput.limit--;
	else
		lastBuf() = end_line_char();
}



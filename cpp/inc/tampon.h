#ifndef TAMPON_H
#define TAMPON_H

#include <string>

char currentBuf(void);
void removeLastBuf(void);
char &lastBuf(void);
void bufBegin(void);
void bufEnd(void);
void bufNext(void);
int posBuf(void);
int sizeBuf(void);
void setBufSize(int);
bool isBufFull(void);
bool atLeastTwoInBuf(void);
std::string readBuf(int, int);
std::string readBufUpTo(int);
std::string readAllBuf(void);
void setBufChangeBadChar(const std::string &, int);
char &getBuf(int);
void shiftBuf(int, int, int);

inline std::string buffer;
inline int First = 1;// 0..bufsize

#endif

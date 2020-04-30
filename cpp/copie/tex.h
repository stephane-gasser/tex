#ifndef TEX_H
#define TEX_H

#include <fstream>

///////////////////////////////////////////////////////////////////////////////
// constantes
///////////////////////////////////////////////////////////////////////////////
constexpr int memmax = 30000;
constexpr int memmin = 0;
constexpr int bufsize = 500;
constexpr int errorline = 72;
constexpr int halferrorline = 42;
constexpr int maxprintline = 79;
constexpr int stacksize = 200;
constexpr int maxinopen = 6;
constexpr int fontmax = 75;
constexpr int fontmemsize = 20000;
constexpr int paramsize = 60;
constexpr int nestsize = 40;
constexpr int maxstrings = 3000;
constexpr int stringvacancies = 8000;
constexpr int poolsize = 32000;
constexpr int savesize = 600;
constexpr int triesize = 8000;
constexpr int trieopsize = 500;
constexpr int dvibufsize = 800;
constexpr int filenamesize = 40;
constexpr char poolname[] = "TeXformats:TEX.POOL                     ";

///////////////////////////////////////////////////////////////////////////////
// types
///////////////////////////////////////////////////////////////////////////////
typedef unsigned char ASCIIcode; // 0..255
typedef unsigned char eightbits; // 0..255
typedef std::fstream alphafile; // file of char
typedef std::fstream bytefile; // file of eightbits
typedef int poolpointer; // 0..poolsize
typedef int strnumber; // 0..maxstrings
typedef unsigned char packedASCIIcode; // 0..255
typedef int scaled;
typedef unsigned int nonnegativeinteger; //0..2147483647
typedef unsigned char smallnumber; // 0..63
typedef float glueratio;
typedef std::uint8_t quarterword; // 0..255
typedef std::uint16_t halfword; // 0..65535

typedef struct
{
    std::uint16_t rh;
    union
    {
    	std::uint16_t lh;
    	struct
    	{
    		std::uint8_t b0;
    		std::uint8_t b1;
    	};
    };
} twohalves;

typedef struct
{
	std::uint8_t b0;
	std::uint8_t b1;
	std::uint8_t b2;
	std::uint8_t b3;
} fourquarters;

typedef struct
{
	union
	{
		std::int32_t int_;
		float gr;
		twohalves hh;
		fourquarters qqqq;
	};
} memoryword;

typedef std::fstream wordfile; // file of memoryword
typedef char glueord; //0..3

typedef struct
{
    int modefield; // -203..203
    halfword headfield, tailfield;
    int pgfield, mlfield;
    memoryword auxfield;
} liststaterecord;

typedef char groupcode; // 0..16

typedef struct
{
    quarterword statefield, indexfield;
    halfword startfield, locfield, limitfield, namefield;
}  instaterecord;

typedef char internalfontnumber; //0..fontmax
typedef int fontindex; // 0..fontmemsize
typedef int dviindex; // 0..dvibufsize
typedef int triepointer; // 0..triesize
typedef int hyphpointer; //0..307

#endif

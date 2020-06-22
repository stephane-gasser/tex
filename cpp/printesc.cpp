#include "printesc.h"
#include "print.h"
#include "printchar.h"
#include "slowprint.h"
#include "texte.h"

void printesc(const std::string &s)
{
	auto &c = escape_char();
	if (c >= 0 && c < 256)
		printchar(c);
	slowprint(txt(s));
}

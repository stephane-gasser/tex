#include "printesc.h"
#include "print.h"
#include "printchar.h"
#include "slowprint.h"
#include "texte.h"

/*void printesc(strnumber s)
{
	auto &c = int_par(escape_char_code);
	if (c >= 0 && c < 256)
		print(c);
	slowprint(s);
}*/

void printesc(const std::string &s)
{
	auto &c = int_par(escape_char_code);
	if (c >= 0 && c < 256)
		printchar(c);
	slowprint(txt(s));
}

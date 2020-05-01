#include "printesc.h"
#include "print.h"
#include "slowprint.h"

void printesc(strnumber s)
{
	auto &c = int_par(escape_char_code);
	if (c >= 0 && c < 256)
		print(c);
	slowprint(s);
}

#include "printfontandchar.h"
#include "printesc.h"
#include "printchar.h"
#include "print.h"
#include "texte.h"

void printfontandchar(int p)
{
	if (p > memend)
		printesc("CLOBBERED.");
	else
	{
		if (type(p) < 0 || type(p) > fontmax)
		printchar('*');
		else
		printesc(TXT(text(frozen_null_font+type(p))));
		printesc("FONT");
		printchar(' ');
		print(TXT(subtype(p)));
	}
}

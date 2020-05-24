#include "printspec.h"
#include "printchar.h"
#include "print.h"
#include "printglue.h"
#include "printscaled.h"
#include "texte.h"

void printspec(int p, const std::string &s)
{
	if (p < memmin || p >= lomemmax)
		printchar('*');
	else
	{
		printscaled(width(p));
		if (txt(s))
			print(s);
		if (stretch(p))
		{
			print(" plus ");
			printglue(stretch(p), type(p), s);
		}
		if (shrink(p))
		{
			print(" minus ");
			printglue(shrink(p), subtype(p), s);
		}
	}
}

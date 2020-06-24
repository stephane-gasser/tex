#include "printfamandchar.h"
#include "printesc.h"
#include "printint.h"
#include "printchar.h"
#include "print.h"
#include "texte.h"

void printfamandchar(halfword p)
{
	printesc("fam");
	printint(type(p));
	printchar(' ');
	print(TXT(subtype(p)));
}

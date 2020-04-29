#include "printfamandchar.h"
#include "printesc.h"
#include "printint.h"
#include "printchar.h"
#include "print.h"

void printfamandchar(halfword p)
{
	printesc(464); //fam
	printint(type(p));
	printchar(' ');
	print(subtype(p));
}

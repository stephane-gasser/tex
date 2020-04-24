#include "printfamandchar.h"
#include "printesc.h"
#include "printint.h"
#include "printchar.h"
#include "print.h"

void printfamandchar(halfword p)
{
	printesc(464); //fam
	printint(mem[p].hh.b0);
	printchar(' ');
	print(mem[p].hh.b1 - 0);
}

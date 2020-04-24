#include "begintokenlist.h"
#include "overflow.h"
#include "begindiagnostic.h"
#include "enddiagnostic.h"
#include "tokenshow.h"
#include "print.h"
#include "printesc.h"
#include "printnl.h"
#include "printcmdchr.h"
#include "constantes.h"

void begintokenlist(halfword p, quarterword t)
{
	if (inputptr > maxinstack)
	{
		maxinstack = inputptr;
		if (inputptr == stacksize)
			overflow(593, stacksize); //input stack size
	}
	inputstack[inputptr++] = curinput;
	curinput.statefield = 0;
	curinput.startfield = p;
	curinput.indexfield = t;
	if (t >= 5)
	{
		mem[p].hh.lh++;
		if (t == 5)
			curinput.limitfield = paramptr;
		else
		{
			curinput.locfield = mem[p].hh.rh;
			if (int_par(tracing_macros_code) > 1)
			{
				begindiagnostic();
				printnl(338); //
				switch (t)
				{
					case 14: 
						printesc(351); //mark
						break;
					case 15: 
						printesc(594); //write
						break;
					default: 
						printcmdchr(72, t+3407);
				}
				print(556); //->
				tokenshow(p);
				enddiagnostic(false);
			}
		}
	}
	else
		curinput.locfield = p;
}

#include "begintokenlist.h"
#include "overflow.h"
#include "begindiagnostic.h"
#include "enddiagnostic.h"
#include "tokenshow.h"
#include "print.h"
#include "printesc.h"
#include "printnl.h"
#include "printcmdchr.h"
#include "pushinput.h"

//! backs up a simple token list
void back_list(halfword p)
{
	begintokenlist(p, backed_up);
}

//! inserts a simple token list
void ins_list(halfword p)
{
	begintokenlist(p, inserted);
}

void begintokenlist(halfword p, quarterword t)
{
	push_input();
	state = token_list;
	start = p;
	index = t;
	if (t >= macro)
	{
		info(p)++;
		if (t == macro)
			param_start = paramptr;
		else
		{
			loc = link(p);
			if (tracing_macros() > 1)
			{
				begindiagnostic();
				printnl("");
				switch (t)
				{
					case mark_text: 
						printesc("mark");
						break;
					case write_text: 
						printesc("write");
						break;
					default: 
						printcmdchr(assign_toks, t-output_text+output_routine_loc);
				}
				print("->");
				tokenshow(p);
				enddiagnostic(false);
			}
		}
	}
	else
		loc = p;
}

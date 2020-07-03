#include "begintokenlist.h"
#include "overflow.h"
#include "impression.h"
#include "pushinput.h"

//! backs up a simple token list
void back_list(halfword p) { begintokenlist(p, backed_up); }

//! inserts a simple token list
void ins_list(halfword p) { begintokenlist(p, inserted); }

void begintokenlist(halfword p, quarterword t)
{
	push_input();
	state = token_list;
	start = p;
	index = t;
	if (t >= macro) //the token list starts with a reference count
	{
		add_token_ref(p);
		if (t == macro)
			param_start = paramptr;
		else
		{
			loc = link(p);
			if (tracing_macros() > 1)
			{
				begindiagnostic();
				switch (t)
				{
					case mark_text: 
						printnl(esc("mark"));
						break;
					case write_text: 
						printnl(esc("write"));
						break;
					default: 
						printnl(cmdchr(assign_toks, t-output_text+output_routine_loc));
				}
				print("->"+tokenshow(p));
				print(enddiagnostic(false));
			}
		}
	}
	else
		loc = p;
}

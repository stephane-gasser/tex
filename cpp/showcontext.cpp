#include "showcontext.h"
#include "printnl.h"
#include "printint.h"
#include "printchar.h"
#include "print.h"
#include "println.h"
#include "printcs.h"
#include "showtokenlist.h"
#include "texte.h"

static void begin_pseudoprint(int l)
{
	l = tally;
	tally = 0;
	selector = pseudo;
	trickcount = 1000000;
}

static void set_trick_count(void)
{
	firstcount = tally; 
	trickcount = tally+1+errorline-halferrorline;
	if (trickcount < errorline)
		trickcount = errorline;
}

void showcontext(void)
{
	int l;
	baseptr = inputptr;
	inputstack[baseptr] = curinput; 
	int nn = -1;
	bool bottomline = false;
	while (true) 
	{
		curinput = inputstack[baseptr];
		if (state)
			if (txt(name) > 17 || baseptr == 0)
				bottomline = true;
		if (baseptr == inputptr || bottomline || nn < error_context_lines())
		{
			if (baseptr == inputptr || state != token_list || token_type != backed_up || loc)
			{
				tally = 0;
				oldsetting = selector;
				if (state)
				{
					if (txt(name) <= 17)
						if (terminal_input(name))
							printnl(baseptr == 0 ? "<*>" : "<insert> ");
						else
						{
							printnl("<read ");
							if (txt(name) == 17)
								printchar('*');
							else
								printint(txt(name)-1);
							printchar('>');
						}
					else
					{
						printnl("l.");
						printint(line);
					}
					printchar(' ');
					begin_pseudoprint(l);
					int j;
					if (buffer[limit] == end_line_char())
						j = limit;
					else
						j = limit+1;
					if (j > 0)
						for (int i = start; i < j; i++)
						{
							if (i == loc)
								set_trick_count();
							printchar(buffer[i]);
						}
				}
				else
				{
					switch (token_type)
					{
						case parameter: 
							printnl("<argument> ");
							break;
						case u_template:
						case v_template:
							printnl("<template> ");
							break;
						case backed_up: 
							if (loc == 0)
								printnl("<recently read> ");
							else
								printnl("<to be read again> ");
							break;
						case inserted: 
							printnl("<inserted text> ");
							break;
						case macro:
							println();
							printcs(txt(name));
							break;
						case output_text: 
							printnl("<output> ");
							break;
						case every_par_text: 
							printnl("<everypar> ");
							break;
						case every_math_text: 
							printnl("<everymath> ");
							break;
						case every_display_text: 
							printnl("<everydisplay> ");
							break;
						case every_hbox_text: 
							printnl("<everyhbox> ");
							break;
						case every_vbox_text: 
							printnl("<everyvbox> ");
							break;
						case every_job_text: 
							printnl("<everyjob> ");
							break;
						case every_cr_text: 
							printnl("<everycr> ");
							break;
						case mark_text: 
							printnl("<mark> ");
							break;
						case write_text: 
							printnl("<write> ");
							break;
						default: 
							printnl("?");
					}
					begin_pseudoprint(l);
					if (token_type < macro)
						showtokenlist(start, loc, 100000);
					else
						showtokenlist(link(start), loc, 100000);
				}
				selector = oldsetting;
				if (trickcount == 1000000)
					set_trick_count();
				int m;
				if (tally < trickcount)
					m = tally - firstcount;
				else
					m = trickcount-firstcount;
				int p, n;
				if (l+firstcount <= halferrorline)
				{
					p = 0;
					n = l+firstcount;
				}
				else
				{
					print("...");
					p = l+firstcount-halferrorline+3;
					n = halferrorline;
				}
				for (int q = p; q < firstcount; q++)
					printchar(trickbuf[q%errorline]);
				println();
				for (int q = 0; q < n; q++)
					printchar(' ');
				if (m + n <= errorline)
					p = firstcount+m;
				else
					p = firstcount+errorline-n-3;
				for (int q = firstcount; q < p; q++)
					printchar(trickbuf[q%errorline]);
				if (m+n > errorline)
					print("...");
				nn++;
			}
		}
		else 
			if (nn == error_context_lines())
			{
				printnl("...");
				nn++;
			}
		if (bottomline)
			break;
		baseptr--;
	}
	curinput = inputstack[inputptr];
}

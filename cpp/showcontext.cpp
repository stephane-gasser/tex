#include "showcontext.h"
#include "printnl.h"
#include "printint.h"
#include "printchar.h"
#include "print.h"
#include "println.h"
#include "printcs.h"
#include "showtokenlist.h"

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
		if (curinput.statefield)
			if (curinput.namefield > 17 || baseptr == 0)
				bottomline = true;
		if (baseptr == inputptr || bottomline || nn < int_par(error_context_lines_code))
		{
			if (baseptr == inputptr || curinput.statefield || curinput.indexfield != 3 || curinput.locfield)
			{
				tally = 0;
				oldsetting = selector;
				if (curinput.statefield)
				{
					if (curinput.namefield <= 17)
						if (curinput.namefield == 0)
							if (baseptr == 0)
								printnl("<*>");
							else
								printnl("<insert> ");
						else
						{
							printnl("<read ");
							if (curinput.namefield == 17)
								printchar('*');
							else
								printint(curinput.namefield - 1);
							printchar('>');
						}
					else
					{
						printnl("l.");
						printint(line);
					}
					printchar(' ');
					l = tally;
					tally = 0;
					selector = pseudo;
					trickcount = 1000000;
					int j;
					if (buffer[curinput.limitfield] == int_par(end_line_char_code))
						j = curinput.limitfield;
					else
						j = curinput.limitfield+1;
					if (j > 0)
						for (int i = curinput.startfield; i < j; i++)
						{
							if (i == curinput.locfield)
							{
								firstcount = tally;
								trickcount = tally + 1 + errorline - halferrorline;
								if (trickcount < errorline)
									trickcount = errorline;
							}
							printchar(buffer[i]);
						}
				}
				else
				{
					switch (curinput.indexfield)
					{
						case parameter: 
							printnl("<argument> ");
							break;
						case u_template:
						case v_template:
							printnl("<template> ");
							break;
						case backed_up: 
							if (curinput.locfield == 0)
								printnl("<recently read> ");
							else
								printnl("<to be read again> ");
							break;
						case inserted: 
							printnl("<inserted text> ");
							break;
						case macro:
							println();
							printcs(curinput.namefield);
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
					l = tally;
					tally = 0;
					selector = pseudo;
					trickcount = 1000000;
					if (curinput.indexfield < 5)
						showtokenlist(curinput.startfield, curinput.locfield, 100000);
					else
						showtokenlist(link(curinput.startfield), curinput.locfield, 100000);
				}
				selector = oldsetting;
				if (trickcount == 1000000)
				{
					firstcount = tally;
					trickcount = tally+1+errorline-halferrorline;
					if (trickcount < errorline)
						trickcount = errorline;
				}
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
			if (nn == int_par(error_context_lines_code))
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

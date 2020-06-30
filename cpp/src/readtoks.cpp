#include "readtoks.h"
#include "beginfilereading.h"
#include "getavail.h"
#include "terminput.h"
#include "impression.h"
#include "fatalerror.h"
#include "inputln.h"
#include "fichier.h"
#include "runaway.h"
#include "gettoken.h"
#include "error.h"
#include "endfilereading.h"
#include "texte.h"

void readtoks(int n, halfword r)
{
	scannerstatus = defining;
	warningindex = r;
	defref = getavail();
	token_ref_count(defref) = 0;
	auto p = defref;
	store_new_token(p, end_match_token);
	smallnumber m = (n < 0 || n > 15) ? 16 : n;
	auto s = alignstate;
	alignstate = 1000000;
	do
	{
		beginfilereading();
		name = m+1;
		if (readopen[m] == closed)
			if (interaction > nonstop_mode)
				if (n < 0)
				{
					print("");
					terminput();
				}
				else
				{
					println();
					print(scs(r)+"=");
					terminput();
					n = -1;
				}
		else
			fatalerror("*** (cannot \read from terminal in nonstop modes)");

		else 
			if (readopen[m] == just_open)
				if (inputln(readfile[m], false))
					readopen[m] = normal;
				else
				{
					aclose(readfile[m]);
					readopen[m] = closed;
				}

			else
				if (!inputln(readfile[m], true))
				{
					aclose(readfile[m]);
					readopen[m] = closed;
					if (alignstate != 1000000)
					{
						runaway();
						print_err("File ended within "+esc("read"));
						helpptr = 1;
						helpline[0] = "This \\read has unbalanced braces.";
						alignstate = 1000000;
						error();
					}
				}
		limit = last;
		if (end_line_char_inactive())
			limit--;
		else
			buffer[limit] = end_line_char();
		First = limit+1;
		loc = start;
		state = new_line;
		while (true)
		{
			gettoken();
			if (curtok == 0)
				break;
			if (alignstate < 1000000)
			{
				do
					gettoken();
				while (curtok);
				alignstate = 1000000;
				break;
			}
			auto q = getavail();
			link(p) = q;
			info(q) = curtok;
			p = q;
		}
		endfilereading();
	} while (alignstate != 1000000);
	curval = defref;
	scannerstatus = 0;
	alignstate = s;
}

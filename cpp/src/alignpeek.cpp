#include "alignpeek.h"
#include "lecture.h"
#include "noeud.h"
#include "normalparagraph.h"
#include "finalign.h"
#include "initrow.h"
#include "initcol.h"

void alignpeek(void)
{
	while (true)
	{
		alignstate = 1000000;
		halfword chr, tok;
		eightbits cmd;
		do
			std::tie(cmd, chr, tok, std::ignore) = getxtoken();
		while (cmd == spacer);
		if (cmd == no_align)
		{
			std::tie(cmd, chr, tok) = scanleftbrace();
			newsavelevel(7);
			if (mode == -vmode)
				normalparagraph();
		}
		else 
			if (cmd == right_brace)
				finalign(tok);
			else 
				if (cmd == car_ret && chr == 258)
					continue;
				else
				{
					initrow();
					initcol(cmd, tok);
				}
		break;
	}
}


#include "alignpeek.h"
#include "lecture.h"
#include "noeud.h"
#include "normalparagraph.h"
#include "finalign.h"
#include "initrow.h"
#include "initcol.h"

void alignpeek(halfword &loop, halfword &span, halfword &align)
{
	while (true)
	{
		alignstate = 1000000;
		halfword chr, tok;
		eightbits cmd;
		do
			std::tie(cmd, chr, tok, std::ignore) = getxtoken(align);
		while (cmd == spacer);
		if (cmd == no_align)
		{
			std::tie(cmd, chr, tok) = scanleftbrace(align);
			newsavelevel(7);
			if (mode == -vmode)
				normalparagraph();
		}
		else 
			if (cmd == right_brace)
				finalign(tok, loop, span, align);
			else 
				if (cmd == car_ret && chr == 258)
					continue;
				else
				{
					initrow(span, align);
					initcol(cmd, tok, align);
				}
		break;
	}
}


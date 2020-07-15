#include "headforvmode.h"
#include "offsave.h"
#include "impression.h"
#include "erreur.h"
#include "backinput.h"
#include "texte.h"

void headforvmode(eightbits cmd, halfword chr, halfword tok)
{
	if (mode < 0)
		if (cmd != hrule)
			offsave(cmd, chr, tok);
		else
			error("You can't use `"+esc("hrule")+"' here except with leaders", "To put a horizontal rule in an hbox or an alignment,\nyou should use \\leaders or \\hrulefill (see The TeXbook).");
	else
	{
		backinput(tok);
		backinput(partoken);
		token_type = inserted;
	}
}

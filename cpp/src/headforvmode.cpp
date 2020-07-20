#include "headforvmode.h"
#include "offsave.h"
#include "impression.h"
#include "erreur.h"
#include "backinput.h"
#include "texte.h"

void headforvmode(Token t)
{
	if (mode < 0)
		if (t.cmd != hrule)
			offsave(t);
		else
			error("You can't use `"+esc("hrule")+"' here except with leaders", "To put a horizontal rule in an hbox or an alignment,\nyou should use \\leaders or \\hrulefill (see The TeXbook).");
	else
	{
		backinput(t);
		Token tk;
		tk.tok = partoken;
		backinput(tk);
		token_type = inserted;
	}
}

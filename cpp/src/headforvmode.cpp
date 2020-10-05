#include "headforvmode.h"
#include "token.h"
#include "offsave.h"
#include "impression.h"
#include "erreur.h"
#include "backinput.h"
#include "lecture.h"

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
		backinput(Token(partoken));
		token_type = inserted;
	}
}

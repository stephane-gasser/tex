#include "scanspec.h"
#include "scandimen.h"
#include "scankeyword.h"
#include "newsavelevel.h"
#include "scanleftbrace.h"

void scanspec(groupcode c, bool threecodes)
{
	int s;
	if (threecodes)
		s = savestack[saveptr+0].int_;
	int speccode;
	if (scankeyword(841)) //to
	{
		speccode = 0;
		scandimen(false, false, false);
	}
	else 
		if (scankeyword(842)) //spread
		{
			speccode = 1;
			scandimen(false, false, false);
		}
		else
		{
			speccode = 1;
			curval = 0;
		}
	if (threecodes)
		savestack[saveptr++].int_ = s;
	savestack[saveptr].int_ = speccode;
	savestack[saveptr].int_ = curval;
	saveptr += 2;
	newsavelevel(c);
	scanleftbrace();
}

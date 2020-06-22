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
	if (scankeyword("to"))
	{
		speccode = exactly;
		scan_normal_dimen();
	}
	else 
		if (scankeyword("spread"))
		{
			speccode = additional;
			scan_normal_dimen();
		}
		else
		{
			speccode = additional;
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

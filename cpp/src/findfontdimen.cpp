#include "findfontdimen.h"
#include "lecture.h"
#include "deleteglueref.h"
#include "erreur.h"
#include "impression.h"
#include "texte.h"

void findfontdimen(bool writing)
{
	int n = scanint();
	internalfontnumber f = scanfontident();
	if (n <= 0)
		curval = fmemptr;
	else
	{
		if (writing && n <= 4 && n >= 2 && fontglue[f])
		{
			deleteglueref(fontglue[f]);
			fontglue[f] = 0;
		}
		if (n > fontparams[f])
			if (f < fontptr)
				curval = fmemptr;
			else
			{
				do
				{
					if (fmemptr == fontmemsize)
						overflow("font memory", fontmemsize);
					fontinfo[fmemptr++].int_ = 0;
					fontparams[f]++;
				} while (n != fontparams[f]);
				curval = fmemptr-1;
			}
		else
			curval = n+parambase[f];
	}
	if (curval == fmemptr)
		error("Font "+esc(TXT(hash[font_id_base+f].rh))+" has only "+std::to_string(fontparams[f])+" fontdimen parameters", "To increase the number of font parameters, you must\nuse \\fontdimen immediately after the \\font is loaded.");
}

#include "findfontdimen.h"
#include "lecture.h"
#include "deleteglueref.h"
#include "erreur.h"
#include "impression.h"
#include "texte.h"

[[nodiscard]] int findfontdimen(bool writing, halfword align)
{
	int n = scanint(align);
	internalfontnumber f = scanfontident(align);
	int val = fmemptr;
	if (n > 0)
	{
		if (writing && n <= space_shrink_code && n >= space_code && fontglue[f])
		{
			deleteglueref(fontglue[f]);
			fontglue[f] = 0;
		}
		if (n > fontparams[f])
		{
			if (f >= fontptr)
			{
				do
				{
					if (fmemptr == fontmemsize)
						overflow("font memory", fontmemsize, align);
					fontinfo[fmemptr++].int_ = 0;
					fontparams[f]++;
				} while (n != fontparams[f]);
				val = fmemptr-1;
			}
		}
		else
			val = n+parambase[f];
	}
	if (val == fmemptr)
		error("Font "+esc(TXT(hash[font_id_base+f].rh))+" has only "+std::to_string(fontparams[f])+" fontdimen parameters", "To increase the number of font parameters, you must\nuse \\fontdimen immediately after the \\font is loaded.", align);
	return val;
}

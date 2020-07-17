#include "alteraux.h"
#include "lecture.h"
#include "impression.h"
#include "erreur.h"
#include "texte.h"

void alteraux(eightbits cmd, halfword chr, halfword align)
{
	if (chr != abs(mode))
		reportillegalcase(cmd, chr, align);
	else
	{
		auto c = chr;
		scanoptionalequals(align);
		if (c == vmode)
			prev_depth = scan_normal_dimen(align);
		else
		{
			int val = scanint(align);
			if (val <= 0 || val > 32767)
				interror(val, "Bad space factor", "I allow only values in the range 1..32767 here.", align);
			else
				space_factor = val;
		}
	}
}

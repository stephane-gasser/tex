#include "alteraux.h"
#include "lecture.h"
#include "impression.h"
#include "erreur.h"
#include "texte.h"

void alteraux(void)
{
	if (curchr != abs(mode))
		reportillegalcase();
	else
	{
		halfword c = curchr;
		scanoptionalequals();
		if (c == vmode)
			prev_depth = scan_normal_dimen();
		else
		{
			int val = scanint();
			if (val <= 0 || val > 32767)
				interror(val, "Bad space factor", "I allow only values in the range 1..32767 here.");
			else
				space_factor = val;
		}
	}
}

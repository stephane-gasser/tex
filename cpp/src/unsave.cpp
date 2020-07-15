#include "unsave.h"
#include "backinput.h"
#include "eqdestroy.h"
#include "erreur.h"

void unsave(halfword tok)
{
	if (curlevel > level_one)
	{
		curlevel--;
		while (true)
		{
			saveptr--;
			if (save_type(saveptr) == level_boundary)
				break;
			halfword p = save_index(saveptr);
			quarterword l;
			if (save_type(saveptr) == insert_token)
				backinput(p);
			else
			{
				if (save_type(saveptr) == restore_old_value)
				{
					l = save_level(saveptr);
					saveptr--;
				}
				else
					saved(0) = eqtb[undefined_control_sequence].int_;
				if (p < int_base)
					if (eq_level(p) == level_one)
					{
						memoryword m;
						m.int_ = saved(0);
						eqdestroy(m);
					}
					else
					{
						eqdestroy(eqtb[p]);
						eqtb[p].int_ = saved(0);
					}
				else 
					if (xeqlevel[p] != level_one)
					{
						eqtb[p].int_ = saved(0);
						xeqlevel[p] = l;
					}
			}
		}	
		curgroup = save_level(saveptr);
		curboundary = save_index(saveptr);
	}
	else
		confusion("curlevel");
}

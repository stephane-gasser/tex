#include "unsave.h"
#include "backinput.h"
#include "eqdestroy.h"
#include "confusion.h"

void unsave(void)
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
			{
				halfword t = curtok;
				curtok = p;
				backinput();
				curtok = t;
			}
			else
			{
				if (save_type(saveptr) == restore_old_value)
				{
					l = save_level(saveptr);
					saveptr--;
				}
				else
					savestack[saveptr] = eqtb[undefined_control_sequence];
				if (p < int_base)
					if (eq_level(p) == level_one)
						eqdestroy(savestack[saveptr]);
					else
					{
						eqdestroy(eqtb[p]);
						eqtb[p] = savestack[saveptr];
					}
				else 
					if (xeqlevel[p] != level_one)
					{
						eqtb[p] = savestack[saveptr];
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

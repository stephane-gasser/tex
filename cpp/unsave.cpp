#include "unsave.h"
#include "backinput.h"
#include "eqdestroy.h"
#include "confusion.h"

void unsave(void)
{
	if (curlevel > 1)
	{
		curlevel--;
		while (true)
		{
			saveptr--;
			if (save_type(saveptr) == 3)
				break;
			halfword p = save_index(saveptr);
			quarterword l;
			if (save_type(saveptr) == 2)
			{
				halfword t = curtok;
				curtok = p;
				backinput();
				curtok = t;
			}
			else
			{
				if (save_type(saveptr) == 0)
				{
					l = save_level(saveptr);
					saveptr--;
				}
				else
					savestack[saveptr] = eqtb[2881];
				if (p < 5263)
					if (eq_level(p) == 1)
						eqdestroy(savestack[saveptr]);
					else
					{
						eqdestroy(eqtb[p]);
						eqtb[p] = savestack[saveptr];
					}
				else 
					if (xeqlevel[p] != 1)
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
		confusion(543); //curlevel
}

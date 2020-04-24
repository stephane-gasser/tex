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
			if (savestack[saveptr].hh.b0 == 3)
				break;
			halfword p = savestack[saveptr].hh.rh;
			quarterword l;
			if (savestack[saveptr].hh.b0 == 2)
			{
				halfword t = curtok;
				curtok = p;
				backinput();
				curtok = t;
			}
			else
			{
				if (savestack[saveptr].hh.b0 == 0)
				{
					l = savestack[saveptr].hh.b1;
					saveptr--;
				}
				else
					savestack[saveptr] = eqtb[2881];
				if (p < 5263)
					if (eqtb[p].hh.b1 == 1)
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
		curgroup = savestack[saveptr].hh.b1;
		curboundary = savestack[saveptr].hh.rh;
	}
	else
		confusion(543); //curlevel
}

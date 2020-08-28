#include "sauvegarde.h"
#include "erreur.h"

/*quarterword& save_type(halfword p) { return savestack[p].hh.b0; }
quarterword& save_level(halfword p) { return savestack[p].hh.b1; }
halfword& save_index(halfword p) { return savestack[p].hh.rh; }
int& saved(halfword p) { return savestack[saveptr+p].int_; }*/

void eqsave(halfword p, quarterword l)
{
	memoryword m;
	if (l == level_zero)
		/*type*/m.hh.b0 = restore_zero;
	else
	{
		savestack.push_back(eqtb[p]);
		/*type*/m.hh.b0 = restore_old_value;
	}
	/*level*/m.hh.b1 = l;
	/*index*/m.hh.rh = p;
	savestack.push_back(m);
}

void saveforafter(halfword t)
{
	if (curlevel > level_one)
	{
		memoryword m;
		/*type*/m.hh.b0 = insert_token;
		/*level*/m.hh.b1 = level_zero;
		/*index*/m.hh.rh = t;
		savestack.push_back(m);
	}
}

void newsavelevel(groupcode c)
{
	memoryword m;
	/*type*/m.hh.b0 = level_boundary;
	/*level*/m.hh.b1 = curgroup;
	/*index*/m.hh.rh = curboundary;
	if (curlevel == 255)
		overflow("grouping levels", 255);
	curboundary = savestack.size();
	curlevel++;
	savestack.push_back(m);
	curgroup = c;
}

#include "backinput.h"
#include "eqdestroy.h"
#include "erreur.h"

void unsave(void)
{
	if (curlevel <= level_one)
	{
		confusion("curlevel");
		return;
	}
	curlevel--;
	quarterword slevel;
	halfword sindex;
	while (true)
	{
		auto m = savestack.back();
		auto stype = m.hh.b0;
		slevel = m.hh.b1;
		sindex = m.hh.rh;
		savestack.pop_back();
		if (stype == level_boundary)
			break;
		halfword p = sindex;
		quarterword l;
		if (stype == insert_token)
		{
			Token t;
			t.tok = p;
			backinput(t);
		}
		else
		{
			if (stype == restore_old_value)
			{
				l = slevel;
				m = savestack.back();
				stype = m.hh.b0;
				slevel = m.hh.b1;
				sindex = m.hh.rh;
				savestack.pop_back();
			}
			else
			{
				m = eqtb[undefined_control_sequence];
				stype = m.hh.b0;
				slevel = m.hh.b1;
				sindex = m.hh.rh;
			}
			if (p < int_base)
				if (eq_level(p) == level_one)
					eqdestroy(m);
				else
				{
					eqdestroy(eqtb[p]);
					eqtb[p] = m;
				}
			else 
				if (xeqlevel[p] != level_one)
				{
					eqtb[p] = m;
					xeqlevel[p] = l;
				}
		}
	}	
	curgroup = slevel;
	curboundary = sindex;
}

#include "sauvegarde.h"
#include "erreur.h"
#include "backinput.h"
#include "equivalent.h"

enum save_type
{
	restore_old_value = 0, //!< \a save_type when a value should be restored later
	restore_zero = 1, //!< \a save_type when an undefined entry should be restored
	insert_token = 2, //!< \a save_type when a token is being saved for later use
	level_boundary = 3 //!< \a save_type corresponding to beginning of group
};

static memoryword memory(quarterword type, quarterword level, halfword index)
{
	memoryword m;
	m.hh.b0 = type;
	m.hh.b1 = level;
	m.hh.rh = index;
	return m;
}

void eqsave(halfword p, quarterword l)
{
	if (l == level_zero)
		savestack.push_back(memory(restore_zero, l, p));
	else
	{
		savestack.push_back(eqtb[p]);
		savestack.push_back(memory(restore_old_value, l, p));
	}
}

void saveforafter(halfword t)
{
	if (curlevel > level_one)
		savestack.push_back(memory(insert_token, level_zero, t));
}

void newsavelevel(groupcode c)
{
	if (curlevel == 255)
		overflow("grouping levels", 255);
	savestack.push_back(memory(level_boundary, curgroup, curboundary));
	curboundary = savestack.size();
	curlevel++;
	curgroup = c;
}

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

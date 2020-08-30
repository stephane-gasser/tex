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

void eqsave(AnyNode *p, quarterword l)
{
	if (l == level_zero)
		savestack.push_back(new MemoryNode(restore_zero, l, p));
	else
	{
		savestack.push_back(dynamic_cast<MemoryNode*>(p));
		savestack.push_back(new MemoryNode(restore_old_value, l, p));
	}
}

void saveforafter(AnyNode *t)
{
	if (curlevel > level_one)
		savestack.push_back(new MemoryNode(insert_token, level_zero, t));
}

static AnyNode *curboundary = nullptr; // 0..savesize

void newsavelevel(groupcode c)
{
	if (curlevel == 255)
		overflow("grouping levels", 255);
	savestack.push_back(new MemoryNode(level_boundary, curgroup, curboundary));
	curboundary = savestack.back();
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
	AnyNode *sindex;
	while (true)
	{
		auto m = savestack.back();
		auto stype = m->type;
		slevel = m->level;
		sindex = m->index;
		savestack.pop_back();
		if (stype == level_boundary)
			break;
		auto p = sindex;
		quarterword l;
		if (stype == insert_token)
		{
			Token t;
			t.tok = p->num;
			backinput(t);
		}
		else
		{
			if (stype == restore_old_value)
			{
				l = slevel;
				m = savestack.back();
				stype = m->type;
				slevel = m->level;
				sindex = m->index;
				savestack.pop_back();
			}
			else
			{
				m = &eqtb_cs[undefined_control_sequence-hash_base];
				stype = m->type;
				slevel = m->level;
				sindex = m->index;
			}
			if (p->num < int_base) // dans eqtb
				if (dynamic_cast<MemoryNode*>(p)->level == level_one)
					eqdestroy(m);
				else
				{
					eqdestroy(dynamic_cast<MemoryNode*>(p));
					*p = *m;
				}
			else 
				if (dynamic_cast<MemoryNode*>(p)->level/*xeqlevel[p]*/ != level_one) //dans xeqlevel
				{
					*p = *m; //eqtb [p] = m;
					dynamic_cast<MemoryNode*>(p)->level = l;//xeqlevel[p] = l;
				}
		}
	}	
	curgroup = slevel;
	curboundary = sindex;
}
